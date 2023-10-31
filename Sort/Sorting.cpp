#include <iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;

template <class T>
class Sorting
{
public:
    /* Function to print an array */
    static void printArray(T *start, T *end){
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << " ";
        cout << start[size - 1];
        cout << endl;
    }

    static void selectionSort(T *start, T *end);
    static void sortSegment(T* start, T* end, int segment_idx, int cur_segment_total);
    static void ShellSort(T* start, T* end, int* num_segment_list, int num_phases);
    static void insertionSort(T* start, T* end);
    static void quickSort(T* start, T* end);
    static void mergeSort(T* start, T* end);
};

template <class T>
void Sorting<T>::selectionSort(T *start, T *end){
    int size = end - start;
    
    for(int i = 0; i<size -1 ;i++){
        int minIndex = i;
        //bool flag = false;
        for(int j = i+1; j<size;j++){
            if(*(start+j)<*(start+minIndex)){
                minIndex = j;
                //flag = true;
            }
        }
        swap(*(start+i),*(start+minIndex));
        printArray(start, end);
    }
}

template<class T>
void Sorting<T>::insertionSort(T* start, T* end){
    int size = end - start;
    for(int i=0;i<size;i++){
        bool flag = false;
        T value = *(start+i);
        int pos = i-1;
        while(pos>=0 && *(start+pos)>value){
            *(start+pos+1) = *(start + pos);
            flag = true;
            pos--;
        }
        *(start+pos+1) = value;
        if(flag) printArray(start, end);
    }
}
// TODO: Write your code here
template<class T>
void Sorting<T>::sortSegment(T* start, T* end, int segment_idx, int cur_segment_total) {
    // TODO
    int size = end - start;
    for(int i = cur_segment_total; i<size;i+=cur_segment_total){
        T value = *(start+i);
        int pos = i-cur_segment_total;
        while(pos>=0 && *(start+pos)>value){
            *(start+pos+cur_segment_total) = *(start+pos);
            pos -= cur_segment_total;
        }
        *(start+pos+ cur_segment_total) = value;
    }
}

template<class T>
void Sorting<T>::ShellSort(T* start, T* end, int* num_segment_list, int num_phases) {
    // TODO
    // Note: You must print out the array after sorting segments to check whether your algorithm is true.
    for(int i = num_phases-1;i>=0;i--){
        for(int j = 0; j<num_segment_list[i];j++){
            sortSegment(start+j,end,j,num_segment_list[i]);
        }
        cout<<num_segment_list[i]<<" segments: ";
        printArray(start,end);
    }
}

template<class T>
void Sorting<T>::quickSort(T* start, T* end){

}

template<class T>
void Sorting<T>::mergeSort(T* start, T* end){


}

int main(){
    srand (time(NULL));
    // int n; cin>>n;
    // int* arr = new int[n];
    // for(int i=0;i<n;i++){
    //     arr[i] = rand() % 100 + 1;
    // }
    int num_segment_list[] = {1, 3, 5};
    int num_phases = 3;
    int array[] = { 10, 9, 8 , 7 , 6, 5, 4, 3, 2, 1 };

    Sorting<int>::ShellSort(&array[0], &array[10], &num_segment_list[0], num_phases);
    // cout<<"List: "; 
    // Sorting<int>::printArray(&arr[0], &arr[n]);
    // cout<<"Sort: "<<endl;
    // Sorting<int>::insertionSort(&arr[0], &arr[n]);
    // delete[] arr;
    return 0;
}
