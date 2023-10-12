#include "BinarySearchTreeGenerator2.h"
#include <map>

const int K_MIN = 2, K_MAX = 6;
const int n_INI = 10, n_MAX = 100000000; 
vector<pair<int, int>> intervals_i_factors = {{1000000, 4}, {1000000000, 2}};

BinSearchTreeGenerator GENERATOR;

//per cada clau {mida, dimensio} -> {coeficient_mitja, variancia}
map<pair<int, int>, pair<double, double>> resultats;

double variancia(const vector<int>& instancies, double mitja) {
    double var = 0;
    for(int x: instancies) {
        double diff = double(x) - mitja;
        var += diff*diff;
    }
    return var / instancies.size();    
}

void print_resultats(const map<pair<int,int>, pair<double, double>>& resultats) {

    for(auto it = resultats.begin(); it != resultats.end(); ++it) {
        cout << "n: " << (*it).first.first << ", k: " << (*it).first.second;
        cout << ", cost_mitja: " << (*it).second.first << ", variancia: " << (*it).second.second << endl;
    }
}

int main() {
    int N = 0; 
    cout << "Introdueix la N: "; cin >> N; //numero arbres per parella {mida, dimensions}
    int Q = 0;
    cout << "Introdueix la Q: "; cin >> Q; //numero queries per arbre

    int n = n_INI;
    int factor = intervals_i_factors[0].second;
    while(n <= n_MAX) {

        for(int k = K_MIN; k <= K_MAX; ++k) {

            //farem la mitja i la variancia de N*Q consultes (per cada parell {mida, dimensions})
            vector<int> nodes; 
            int suma_nodes_visitats = 0;

            for(int i = 0; i < N; ++i) { //genearar N arbres
                
                BinSearchTree<int> tree = GENERATOR.generate_tree(n, k);

                for(int q = 0; q < Q; ++q) { //fer Q queries

                    vector<double> p = GENERATOR.generar_targets(k);
                    int nodes_visitats = tree.nearestNeighbour(p).first; //retorna {nodes, punt_proper}
                    
                    nodes.push_back(nodes_visitats);
                    suma_nodes_visitats += nodes_visitats;
                }
            }

            double mitja_nodes_visitats = suma_nodes_visitats / (N*Q);
            double variancia_nodes_visitats = variancia(nodes, mitja_nodes_visitats);
            pair<int, int> key = {n, k};
            pair<double, double> value = {mitja_nodes_visitats, variancia_nodes_visitats};
            resultats.insert({key, value});
        }

        if(intervals_i_factors[0].first <= n) 
            factor = intervals_i_factors[1].second;
        
        n *= factor;
    }

    print_resultats(resultats);
}

// (sumatori (Xi - X_mean)^2  ) / (N-1)
