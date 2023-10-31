#include<iostream>
#include<stdlib.h>
#include<unordered_map>
using namespace std;

struct ListNode {
    int val;
    ListNode *left;
    ListNode *right;
    ListNode(int x = 0, ListNode *l = nullptr, ListNode* r = nullptr) : val(x), left(l), right(r) {}
};

ListNode* reverse(ListNode* head, int a, int b) {
    //To Do
    if (a == b || head == nullptr) return head;
    ListNode* tmpl = nullptr;
    ListNode* tmpr = nullptr;
    ListNode* newlist = head;
    ListNode* cur = head;
    ListNode* pre = nullptr;
    int idx = 1;

    while(cur){
        if(idx==a){
            tmpl = cur->left;
            pre = cur;
        }else if(idx==b){
            tmpr = cur->right;
            break;
        }
        cur = cur->right;
        idx++;
    }
    pre->left = nullptr; cur->right = nullptr;
    ListNode* p =pre;
    while(p!=cur){
        ListNode* temp =p->left;
        p->left = p->right;
        p->right = temp;
        p=p->left;
    }
    cur->left = tmpl;
    pre->right = tmpr;
    tmpl->right = cur;
    tmpr->left = pre;
    return newlist;

}

int main(){
    int size;
    cin >> size;
    int* list = new int[size];
    for(int i = 0; i < size; i++) {
        cin >> list[i];
    }
    int a, b;
    cin >> a >> b;
    unordered_map<ListNode*, int> nodeValue;
    ListNode* head = init(list, size, nodeValue);
    ListNode* reversed = reverse(head, a, b);
    try {
        printList(reversed, nodeValue);
    }
    catch(char const* err) {
        cout << err << '\n';
    }
    freeMem(head);
    delete[] list;
    return 0;
}