#include<bits/stdc++.h> 
using namespace std; 

struct Node 
{ 
	int data, degree; 
	Node *child, *sibling, *parent; 

  Node(int key) {
    data = key, degree = 0;
    child = parent = sibling = NULL;
  }
}; 

Node* mergeBinomialTrees(Node *b1, Node *b2) 
{ 
	if (b1->data > b2->data) 
		swap(b1, b2); 
	b2->parent = b1; 
	b2->sibling = b1->child; 
	b1->child = b2; 
	b1->degree++; 

	return b1; 
} 

list<Node*> unionBionomialHeap(list<Node*> l1, list<Node*> l2)
{ 
	list<Node*> _new; 
	auto it = l1.begin(), ot = l2.begin(); 
	while (it!=l1.end() && ot!=l2.end()) 
	{ 
		if((*it)->degree <= (*ot)->degree) 
		{ 
			_new.push_back(*it); 
			it++; 
		} 
		else
		{ 
			_new.push_back(*ot); 
			ot++; 
		} 
	} 
	while (it != l1.end()) 
	{ 
		_new.push_back(*it); 
		it++; 
	} 
	while (ot!=l2.end()) 
	{ 
		_new.push_back(*ot); 
		ot++; 
	} 
	return _new; 
} 

list<Node*> adjust(list<Node*> _heap) 
{ 
	if (_heap.size() <= 1) 
		return _heap; 
	list<Node*> new_heap; 
	auto it1 = _heap.begin(), it2 = _heap.begin(), it3 = _heap.begin(); 
	if (_heap.size() == 2) 
	{ 
		it2 = it1; 
		it2++; 
		it3 = _heap.end(); 
	} 
	else
	{ 
		it2++; 
		it3=it2; 
		it3++; 
	} 
	while (it1 != _heap.end()) 
	{ 
		if (it2 == _heap.end()) it1++; 
		else if ((*it1)->degree < (*it2)->degree) 
		{ 
			it1++; 
			it2++; 
			if(it3!=_heap.end()) it3++; 
		} 
		else if (it3!=_heap.end() && (*it1)->degree == (*it2)->degree && (*it1)->degree == (*it3)->degree)
		{ 
			it1++; 
			it2++; 
			it3++; 
		} 
		else if ((*it1)->degree == (*it2)->degree) 
		{ 
			Node *temp; 
			*it1 = mergeBinomialTrees(*it1,*it2); 
			it2 = _heap.erase(it2); 
			if(it3 != _heap.end()) 
				it3++; 
		} 
	} 
	return _heap; 
} 

list<Node*> insertATreeInHeap(list<Node*> _heap, Node *tree) 
{ 
	list<Node*> temp; 
	temp.push_back(tree); 
	temp = unionBionomialHeap(_heap,temp); 
	return adjust(temp); 
} 

list<Node*> removeMinFromTreeReturnBHeap(Node *tree) 
{ 
	list<Node*> heap; 
	Node *temp = tree->child; 
	Node *lo; 

	while (temp) 
	{ 
		lo = temp; 
		temp = temp->sibling; 
		lo->sibling = NULL; 
		heap.push_front(lo); 
	} 
	return heap; 
} 

list<Node*> insert(list<Node*> _head, int key) 
{ 
	Node *temp = new Node(key); 
	return insertATreeInHeap(_head,temp); 
} 

Node* getMin(list<Node*> _heap) 
{ 
	auto it = _heap.begin(); 
	Node *temp = *it; 
	while (it != _heap.end()) 
	{ 
		if ((*it)->data < temp->data) 
			temp = *it; 
		it++; 
	} 
	return temp; 
} 

list<Node*> extractMin(list<Node*> _heap) 
{ 
	list<Node*> new_heap,lo; 
	Node *temp; 

	temp = getMin(_heap); 
	auto it =_heap.begin(); 
	while (it != _heap.end()) 
	{ 
		if (*it != temp) 
		{ 
			new_heap.push_back(*it); 
		} 
		it++; 
	} 
	lo = removeMinFromTreeReturnBHeap(temp); 
	new_heap = unionBionomialHeap(new_heap,lo); 
	new_heap = adjust(new_heap); 
	return new_heap; 
} 

void printTree(Node *h) 
{ 
	while (h) 
	{ 
		cout << h->data << " "; 
		printTree(h->child); 
		h = h->sibling; 
	} 
} 

void printHeap(list<Node*> _heap) 
{ 
	auto it = _heap.begin(); 
	while (it != _heap.end()) 
	{ 
		printTree(*it); 
		it++; 
	} 
} 

int main() 
{ 
	int ch, key; 
  bool run = true;
	list<Node*> heap; 

  while(run) {
    cout << "1. Insert" << endl
         << "2. Get Min" << endl
         << "3. Delete Min (Extract Min)" << endl
         << "4. Print Binomial Heap" << endl
         << "5. Exit" << endl
         << "Option: ";
    int option, k; cin >> option;
    switch (option) {
      case 1:
        cout << "Enter key: ";
        cin >> k;
        heap = insert(heap, k);
        break;
      case 2:
        cout << "Min: " << getMin(heap)->data << endl;
        break;
      case 3:
        cout << "Min " << getMin(heap)->data << " extracted" << endl;
        heap = extractMin(heap);
        break;
      case 4:
        cout << "Heap is: " << endl;
        printHeap(heap);
        cout << endl;
        break;
      default:
        run = false;
    }
  } 

	return 0; 
} 
