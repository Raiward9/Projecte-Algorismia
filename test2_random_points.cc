#include "BinarySearchTree.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


void generar_punts(vector<vector<double>>& coords, int n, int k) {

	srand(static_cast<unsigned>(time(nullptr))); // Inicializa la semilla del generador de números aleatorios
	
	for (int i = 0; i < n; ++i) {
		vector<double> p(k);
		for (int j = 0; j < k; j++) {
        	double coordenada = static_cast<double>(rand()) / RAND_MAX; // Genera un número aleatorio en [0, 1]
			p[j] = coordenada;
			//cout << p[j] << endl;
    	}
		//cout << p[0] << " " << p[1] << endl;
		coords.push_back(p);
		//cout << double(coords[0][0])  << " " << double(coords[0][1]) << endl;
	}
	//cout << coords.size() << endl << endl;
}
int main() {
	cout.setf(ios::fixed);
	cout.precision(4);

	vector<vector<double>> val;
	cout << "INTRODUEIX EL NUMERO DE VALORS I EL NUMERO DE DIMENSIONS" << endl;
	int n, k;
	cin >> n >> k;

	BinSearchTree<int> t(k);
	generar_punts(val,n,k);

	for (int i = 0; i < n; ++i){
		t.insert(i,val[i]);
	}
	/*
	t.insert('A', val[0]);
	t.insert('D', val[3]);
	t.insert('B', val[1]);
	t.insert('C', val[2]);
	t.insert('F', val[5]);
	t.insert('E', val[4]);
	t.insert('G', val[6]);
	*/
	t.print_tree();
}