#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};

class RedBlackTree {
private:
  Node* root;
  Node* TNULL;

  void insertFix(Node* k) {
    Node* u;
    while (k->parent->color == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;
        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root) break;
    }
    root->color = 0;
  }

  void printHelper(Node* root, string indent, bool last) {
    if (root != TNULL) {
      cout << indent;
      if (last) {
        cout << "R----";
        indent += "   ";
      } else {
        cout << "L----";
        indent += "|  ";
      }

      string sColor = root->color ? "RED" : "BLACK";
      cout << root->data << "(" << sColor << ")" << endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }

public:
  RedBlackTree() {
    TNULL = new Node;
    TNULL->color = 0;
    TNULL->left = NULL;
    TNULL->right = NULL;
    root = TNULL;
  }

  void leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != TNULL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) this->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
  }

  void rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != TNULL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) this->root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
  }

  void insert(int key) {
    Node* node = new Node;
    node->parent = NULL;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;
    Node* y = NULL;
    Node* x = this->root;
    while (x != TNULL) {
      y = x;
      if (node->data < x->data) x = x->left;
      else  x = x->right;
    }
    node->parent = y;
    if (y == NULL) root = node;
    else if (node->data < y->data) y->left = node;
    else y->right = node;
    if (node->parent == NULL) {
      node->color = 0;
      return;
    }
    if (node->parent->parent == NULL) return;
    insertFix(node);
  }

  void printTree() {
    if (root) {
      printHelper(this->root, "", true);
    }
  }
};

int main() {
  RedBlackTree bst;
  cout << "Enter number of nodes to insert: ";
  int n; cin >> n;
  while (n--) {
    cout << "Enter node: ";
    int key; cin >> key;
    bst.insert(key);
    bst.printTree();
  }

  return 0;
}
