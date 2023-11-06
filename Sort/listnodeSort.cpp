#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int _val = 0, ListNode* _next = nullptr) : val(_val), next(_next) { }
};

void Add(ListNode* &head, int val){
    if(!head) head = new ListNode(val);
    else{
        ListNode* cur = head;
        while(cur->next){
            cur=cur->next;
        }
        cur->next = new ListNode(val);
    }
}

void printList(ListNode* head){
    if(!head) { cout<<"NULL"<<endl; return;}
    ListNode* cur = head;
    while(cur){
        cout<<cur->val<<" ";
        cur=cur->next;
    }
    cout<<endl;
}
// You must use the nodes in the original list and must not modify ListNode's val attribute. 
// Hint: You should complete the function mergeLists first and validate it using our first testcase example

// Merge two sorted lists
ListNode* mergeLists(ListNode* a, ListNode* b) {
    ListNode* tmp = new ListNode();
    ListNode* cur = tmp;
    while(a && b){
        if(a->val<b->val){
            cur->next = a;
            a = a->next;
        }else{
            cur->next = b;
            b=b->next;
        }
        cur=cur->next;
    }
    
    if(a) cur->next=a;
    else if(b) cur->next = b;
    return tmp->next;
}

ListNode* middle(ListNode* head){
    ListNode* slow = head;
    ListNode* fast = head->next;
 
    while (slow->next && (fast && fast->next)) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
// Sort and unsorted list given its head pointer
ListNode* mergeSortList(ListNode* head) {
    if(!head || !head->next) return head;
    ListNode* mid = middle(head);
    ListNode* a = head;
    ListNode* b = mid->next;
    mid->next = nullptr; //split list

    //recusion mergesort
    a = mergeSortList(a);
    b = mergeSortList(b);

    // merge list sorted
    return mergeLists(a,b);
}

int main(){
    int arr1[] = {9, 3, 8 ,2 ,1, 6, 7, 4, 5 };
    ListNode* a = nullptr, *b=nullptr;
    for(int i=0;i<9;i++) Add(a,arr1[i]);
    printList(a);
    ListNode* sort = mergeSortList(a);
    printList(sort);
    return 0;
}