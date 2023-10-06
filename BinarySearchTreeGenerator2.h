#include "BinarySearchTree.h"
#include <random>
using namespace std;

class BinSearchTreeGenerator {
public:

    //Pre:
    //Inicialitza el generador de numeros amb una seed random i l'objecte
    //per seguir una distribucio uniforme
    BinSearchTreeGenerator() {
        this->num_generator =  mt19937_64(random_seed_generator());
        this->Uniforme = uniform_real_distribution<double>(0.0, 1.0);
    }

    ~BinSearchTreeGenerator(){}

    
    //Pre: 0 < k_dims and 0 <= num_nodes 
    //Genera un k-d tree aleatori de mida num_nodes
    BinSearchTree<int> generate_tree(unsigned int num_nodes, unsigned int k_dim) {
        BinSearchTree<int> tree(k_dim);
        
        for(int i = 0; i < num_nodes; ++i) {
            pair<int, vector<double>> node = create_node(k_dim);
            int info = node.first;
            vector<double> key = node.second;

            tree.insert(info, key);
        }

        return tree;
    }

private:
    //mersenne_twister_engine de 64 bits, crea numeros pseudorandoms de 64 bits
    //L'engine de l'algorisme esta optimitzar per crear llargues sequencies de numeros seguint una 
    //distribucio casi uniforme (nosaltres volem una distribucio uniforme)
    //Altres alternativas a <random>: linear_congruential_engine, substract_with_carry_engine
    random_device random_seed_generator;
    mt19937_64 num_generator; 
    uniform_real_distribution<double> Uniforme;


    //Pre: 0 < dim
    //Genera dim números aleatoris seguint una distribució uniforme i un valor de info
    pair<int, vector<double>> create_node(unsigned int dim) {
        int info = 1;        // ni idea de que ha de ser la info, no se ni si ho posa a l'enunciat
        
        vector<double> key(dim);
        for(int i = 0; i < dim; ++i) 
            key[i] = Uniforme(num_generator);
        
        pair<int, vector<double>> res = {info, key};
        return res;
    }
};