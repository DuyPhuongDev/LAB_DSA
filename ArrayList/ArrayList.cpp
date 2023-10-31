#include<iostream>
#include<string>
using namespace std;
template <class T>
class ArrayList {
protected:
    T* data;        // dynamic array to store the list's items
    int capacity;   // size of the dynamic array
    int count;      // number of items stored in the array
public:
    ArrayList(){capacity = 5; count = 0; data = new T[5];}
    ~ArrayList(){ delete[] data; }
    void    add(T e);
    void    add(int index, T e);
    int     size();
    void    ensureCapacity(int index);
    string toString(){
        string s("");
        for(int i=0;i<count;i++){
            s+=to_string(data[i]) + " ";
        }
        return s;
    }
    bool    empty();
    void    clear();
    T       get(int index);
    void    set(int index, T e);
    int     indexOf(T item);
    bool    contains(T item);
    T       removeAt(int index);
    bool    removeItem(T item);
};
template<class T>
void ArrayList<T>::ensureCapacity(int cap){
    /* 
        if cap == capacity: 
            new_capacity = capacity * 1.5;
            create new array with new_capacity
        else: do nothing
    */
   if(cap==capacity){
        capacity = capacity*1.5;
        T* new_data = new T[capacity];
        for(int i=0;i<capacity;i++){
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
   }
}

template <class T>
void ArrayList<T>::add(T e) {
    /* Insert an element into the end of the array. */
    ensureCapacity(count);
    data[count]=e;
    count++;
}

template<class T>
void ArrayList<T>::add(int index, T e) {
    /* 
        Insert an element into the array at given index.
        if index is invalid:
            throw std::out_of_range("the input index is out of range!");
    */
    if(index>=0){
        ensureCapacity(count);
        T* a = new T[capacity];
        for(int i=0;i<capacity;i++){
            if(i<index) a[i]=data[i];
            else if(i>index) a[i]=data[i-1];
            else{
                a[i]=e;
                count++;
            }
        }
        delete[] data;
        data = a;
    }else throw out_of_range("the input index is out of range!");
}

template<class T>
int ArrayList<T>::size() {
     /* Return the length (size) of the array */
    return count;
}

template<class T>
T ArrayList<T>::removeAt(int index){
    /*
    Remove element at index and return removed value 
    if index is invalid:
        throw std::out_of_range("index is out of range");
    */
    if(index>=0 && index<count){
        T* np = new T[capacity];
        for(int i=0;i<count-1;i++){
            if(i<index) np[i]=data[i];
            else np[i]=data[i+1];
        }
        count--;
        T value = data[index];
        delete[] data;
        data = np;
        return value;
    }else throw std::out_of_range("index is out of range");
    
}

template<class T>
bool ArrayList<T>::removeItem(T item){
     /* Remove the first apperance of item in array and return true, otherwise return false */
    int idx=-1;
    for(int i=0;i<count;i++){
        if(data[i]==item){
            idx = i;
            break;
        }
    }
    if(idx>=0){
        T* p =  new T[count-1];
        for(int i=0;i<count-1;i++){
            if(i<idx) p[i]=data[i];
            else p[i]=data[i+1];
        }
        count--;
        delete[] data;
        data = p;
        return true;
    }
    return false;
}

template<class T>
void ArrayList<T>::clear(){
    /* 
        Delete array if array is not NULL
        Create new array with: size = 0, capacity = 5
    */
    if(count>0) delete[] data;
    capacity=5;
    count=0;
    data = new T[5];
}

int main(){
	
    ArrayList<int> arr;

    for (int i = 0; i < 10; ++i) {
        arr.add(i);
    }
    arr.removeItem(5);

    cout << arr.toString() << '\n';
    cout << arr.size();
    return 0;
}