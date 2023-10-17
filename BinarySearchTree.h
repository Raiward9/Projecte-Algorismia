#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

template <typename T> 
class BinSearchTree {
public:
	// Pre: 0 < k
	// Crea un arbre buit de k-dimensions
	BinSearchTree(unsigned int k) {
		n = 0;					
		this->k = k;			
		root = nullptr;
	}

	// Copy constructor, needed for deep copies
	/*	Automatically called when the object is:
			-passed as a value parameter to a function,
			-returned (by value) as a function result,
			-declared with initialization from an existing object of the same class.

		For more info: https://pages.cs.wisc.edu/~hasti/cs368/CppTutorial/NOTES/CLASSES-PTRS.html#copyCons
	*/
	BinSearchTree(const BinSearchTree<T>& ref) {
		deepCopy(ref);
	}
	
	// Assignment constructor, to avoid dangling pointers when the referenced object to assign is deleted, deep copy is needed
	/*	Automatically called when an object is assigned to another object
		For more info: https://pages.cs.wisc.edu/~hasti/cs368/CppTutorial/NOTES/CLASSES-PTRS.html#assign
	*/
	BinSearchTree<T> & operator=(const BinSearchTree<T> &ref) {
		// check for "self assignment" and do nothing in that case
		if (this == &ref) return *this;
		else {
			delete root; // free the storage
			deepCopy(ref);
			return *this;
		}
	}

	// Destructora
	~BinSearchTree() {
		delete root;
	}
	
	// Pre la clau té mida k
	// Insereix x a l'arbre seguint la clau
	void insert(const T& info, const vector<double>& key) {
		if (key.size() != k) throw invalid_argument("BinSearchTree::insert key must be of size k");

		for(auto x: key) 
			if(x < 0 or x > 1) throw invalid_argument("BinSearchTree::all key values must between 0 and 1 (included)");
		

		if (empty(root)) root = new node(info, key);
		else {
			int level = 0;
			node* a = root;
			bool found = false;
			while (not found) {
				if (key[level%k] <= a->key[level%k]) {
					if (empty(a->left)) {
						node* newnode = new node(info, key);
						a->left = newnode;
						found = true;
					}	
					else a = a->left;
				}
				else {
					if (empty(a->right)) {
						node* newnode = new node(info, key);
						a->right = newnode;
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

	pair<double, vector<double>> ideal_euclidean_keys(const vector<double>& p) {
		vector<vector<double>> ks = keys();
		double best_euclidean_dist = p.size() + 1;
		vector<double> best_point;
		for(auto x: ks) {
			double new_dist = euclideanDist(x, p);
			if(best_euclidean_dist >= new_dist) {
				best_euclidean_dist = new_dist;
				best_point = x;
			}
		}
		pair<double, vector<double>> res = {best_euclidean_dist, best_point};
		return res;
	}

	void list_keys() {
		vector<vector<double>> ks = keys();
		for(int i = 0; i < ks.size(); ++i) {
			cout << i+1 << ": ";
			for(int j = 0; j < ks[i].size(); ++j) {
				cout << ks[i][j] << ' ';
			}
			cout << endl;
		}
	}

	// Pre: p.size() == k
	// Returns the closest point from p in the tree by euclidean distance and the number of nodes visited in the process
	pair<int, vector<double>> nearestNeighbour(const vector<double>& p) {
		
		vector<double> closestPoint = closest_leaf(p, root, 0)->key;
		double distClosestPoint = euclideanDist(closestPoint,p);
		int numNodes = 0;
		nearestNeighbourRecursive(p,root,closestPoint,distClosestPoint,numNodes,0);

		//cout << "Distance from p: " << distClosestPoint << endl;
		pair<int, vector<double>> res = {numNodes, closestPoint};
		return res;
	}

private:
	struct node {
		T info;
		vector<double> key;
		node* left;
		node* right;

		node(const T& i, const vector<double>& k) {
			info = i;
			key = k;
			left = nullptr;
			right = nullptr; 
		}

		~node() {
			if (not empty(left)) delete left;
			if (not empty(right)) delete right;
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

	//recorre l'arbre fins trobar la fulla on hauria d'anar p
	node* closest_leaf(const vector<double>& p, node* a, int level) {
		if(is_leaf(a)) return a;
		
		int discriminant = level % k;
		if(a->key[discriminant] >= p[discriminant]) {
			if(empty(a->left)) return a;
			else return closest_leaf(p, a->left, level+1);
		}
		else {
			if(empty(a->right)) return a;
			else return closest_leaf(p, a->right, level+1);
		}
	}

	
	//Returns true if the node is a leaf, false otherwise
	bool is_leaf(node* a) {
		return not empty(a) and empty(a->left) and empty(a->right);
	}

	
	// recursively finds the nearest neighbour
	void nearestNeighbourRecursive(const vector<double>& p, node* x,  vector<double>& closestPoint, 
								 double& distClosestPoint, int& numNodes, int level) {
			
		if(not empty(x)) { 
			int discriminant = level % k;
			double newDist = euclideanDist(x->key, p);
			if (newDist < distClosestPoint) {
				closestPoint = x->key;
				distClosestPoint = newDist;
			}
			
			if (distClosestPoint > (absValue(p[discriminant] - x->key[discriminant]))) {
				nearestNeighbourRecursive(p,x->left,closestPoint,distClosestPoint,numNodes,level+1);
				nearestNeighbourRecursive(p,x->right,closestPoint,distClosestPoint,numNodes,level+1);
			}
			else {
				if (x->key[discriminant] - p[discriminant] > double(0)) nearestNeighbourRecursive(p,x->left,closestPoint,distClosestPoint,numNodes,level+1);
				else nearestNeighbourRecursive(p,x->right,closestPoint,distClosestPoint,numNodes,level+1);
			}

			++numNodes;
		}
	}

	//Retorna totes les keys de l'arbre
	vector<vector<double>> keys() {
		vector<vector<double>> ks;
		keys_rec(root, ks);
		return ks;
	}

	//Crida recursiva per calcular les keys de l'arbre
	void keys_rec(const node* a, vector<vector<double>>& keys) {
		if(not empty(a)) keys.push_back(a->key);
		else return;

		keys_rec(a->left, keys);
		keys_rec(a->right, keys);
	}

	// pre: p1.size() == p2.size() > 0
	// calculates euclidean distance d(p1,p2) in the respective number of dimensions
	double euclideanDist(const vector<double>& p1, const vector<double>& p2) {
		int dim = p1.size();
		double sum = 0.0;
		for (int i = 0; i < dim; ++i) {
			double diff = p2[i] - p1[i];
			sum += diff*diff;
		}
		return sqrt(sum);
	}

	double absValue(double x) {
		if (x < double(0)) return -x;
		return x;
	}

	void deepCopy(const BinSearchTree<T>& ref) {
		k = ref.k;
		n = ref.n;
		if (not empty(ref.root)) {
			root = new node(ref.root->info, ref.root->key);
			recursiveCopy(ref.root, root);
		}
	}

	void recursiveCopy(node* refNode, node* copyNode) {
		if (not empty(refNode->left)) {
			copyNode->left = new node(refNode->left->info, refNode->left->key);
			recursiveCopy(refNode->left, copyNode->left);
		}
		if (not empty(refNode->right)) {
			copyNode->right = new node(refNode->right->info, refNode->right->key);
			recursiveCopy(refNode->right, copyNode->right);
		}
	}

	node* root;
	int n;
	unsigned int k;
};
