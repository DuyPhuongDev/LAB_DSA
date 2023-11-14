#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<utility>
using namespace std;

class BTNode {
    public: 
        int val; 
        BTNode *left; 
        BTNode *right; 
        BTNode() {
            this->left = this->right = NULL;
        } 
        BTNode(int val) {
            this->val = val;
            this->left = this->right = NULL;
        } 
        BTNode(int val, BTNode*& left, BTNode*& right) {
            this->val = val;
            this->left = left;
            this->right = right;
        } 
    //static BTNode* createTree(int *start, int* end, int *value);
};   

void LRN(BTNode* root){
    if(!root) {return;}

    LRN(root->left);
    LRN(root->right);
    cout<<root->val<<" ";
}

int sumOfSubTree(BTNode* root){
    // using DFS
    if(!root) return 0;

    int sumLeft = sumOfSubTree(root->left);
    int sumRight = sumOfSubTree(root->right);

    return root->val + sumLeft + sumRight;
}

int distinctParities(BTNode* root){
    if(!root) return 0;

    // using BFS
    int count = 0;
    queue<BTNode*> q; q.push(root);

    while(!q.empty()){
        BTNode* cur = q.front(); q.pop();

        if(cur->left && cur->right && (sumOfSubTree(cur->left)%2 != sumOfSubTree(cur->right)%2)) count++;
        if(cur->left) q.push(cur->left);
        if(cur->right) q.push(cur->right);
    }

    return count;
}

bool isLeaf(BTNode* root){
    if(!root || root->left || root->right) return false;
    return true;
}

int maximum_Value(BTNode* root){
    // using DFS
    if(!root) return 0;
    if(isLeaf(root)) return root->val;
    int maxLeft = maximum_Value(root->left);
    int maxRight = maximum_Value(root->right);
    return max(maxLeft, maxRight);
}

bool isGreatAncestor(BTNode* root){
    if(!root) return false;
    return root->val>=max(maximum_Value(root->left), maximum_Value(root->right));
}

int greatAncestor(BTNode* root) {
    // using DFS
    if(!root) return 0;

    int AncestorLeft = greatAncestor(root->left);
    int AncestorRight = greatAncestor(root->right);

    
    return (isGreatAncestor(root)? 1:0) + AncestorLeft + AncestorRight;
}

int largest(BTNode* root, int& result) {
    if (root == nullptr) {
        return 0;
    }

    int left_min = largest(root->left, result);
    int right_min = largest(root->right, result);

    int current_min = min({left_min, right_min, root->val});
    int current_max = max({left_min, right_min, root->val});

    result = max(result, abs(current_max - current_min));

    return current_min;
}

int largestDiff(BTNode* root) {
    int result = 0;
    largest(root, result);
    return result;
}

int lowestAncestor(BTNode* root, int a, int b) {
    // using DFS
    if(!root) return -1;

    if(root->val==a || root->val==b) return root->val;

    int left = lowestAncestor(root->left,a,b);
    int right = lowestAncestor(root->right,a,b);
    if(left!= -1 && right != -1) return root->val;

   return left!=-1? left:right;

}

int sumSofar(BTNode* root, int sum){
    if(!root) return 0;

    // update sum
    sum = sum*10+root->val;
    if(!root->left && !root->right) return sum;
    return sumSofar(root->left, sum)+sumSofar(root->right,sum);
}

int sumDigitPath(BTNode* root) {
    int sum = 0;
    sum = sumSofar(root, sum);
    return sum%27022001;
}

int sumSt(stack<int> st){
    int ans = 0;
    while(!st.empty()){
        ans += st.top();
        st.pop();
    }
    return ans;
}
stack<int> longestPath(BTNode* root, stack<int> st){
    if(root == nullptr){
        return st;
    }
    st.push(root->val);
    stack<int> st1 = longestPath(root->left,st);
    stack<int> st2 = longestPath(root->right,st);
    if(st1.size() > st2.size()) st = st1;
    else if(st1.size() < st2.size()) st = st2;
    else {
        int sum1 = sumSt(st1);
        int sum2 = sumSt(st2);
        st = (sum1 > sum2)? st1 : st2;
    }
    return st;
}
int longestPathSum(BTNode* root) {
    stack<int> st;
    st = longestPath(root,st);
    int ans = sumSt(st);
    return ans;
}

int stToInt(stack<int> st)
{
    vector<int> q;
    while (!st.empty())
    {
        q.insert(q.begin(), st.top());
        st.pop();
    }
    int ans = 0;
    while (!q.empty())
    {
        int tmp = q[0];
        q.erase(q.begin());
        ans = ((ans * 10) + tmp) % 27022001;
    }
    return ans;
}
int sumDigitPathRec(BTNode *root, stack<int> &st)
{
    if (root == nullptr)
    {
        return 0;
    }
    if (root->left == nullptr && root->right == nullptr)
    {
        st.push(root->val);
        int ans = stToInt(st);
        st.pop();
        return ans;
    }
    st.push(root->val);
    int ans = (sumDigitPathRec(root->left, st) + sumDigitPathRec(root->right, st)) % 27022001;
    st.pop();
    return ans;
}
int sumDigitPath(BTNode *root)
{
    stack<int> st;
    return sumDigitPathRec(root, st);
}

int main(){
    //cout<<sizeof(arr)/sizeof(int);
    //BTNode* root = BTNode::createTree(arr, arr + sizeof(arr)/sizeof(int), value);
    //cout << distinctParities(root);
    // construct tree
    BTNode* root = new BTNode(3);
    root->left = new BTNode(5);
    root->right = new BTNode(2);
    root->right->left = new BTNode(1);
    root->right->right = new BTNode(4);
    LRN(root); cout<<'\n';
    cout<<sumDigitPath(root);
    return 0;
}