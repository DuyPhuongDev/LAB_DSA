#include<iostream>
#include<string>
using namespace std;
string expand(string s);
string change(string s, int n){
    if(n==1) return expand(s);
    return change(s,n-1);
}
string expand(string s){
    string s1("");
    if(isdigit(s[0])) change(s.substr(s.length()-1),s[0]-'0');
    if(s[0]=='(') return expand(s.substr(1,s.length()-1));
    if(s[0]>='a' && s[0]<='z') s1+=s[0];
    if(s[0]==')') return expand(s.substr(1,s.length()-1));
    return s1;
}
int main(){
    cout << expand("2(a)") << "\n";
    return 0;
}