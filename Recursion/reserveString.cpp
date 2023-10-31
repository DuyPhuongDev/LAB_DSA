#include<iostream>
#include<string>
using namespace std;

string reverseSentence(string s) {
    // STUDENT ANSWER
    size_t posSpace = s.find(" ");
    if(s.empty() || posSpace == string::npos) return s;
    string firstWord = s.substr(0,posSpace);
    return reverseSentence(s.substr(posSpace+1)) +" "+ firstWord;
}

int main(){
    cout << reverseSentence("data structure and algorithm is scary");
    return 0;
}