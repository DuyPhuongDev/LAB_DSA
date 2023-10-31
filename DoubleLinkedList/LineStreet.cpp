#include<iostream>
#include<string>
using namespace std;


class LineStreet {
public:
    
    LineStreet(string homepage) {
        root = new node(homepage);
        tail = root;
        size=0;
    }
    
    void addNewElement(string url) {
        node* ele = new node(url);
        // delete all node behide current
        if(curr) while(tail!=curr) removeE();
        // add member into back
        ele->prev = tail;
        tail->next = ele;
        tail = tail->next;
        size++;
    }

    string back(int steps) {
        if(!curr) curr = tail;
        while(steps){
            if(curr->prev == root) break;
            curr = curr->prev;
            steps--;
        }
        return curr->name;
    }

    string forward(int steps) {
        if(!curr) curr=root->next;
        while(steps){
            if(curr->next==nullptr) break;
            curr=curr->next;
            steps--;
        }
        return curr->name;
    }

protected:
    struct node{
        string name;
        node* prev, *next;
        node(string name, node* prev=nullptr, node* next=nullptr): name(name), prev(prev), next(next){}
    };
    node* root;
    node* tail;
    node* curr = nullptr; // point to mem has last change
    int size;
    void removeE(){
        node* n = tail;
        tail = tail->prev;
        tail->next = nullptr;
        n->prev = nullptr;
        delete n;
        size--;
    }
};

int main(){
LineStreet* obj = new LineStreet("home");
obj->addNewElement("Bob");
obj->addNewElement("Smith");
obj->addNewElement("Ann");
cout << obj->back(1) << endl;
cout << obj->back(1) << endl;
cout << obj->forward(1) << endl;
obj->addNewElement("Peter");
cout << obj->forward(2) << endl;
cout << obj->back(1) << endl;
return 0;
}

