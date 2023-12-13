#include<bits/stdc++.h>
using namespace std;

int pairMatching(vector<int>& nums, int target) {
    int count =0;
    multiset<int> mlts(nums.begin(), nums.end());
    for(unsigned int i=0;i<nums.size();++i){
        int item = target-nums[i];
        if(mlts.find(item)!=mlts.end()){
            count++;
            mlts.erase(mlts.find(nums[i]));
            mlts.erase(mlts.find(item));
        }
    }
    return count;
}
int main(){
int target = 11;
vector<int>items{2,6,9,2,2,9,8,4,7,5};
cout << pairMatching(items, target);
return 0;
}