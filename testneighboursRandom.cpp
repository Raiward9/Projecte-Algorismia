#include "BinarySearchTreeGenerator2.h"
using namespace std;

int main() {
    int num_examples = 0, k = 1, n = 1;

    cout << "Quants exemples vols? : ";
    cin >> num_examples;
    cout << endl;

    cout << "De quantes dimensions han de ser les claus? : ";
    cin >> k;
    cout << endl;

    cout << "Quants nodes cal inserir? : ";
    cin >> n;
    cout << endl;

    for(int i = 0; i < num_examples; ++i) {
        BinSearchTreeGenerator generator;
        BinSearchTree<int> tree = generator.generate_tree(n, k);
        tree.list_keys();

        vector<double> p = {double(0.0),double(0.0), double(0.0)};
        cout << "p: ";
        for(auto x: p) {
            cout << x << ' ';
        }
        cout << endl;

        vector<double> closestPoint = tree.nearestNeighbour(p);
        
        cout << "Closest Point: ";
        for(auto x: closestPoint) {
            cout << x << ' ';
        }
        cout << endl;
    }
}