#include "BinarySearchTree.h"
using namespace std;

int main() {
    BinSearchTree<char> t(2);
	vector<vector<double>> val =
	{{0.0,0.0},
	{-1.0,0.0},
	{-1.0,-1.0},
	{-1.0,1.0},
	{1.0,0.0},
	{1.0,-1.0},
	{1.0,1.0}};
	t.insert('A', val[0]);
	t.insert('D', val[3]);
	t.insert('B', val[1]);
	t.insert('C', val[2]);
	t.insert('F', val[5]);
	t.insert('E', val[4]);
	t.insert('G', val[6]);
	
    vector<double> p = {double(0.2),double(0.5)};
    p = t.nearestNeighbour(p);
    cout << "hola";
}