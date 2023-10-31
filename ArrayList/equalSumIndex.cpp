#include<iostream>
#include<vector>
using namespace std;
int equalSumIndex(vector<int>& nums) {
    // STUDENT ANSWER
    int sum = 0, suml=0;
    for(int i=0;i<nums.size();i++){
        sum += nums[i];
    }
    for(int i=1;i<nums.size();i++){
        suml+=(nums[i-1]);
        int sumr = sum - suml - nums[i];
        if(suml == sumr) return i;
    }
    return -1;
}
int main(){
    vector<int> nums {5};
    cout << equalSumIndex(nums);
    return 0;
}
// 3 5 2 7 6 4