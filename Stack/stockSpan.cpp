#include<iostream>
#include<stack>
#include<climits>
#include<vector>
using namespace std;

vector<int> stock_span(const vector<int>& ns) {
    // STUDENT ANSWER
    if(ns.empty()) throw out_of_range("Error");
    stack<int> st;
    vector<int> v(ns.size(),0);
    st.push(0);
    v[0]=1;
    for(int i = 1;i<ns.size();i++){
        while(!st.empty() && ns[st.top()]<=ns[i]) st.pop();
        if(st.empty()) v[i] = i + 1;
        else v[i] = i - st.top();
        st.push(i);
    }
    return v;
}

int main(){
    vector<int> vt = {};
    vector<int> result = stock_span(vt);
    for(int x : result) cout<<x<<" ";
    return 0;
}