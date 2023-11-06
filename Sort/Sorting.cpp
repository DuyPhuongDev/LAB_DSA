#include <iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;

template <class T>
class Sorting{
private:
    
    T* PartitionHoare(T* start, T* end) ;
    T* PartitionLomuto(T* start, T* end) ;
    void merge(T* start, T* middle, T* end);
public:
    /* Function to print an array */
    void printArray(T *start, T *end){
        int size = end - start +1;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << " ";
        cout << start[size - 1];
        cout << endl;
    }
    void mergeSort(T* start, T* end);
    void selectionSort(T *start, T *end);
    void sortSegment(T* start, T* end, int segment_idx, int cur_segment_total);
    void ShellSort(T* start, T* end, int* num_segment_list, int num_phases);
    void insertionSort(T* start, T* end);
    void QuickSort(T* start, T* end) ;
    void oddEvenSort(T *start, T *end);
    void hybridQuickSort(T *start, T *end, int min_size);
    void TimSort(T* start, T* end, int min_size);

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

// template<class T>
// void Sorting<T>::insertionSort(T* start, T* end){
//     int size = end - start;
//     for(int i=0;i<size;i++){
//         bool flag = false;
//         T value = *(start+i);
//         int pos = i-1;
//         while(pos>=0 && *(start+pos)>value){
//             *(start+pos+1) = *(start + pos);
//             flag = true;
//             pos--;
//         }
//         *(start+pos+1) = value;
//         if(flag) printArray(start, end);
//     }
// }
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
void Sorting<T>::oddEvenSort(T *start, T *end){
    int size = end - start;
    for(int i=0;i< size;i++){
        //o: le , e: chan
        bool flag = false;
        for(int e = 0;e<size;e+=2) if(*(start+e+1)<*(start+e)){
            swap(*(start+e+1),*(start+e));
            flag=true;
        }
        for(int o = 1;o<size-1;o+=2) if(*(start+o+1)<*(start+o)){
            swap(*(start+o+1),*(start+o));
            flag=true;
        }
        if(flag) printArray(start,end);
    }
    printArray(start,end);
}


template<class T>
T* Sorting<T>::PartitionLomuto(T* start, T* end) {
    //TODO: return the pointer which points to the pivot after rearrange the array.
    int l = 0, r = end - start -1;
    int pivot = *(start+r);
    int i=-1;

    for(int j=0;j<r;j++){
        if(*(start+j)<pivot){
            i++;
            swap(*(start+i), *(start+j));
        }
    }
    i++;
    swap(*(start+i), *(start+r));
    cout<<i<<" ";
    return (start+i); 
}

template<class T>
T* Sorting<T>::PartitionHoare(T* start, T* end){
    // using first element is a pivot
    
    T* i = start+1;
    T* j = end-1;
    int index = end-start-1;
    T pivot = *start;
    do{
        while(i<=j && *i<=pivot) i++;
        while(j>=i && *j>=pivot) {j--; index--;}
        if(i<=j){
            swap(*i,*j);
            i++; j--; index--;
        } 
    }while(i<=j);

    swap(*j,*start);
    //cout<<index<<"\n";
    return j;
}
template<class T>
void Sorting<T>::QuickSort(T* start, T* end) {
    // TODO
    // In this question, you must print out the index of pivot in subarray after everytime calling method Partition.
    if(end-start<1) return;
    printArray(start,end);
    T* mid = PartitionHoare(start,end);
    
    QuickSort(start,mid); // sort phan trai
    QuickSort(mid+1,end);

}

template <class T>
void Sorting<T>::hybridQuickSort(T *start, T *end, int min_size){
    if(end-start<1) return;
    if(end-start<min_size && end-start>=1){
        insertionSort(start, end);
        return;
    }
    cout<<"Quick sort: "; printArray(start,end);
    T* pivot = PartitionHoare(start,end);
    hybridQuickSort(start,pivot, min_size);
    hybridQuickSort(pivot+1,end, min_size);
}

template<class T>
void Sorting<T>::insertionSort(T* start, T* end){
    //cout<<"Insertion sort: "; printArray(start,end);
    int size = end - start;
    for(int i=1;i<size;i++){
        T key = *(start+i);
        int j=i-1;
        while(j>-1 && *(start+j)>key){
            *(start+j+1)=*(start+j);
            j--;
        }
        *(start+j+1) = key;
    }
}

// template<class T>
//  void Sorting<T>::merge(T* start, T* middle, T* end){
//     // divide list to 2 list a, b
//     if(end-middle<1) return;
//     int sizeA = middle-start;
//     int sizeB = end - middle;
//     T a[sizeA], b[sizeB];

//     for(int i=0;start+i<middle;i++){
//         a[i] = *(start+i);
//     }

//     for(int i=0;middle+i<end;i++){
//         b[i] = *(middle+i);
//     }
//     // merge 2 list
    
//     int i=0, j=0,k=0;

//     while(i<sizeA && j<sizeB){
//         if(a[i]<b[j]){
//             *(start+k) = a[i];
//             i++;
//         }else{
//             *(start+k) = b[j];
//             j++;
//         }
//         k++;
//     }

//     while(i<sizeA){
//         *(start+k) = a[i];
//         i++; k++;
//     }

//     while(j<sizeB){
//         *(start+k) = b[j];
//         j++; k++;
//     }

//     printArray(start,end);
//  }

template<class T>
void Sorting<T>::merge(T* left, T* middle, T* right){
    /*TODO*/
    if(right - middle<1) return;
    
    int sizeA = middle - left + 1, sizeB = right - middle;
    int a[sizeA], b[sizeB];
    
    for(int i=0;i<sizeA;i++) a[i] = *(left+i);
    for(int i=0;i<sizeB;i++) b[i] = *(middle+1+i);
    
    
    int i=0, j=0;
    int k=0;
    while(i<sizeA && j<sizeB){
        if(a[i]<b[j]){
            *(left+(k++)) = a[i];
            i++;
        }else{
            *(left+(k++)) = b[j];
            j++;
        }
    }
    
    while(i<sizeA) {*(left+(k++)) = a[i]; i++;}
    while(j<sizeB) {*(left+(k++)) = b[j]; j++;}
    printArray(left, right);
}


template<class T>
void Sorting<T>::TimSort(T* start, T* end, int min_size){
    int size = end - start;
    
    for(int i=0;i<size;i+=min_size){
        T* e = start+i+min_size>=end? end: start+i+ min_size;
        insertionSort(start + i, e);
    }

    cout<<"Insert Sort: "; printArray(start,end);


    // merge sort 
    int count = 0;
    while(min_size<size){
        for(int i = 0; i<size; i+=min_size*2){
            T* mid = start+i + min_size;
            T* e = mid+min_size>=end? end: mid+min_size;
            merge(start+i, mid, e);
            cout<<"Merge "<<++count<<": "; printArray(start, end);
        }
        min_size*=2;
    }
}


template<class T>
void Sorting<T>::mergeSort(T* start, T* end){
    if(start>=end) return;  
    T* mid = start + (end-start)/2;
    mergeSort(start,mid);
    mergeSort(mid+1,end);

    merge(start,mid,end);
}
int main(){
    srand (time(NULL));
    Sorting<int>* list;
    // int n; cin>>n;
    // int* arr = new int[n];
    // for(int i=0;i<n;i++){
    //     arr[i] = rand() % 100 + 1;
    // }
    int arr[] = {0,2,4,3,1,4};
    cout<<"List: "; 
    list->printArray(&arr[0], &arr[5]);
    list->mergeSort(&arr[0], &arr[5]);
    //list->printArray(&arr[0], &arr[20]);
    // delete[] arr;
    return 0;
}