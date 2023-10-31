#include<iostream>
#include<string>
using namespace std;
template <class T>
class DLinkedList {
public:
    class Iterator; //forward declaration
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList() : head(NULL), tail(NULL), count(0){};
    ~DLinkedList(){clear();}
    void    add(const T &e);
    void    add(int index, const T &e);
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index, const T &e);
    int     indexOf(const T &item);
    bool    contains(const T &item);
    T       removeAt(int index);
    bool    removeItem(const T &item);
    void    clear();
    string toString();
    Iterator begin(){
        return Iterator(this, true);
    }
    Iterator end(){
        return Iterator(this, false);
    }
public:
    class Node{
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;
        Iterator begin(){
            return Iterator(this, true);
        }
        Iterator end(){
            return Iterator(this, false);
        }
    public:
        Node(){
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T &data){
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };

    class Iterator{
    private:
        DLinkedList<T> *pList;
        Node *current;
        int index; // is the index of current in pList
    public:
        Iterator(DLinkedList<T> *pList, bool begin);
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
void DLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    Node* n = new Node(e);
    if(!head){
        head = n;
        tail = head;
    }else{
        n->previous = tail;
        tail->next = n;
        tail = tail->next;
    }

    count++;
}

template<class T>
void DLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */ 
    Node* n = new Node(e);

    if(!head){
        head = n;
        tail = head;
    }else{
        if(index <= 0){
            n->next = head;
            head->previous = n;
            head = n;
        }else if(index >= count){
            n->previous = tail;
            tail->next = n;
            tail = tail->next;
        }else{
            int idx = 0;
            Node* curr = head;
            while(curr){
                if(index==idx) break;
                curr=curr->next;
                idx++;
            }
            n->previous=curr->previous;
            n->next = curr;
            curr->previous->next = n;
            curr->previous = n;
        }
    } 
    count++;
    
}

template<class T>
int DLinkedList<T>::size() {
    /* Return the length (size) of list */ 
    return count;
}

template<class T>
T DLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    int idx = 0;
    Node* curr = head;
    while(curr){
        if(idx == index) break;
        curr = curr->next;
        idx++;
    }
    return curr->data;
    
}

template <class T>
void DLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if(!head) return;
    int idx = 0;
    Node* curr = head;
    while(curr){
        if(idx == index){
            curr->data = e;
            break;
        }
        curr = curr->next;
        idx++;
    }
}

template<class T>
bool DLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    if(head) return false;
    return true;
}

template<class T>
int DLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    if(!head) return -1;
    int idx = 0;
    Node* curr = head;
    while(curr){
        if(curr->data == item) return idx;
        curr = curr->next;
        idx++;
    }
    return -1;
}

template<class T>
bool DLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    int idx = 0;
    Node* curr = head;
    while(curr){
        if(curr->data == item) return true;
        curr = curr->next;
        idx++;
    }
    return false;
}

template <class T>
T DLinkedList<T>::removeAt(int index){
    /* Remove element at index and return removed value */
    if (index < 0 || index >= count || head==nullptr) {
        throw std::out_of_range("Index out of range");
    }
    T memory;
    Node* curr = nullptr;
    if(count==1){
        memory = head->data;
        head = nullptr;
        tail = nullptr;
    }else{
        if(index==0){
            curr = head;
            memory = head->data;
            head = head->next;
            head->previous = nullptr;
        }else if(index == count-1){
            curr = tail;
            memory = tail->data;
            tail = tail->previous;
            tail->next = nullptr;
        }else{
            int idx = 0;
            curr = head;
            while(curr){
                if(index == idx) break;
                curr = curr->next;
                idx++;
            }
            memory = curr->data;
            curr->previous->next = curr->next;
            curr->next->previous = curr->previous;
        }
        curr->previous = nullptr;
        curr->next = nullptr;
        delete curr;
    }
    count--;
    return memory;
}

template <class T>
bool DLinkedList<T>::removeItem(const T& item){
    /* Remove the first apperance of item in list and return true, otherwise return false */
    int idx = 0;
    Node* curr = head;
    while(curr){
        if(curr->data == item) {
            removeAt(idx);
            return true;
        }
        curr = curr->next;
        idx++;
    }
    return false;
}

template<class T>
void DLinkedList<T>::clear(){
    /* Remove all elements in list */
    while(count>0){
        removeAt(count-1);
    }
}

template<class T>
string DLinkedList<T>::toString(){
    string s("");
    if(!head) s+="[]";
    Node* cur = head;
    while(cur){
        s+= to_string(cur->data)+" |";
        cur = cur->next;
    }
    return s;
}

/*
 * TODO: Implement class Iterator's method
 * Note: method remove is different from SLinkedList, which is the advantage of DLinkedList
 */
template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T> *pList, bool begin) {
    this->pList = pList;
    if(begin){
        this->current = pList?pList->head:nullptr;
        this->index = pList?0:-1;
    }else{
        this->current = nullptr;
        this->index = pList?pList->size():0;
    }
}

template <class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator &iterator){
    this->pList = iterator.pList;
    this->current =iterator.current;
    this->index = iterator.index;
    return *this;
}

template <class T> 
void DLinkedList<T>::Iterator::set(const T &e){
    if(current == nullptr) return;
    else current->data = e;
}

template<class T>
T& DLinkedList<T>::Iterator::operator*() {
    if(current == nullptr) throw std::out_of_range("Segmentation fault!");
    return current->data;
}

template<class T>
void DLinkedList<T>::Iterator::remove() {
    /*
    * TODO: delete Node in pList which Node* current point to. 
    *       After that, Node* current point to the node before the node just deleted.
    *       If we remove first node of pList, Node* current point to nullptr.
    *       Then we use operator ++, Node* current will point to the head of pList.
    */
    if(!current) return;
    //assign current to the node prev
    if(!index) current = nullptr;
    else current = current->previous;
    // delete current node
    pList->removeAt(index);
    this->index--;
}

template<class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator &iterator) {
    return this->pList!=iterator.pList || current!=iterator.current || index!=iterator.index;
}

template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator++() {
    //prefix
    current = current->next;
    index++;
    return *this;
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int) {
    //postfix
   Iterator clone = *this;
   current = current?current->next:pList->head;
   index++;
   return clone;
}

int main(){
	
DLinkedList<int> list;
int size = 10;
for (int idx = 0; idx < size; idx++)
{
    list.add(idx);
}

DLinkedList<int>::Iterator it = list.begin();
while (it != list.end()){
    it.remove();
    it++;
}
cout << list.toString();
return 0;
}