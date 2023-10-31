#include <iostream>
#include <sstream>
#include<time.h>
#include<stdlib.h>
using namespace std;

template <class T>
class SLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList()
    {
      this->head = nullptr;
      this->tail = nullptr;
      this->count = 0;
    }
    ~SLinkedList(){};
    void add(T e)
    {
        Node *pNew = new Node(e);

        if (this->count == 0)
        {
            this->head = this->tail = pNew;
        }
        else
        {
            this->tail->next = pNew;
            this->tail = pNew;
        }

        this->count++;
    }
    int size()
    {
        return this->count;
    }

    void printList()
    {
        stringstream ss;
        ss << "[";
        Node *ptr = head;
        while (ptr != tail)
        {
            ss << ptr->data << ",";
            ptr = ptr->next;
        }

        if (count > 0)
            ss << ptr->data << "]";
        else
            ss << "]";
        cout << ss.str() << endl;
    }
public:
    class Node {
    private:
        T data;
        Node* next;
        friend class SLinkedList<T>;
    public:
        Node() {
            next = 0;
        }
        Node(T data) {
            this->data = data;
            this->next = nullptr;
        }
    };

    void bubbleSort();
};

template <class T>
void SLinkedList<T>::bubbleSort(){

    int lastIndex = size() - 1;

    while(lastIndex>0){
        Node* curr = head;
        for(int j = 0; j<lastIndex; j++){
            if(curr->data > curr->next->data){
                int tmp = curr->data;
                curr->data = curr->next->data;
                curr->next->data = tmp;
            }
            curr = curr->next;
        }
        lastIndex--;
        printList();
    }
}
int main(){
    srand (time(NULL));
    int n; cin>>n;
    int* arr = new int[n];
    for(int i=0;i<n;i++){
        arr[i] = rand() % 100 + 1;
    }
    SLinkedList<int> list;
    for(int i = 0; i < n;i++) list.add(arr[i]);
    cout<<"List: "; list.printList();
    cout<<"Bubble Sort: "<<endl;
    list.bubbleSort();
    delete[] arr;
    return 0;
}