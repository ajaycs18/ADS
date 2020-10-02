#include <bits/stdc++.h>
#define inf 1e9
using namespace std;

struct Node {
  int key;
  Node *prev, *next, *above, *below;

  Node() : key(-inf), prev(NULL), next(new Node(inf)), above(NULL), below(NULL) {}
  Node(int key) : key(key), prev(NULL), next(NULL), above(NULL), below(NULL) {}
};

class SkipList {
  Node* head;
  int height;

  int getRandomLevel(int height) {
    return rand() % height + 1;
  }

 public:
  SkipList(int height) : height(height) {
    head = new Node();
    Node* curr = head;
    for (int i = 0; i < height; ++i) {
      curr->below = new Node();
      curr->next->below = curr->below->next, curr->next->prev = curr;
      curr->below->above = curr;
      curr = curr->below;
      curr->next->above = curr->above->next;
    }
  }

  Node* search(int key) {
    Node* curr = head;
    while (curr->below) {
      curr = curr->below;
      while (curr->next && curr->next->key <= key)
        curr = curr->next;
    }
    return curr;
  }

  void insert(int key) {
    Node *prev = search(key), *node = new Node(key), *below = NULL;
    int level = getRandomLevel(height);
    while (level--) {
      node->next = prev->next, node->prev = prev;
      prev->next->prev = node, prev->next = node;
      node->above = level ? new Node(key) : NULL, node->below = below;
      below = node, node = node->above;
      while (level && !prev->above)
        prev = prev->prev;
      prev = prev->above;
    }
  }

  bool remove(int key) {
    Node* node = search(key);
    if (node->key != key)
      return false;
    while (node) {
      node->prev->next = node->next, node->next->prev = node->prev;
      Node* toDelete = node;
      node = node->above;
      delete toDelete;
    }
    return true;
  }

  void displayList() {
    Node* level = head;
    int height = SkipList::height;
    while (level->below) {
      level = level->below;
      Node* curr = level;
      cout << height-- << ": ";
      while (curr) {
        cout << (curr->key == inf ? "inf" : (curr->key == -inf ? "-inf" : to_string(curr->key))) << ' ';
        curr = curr->next;
      }
      cout << '\n';
    }
  }
};

int main() {
  srand(time(0));

  cout << "Enter height: ";
  int height; cin >> height;
  
  SkipList sl(height);
  
  int choice, n;
  bool run = true;
  while (run) {
    cout << "1.Insert Element\n";
    cout << "2.Delete Element\n";
    cout << "3.Search Element\n";
    cout << "4.Display List\n";
    cout << "5.Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch(choice) {
      case 1:
        cout << "Enter the element to be inserted: ";
        cin >> n;
        sl.insert(n);
        cout << n << " inserted.";
        break;
      case 2:
        cout << "Enter the element to be deleted: ";
        cin >> n;
        if (sl.remove(n)) cout << n << " removed.";
        else cout << n << " not found.";
        break;
      case 3:
        cout << "Enter the element to be searched: ";
        cin >> n; 
        if (sl.search(n)->key == n) cout << n << " found.";
        else cout << n << " not found."
        break;
      case 4:
        cout << "The List is: ";
        sl.displayList();
        break;
      case 5:
        run = false;
        break;
      default:
        cout << "Wrong Choice";
    }
    cout << '\n';
  }

  return 0;
}
