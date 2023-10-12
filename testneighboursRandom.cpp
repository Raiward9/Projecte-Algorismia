#include "BinarySearchTreeGenerator2.h"
using namespace std;

int main() {
    int num_examples = 0, k = 1, n = 1;

    cout << "Quants exemples vols? : ";
    cin >> num_examples;
    cout << endl;

    cout << "Quants nodes cal inserir? : ";
    cin >> n;
    cout << endl;

    cout << "Quantes dimensions han de tindre els punts? : ";
    cin >> k;
    cout << endl;


    for(int i = 0; i < num_examples; ++i) {
        
        BinSearchTreeGenerator generator;
        vector<double> p = generator.generar_targets(k);
        BinSearchTree<int> tree = generator.generate_tree(n, k);
        //tree.list_keys();

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

        pair<double, vector<double>> ideal = tree.ideal_euclidean_keys(p);
        cout << "Ideal distance: " << ideal.first << endl;
        vector<double> ideal_point = ideal.second;

        cout << "Ideal point: " << ' ';
        for(double x: ideal_point)
            cout << x << ' ';
        
        cout << endl << endl;
    }
}