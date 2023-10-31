#include<iostream>
#include<vector>
using namespace std;

// A double-ended queue or deque (pronounced "deck") is like a queue or a stack but supports adding and removing items at both ends.
// A deque stores a collection of items and supports the following methods:
// + getSize(): int                   => number of items in the deque
// + pushFront(int item): void      => add an item to the left end   
// + pushBack(int item): void     => add an item to the right end
// + popFront(): int                => remove and return an item from the left end
// + popBack(): int               => remove and return an item from the right end
// + clear(): void                 => erase all items in the deque

// // For checking purposes
// + printQueue(): void            => print all items in the deque from left to right, separated by a space, with a new line (i.e '\n') at the end.
// + printQueueReverse(): void     => print all items in the deque from right to left, separated by a space, with a new line at the end.
// Note: if the deque is empty, every pop method return -1;

class Deque {
private:
    class Node {
    private:
        int value;
        Node* left;
        Node* right;
        friend class Deque;
    public:
        Node(int val = 0, Node* l = nullptr, Node* r = nullptr) : value(val), left(l), right(r) { }
    };

private:
    Node* head;
    Node* tail;
    int curSize;

public:
    Deque();
    ~Deque();
    int getSize();
    void pushFront(int item);
    void pushBack(int item);
    int popFront();
    int popBack();
    void clear();
    void printDequeReverse();
    void printDeque();
};

Deque::Deque() {
    head = nullptr;
    tail = nullptr;
    curSize = 0;
}

Deque::~Deque() {
    delete head;
    delete tail;
    curSize = 0;
}

void Deque::clear() {
    while(curSize>0){
        popFront();
    }
}

int Deque::getSize() {
    return curSize;
}

void Deque::pushFront(int i) {
    Node* n = new Node(i);
    if(!head) {head = n; tail = n;}
    else{
        n->right = head;
        head->left = n;
        head = head->left;
    }
    curSize++;
}

void Deque::pushBack(int i) {
    Node* n = new Node(i);
    if(!tail) {head = n; tail = n;}
    else{
        n->left = tail;
        tail->right = n;
        tail = tail ->right;
    }
    curSize++;
}

int Deque::popFront() {
    if(!curSize) return -1;
    int memory = head->value;

    if(curSize==1){
        head = nullptr;
        tail = nullptr;
    }else{
        head = head->right;
        head->left = nullptr;
    }
    
    curSize--;
    return memory;
}

int Deque::popBack() {
    if(!curSize) return -1;
    int memory = tail->value;
    if(curSize==1){
        head = nullptr;
        tail = nullptr;
    }else{
        tail = tail->left;
        tail->right = nullptr;
    }
    curSize--;
    return memory;
}

void Deque::printDequeReverse() {
    if(!tail) return;
    Node* curr = tail;
    while(curr){
        cout<<curr->value<<" ";
        curr = curr->left;
    }
    cout<<'\n';
}

void Deque::printDeque() {
    if(!head) return;
    Node* curr = head;
    while(curr){
        cout<<curr->value<<" ";
        curr = curr->right;
    }
    cout<<'\n';
}

int main(){
    Deque* deque = new Deque();
    vector<int> arr = {223, 1234, 43, 568, 90, 193, 2109};
    for(int i = 0; i < (int)arr.size(); i++) {
        if (i < (int)arr.size() / 2)
            deque->pushFront(arr[i]);
        else {
            deque->pushBack(arr[i]);
        }
    }
    deque->printDeque();
    cout << deque->getSize();
    delete deque;
    return 0;
}