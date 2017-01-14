// Creating a template for avl tree
// cpp file to create an interface for avl tree
#include <iostream>
#include "./my_avl_tree_oop.hpp"

int main() {
  // to check the standard of current c++
  if ( __cplusplus == 201103L )
    std::cout << "C++11\n";
  else if ( __cplusplus == 199711L )
    std::cout << "C++98\n";
  else
    std::cout << "pre-standard C++\n";
  bool key = true;
  int n;
  myavl<int> tree;
  while (key) {
    std::cout << "enter your choice\n 1)insert, 2)multiple insertion 3)delete, 4)find predecessor, ";
    std::cout << "5)find successor\n 6)find height 7)find slope -1)quit" << "\n";
    std::cin >> n;
    switch (n) {
      case 1: {
        std::cout << "enter value to insert:" << "\n";
        std::cin >> n;
        tree.insert_node(n);
        tree.print_model();
        break;
      }
      case 2: {
        int N;
        std::cout << "enter no of elements to insert:" << "\n";
        std::cin >> N;
        for (int i = 0; i < N; i++) {
          std::cout << "enter value no:" << i+1  << "\n";
          std::cin >> n;
          tree.insert_node(n);
        }
        tree.print_model();
        break;
      }
      case 3: {
        std::cout << "enter value to deleted:" << "\n";
        std::cin >> n;
        tree.delete_node(n);
        tree.print_model();
        break;
      }
      case 4: {
        std::cout << "enter value:" << "\n";
        std::cin >> n;
        std::cout << "its predecessor is:" << tree.predecessor(n) << "\n";
        break;
      }
      case 5: {
        std::cout << "enter value:" << "\n";
        std::cin >> n;
        std::cout << "its successor is:" << tree.successor(n) << "\n";
        break;
      }
      case 6: {
        std::cout << "enter value:" << "\n";
        std::cin >> n;
        std::cout << "its height is:" << tree.height(n) << "\n";
        break;
      }
      case 7: {
        std::cout << "enter value:" << "\n";
        std::cin >> n;
        std::cout << "its slope is:" << tree.slope(n) << "\n";
        break;
      }
      case -1: {
        std::cout << "exiting.."  << "\n";
        key = false;
        break;
      }
      default:
        std::cout << "wrong choice! try again.." << "\n";
        break;
    }
  }
  std::cout << "now go and plant a tree!" << "\n";
  return 0;
}
