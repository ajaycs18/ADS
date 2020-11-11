#include <iostream>
using namespace std;

class Node {
  int *keys;
  int degree;
  Node **C;
  int n;
  bool leaf;

   public:
  Node(int, bool);

  void insertNonFull(int);
  void splitChild(int, Node *);
  void traverse();

  friend class BTree;
};

class BTree {
  Node *root;
  int degree;

  public:
  BTree(int deg) {
    root = NULL;
    degree = deg;
  }

  void traverse() {
    if (root != NULL)
      root->traverse();
  }

  void insert(int);
};

Node::Node(int t1, bool leaf1) {
  degree = t1;
  leaf = leaf1;

  keys = new int[2 * degree - 1];
  C = new Node *[2 * degree];

  n = 0;
}

void Node::traverse() {
  int i;
  for (i = 0; i < n; i++) {
    if (leaf == false)
      C[i]->traverse();
    cout << " " << keys[i];
  }

  if (leaf == false)
    C[i]->traverse();
}

void BTree::insert(int k) {
  if (root == NULL) {
    root = new Node(degree, true);
    root->keys[0] = k;
    root->n = 1;
  } else {
    if (root->n == 2 * degree - 1) {
      Node *s = new Node(degree, false);

      s->C[0] = root;

      s->splitChild(0, root);

      int i = 0;
      if (s->keys[0] < k)
        i++;
      s->C[i]->insertNonFull(k);

      root = s;
    } else
      root->insertNonFull(k);
  }
}

void Node::insertNonFull(int k) {
  int i = n - 1;

  if (leaf == true) {
    while (i >= 0 && keys[i] > k) {
      keys[i + 1] = keys[i];
      i--;
    }

    keys[i + 1] = k;
    n = n + 1;
  } else {
    while (i >= 0 && keys[i] > k)
      i--;

    if (C[i + 1]->n == 2 * degree - 1) {
      splitChild(i + 1, C[i + 1]);

      if (keys[i + 1] < k)
        i++;
    }
    C[i + 1]->insertNonFull(k);
  }
}

void Node::splitChild(int i, Node *y) {
  Node *z = new Node(y->degree, y->leaf);
  z->n = degree - 1;

  for (int j = 0; j < degree - 1; j++)
    z->keys[j] = y->keys[j + degree];

  if (y->leaf == false) {
    for (int j = 0; j < degree; j++)
      z->C[j] = y->C[j + degree];
  }

  y->n = degree - 1;
  for (int j = n; j >= i + 1; j--)
    C[j + 1] = C[j];

  C[i + 1] = z;

  for (int j = n - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = y->keys[degree - 1];
  n = n + 1;
}

int main() {
  cout << "Enter degree of B-Tree: ";
  int deg; cin >> deg;

  BTree tree(deg);

  cout << "Enter number of values to insert: ";
  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    cout << "Enter value " << i+1 << " : ";
    int val; cin >> val;
    tree.insert(val);
    cout << "Tree after inserting " << val << endl;
    tree.traverse();
    cout << endl;
  }

  return 0;
}
