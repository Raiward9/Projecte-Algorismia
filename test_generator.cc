#include "BinarySearchTreeGenerator2.h"

int main() {
    BinSearchTreeGenerator generator;
    BinSearchTree<int> tree = generator.generate_tree(5, 7);

    tree.print_tree();

    tree = generator.generate_tree(5, 7);

    tree.print_tree();
}