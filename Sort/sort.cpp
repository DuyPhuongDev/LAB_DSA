#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

// pair<value, freq>

bool compare(pair<int,int> a, pair<int, int>b){
    return a.second>b.second;
}
void sortByFrequency(int arr[], int n){
    vector<pair<int, int>> v;

    // count freq of each elements
    for(int i=0;i<n;++i){
        bool flag=false;
        for(unsigned int j=0;j<v.size();++j){
            if(v[j].first==arr[i]){
                v[j].second+=1;
                flag=true;
                break;
            }
        }    
        if(!flag) v.push_back({arr[i],1});
    }

    // sort
    stable_sort(v.begin(), v.end(), compare);
    int k=0;
    for(auto x:v){
        for(int i =0;i<x.second;++i){
            arr[k++]=x.first;
        }
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