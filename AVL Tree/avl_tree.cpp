#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    // balance tree
    void rotateLeft(Node*&root){
        Node* right_tree=root->pRight;
        root->pRight=right_tree->pLeft;
        right_tree->pLeft=root;
        root=right_tree;
    }
    void rotateRight(Node*&root){
        Node* left_tree=root->pLeft;
        root->pLeft=left_tree->pRight;
        left_tree->pRight=root;
        root=left_tree;
    }
    void right_balance(Node* & root){
        Node* right_tree=root->pRight;
        if(right_tree->balance==RH){
            root->balance=EH;
            right_tree->balance=EH;
            rotateLeft(root);
        }
        if(right_tree->balance==LH){
            Node* sub_tree=right_tree->pLeft;
            if(sub_tree->balance==EH){
                root->balance=EH;
                right_tree->balance=EH;
            }
            else if(sub_tree->balance==LH){
                right_tree->balance=RH;
                root->balance=EH;
            }
            else if(sub_tree->balance==RH){
                right_tree->balance=EH;
                root->balance=LH;
            }
            sub_tree->balance=EH;
            rotateRight(root->pRight);
            rotateLeft(root);
        }
        
    }
    void left_balance(Node* & root){
        Node* left_tree=root->pLeft;
        if(left_tree->balance==LH){
            root->balance=EH;
            left_tree->balance=EH;
            rotateRight(root);
        }
        else if(left_tree->balance==RH){
            Node* sub_tree=left_tree->pRight;
            if(sub_tree->balance==EH){
                left_tree->balance=EH;
                root->balance=EH;
            }
            else if(sub_tree->balance==LH){
                left_tree->balance=EH;
                root->balance=RH;
            }
            else{
                root->balance=EH;
                left_tree->balance=LH;
            }
            sub_tree->balance=EH;
            rotateLeft(root->pLeft);
            rotateRight(root);
        }
        
    }

    Node* AVL_insert(Node* &root, const T& value, bool &taller){
        if(!root){
            root = new Node(value);
            taller = true;
            return root;
        }

        if(value<root->data){
            root->pLeft = AVL_insert(root->pLeft, value, taller);
            if(taller){
                if(root->balance == LH){
                    left_balance(root);
                    taller = false;
                }
                else if(root->balance == EH) root->balance = LH;
                else{
                    root->balance = EH;
                    taller =false;
                }
            }
        }else{
            root->pRight = AVL_insert(root->pRight, value, taller);
            // right subtree is taller
            if(taller){
                if(root->balance==LH) {
                    root->balance = EH;
                    taller = false;
                }else if(root->balance == EH) root->balance = RH;
                else{
                    right_balance(root);
                    taller = false;
                }
            }
        }
        return root;
    }

    void insert(const T& value){
        bool taller = false;
        root = AVL_insert(root, value, taller);
    }

    void deleteRightBalance(Node* &root, bool &shorter){
        if(root->balance == EH){
            root->balance = EH;
        }else if(root->balance == EH){
            root->balance=RH;
            shorter = false;
        }else{
            Node* rTree = root->pRight;
            if(rTree->balance == LH){
                Node* subleft = rTree->pLeft;
                if(subleft->balance==LH){
                    rTree->balance = RH;
                    root->balance = EH;
                }else if(subleft->balance == EH){
                    root->balance = EH;
                    rTree->balance = EH;
                }else{
                    root->balance = LH;
                    rTree->balance = EH;
                }
                subleft->balance = EH;
                rotateRight(root->pRight);
                rotateLeft(root);
            }else{
                if(rTree->balance!=EH){
                    root->balance = EH;
                    rTree->balance = EH;
                }else{
                    root->balance = RH;
                    rTree->balance = LH;
                    shorter = false;
                }
                rotateLeft(root);
            }
        }
    }

    void deleteLeftBalance(Node* &root, bool& shorter){
        if(root->balance == RH){
            root->balance = EH;
        }else if(root->balance == EH){
            root->balance = LH;
            shorter = false;
        }else{
            Node* lTree = root->pLeft;
            if(lTree->balance == RH){
                Node* subright = lTree->pRight;
                if(subright->balance == RH){
                    lTree->balance = LH;
                    root->balance = EH;
                }else if(subright->balance == EH){
                    root->balance = EH;
                    lTree->balance = EH;
                }else{
                    root->balance = RH;
                    lTree->balance = EH;
                }
                subright->balance = EH;
                rotateLeft(root->pLeft);
                rotateRight(root);
            }else{
                if(lTree->balance != EH){
                    root->balance = EH;
                    lTree->balance = EH;
                }else{
                    root->balance = LH;
                    lTree->balance = RH;
                    shorter = false;
                }
                rotateRight(root);
            }
        }
    }
    Node* AVL_delete(Node* root, const T& value, bool &shorter){
        if(root){
            if(value<root->data){
                root->pLeft = AVL_delete(root->pLeft,value,shorter);
                if(shorter){
                    if(root->balance==RH){
                        deleteRightBalance(root,shorter);
                        shorter = false;
                    }else if(root->balance==EH){
                        root->balance=RH;
                        shorter=false;
                    }else{
                        root->balance=EH;
                    }
                }
                return root;
            }else if(value>root->data){
                root->pRight = AVL_delete(root->pRight,value,shorter);\
                if(shorter){
                    if(root->balance == LH){
                        deleteLeftBalance(root,shorter);
                        shorter = false;
                    }else if(root->balance==EH){
                        root->balance = LH;
                        shorter = false;
                    }else{
                        root->balance = EH;
                    }
                }
                return root;
            }else{

                if(!root->pLeft){
                    Node* tmp = root->pRight;
                    delete root;
                    shorter = true;
                    return tmp;
                }else if(!root->pRight){
                    Node* tmp = root->pLeft;
                    shorter = true;
                    delete root;
                    return tmp;
                }else{
                    Node* suc = root->pLeft;
                    while(suc->pRight){
                        suc= suc->pRight;
                    }
                    swap(root->data, suc->data);
                    root->pLeft = AVL_delete(root->pLeft,value,shorter);
                }
            }
        } 
        return root;
    }
    void remove(const T &value){
    //TODO
        bool shorter = false;
        root = AVL_delete(root,value,shorter);
    }
    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

int main(){
	
AVLTree<int> avl;
int arr[] = {20,10,40,5,7,42,2};
for (int i = 0; i < 7; i++){
avl.insert(arr[i]);
}
avl.remove(20);
avl.printTreeStructure();
return 0;
}