// Q) finding unique values from an array
#include <iostream>
#include "./my_avl_tree_oop.hpp"
int main() {
  int n;
  int k;
  myavl<int> tree;
  std::cout << "enter the number of elemnets to insert" << "\n";
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cout << "enter value no" << (i+1) << ":"<< "\n";
    std::cin >> k;
    tree.insert_node(k);
  }
  tree.print_model();
  return 0;
}

