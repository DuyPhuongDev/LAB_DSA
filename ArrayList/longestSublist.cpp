#include<iostream>
#include<vector>
using namespace std;
int arr[26];
int longestSublist(vector<string>& words) {
    // STUDENT ANSWER
    int maxlong = 0;
    int curlong = 0;
    char curChar = '\0';
    for(string x : words){
        if(x.empty()) continue;
        char firstChar = x[0];
        if(firstChar==curChar) curlong++;
        else{
            curChar = firstChar;
            curlong = 1;
        }
        maxlong = maxlong>curlong? maxlong:curlong;
    }
    return maxlong;
}
int main(){
    vector<string> words {"aaa","bk","bku"};
    cout << longestSublist(words);
    return 0;
}