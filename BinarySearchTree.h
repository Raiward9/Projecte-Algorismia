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
						newnode->parent = a;
						found = true;
					}	
					else a = a->left;
				}
				else {
					if (empty(a->right)) {
						node* newnode = new node(info, key);
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
	// Returns the closest point from p in the tree by euclidean distance
	vector<double> nearestNeighbour(const vector<double>& p) {
		//if (empty(root)) 
		vector<double> closestPoint = root->key;
		double distClosestPoint = euclideanDist(root->key,p);
		int numNodes = 0;
		nearestNeighbourRecursive(p,root,closestPoint,distClosestPoint,numNodes,0);

		cout << "Distance from p: " << distClosestPoint << endl;
		cout << "Number of visited nodes: " << numNodes << endl;
		return closestPoint;
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

	void nearestNeighbourRecursive(const vector<double>& p, node* x,  vector<double>& closestPoint, 
								 double& distClosestPoint, int& numNodes, int level) {
			
		if(not empty(x)) { 
			int discriminant = level % k;
			double newDist = euclideanDist(x->key, p);
			if(newDist <= distClosestPoint) { //d(q, x) < d(q, closestPoint)
				closestPoint = x->key;
				distClosestPoint = newDist;
				nearestNeighbourRecursive(p,x->left,closestPoint,distClosestPoint,numNodes,level+1);
				nearestNeighbourRecursive(p,x->right,closestPoint,distClosestPoint,numNodes,level+1);
			}
			else if(level <= k) {
				nearestNeighbourRecursive(p,x->left,closestPoint,distClosestPoint,numNodes,level+1);
				nearestNeighbourRecursive(p,x->right,closestPoint,distClosestPoint,numNodes,level+1);
			}
			else if(p[discriminant] > x->key[discriminant]) //d(q,x) > d(q,closestPoint) and p[disc] > x[disc] (els mes semblants estan a drt de x)
				nearestNeighbourRecursive(p,x->right,closestPoint,distClosestPoint,numNodes,level+1);
			
			else if(p[discriminant] < x->key[discriminant]) //d(q,x) > d(q,closestPoint) and p[disc] < x[disc] (els mes semblants estan a esq de x)
				nearestNeighbourRecursive(p,x->left,closestPoint,distClosestPoint,numNodes,level+1);
			
			else { //d(q,x) > d(q,closestPoint) and p[disc] == x[disc] (els mes semblants a p podrien estar a esq o drt)
				nearestNeighbourRecursive(p,x->left,closestPoint,distClosestPoint,numNodes,level+1);
				nearestNeighbourRecursive(p,x->right,closestPoint,distClosestPoint,numNodes,level+1);
			}

			++numNodes;
		}
	}

	vector<vector<double>> keys() {
		vector<vector<double>> ks;
		keys_rec(root, ks);
		return ks;
	}

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

	BinSearchTree<T> operator=(const BinSearchTree<T>& other) {
		this->root = other.root;
		this->n = other.n;
		this->k = other.k;
		return *this;
	}

	node* root;
	int n;
	unsigned int k;
};
