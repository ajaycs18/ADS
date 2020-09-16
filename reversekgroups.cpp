#include<iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
 };
 
 ListNode* reverseKGroup(ListNode* head, int k) {
  if (!head || k == 1) return head;

  ListNode *dummy = new ListNode(-1);
  dummy->next = head;
  ListNode *curr = dummy, *next, *prev = dummy;

  int dist = 0;
  while((curr = curr->next)) 
    dist++;

  while(dist >= k) {
    curr = prev->next;
    next = curr->next;
    for(int i = 1; i < k; ++i) {
      curr->next = next->next;
      next->next = prev->next;
      prev->next = next;
      next = curr->next;
    }
    prev = curr;
    dist -= k;
  }

  return dummy->next;
}
 
 int main() {
  ListNode* head = new ListNode();
  cout << "Enter number of nodes: ";
  int n;
  cin >> n;
  ListNode* curr = head;
  cout << "Enter the nodes: " << endl;
  while (n--) {
    cin >> curr->val;
    if (n) {    
      curr->next = new ListNode();
      curr = curr->next;
    }
  }
  cout << "Enter k: ";
  int k;
  cin >> k;
  
  head = reverseKGroup(head, k);
  
  cout << "Reversed List: " << endl;
  curr = head;
  while (curr) {
    cout << curr->val << ' ';
    curr = curr->next;
  }
  
  return 0;
}
