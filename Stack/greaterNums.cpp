#include <stack>
#include <vector>
#include <iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
// iostream, stack and vector are included

vector<int> nextGreater(vector<int>& nums){
    int n = nums.size();
    vector<int> result(n, -1); // create vector with N elements and assign each ele = -1
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[i] > nums[st.top()]) {
            result[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }

    return result;
} 

bool tripleIndexSLM(std::vector<int>& nums) {
    stack<int> stack;
    int minimum = 999999;

    for (int num : nums) {
        while (!stack.empty() && num > stack.top()) {
            int midNum = stack.top();
            stack.pop();

            if (num > midNum && minimum < num) {
                return true;
            }

            minimum = min(minimum, midNum);
        }

        if (num <= minimum) {
            minimum = num;
        }

        stack.push(num);
    }

    return false;
}

int main(){
    int N;
    cin >> N;
    vector<int> nums(N);
    srand(time(NULL));
    for(int i = 0; i < N; i++) nums[i] = rand() % 10000000000 + 1;
    for(int i = 0; i < N; i++) cout<<nums[i]<<" ";
    cout << '\n';
    vector<int> greaterNums = nextGreater(nums);
    for(int i : greaterNums) 
        cout << i << ' ';
    cout << '\n';
    return 0;
}