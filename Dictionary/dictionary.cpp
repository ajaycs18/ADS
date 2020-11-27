#include<bits/stdc++.h> 
using namespace std; 

class Dictionary { 
	int size;
	vector<list<pair<int ,int>>> table; 

public: 
	Dictionary(int n) {
    size = n; 
    table = vector<list<pair<int, int>>>(n);
  }

	void insertItem(int key, int value) {
    int index = hash(key); 
	  table[index].push_back({key, value});
  } 

	void deleteItem(int key) {
    int index = hash(key); 
    for (auto it = table[index].begin(); it != table[index].end(); it++) if (it->first == key) {
      table[index].erase(it);
      break;
    }
  }

	int hash(int x) { 
		return (x % size); 
	} 

	void displayHash() {
    for (int i = 0; i < size; i++) { 
      cout << i; 
      for (auto x : table[i]) 
        cout << " --> <" << x.first << ", " << x.second << ">"; 
      cout << endl; 
    } 
  } 
}; 

int main() { 
  Dictionary dict(7);
  bool run = true; 
  
  while (run) {
    cout << "1. Insert" << endl
         << "2. Delete" << endl
         << "3. Display" << endl
         << "4. Exit" << endl
         << "Option: ";
    int option, k, v; cin >> option;
    switch (option) {
      case 1:
        cout << "Enter [key] [value]: ";
        cin >> k >> v;
        dict.insertItem(k, v);
        break;
      case 2:
        cout << "Enter [key]: ";
        cin >> k;
        dict.deleteItem(k);
        break;
      case 3:
        dict.displayHash();
        break;
      default:
        run = false;
    }
  } 

  return 0; 
} 
