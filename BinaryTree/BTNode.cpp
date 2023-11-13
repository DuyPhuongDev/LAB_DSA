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

int largestDiff(BTNode* root) {
    // using DFS
    if(!root) return -1;
    if(isLeaf(root)) return 0;

    int largestLeft = largestDiff(root->left);
    int largestRight = largestDiff(root->right);

    int maxLeft = maximum_Value(root->left);
    int maxRight = maximum_Value(root->right);
    
    return max(abs(root->val-max(maxLeft,maxRight)), max(largestLeft, largestRight));
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