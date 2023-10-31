#include <stack>
#include <vector>
#include<list>
#include <iostream>
#include<climits>
#include<string>
#include<utility>
using namespace std;

string reversal(string s){
    string s1;
    for(int i=s.length()-1;i>=0;i--){
        s1+=s[i];
    }
    return s1;
}

bool isValidParentheses (string s){
    /*TODO*/
    stack<char> st;
    for(char x:s){
        if(st.empty()|| x=='[' || x=='(' || x=='{') st.push(x);
        else if(x==']'){
            if(st.top()!='[') return 0;
            st.pop();
        }else if(x==')'){
            if(st.top()!='(') return 0;
            st.pop();
        }else if(x=='}'){
            if(st.top()!='{') return 0;
            st.pop();
        }
    }
    if(!st.empty()) return 0;
    return 1;
}

string parenthesesReversal(string s){
    stack<char> st;
    string result("");

    for(auto i = s.begin(); i!=s.end();i++){
        char c = *i; // get value from iterator i
        if(c==')'){
            string tmp("");
            while(st.top()!='('){
                tmp+=st.top();
                st.pop();
            }
            st.pop(); // pop '('

            for(char x:tmp){
                st.push(x);
            }
        }else st.push(c);
    }

    while(!st.empty()){
        result+=st.top();
        st.pop();
    }

    return reversal(result);
}

int baseballScore(string ops){
/*TODO*/
    stack<int> st;
    for(auto i=ops.begin();i!=ops.end();i++){
        char c = *i;
        if(isdigit(c)) st.push(c-'0');
        else if(c=='C'){
            if(!st.empty()) st.pop();
        }else if(c=='D'){
            if(!st.empty()) st.push(st.top()*2);
        }else if(c=='+'){
            if(st.size()>1){
                int temp=st.top();
                st.pop();
                int temp2 =st.top()+temp;
                st.push(temp);
                st.push(temp2);
            }
        }
    }
    int sum = 0;
    while(!st.empty()){
        sum += st.top();
        st.pop();
    }
    return sum;

}

string removeDuplicates(string S){
    /*TODO*/
    stack<char> st;
    string result("");

    for( char c : S){
        if(!st.empty() && st.top()==c) st.pop();
        else st.push(c);
    }

    while(!st.empty()){
        result.push_back(st.top());
        st.pop();
    }
    
    return reversal(result);
}

int evaluatePostfix(string expr){
    /*TODO*/
    stack<int> st;
    for(auto i=expr.begin();i!=expr.end();i++){
        char c = *i;
        if(st.empty() || isdigit(c)){
            string num("");
            while(isdigit(*i)){
                num+=*i;
                i++;
            }
            i--;
            st.push(stoi(num));
        }
        else if(c=='+'){
            int x1=st.top(); st.pop();
            int x2=st.top(); st.pop();
            st.push(x1+x2);
        }else if(c=='-'){
            int x1=st.top(); st.pop();
            int x2=st.top(); st.pop();
            st.push(x2-x1);
        }else if(c=='*'){
            int x1=st.top(); st.pop();
            int x2=st.top(); st.pop();
            st.push(x2*x1);
        }else if(c=='/'){
            int x1=st.top(); st.pop();
            int x2=st.top(); st.pop();
            st.push(x2/x1);
        }
    }
    int eval = st.top();
    st.pop();
    return eval;
}
// aabbbdddadd
string deleteDuplicate(string s, int k) {
    stack<pair<char,int>> st;
    for(char c: s){
        if(!st.empty() && c==st.top().first){
            st.top().second++;  
        }else st.push(make_pair(c,1));

        if(st.top().second==k) st.pop();
    }

    string result("");
    while(!st.empty()){
        result+=string(st.top().second, st.top().first);
        st.pop();
    }
    return reversal(result);
}

bool tripleIndexSLM(vector<int>& nums) {
    // STUDENT ANSWER
}

int main(){
    string s = "aabbbdddadd";
int k = 3;
cout << deleteDuplicate(s, k);
    
    return 0;
}

