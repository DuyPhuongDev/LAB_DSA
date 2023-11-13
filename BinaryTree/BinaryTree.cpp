#include <iostream>
#include <string>
#include <sstream>
#include<queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class K, class V>
class BinaryTree
{
public:
    class Node;
private:
    Node* root;
    int diameter(Node* root);
    int height(Node* root);
    int countTwoChildrenNode(Node* root, int &count);
    string preOrder(Node* root);
    string postOrder(Node* root);
    string inOrder(Node* root);
    int sumOfLeafs(Node* root);
public:
    
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    class Node
    {
    private:
        K key;
        V value;
        Node* pLeft, * pRight;
        friend class BinaryTree<K, V>;
    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node* walker = this->root;
        int l = (int)posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }

    //Helping functions
    int getDiameter(){return diameter(root);}
    void BFS();
    int getHeight(){ return height(root);}
    int countTwoChildrenNode(){
        int count =0;
        countTwoChildrenNode(root,count);
        return count;
    }
    string preOrder(){return preOrder(root);}
    string postOrder(){return postOrder(root);};
    string inOrder(){return inOrder(root);};
    int sumOfLeafs(){return sumOfLeafs(root);}
};

template<class K, class V>
void BinaryTree<K, V>::BFS(){
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* cur = q.front(); q.pop();
        cout<<cur->value<<" ";
        if(cur->pLeft) q.push(cur->pLeft);
        if(cur->pRight) q.push(cur->pRight);
        
    }
}

template<class K, class V>
int BinaryTree<K, V>::diameter(Node* root){
    if(!root) return 0;
    
    // get hight of subtree left and right
    int hightLeft = height(root->pLeft);
    int highRight = height(root->pRight);

    // get diameter of subtree left and right
    // diameter = max HL + HR + 1
    int diameterLeft = diameter(root->pLeft);
    int diameterRight = diameter(root->pRight);

    return max(1+highRight+hightLeft, max(diameterLeft,diameterRight));

    
}

template<class K, class V>
int BinaryTree<K, V>::height(Node* root){
    if(!root) return 0;

    return 1 + max(height(root->pLeft), height(root->pRight));
}

template<class K, class V>
int BinaryTree<K,V>::countTwoChildrenNode(Node* root, int &count){
    // using DFS
    if(!root) return 0;

    if(!root->pLeft && !root->pRight) return root->value;

    int left = countTwoChildrenNode(root->pLeft,count);
    int right = countTwoChildrenNode(root->pRight,count);

    if(left && right){ count++; return root->value;}


    return left?left:right;
}

template<class K, class V>
string BinaryTree<K,V>::preOrder(Node* root){
    if(!root) return "\0";

    return to_string(root->value) + " " + preOrder(root->pLeft) + preOrder(root->pRight);
}

template<class K, class V>
string BinaryTree<K, V>::inOrder(Node* root){
    if(!root) return "\0";

    return inOrder(root->pLeft) + to_string(root->value)+" "+inOrder(root->pRight);
}

template<class K, class V>
string BinaryTree<K, V>::postOrder(Node* root){
    if(!root) return "\0";

    return postOrder(root->pLeft) + postOrder(root->pRight) + to_string(root->value) + " ";
}

template<class K, class V>
int BinaryTree<K, V>::sumOfLeafs(Node* root){
    if(!root) return 0;
    if(!root->pLeft && !root->pRight) return root->value;
    int left = sumOfLeafs(root->pLeft);
    int right = sumOfLeafs(root->pRight);

    return left+right;
}

int main(){
	
BinaryTree<int, int> binaryTree;
binaryTree.addNode("", 2, 4);
binaryTree.addNode("L", 3, 6);
binaryTree.addNode("R", 5, 9);
cout << binaryTree.sumOfLeafs();
     return 0;
}