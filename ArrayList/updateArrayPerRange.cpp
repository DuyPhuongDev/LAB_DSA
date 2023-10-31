#include<iostream>
#include<vector>
using namespace std;
vector<int> updateArrayPerRange(vector<int>& nums, vector<vector<int>>& operations) {
    // STUDENT ANSWER
    for(int i=0;i<operations.size();i++){
        int L = operations[i][0];
        int R = operations[i][1];
        int X = operations[i][2];
        for(int j=L;j<=R;j++){
            nums[j]+=X;
        }
    }
    return nums;
}
void printVector(vector<int> nums){
    for(int i=0;i<nums.size();i++){
        cout<<nums[i]<<" ";
    }
}
int main(){
    vector<int> nums {13, 0, 6, 9, 14, 16};
    vector<vector<int>> operations {{5, 5, 16}, {3, 4, 0}, {0, 2, 8}};
    printVector(updateArrayPerRange(nums, operations));
    return 0;
}