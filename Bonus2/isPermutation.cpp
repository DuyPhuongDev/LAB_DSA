#ifndef SORTINGAPPLICATION_H
#define SORTINGAPPLICATION_H
#include <iostream>
#include <string>
#include<queue>
#include <algorithm>
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

int main(){
    int N;
    int k;
    cin >> N >> k;
    cout << numberOfTheWinner(N, k);
    return 0;
}