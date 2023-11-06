#ifndef SORTINGAPPLICATION_H
#define SORTINGAPPLICATION_H
#include <iostream>
#include <string>
#include<queue>
#include <algorithm>
#include<stack>
using namespace std;
bool isPermutation (string a, string b);
#endif /* SORTINGAPPLICATION_H */

/* Your helping functions go here */
bool isPermutation (string a, string b) {
    //TODO
    if(a.length()!=b.length()) return false;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for(int i=0;i<a.length();i++) if(a[i]!=b[i]) return false;
    return true;
}

int numberOfTheWinner(int N, int k) {
    queue<int> q;
    for(int i=1;i<=N;i++) q.push(i);

    while(q.size()>1){
        for(int i=1;i<k;i++) {int cur= q.front(); q.pop(); q.push(cur);}
        q.pop();
    }

    return q.front();
}

int trap(vector<int>& height) {
    stack<int> st;
    int water = 0;

    for (unsigned int i = 0; i < height.size(); i++) {
        while (!st.empty() && height[i] > height[st.top()]) {
            int prevIndex = st.top();
            st.pop();

            if (!st.empty()) {
                int distance = i - st.top() - 1;
                int boundedHeight = min(height[i], height[st.top()]) - height[prevIndex];
                water += boundedHeight * distance;
            }
        }

        st.push(i);
    }

    return water;
}
int sumOfMinSubarray(vector<int>& nums) {
    int n = nums.size();
    const int MOD = 10000;

    stack<int> st;

    vector<int> left(n), right(n);

    // Find the next smaller element on the left for each element
    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[st.top()] >= nums[i]) {
            st.pop();
        }

        if (st.empty()) {
            left[i] = -1;
        } else {
            left[i] = st.top();
        }

        st.push(i);
    }

    while (!st.empty()) {
        st.pop();
    }

    // Find the next smaller element on the right for each element
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && nums[st.top()] >= nums[i]) {
            st.pop();
        }

        if (st.empty()) {
            right[i] = n;
        } else {
            right[i] = st.top();
        }

        st.push(i);
    }

    // Calculate the sum of the minimum values of all subarrays
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int subarraySize = right[i] - left[i] - 1;
        sum = (sum + (nums[i] * subarraySize) % MOD) % MOD;
    }

    return sum;
}


int main(){
    int N;
    int k;
    cin >> N >> k;
    cout << numberOfTheWinner(N, k);
    return 0;
}