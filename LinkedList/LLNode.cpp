#include<iostream>
#include<stack>
using namespace std;

class LLNode {
public:
    int val;
    LLNode* next;
    LLNode(): val(0), next(nullptr){} // Constructor: val = 0, next = nullptr
    LLNode(int val, LLNode* next): val(val), next(next){} // Constructor with customized data
    LLNode* reverseLinkedList(LLNode* head);
    LLNode* rotateLinkedList(LLNode* head, int k);
    LLNode* foldLinkedList(LLNode* head);
    LLNode* replaceFirstGreater(LLNode* head);
};

LLNode* reverseLinkedList(LLNode* head) {
    // STUDENT ANSWER
    int arr[100001];
    int i=0;
    LLNode* cur = head;
    while(cur){
        arr[i++]=cur->val;
        cur = cur->next;
    }
    cur = head;
    while(i>0){
        cur->val = arr[--i];
        cur = cur->next;
    }
    return head;
}

LLNode* rotateLinkedList(LLNode* head, int k) {
    // STUDENT ANSWER
    if(head==NULL) return head;
    while(k>0){
        LLNode* cur = head->next;
        LLNode* pre = head;
        while(cur && cur->next){
            pre = cur;
            cur = cur->next;
        }
        cur->next= head;
        pre->next = NULL;
        head = cur;
        k--;
    }
    return head;
}

LLNode* foldLinkedList(LLNode* head){
    int arr[100001];
    LLNode* cur = head;
    int i=0, s=0;
    while(cur){
        arr[i++] = cur->val;
        cur = cur->next;
    }
    LLNode* newnode = new LLNode();
    LLNode* temp = newnode;
    int e = i-1;
    while(e>s){
        newnode->next = new LLNode(arr[e--]+arr[s++], nullptr);
        newnode = newnode->next;
    }
    if(e==s) newnode->next = new LLNode(arr[s],nullptr);
    temp = temp->next;
    return reverseLinkedList(temp);
}

LLNode* replaceFirstGreater(LLNode* head) {
    if(head==NULL) return head;
    
    stack<LLNode*> st;
    LLNode* cur = head;
    
    while (cur) {
        while (!st.empty() && st.top()->val < cur->val) {
            st.top()->val = cur->val;
            st.pop();
        }
        st.push(cur);
        cur = cur->next;
    }
    
    while (!st.empty()) {
        st.top()->val = 0;
        st.pop();
    }
    return head;
}

int main(){
    int arr[] = {13, 88, 60, 7, 192};
    LLNode* head = LLNode::createWithIterators(arr, arr + sizeof(arr) / sizeof(int));
    LLNode::printList(head);
    cout << "\n";
    LLNode* newhead = reverseLinkedList(head);
    LLNode::printList(newhead);
    newhead->clear();
    return 0;
}