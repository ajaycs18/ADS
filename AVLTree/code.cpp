#include <bits/stdc++.h>

using namespace std;

class Node {
public:
  int key;
  Node* left, *right;
  int height;

  Node(int key): key(key), height(1), left(NULL), right(NULL) {}

  static int getHeight(Node* node) {
    if (!node) return 0;
    else return node->height;
  }

  Node* rightRotate() {
    Node* x = left, *xRight = x->right;
    x->right = this;
    left = xRight;
    height = max(getHeight(left), getHeight(right)) + 1; 
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
  }

  Node* leftRotate() {
    Node* x = right, *xLeft= x->left;
    x->left = this;
    right = xLeft;
    height = max(getHeight(left), getHeight(right)) + 1; 
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
  }

  int getBalanceFactor() {
    return getHeight(left) - getHeight(right);
  } 

  Node* inorderSuccessor() {
    Node* curr = this->right;
    while (curr->left) curr = curr->left;
    return curr;
  }
};

Node *insertNode(Node* node, int key) {
  if (!node) return new Node(key);
  else if (key < node->key) node->left = insertNode(node->left, key);
  else if (key > node->key) node->right = insertNode(node->right, key);
  else return node;

  node->height = max(Node::getHeight(node->left), Node::getHeight(node->right)) + 1;
  int balanceFactor = node->getBalanceFactor();

  if (balanceFactor > 1) {
    if (key > node->left->key) node->left = node->left->leftRotate();
    return node->rightRotate();
  } else if (balanceFactor < -1) {
    if (key < node->right->key) node->right = node->right->rightRotate();
    return node->leftRotate();
  } else {
    return node;
  }
}

Node *deleteNode(Node* node, int key) {
  if (!node) return NULL;
  else if (key < node->key) node->left = deleteNode(node->left, key);
  else if (key > node->key) node->right = deleteNode(node->right, key);
  else {
    if (!node->left || !node->right) {
      Node* temp = node->left ? node->left : node->right;
      if (!temp) {
        delete node;
        return NULL;
      }
      *node = *temp;
      delete temp;
    } else {
      Node* successor = node->inorderSuccessor();
      node->key = successor->key;
      node->right = deleteNode(node->right, successor->key);
    }

    node->height = max(Node::getHeight(node->left), Node::getHeight(node->right)) + 1;
    int balanceFactor = node->getBalanceFactor();

    if (balanceFactor > 1) {
      if (node->left->getBalanceFactor() < 0) node->left = node->left->leftRotate();
      return node->rightRotate();
    } 
    if (balanceFactor < -1) {
      if (node->right->getBalanceFactor() > 0) node->right = node->right->rightRotate();
      return node->leftRotate();
    }
  }

  return node;
}

void printTree(Node* root, bool inorder) {
  if (!root) return;

  if (!inorder) cout << root->key << ' ';
  printTree(root->left, inorder);
  if (inorder) cout << root->key << ' ';
  printTree(root->right, inorder);
}

int main() {
  Node* root = NULL;
  bool run = true;

  while (run) { 
    int choice;
    cout << "1. Insert\n" 
         << "2. Delete\n" 
         << "3. Print Tree (Inorder & Preorder)\n" 
         << "4. Exit\n";
    cout << "Choice: "; cin >> choice;
    switch (choice) {
      int e; 
      case 1:
        cout << "Element to Insert: "; cin >> e;
        root = insertNode(root, e);
        break;
      case 2:
        cout << "Element to Delete: "; cin >> e;
        root = deleteNode(root, e);
        break;
      case 3:
        printTree(root, true);
        cout << endl;
        printTree(root, false);
        cout << endl;
        break;
      default:
        run = false;
    }
  }

  return 0;
}
