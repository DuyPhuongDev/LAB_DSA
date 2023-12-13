#include<math.h>
#include<iostream>
using namespace std;

int binarySearch(int arr[], int left, int right, int x){
    while(left<=right){
        int mid = left +(right-left)/2;
        cout << "We traverse on index: " << mid << endl;
        if(arr[mid]==x) return mid;
        if(x<arr[mid]){
            right=mid-1;
        }else left = mid+1;
    }
    return -1;
}

int interpolationSearch(int arr[], int left, int right, int x){
    int pos;
    if(left<=right && x>=arr[left]&& x<=arr[right]){
            pos = left
              + (((double)(right - left) / (arr[right] - arr[left]))
                 * (x - arr[left]));
            cout << "We traverse on index: " << pos << endl;
        if(arr[pos]==x) return pos;
        else if(x<arr[pos]) return interpolationSearch(arr,left,pos-1,x);
        else return interpolationSearch(arr,pos+1,right,x);
    }
    return -1;
}

int jumpSearch(int arr[], int x, int n) {
    // TODO: print the traversed indexes and return the index of value x in array if x is found, otherwise, return -1.
    int step = sqrt(n);
    int prev = 0;
    cout<<prev<<" ";
    do{
        cout<<step<<" ";
        prev = step;
        step+=sqrt(n);
    }while(arr[min(step,n-1)]<x && step<n);
    if()
    while(prev<step-1){
        ++prev;
        cout<<prev<<" ";
        if(arr[prev]==x) return prev;
        if(prev == min(step,n)) return -1;
    }
    return -1;
}
int main(){
int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 611, 612, 613 };
int x = 614;
int n = sizeof(arr) / sizeof(arr[0]);
int index = jumpSearch(arr, x, n);

if (index != -1) {
    cout << "\nNumber " << x << " is at index " << index;
}
else {
    cout << "\n" << x << " is not in array!";
}
    return 0;
}