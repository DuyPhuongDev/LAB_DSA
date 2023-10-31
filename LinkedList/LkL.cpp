#include<iostream>
#include<sstream>
using namespace std;

class LinkedList {
    public: 
        class Node;
    private:
        Node* head;
        Node* tail;
        int size;
    public: 
        class Node {
            private: 
                int value;
                Node* next;
                friend class LinkedList;
            public:
                Node() {
                    this->value =0;
                    this->next = NULL;
                }
                Node(Node* node) {
                    this->value = node->value;
                    this->next = node->next;
                }
                Node(int value, Node* next = NULL) {
                    this->value = value;
                    this->next = next;
                }
        };
    LinkedList(): head(NULL), tail(NULL), size(0) {};
	void partition(int k);
    void add(int n);
    void replace(LinkedList* linked_list, int low, int high);;
    string toString();
};

void LinkedList::add(int n){
    if(head==NULL){
        head = new Node(n);
        tail = head;
        size++;
    }
    else{
        while(tail->next){
            tail = tail->next;
        }
        tail->next = new Node(n);
        tail = tail->next;
        size++;
    }
}

string LinkedList::toString(){
    Node* cur = head;
    string s("[ ");
    while(cur){
        s += to_string(cur->value) + " ";
        cur = cur->next;
    }
    s+=']';
    return s;
}

void LinkedList::replace(LinkedList* linked_list, int low, int high) {
    if(head!=nullptr){
        low = low<0?0:low;
        high = high>=size?size-1:high;
        if(low == 0 && high==size-1){
            head = linked_list->head;
            tail = linked_list->tail;
            size =linked_list->size;
        }else{
            // duyet linkedlist
            Node* cur = head;
            Node* pre = nullptr;
            int count = 0;
            while(cur){
                if(count==low-1) pre = cur;
                if(count == high) break;
                cur = cur->next;
                count++;
            }
            
            size = size - (high-low+1);
            //match linked_list
            if(linked_list->head!=NULL){
                if(pre!=nullptr){
                    pre->next = linked_list->head;
                    linked_list->tail->next = cur->next;
                }else{
                    linked_list->tail->next = cur->next;
                    head = linked_list->head;
                }
                size = linked_list->size + size;
            }else{
                // replace
                if(pre!=nullptr){
                    pre->next = cur->next;
                }else head = cur->next;
            }
        }
    }
}

void LinkedList::partition(int k) {
    if (!head || !head->next) {
        return;
    }
    Node* h1 = nullptr;
    Node* t1 = nullptr;
    Node* h2 = nullptr;
    Node* t2 = nullptr;
    Node* h3 = nullptr;
    Node* t3 = nullptr;

    Node* cur = head;

    while (cur) {
        if (cur->value < k) {
            if (!h1) {
                h1 = cur;
                t1 = cur;
            } else {
                t1->next = cur;
                t1 = cur;
            }
        } else if (cur->value == k) {
            if (!h2) {
                h2 = cur;
                t2 = cur;
            } else {
                t2->next = cur;
                t2 = cur;
            }
        } else {
            if (!h3) {
                h3 = cur;
                t3 = cur;
            } else {
                t3->next = cur;
                t3 = cur;
            }
        }

        cur = cur->next;
    }

    if (h1) {
        head = h1;
        t1->next = h2;
    } else if (h2) {
        head = h2;
    } else {
        head = h3;
    }

    if (h3) {
        t2->next = h3;
        tail = t3;
    } else {
        tail = t2;
    }

    if (tail) {
        tail->next = nullptr;
    }
}

int main(){
LinkedList* l1 = new LinkedList();
LinkedList* l2 = new LinkedList();
l1->add(10);
// l1->add(20); l1->add(30); l1->add(40); l1->add(50);
l2->add(55); l2->add(45); l2->add(42);
l1->replace(l2, 0,1);
cout << l1->toString() << "\n";
    return 0;
}