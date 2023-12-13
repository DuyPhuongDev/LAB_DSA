#include <iostream>
#include <queue>
using namespace std;
template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }
    //Helping functions go here
    static void reheapDown(T* start, T* end, int index){   
        int size = end - start;
        int lc = index*2+1;
        int rc =index*2+2;
        int small=index;
        if(lc<size && *(start+lc)>*(start+small)) small = lc;
        if(rc<size && *(start+rc)>*(start+small)) small = rc;
        
        if(index!=small){
            swap(*(start+index),*(start+small));
            reheapDown(start, end, small);
        }
    }
    //Helping functions go here
    static void heapSort(T* start, T* end){
        //TODO
            int N = end -start;
    for (int i = N / 2 - 1; i >= 0; i--) Sorting<T>::reheapDown(start,end,i);
    for (int i = N - 1; i > 0; i--) {
 
        // Move current root to end
        swap(*start, *(start+i));
        // call max heapify on the reduced heap
        Sorting<T>::reheapDown(start, start+i,0);
    }
    Sorting<T>::printArray(start,end);
    }
    
};

int main(){
    int arr[4]={4,2,9,1};
    Sorting<int>::heapSort(&arr[0],&arr[4]);
}