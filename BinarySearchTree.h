#include <vector>
#include <iostream>
using namespace std;


class test {};

template <typename T> class BinSearchTree {
public:
	// Pre: 0 < k
	// Crea un arbre buit de k-dimensions
	BinSearchTree(unsigned int k) {
		n = 0;
		this->k = k;
		root = nullptr;
	}
	
	// Destructora
	~BinSearchTree() {
		delete root;
	}
	
	// Pre la clau té mida k
	// Insereix x a l'arbre seguint la clau
	void insert(const T& x, const vector<double>& key) {
		if (key.size() != k) throw invalid_argument("BinSearchTree::insert key must be of size k");
		if (empty(root)) root = new node(x, key);
		else {
			int level = 0;
			node* a = root;
			bool found = false;
			while (not found) {
				if (key[level%k] <= a->key[level%k]) {
					if (empty(a->left)) {
						node* newnode = new node(x, key);
						a->left = newnode;
						newnode->parent = a;
						found = true;
					}	
					else a = a->left;
				}
				else {
					if (empty(a->right)) {
						node* newnode = new node(x, key);
						a->right = newnode;
						newnode->parent = a;
						found = true;
					}
					else a = a->right;
				}
				++level;
			}

		}
		++n;
	}
	

	// Prints tree in readable format
	void print_tree() {
		vector<bool> l;
		print_tree_rec(root, 0, l);
	}
	

private:
	struct node {
		T info;
		vector<double> key;
		node* parent;
		node* left;
		node* right;

		node(const T& i, const vector<double>& k) {
			info = i;
			key = k;
		}

		~node() {
			if (empty(left)) delete left;
			if (empty(right)) delete right;
		}
	};

	static bool empty(const node* n) {
		return n == nullptr;
	}

	static void print_tree_rec(node* a, int level, vector<bool>& l) {
		for (int i = 0; i < level-1; ++i) {
			if (l[i]) cout << "| ";
			else cout << "  ";
		}
		if (level != 0) cout << (l[level-1] ? "├─" : "└─");
		if (not empty(a)) {
			cout << a->info << " {";
			for (int i = 0; i < a->key.size()-1; ++i) {
				cout << a->key[i] << ", ";
			}
			cout << a->key[a->key.size()-1] << "}";
			cout << endl;
			if (not (empty(a->left) and empty(a->right))) {
				l.push_back(true);
				print_tree_rec(a->left, level+1, l);
				l[l.size()-1] = false;
				print_tree_rec(a->right, level+1, l);
				l.pop_back();
			}
		}
		else cout << endl;
	}
	// Prints tree from provided in readable format

	node* root;
	int n;
	unsigned int k;
};
