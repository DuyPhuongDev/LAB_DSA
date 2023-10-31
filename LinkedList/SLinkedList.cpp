#include<iostream>
#include<assert.h>
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
    SLinkedList(){
        head = NULL;
        tail = NULL;
        count =0;
    }
    ~SLinkedList(){
        delete head;
        delete tail;
    }
    void    add(const T& e);
    void    add(int index, const T& e);
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index, const T& e);
    int     indexOf(const T& item);
    bool    contains(const T& item);
    T       removeAt(int index);
    bool    removeItem(const T& item);
    void    clear();
    string toString(){
        Node* cur = head;
        string s("[ ");
        while(cur){
            s += to_string(cur->data) + " ";
            cur = cur->next;
        }
        s+=']';
        return s;
    }
    SLinkedList(const SLinkedList &list){
        this->count = list.count;
        this->head = list.head;
        this->tail = list.tail;
    }
    Iterator begin(){
        return Iterator(this, true);
    }
    Iterator end(){
        return Iterator(this, false);
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
        Node(Node* next) {
            this->next = next;
        }
        Node(T data, Node* next) {
            this->data = data;
            this->next = next;
        }
    };
    class Iterator
    {
    private:
        SLinkedList<T> *pList;
        Node *current;
        int index; // corresponding with current node
    public:
        Iterator(): pList(NULL), current(NULL), index(0){}
        Iterator(SLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        void remove();
        // Prefix ++ overload
        Iterator &operator++();
        
        // Postfix ++ overload
        Iterator operator++(int);
    };
};


template <class T>
void SLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    if(head==NULL){
        head = new Node(e,nullptr);
        tail = head;
        count++;
    }else{
        tail->next = new Node(e,nullptr);
        tail = tail->next;
        count++;
    }
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */
    if(head==NULL){
        head = new Node(e,nullptr);
        tail = head;
        count++;
    }else{
        if(index==0){
            Node* newnode = new Node(e,head);
            head = newnode;
            count++;
        }else if(index>0 && index<count){
            Node* cur = head;
            Node* pre = nullptr;
            int countidx = 0;
            while(cur){
                pre = cur;
                cur = cur->next;
                countidx++;
                if(countidx==index){
                    pre->next = new Node(e,cur);
                    count++;
                    break;
                }
            }
        }else if(index==count) add(e);
    }
}

template<class T>
int SLinkedList<T>::size() {
    /* Return the length (size) of list */ 
    return count;
}

template<class T>
T SLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    Node* cur = head;
    int cd =0;
    T x;
    while(cur){
        if(index==cd){
            x=cur->data;
            break;
        }
        cur = cur->next;
        cd++;
    }
    return x;
}

template <class T>
void SLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if(index>=0 && index<count){
        Node* cur = head;
        int cd =0;
        while(cur){
            if(index==cd) cur->data = e;
            cur = cur->next;
            cd++;
        }
    }else throw std::out_of_range("index is out of range");
}

template<class T>
bool SLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return head==NULL? true:false;
}

template<class T>
int SLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    if(head){
        Node* cur = head;
        int idx=0;
        while(cur){
            if(cur->data==item) return idx;
            cur=cur->next;
            idx++;
        }
    }
    return -1;
}

template<class T>
bool SLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    if(head){
        Node* cur = head;
        while(cur){
            if(cur->data==item) return true;
            cur=cur->next;
        }
    }
    return false;
}

template <class T>
T SLinkedList<T>::removeAt(int index){
    /* Remove element at index and return removed value */
    if(index==0){
        T temp = head->data;
        head = head->next;
        count--;=
        return temp;
    }
    Node* cur = head->next;
    Node* pre = head;
    int idx =1;
    T temp;
    while(cur){
        if(idx==index){
            temp = cur->data;
            pre->next = cur->next;
            if(pre->next==NULL) tail=pre;
            count--;
            break;            
        }
        pre = cur;
        cur = cur->next;
        idx++;
    }
    return temp;
}

template <class T>
bool SLinkedList<T>::removeItem(const T& item){
    /* Remove the first apperance of item in list and return true, otherwise return false */
    if(head){
        if(head->data==item){
            head = head->next;
            count--;
            return true;
        }else{
            Node* cur = head->next;
            Node* pre = head;
            while(cur){
                if(cur->data==item){
                    pre->next = cur->next;
                    count--;
                    if(pre->next==NULL) tail= pre;
                    return true;
                }
                pre = cur;
                cur = cur->next;
            }
        }
    }
    return false;
}

template<class T>
void SLinkedList<T>::clear(){
    /* Remove all elements in list */
    delete head;
    delete tail;
    count=0;
}

template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin)
{
    /*
        Constructor of iterator
        * Set pList to pList
        * begin = true: 
        * * Set current (index = 0) to pList's head if pList is not NULL
        * * Otherwise set to NULL (index = -1)
        * begin = false: 
        * * Always set current to NULL
        * * Set index to pList's size if pList is not NULL, otherwise 0
    */
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator)
{
    /*
        Assignment operator
        * Set this current, index, pList to iterator corresponding elements.
    */
}

template <class T>
void SLinkedList<T>::Iterator::remove()
{
    /*
        Remove a node which is pointed by current
        * After remove current points to the previous node of this position (or node with index - 1)
        * If remove at front, current points to previous "node" of head (current = NULL, index = -1)
        * Exception: throw std::out_of_range("Segmentation fault!") if remove when current is NULL
    */
}

template <class T>
void SLinkedList<T>::Iterator::set(const T& e)
{
    /*
        Set the new value for current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
}

template <class T>
T& SLinkedList<T>::Iterator::operator*()
{
    /*
        Get data stored in current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
}

template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator)
{
    /*
        Operator not equals
        * Returns false if two iterators points the same node and index
    */
}
// Prefix ++ overload
template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++()
{
    /*
        Prefix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
}
// Postfix ++ overload
template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int)
{
    /*
        Postfix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
}

int main(){
SLinkedList<int> list;
    
int size = 10;
for(int idx=0; idx < size; idx++){
    list.add(idx);
}
        
SLinkedList<int>::Iterator it;
int expvalue = 0;
for(it = list.begin(); it != list.end(); ++it){
    assert(*it == expvalue);
    expvalue += 1;
}
    return 0;
}