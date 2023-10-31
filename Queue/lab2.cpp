#include<iostream>
#include<queue>
#include<stack>
#include<vector>

using namespace std;
bool isBipartite(vector<vector<int>> graph);
void interleaveQueue(queue<int>& q);
long long nthNiceNumber(int n);

void interleaveQueue(queue<int>& q){
    stack<int> st1;
    stack<int> st2;
    stack<int> st3;
    int len = q.size();
    for(int i=0;i<len;i++){
        if(i<len/2) st1.push(q.front());
        else st2.push(q.front());
        q.pop();
    }
    int count = 0;
    while(!st1.empty() || !st2.empty()){
        if(count%2){
            st3.push(st1.top());
            st1.pop();
        }else{
            st3.push(st2.top());
            st2.pop();
        }
        count++;
    }

    while(!st3.empty()){
        q.push(st3.top());
        st3.pop();
    }
}

long long nthNiceNumber(int n){
    queue<long long> q;
    long long result;
    q.push(2); q.push(5);
    int i=0;
    while(i++<(n-1)/2){
        long long cur = q.front(); q.pop();
        q.push(cur*10+2);
        q.push(cur*10+5); 
        result = n%2? cur*10+2:cur*10+5;
    }
    return result;
}

int main(){
    int n; cin>>n;
cout << nthNiceNumber(n) << endl;
    return 0;
}