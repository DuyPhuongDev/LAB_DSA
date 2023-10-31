#include<iostream>
#include<queue>
#include<deque>
#include<vector>
#include<stdlib.h>
#include<time.h>
using namespace std;


int sumOfMaxSubarray(vector<int>& nums, int k) {
    deque<int> window;
    int sum = 0;

    // Process the first k elements
    for (int i = 0; i < k; i++) {
        while (!window.empty() && nums[i] >= nums[window.back()]) {
            window.pop_back();
        }
        window.push_back(i);
    }

    // Process the remaining elements
    int N = nums.size();
    for (int i = k; i < N; i++) {
        sum += nums[window.front()];

        while (!window.empty() && nums[i] >= nums[window.back()]) {
            window.pop_back();
        }
        if (!window.empty() && window.front() <= i - k) {
            window.pop_front();
        }
        window.push_back(i);
    }

    // Add the maximum element in the last window to the sum
    sum += nums[window.front()];

    return sum;
}
int main(){
    int n; cin>>n;
    srand(time(NULL));
vector<int> nums(n);
for(int i=0;i<n;i++) nums[i] = rand()%10+1;
// for(int i=0;i<n;i++) cout<<nums[i]<<" ";
int k; cin>>k;
cout << sumOfMaxSubarray(nums, k);
return 0;
}