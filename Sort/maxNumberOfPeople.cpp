#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<string>
using namespace std;

int maxNumberOfPeople(vector<int>& rooms, vector<int>& people, int k) {
    sort(rooms.begin(), rooms.end());
    sort(people.begin(), people.end());

    int count=0, i=0, j=0;
    // mỗi người 1 phòng :-)))
    while(i<rooms.size() && j<people.size()){
        if(people[j]+k<rooms[i]) j++;
        else if(people[j]-k>rooms[i]) i++;
        else {count++; j++; i++;}
    }

    return count;
}

string minDiffPairs(int* arr, int n){
    // STUDENT ANSWER
    sort(arr,arr+n);
    string s("");
    int minsofar = abs(*(arr+n-1) - *arr);
    for(int i=0;i<n-1;i++){
        int curMin = abs(*(arr+i+1)-*(arr+i));
        if( curMin < minsofar) minsofar = curMin;
    }

    for(int i=0;i<n-1;i++){
        if(abs(*(arr+i+1) - *(arr+i))==minsofar){
            s+= '(' +to_string(*(arr+i)) +", "+to_string(*(arr+i+1)) +"), ";
        }
    }
    if(!s.empty()){s.pop_back(); s.pop_back();}
    return s;
}

void sortByFrequency(int arr[], int n){
    int a[100001], b[100001]={0};

    for(int i=0;i<n;i++){
        
    }
}

int main(){
	int arr[] = {-4,1,2,2,-4,9,1,-1};
	int n = sizeof(arr) / sizeof(arr[0]);

	sortByFrequency(arr, n);

	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
    return 0;
}