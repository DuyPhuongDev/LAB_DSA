#include<iostream>
#include<stack>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

class BSTNode {
public: 
    int val; 
    BSTNode *left; 
    BSTNode *right; 
    BSTNode() {
        this->left = this->right = nullptr;
    } 
    BSTNode(int val) {
        this->val = val;
        this->left = this->right = nullptr;
    } 
    BSTNode(int val, BSTNode*& left, BSTNode*& right) {
        this->val = val;
        this->left = left;
        this->right = right;
    }
    static BSTNode* add(BSTNode* root, int val){
        if(!root){
            root = new BSTNode(val);
            return root;
        }
        if(val>root->val){
            root->right = add(root->right,val);
        }else root->left = add(root->left, val);

        return root;
    }
    static BSTNode* createBSTree(int *start, int *end){
        BSTNode* root= nullptr;
        int size = end -start;
        for(int i=0;i<size;++i){
            root = add(root,*(start+i));
        }
        return root;
    }
    static void deleteTree(BSTNode* root){
        if(!root) return;
        queue<BSTNode*> q;
        q.push(root);
        while(!q.empty()){
            BSTNode* cur = q.front(); q.pop();
            if(cur->left) q.push(cur->left);
            if(cur->right) q.push(cur->right);
            delete cur;
        }
    }
    static void printPreorder(BSTNode* root){
        if(!root) return;
        cout<<root->val<<" ";
        printPreorder(root->left);
        printPreorder(root->right);
        
    }
    static void printInorder(BSTNode* root){
        if(!root) return;
        printInorder(root->left);
        cout<<root->val<<" ";
        printInorder(root->right);
    }
};



int getLevel(BSTNode* root){
    if(!root) return 0;
    return 1+ max(getLevel(root->left), getLevel(root->right));
}

vector<int> levelAlterTraverse(BSTNode* root) {
    // STUDENT ANSWER
    // using BFS
    // Level lẻ => left to right
    // Level chẵn => right to left
    vector<int> result;
    if(root){
        queue<BSTNode*> q;
        q.push(root);
        bool l2r=true;
        stack<int> tmp;
        while(!q.empty()){
            int size = q.size();
            for(int i=0;i<size;++i){
                BSTNode* cur = q.front(); q.pop();
                if(l2r) result.push_back(cur->val);
                else tmp.push(cur->val);

                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            while(!tmp.empty()){
                result.push_back(tmp.top());
                tmp.pop();
            }

            l2r = !l2r;
        }
    }
    return result;
}

void LNR(BSTNode* root, vector<int> &v){
    if(!root) return;
    LNR(root->left,v);
    v.push_back(root->val);
    LNR(root->right,v);
}

int kthSmallest(BSTNode* root, int k) {
    // STUDENT ANSWER
    vector<int> v;
    LNR(root,v);
    return v[k-1];
}

void inOrder(BSTNode* root, BSTNode* &prev, int &ans){
    if(!root) return;

    inOrder(root->left,prev,ans);
    if(prev) ans=min(root->val-prev->val, ans);
    inOrder(root->right,prev,ans);
}

int minimumAbsolute(BSTNode* root){
    BSTNode* prev = nullptr;
    int ans = 999999999;
    inOrder(root,prev,ans);
    return ans;
}


BSTNode* deleteNode(BSTNode* root, int e){
    if(root){
        if(root->val>e) root->left = deleteNode(root->left,e);
        else if(root->val<e) root->right = deleteNode(root->right,e);
        else{
            if(!root->left){
                BSTNode* tmp = root->right;
                delete root;
                return tmp;
            }else if(!root->right){
                BSTNode* tmp = root->left;
                delete root;
                return tmp;
            }else{
                // tim node min
                BSTNode* suc = root->right;
                BSTNode* parsuc = root;
                while(suc->left){
                    parsuc = suc;
                    suc=suc->left;
                }

                // rotate subtree
                if(parsuc==root){
                    parsuc->right = suc->right;
                }else{
                    parsuc->left = suc->right;
                }
                root->val = suc->val;
                delete suc;
                return root;
                
            }
        }
    }
    return nullptr;
}

BSTNode* subtreeWithRange(BSTNode* root, int lo, int hi) {
    // STUDENT ANSWER
    if(!root) return nullptr;
    
   
    if (root->val < lo) {
        BSTNode* newRoot = subtreeWithRange(root->right, lo, hi);
        delete root;
        return newRoot;
    } else if (root->val > hi) {
        BSTNode* newRoot = subtreeWithRange(root->left, lo, hi);
        delete root;
        return newRoot;
    }
    root->left = subtreeWithRange(root->left,lo,hi);
    root->right =  subtreeWithRange(root->right,lo,hi);
    return root;
}
void enlar(BSTNode* &root, int &sum){
    if(!root) return;
    enlar(root->right,sum);
    int tmp = root->val;
    root->val += sum;
    sum+=tmp;
    enlar(root->left,sum);
}
BSTNode* enlarge(BSTNode* root){
    int sum=0;
    enlar(root,sum);
    return root;
}

void single(BSTNode* root, int &num){
    if(!root) return;
    single(root->left, num);
    single(root->right, num);
    if(bool(root->left) != bool(root->right)) num+=1;
}
int singleChild(BSTNode* root){
    int num =0;
    single(root,num);
    return num;
}
int main(){
int arr[] = {4,2,5,1,3};
BSTNode* root= BSTNode::createBSTree(arr, arr + sizeof(arr)/sizeof(int));
root = enlarge(root);
BSTNode::printInorder(root); 
return 0;
}