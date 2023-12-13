#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class Heap {
protected:
    T* elements;
    int capacity;
    int count;
public:
    Heap()
    {
        this->capacity = 10;
        this->count = 0;
        this->elements = new T[capacity];
    }
    ~Heap()
    {
        delete[]elements;
    }
    
    bool isEmpty();
    bool contains(T item);
    T peek();
    bool pop();
    int size();
    void push(T item);
    int getItem(T item);
    void remove(T item);
    void clear();
    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]\n";
    }
private:
    void ensureCapacity(int minCapacity);
    void reheapUp(int position);
    void reheapDown(int position);
};

template<class T>
int Heap<T>::size(){
    return count;
}

template<class T>
bool Heap<T>::isEmpty(){
    return count==0? true:false;
}

template<class T>
T Heap<T>::peek(){
    return *(elements);
}

template<class T>
bool Heap<T>::contains(T item){
    for(int i=0;i<count;++i){
        if(item == elements[i]) return true;
    }

    return false;
}

template<class T>
bool Heap<T>::pop(){
    if(count>0){
        *(elements)=*(elements+count-1);
        --count;
        reheapDown(0);
        return true;
    }
    return false;
}

template<class T>
void Heap<T>::push(T item){
    count++;
    ensureCapacity(capacity);
    elements[count-1] = item;
    reheapUp(count-1);
}

template<class T>
void Heap<T>::ensureCapacity(int minCapacity){
    if(count > capacity) {
        capacity = minCapacity + 1;
        T* newE = new T[capacity];
        for(int i = 0; i < count-1; i ++) newE[i] = elements[i];
        delete[] elements;
        elements = newE;
    }
}

template<class T>
void Heap<T>::reheapUp(int position){
    int par = (position-1)/2;
    if(position>0 && elements[par]<elements[position]){
        swap(elements[par], elements[position]);
        reheapUp(par);
    }
}

template<class T>
int Heap<T>::getItem(T item) {
    // TODO: return the index of item in heap
    for(int i=0;i<count;++i) if(item == elements[i] ) return i;
    return -1;
}

template<class T>
void Heap<T>::remove(T item) {
    // TODO: remove the element with value equal to item
    int idx = getItem(item);
    if(idx<0) return;
    elements[idx] = elements[count-1];
    count--;
    reheapDown(idx);
}

template<class T>
void Heap<T>::clear() {
    // TODO: delete all elements in heap
    //    then reallocate memory as initial state
    count=0;
}

template<class T>
void Heap<T>::reheapDown(int position){
    int lc = position*2+1;
    int rc = position*2+1;
    int greater = position;
    if(lc<count && elements[lc]>elements[greater]) greater = lc;
    if(rc<count && elements[rc]>elements[greater] )   greater = rc;
    if(greater>position){
        swap(elements[greater], elements[position]);
        reheapDown(greater);
    }
}
int main(){
int arr[] = {1,2,3,4,5,6,7,8};
int size = sizeof(arr)/sizeof(arr[0]);
reheapDown(arr,size,0);
cout << "[ ";
for(int i=0;i<size;i++)
    cout << arr[i] << " ";
cout << "]";
return 0;
}