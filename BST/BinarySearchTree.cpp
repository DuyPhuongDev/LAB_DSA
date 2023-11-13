#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class BinarySearchTree
{
public:
    class Node;
private:
    Node* root;
    // Node* getMin(Node* root){
    //     if(!root) return 0;
    //     if(!root->pLeft) return root;
    //     return getMin(root->pLeft);
    // }
    bool find(Node* root, T i){
        if(!root) return false;
        if(i>root->value) return find(root->pRight,i);
        else if(i<root->value) return find(root->pLeft,i);
        return true;
    }
    
    void sum(Node* root, T l, T r, T &s){
        if(!root) return;
        if(root->value>=l && root->value<=r) s+=root->value;
        sum(root->pLeft,l,r,s);
        sum(root->pRight,l,r,s);
    }

    // Node* getMax(Node* root){
    //     if(!root) return 0;
    //     if(!root->pRight) return root;
    //     return getMax(root->pRight);
    // }
    Node* add(Node* root, int val){
        if(!root){
            root = new Node(val);
            return root;
        }
        if(val>root->value){
            root->pRight = add(root->pRight,val);
        }else root->pLeft = add(root->pLeft, val);

        return root;
    }

    Node* deleteNode(Node* root, int val){
        if(root){
            if(val>root->value){
                root->pRight = deleteNode(root->pRight,val);
                return root;
            }
            else if(val<root->value){
                root->pLeft = deleteNode(root->pLeft, val);
                return root;
            }
            else {
                // có cả 2 con
                if(root->pLeft&&root->pRight){
                    Node* sucpar = root;
                    Node* suc = root->pRight;
                    while(suc->pLeft){
                        sucpar = suc;
                        suc = suc->pLeft;
                    }

                    if(sucpar!=root){
                        sucpar->pLeft = suc->pRight;
                    }else sucpar->pRight = suc->pRight;
                    
                    root->value = suc->value;
                    delete suc;
                    return root;
                }
                // co 1 or 0 con
                if(!root->pLeft){
                    Node* tmp = root->pRight;
                    delete root;
                    return tmp;
                }
                if(!root->pRight){
                    Node* tmp = root->pLeft;
                    delete root;
                    return tmp;
                }
            }
        }
        
        return nullptr;
   }

    Node* getMin(Node* root){
        if(!root) return 0;
        if(!root->pLeft) return root;
        return getMin(root->pLeft);
    }

    Node* getMax(Node* root){
        if(!root) return 0;
        if(!root->pRight) return root;
        return getMax(root->pRight);
    }
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    //Helping function
    bool isLeaf(Node* n){return !n->pLeft&&!n->pRight;}
    void add(T value){
        //TODO
        root = add(root,value);
    }
   
    void deleteNode(T value){
        //TODO
        root = deleteNode(root,value);
    }
    
    // T getMin() {
    //     //TODO: return the minimum values of nodes in the tree.
    //     return getMin(root)->value;
    // }

    // T getMax() {
    //     //TODO: return the maximum values of nodes in the tree.
    //     return getMax(root)->value;
    // }
    bool find(T i) {
        // TODO: return true if value i is in the tree; otherwise, return false.
        return find(root,i);
    }

    T sum(T l, T r) {
        // TODO: return the sum of all element in the tree has value in range [l,r].
        T s=0;
        sum(root,l,r,s);
        return s;
    }
    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }
    
    string inOrder(){
        return inOrderRec(this->root);
    }
    
    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;
    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};

int main(){
	
    int values[] = { 75,13,83,83,30,40,10,86,17,21,45,22,22,72,63 };
    BinarySearchTree<int> bst;
    for (int i = 0; i < 15; ++i) {
        bst.add(values[i]);
    }

    cout << bst.find(34) << endl;
    cout << bst.sum(10, 40);
return 0;
}