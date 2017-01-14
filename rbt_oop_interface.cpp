// interface for red black trees
#include <iostream>
#include "./my_red_black_tree_oop.hpp"
int main() {
  bool key = true;
  int n;
  myrbt<int> tree;
  while (key) {
    std::cout << "enter your choice\n 1)insert, 2)multiple insertion 3)delete, 4)find Predecessor, ";
    std::cout << "5)find Successor\n 6)find height 7)find slope -1)quit" << "\n";
    std::cin >> n;
    switch (n) {
      case 1: {
        std::cout << "enter value to insert:" << "\n";
        std::cin >> n;
        tree.Insert_node(n);
        tree.Print_model();
        break;
      }
      case 2: {
        int N;
        std::cout << "enter no of elements to insert:" << "\n";
        std::cin >> N;
        for (int i = 0; i < N; i++) {
          std::cout << "enter value no:" << i+1  << "\n";
          std::cin >> n;
          tree.Insert_node(n);
        }
        tree.Print_model();
        break;
      }
      case 3: {
        std::cout << "enter value to deleted:" << "\n";
        std::cin >> n;
        tree.Delete_node(n);
        tree.Print_model();
        break;
      }
      case 4: {
        std::cout << "enter value:" << "\n";
        std::cin >> n;
        std::cout << "its Predecessor is:" << tree.Predecessor(n) << "\n";
        break;
      }
      case 5: {
        std::cout << "enter value:" << "\n";
        std::cin >> n;
        std::cout << "its Successor is:" << tree.Successor(n) << "\n";
        break;
      }
      case 6: {
        std::cout << "enter value:" << "\n";
        std::cin >> n;
        //        std::cout << "its height is:" << tree.Height(n) << "\n";
        break;
      }
      case 7: {
        std::cout << "enter value:" << "\n";
        std::cin >> n;
        //        std::cout << "its slope is:" << tree.slope(n) << "\n";
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
