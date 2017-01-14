// Copyright 2017 creating a template for avl tree
// including required operations for avl tree
// such as insert, delete, rebalence, print
// adding gaurd
#ifndef my_avl_tree_oop
#define my_avl_tree_oop
// including required operations for avl tree
// such as insert, delete, rebalence, print
#include <queue>
#include <stack>
#include <algorithm>
#include <sstream>
#include <cmath>

// creating name space myavl
// creating template for node struct
template <typename T>
struct node {
  // to store value of user specified type
  T value;
  // to store height of current node
  // height = 1+ max number of nodes in left child or right child
  int height;
  // pointer of type node to store parent
  node<T>* parent;
  // pointer of type node to store left_child
  node<T>* left_child;
  // pointer of type node to store right_child
  node<T>* right_child;
};

// creating template for avl tree
// contains pointer to root of current tree object
// and non recurssive functions to perform operations
// on tree object
template <class T>
class myavl {
 public:
  // a pointer to keep track of root
  // of current instance of tree object
  node<T>* root;
 public:
  // constructor
  myavl() {
    // creating a new avl tree object
    // the root points to null
    root = NULL;
  }
  node<T>* create_node(T);
  // following operations have complexity O(log(n))
  void insert_node(T);
  void delete_node(T);
  node<T>* find_node(T);
  T find_min(node<T>*);
  T find_max(node<T>*);
  T find_min();
  T find_max();
  T predecessor(node<T>*);
  T successor(node<T>*);
  T predecessor(T);
  T successor(T);
  int height(T);
  int slope(T);
  // following operations have complexity O(1)
  int height();
  int readjust_height(node<T>*);
  int slope(node<T>*);
  void rebalence(node<T>*);
  void rotate_left(node<T>*);
  void rotate_right(node<T>*);
  // has complexity O(log(n))
  void print_inorder(node<T>*);
  void print_inorder();
  // has complexity O(log(N))
  // where N is the number of nodes in
  // a full/complete tree of height h
  void print_model();
};

// creating funtions for avl
// to create a new node in avl
template <class T>
node<T>* myavl<T>::create_node(T value) {
  // create a new node in heap, and return its address
  node<T>* new_node = ( node<T>* )malloc(sizeof(node<T> ) );
  new_node->value = value;
  new_node->height = 1;
  new_node->parent = NULL;
  new_node->left_child = NULL;
  new_node->right_child = NULL;
  return new_node;
}

// returns height of root
template <class T>
int  myavl<T>::height() {
  if (root)
    return root->height;
  else
    return 0;
}

template <class T>
void myavl<T>::insert_node(T value) {
  // using non recursive method
  // checking if the tree is empty
  if (!root) {
    // this node/sub-tree is empty
    // creating a new node and make the root point to it
    root = create_node(value);
    // return void
    return;
  }
  // creating a stack to store pointer to nodes of this tree
  std::stack<node<T>* > stack_of_nodes;
  // adding nodes in stack till right place to insert current value is found
  // rebalencing the nodes in stack in lifo order
  // starting the traversal of nodes of tree from its root
  // note: the root of current tree may change after insertion
  // and rebalencing inorder to maintain balance in the tree
  stack_of_nodes.push(root);
  node<T>* tracer = NULL;
  bool inserted = false;
  // this loop has complexity O(log(n))
  while (!inserted) {
    tracer = stack_of_nodes.top();
    if (tracer->value > value) {
      // the entered value will be left child of current node
      // if tracers left child doesnt exit, create new node with inserted value
      // and add it as the left child of current node
      if (!tracer->left_child) {
        node<T>* new_node = create_node(value);
        new_node->parent = tracer;
        tracer->left_child = new_node;
        // rebalencing tracer
        rebalence(tracer);
        // removing tracer from the stack, since it is now balanced
        stack_of_nodes.pop();
        // setting inserted to true to break the loop
        inserted = true;
      }
      else {
        // else store the left child in the stack
        stack_of_nodes.push(tracer->left_child);
      }
    }
    else if (tracer->value < value) {
      // the entered value will be right child of current node
      // if tracers right child doesnt exit, create new node with inserted value
      // and add it as the right child of current node
      if (!tracer->right_child) {
        node<T>* new_node = create_node(value);
        new_node->parent = tracer;
        tracer->right_child = new_node;
        // rebalencing tracer
        rebalence(tracer);
        // removing tracer from the stack, since it is now balanced
        stack_of_nodes.pop();
        // setting inserted to true to break the loop
        inserted = true;
      }
      else {
        // else store it's right child in the stack
        stack_of_nodes.push(tracer->right_child);
      }
    }
    else {
      // value = tracer-> value
      // not inserting duplicate values
      // returning void
      return;
    }
  }
  // rebalencing the heights of all the nodes in the stack
  // has complexity O(log(n))
  while (!stack_of_nodes.empty()) {
    tracer = stack_of_nodes.top();
    stack_of_nodes.pop();
    rebalence(tracer);
    readjust_height(tracer);
  }
}

// readjusts height by using height of it's subtrees,
// returns slope of the give node
// has complexity O(1)
template <class T>
int myavl<T>::readjust_height(node<T>* tracer) {
  int height_of_right_sub_tree = 0;
  int height_of_left_sub_tree = 0;
  if (tracer->right_child)
    height_of_right_sub_tree = tracer->right_child->height;
  if (tracer->left_child)
    height_of_left_sub_tree = tracer->left_child->height;
  tracer->height = 1 + std::max(height_of_left_sub_tree, height_of_right_sub_tree);
  // 1 is for the current height
  // slope is given by the diffence b/w the
  // height of left subtree - height of right subtree
  return (height_of_left_sub_tree - height_of_right_sub_tree);
  // the slope of tracer
}

// rebalances the subtree of the given node
// has complexity O(1)
template <class T>
void myavl<T>::rebalence(node<T>* tracer) {
  node<T>* child;
  // to point to the child of the tracer
  int slope;
  slope = readjust_height(tracer);
  // if slope is 2 or -2, then the subtree is unbalanced
  // rotating the subtree of tracer,
  // inorder to maintain the slope to be -1,0 or 1
  if (slope == 2) {
    // calculating the slope of its left subtree
    child = tracer->left_child;
    slope = readjust_height(child);
    // if it is 1 or 0, rotate right, else rotate it's
    // left child to left then rotate tracer to right
    if (slope == -1) {
      // rotate left child to left
      rotate_left(child);
    }
    // rotate the tracer to right
    rotate_right(tracer);
  }
  // symmetrical rotating for slope == -2
  else if (slope == -2) {
    // calculating the slope of its right subtree
    child = tracer->right_child;
    slope = readjust_height(child);
    // if it is -1 or 0, rotate left, else rotate it's
    // right child to right then rotate tracer to left
    if (slope == 1) {
      // rotate right child to right
      rotate_right(child);
    }
    // rotate the tracer to left
    rotate_left(tracer);
  }
}

// rotate right by rehooking
// has complexity O(1)
template <class T>
void myavl<T>::rotate_right(node<T>* tracer) {
  node<T>* left_child = tracer->left_child;
  node<T>* parent = tracer->parent;
  // rehooking
  tracer->left_child = left_child->right_child;
  left_child->right_child = tracer;
  left_child->parent = parent;
  tracer->parent = left_child;
  // rehooking left child to the old parent of tracer
  if (!parent) {
    // if parent is null,
    // meaning the tracer is root,
    // changing the root to left child
    root = left_child;
  }
  else if (parent->left_child == tracer) {
    parent->left_child = left_child;
  }
  else {
    parent->right_child = left_child;
  }
  // readjusting the heigth of tracer
  readjust_height(tracer);
  // for the left child
  readjust_height(left_child);
}

// rotate left by rehooking
// has complexity O(1)
template <class T>
void myavl<T>::rotate_left(node<T>* tracer) {
  node<T>* right_child = tracer->right_child;
  node<T>* parent = tracer->parent;
  // rehooking
  tracer->right_child = right_child->left_child;
  right_child->left_child = tracer;
  right_child->parent = parent;
  tracer->parent = right_child;
  // rehooking right child to the old parent of tracer
  if (!parent) {
    // if parent is null,
    // meaning the tracer is root,
    // changing the root to right child
    root = right_child;
  }
  else if (parent->left_child == tracer) {
    parent->left_child = right_child;
  }
  else {
    parent->right_child = right_child;
  }
  // readjusting the heigth of tracer
  readjust_height(tracer);
  // for the right child
  readjust_height(right_child);
}

// finding minimum of given node
// complexity O(log(n))
template <class T>
T myavl<T>::find_min(node<T>* tracer) {
  // minimum value of a subtree is the leftmost
  // child of this subtree, if no left child then tracer
  // is the minimum of this subtree
  node<T>* left_child = tracer->left_child;
  while (left_child) {
    tracer = left_child;
    left_child = left_child->left_child;
  }
  return tracer->value;
}

// finding maximum of given node
// complexity O(log(n))
template <class T>
T myavl<T>::find_max(node<T>* tracer) {
  // maximum value of a subtree is the rightmost
  // child of this subtree, if no right child then tracer
  // is the maximum of this subtree
  node<T>* right_child = tracer->right_child;
  while (right_child) {
    tracer = right_child;
    right_child = right_child->right_child;
  }
  return tracer->value;
}

// finding maximum of tree
// complexity O(log(n))
template <class T>
T myavl<T>::find_max() {
  return find_max(root);
}

// finding minmum of tree
// complexity O(log(n))
template <class T>
T myavl<T>::find_min() {
  return find_min(root);
}

// finding the node address in heap,
// whoes value is passed as argument
// complexity O(log(n))
template <class T>
node<T>* myavl<T>::find_node(T value) {
  node<T>* tracer = root;
  while (tracer) {
    if (tracer->value == value) {
      // found
      return tracer;
    }
    if (tracer->value > value) {
      // on left subtree
      tracer = tracer->left_child;
    }
    else {
      tracer = tracer->right_child;
    }
  }
  // value not found
  // returning NULL
  return NULL;
}

// finding predecessor
// complexity O(log(n))
template <class T>
T myavl<T>::predecessor(node<T>* tracer) {
  // predecessor is the immediate smallest value in the entire tree
  // if current node has a left sub tree, then its predecessor is the node
  // with maximum value in this left subtree, else current node is the max
  // valued child of this subtree and its predecessor will be the node whose
  // right child is the current subtree, if there is no such node whose
  // right child is the current subtree, then the current node is the
  // smallest value in the entire tree, hence no predecessor,
  // returns tracer->value
  if (tracer->left_child) {
    // if left child exits
    // predecessor is the max valued child of left subtree
    return find_max(tracer->left_child);
  }
  node<T>* parent = tracer->parent;
  // if the parent exits
  while (parent) {
    // if tracer is the right child of parent
    if (parent->right_child == tracer) {
      // then parent is the predecessor
      return parent->value;
    }
    // if not then finding parent of tracer's parent
    tracer = parent;
    parent = parent->parent;
  }
  // if tracer has no node acting as the right child of
  // tracer's subtree then its the smallest value in the entire tree
  // returning root value
  return tracer->value;
}

// finding successor
// complexity O(log(n))
template <class T>
T myavl<T>::successor(node<T>* tracer) {
  // predecessor is the immediate largest value in the entire tree
  // if current node has a right sub tree, then its successor is the node
  // with minimum value in this right subtree, else current node is the min
  // valued child of this subtree and its successor will be the node whose
  // left child is the current subtree, if there is no such node whose
  // left child is the current subtree, then the current node is the
  // largest value in the entire tree, hence no successor, returns tracer->value
  if (tracer->right_child) {
    // if right child exits
    // successor is the min valued child of left subtree
    return find_min(tracer->right_child);
  }
  node<T>* parent = tracer->parent;
  // if the parent exits
  while (parent) {
    // if tracer is the left child of parent
    if (parent->left_child == tracer) {
      // then parent is the predecessor
      return parent->value;
    }
    // if not then finding parent of tracer's parent
    tracer = parent;
    parent = parent->parent;
  }
  // if tracer has no node acting as the right child of
  // tracer's subtree then its the smallest value in the entire tree
  // returning root value
  return tracer->value;
}

// finding predecessor
// complexity O(log(n))
template <class T>
T myavl<T>::predecessor(T value) {
  node<T>* tracer = find_node(value);
  if (tracer)
    return predecessor(find_node(value));
  else
    return value;
}

// finding successor
// complexity O(log(n))
template <class T>
T myavl<T>::successor(T value) {
  node<T>* tracer = find_node(value);
  if (tracer)
    return successor(find_node(value));
  else
    return value;
}

// finding height of value
// complexity O(log(n))
template <class T>
int myavl<T>::height(T value) {
  node<T>* tracer = find_node(value);
  if (!tracer)
    // value not found
    return 0;
  int height_of_right_sub_tree = 0;
  int height_of_left_sub_tree = 0;
  if (tracer->right_child)
    height_of_right_sub_tree = tracer->right_child->height;
  if (tracer->left_child)
    height_of_left_sub_tree = tracer->left_child->height;
  return (1 + std::max(height_of_left_sub_tree, height_of_right_sub_tree));
}

// finding slope
// complexity O(log(n))
template <class T>
int myavl<T>::slope(T value) {
  node<T>* tracer = find_node(value);
  if (!tracer)
    // value not found
    return 0;
  return readjust_height(tracer);
}

// deleting a node
// complexity O(log(n))
template <class T>
void myavl<T>::delete_node(T value) {
  // using non recursive method
  if (!root)
    // if tree is empty
    return;
  // checking if value to be deleted is the root
  if (root->value == value) {
    // deleteing the tree
    //  node<T>* temp = root;
    //     free(temp);
    root = NULL;
    // return void
    return;
  }
  // creating a stack to store pointer to nodes of this tree
  std::stack<node<T>* > stack_of_nodes;
  // adding nodes in stack till right place to delete current value is found
  // rebalencing the nodes in stack in lifo order
  // starting the traversal of nodes of tree from its root
  // note: the root of current tree may change after deletion
  // and rebalencing inorder to maintain balance in the tree
  stack_of_nodes.push(root);
  node<T>* tracer = NULL;
  bool found = false;
  // finding the node with value = given value
  // this loop has complexity O(log(n))
  while (!found) {
    tracer = stack_of_nodes.top();
    if (tracer->value > value) {
      // the entered value will be left child of current node
      // if tracers left child doesnt exit, value is not in the tree
      // return void
      if (!tracer->left_child) {
        return;
      }
      else {
        // else store the left child in the stack
        stack_of_nodes.push(tracer->left_child);
      }
    }
    else if (tracer->value < value) {
      // the entered value will be right child of current node
      // if tracers right child doesnt exit, value is not in the tree
      // return void
      if (!tracer->right_child) {
        return;
      }
      else {
        // else store it's right child in the stack
        stack_of_nodes.push(tracer->right_child);
      }
    }
    else {
      // value = tracer-> value
      // if node has 2 childeren, swapping value of current
      // node with its successor/predecessor and deleting it's
      // successor/predecessor
      if (tracer->left_child && tracer->right_child) {
        // swapping with value in smaller subtree
        if (tracer->left_child->height > tracer->right_child->height) {
          // chaning the value to find and delete
          value = find_min(tracer->right_child);
          // or value = successor(tracer);
          // swapping tracers value with its successor
          tracer->value = value;
          // pushing the right child in the stack
          stack_of_nodes.push(tracer->right_child);
        }
        else {
          // chaning the value to find and delete
          value = find_max(tracer->left_child);
          // or value = predecessor(tracer);
          // swapping tracers value with its predecessor
          tracer->value = value;
          // pushing the left child in the stack
          stack_of_nodes.push(tracer->left_child);
        }
      }
      else {
        // else found the tracer that is either a leaf node
        // or node with only one child
        found = true;
      }
    }
  }
  // rehooking parent and child of tracer
  // if tracer has only left child
  if (tracer->left_child) {
    tracer->left_child->parent = tracer->parent;
    // if tracer is the left child of its parent
    if (tracer->parent->left_child == tracer) {
      tracer->parent->left_child = tracer->left_child;
    }
    else {
      tracer->parent->right_child = tracer->left_child;
    }
  }
  else if(tracer->right_child) {
    // if tracer has only right child
    tracer->right_child->parent = tracer->parent;
    // if tracer is the left child of its parent
    if (tracer->parent->left_child == tracer) {
      tracer->parent->left_child = tracer->right_child;
    }
    else {
      tracer->parent->right_child = tracer->right_child;
    }
  }
  // else tracer is a leaf node
  else {
    if (tracer->parent->left_child == tracer) {
      tracer->parent->left_child = NULL;
    }
    else {
      tracer->parent->right_child = NULL;
    }
  }
  // tracer deleted
  // free(temp);
  // rebalencing the heights of all the nodes in the stack
  // has complexity O(log(n))
  while (!stack_of_nodes.empty()) {
    tracer = stack_of_nodes.top();
    stack_of_nodes.pop();
    rebalence(tracer);
    readjust_height(tracer);
  }
}

// prints the tree
template <class T>
void myavl<T>::print_inorder() {
  print_inorder(root);
}

// prints the tree
template <class T>
void myavl<T>::print_inorder(node<T>* root) {
  if (root == NULL)
    return;
  print_inorder(root->left_child);
  std::cout << " " << root->value;
  std::cout << " :height :" << root->height << "\n";
  print_inorder(root->right_child);
}

// prints the tree
template <class T>
void myavl<T>::print_model() {
  // has complexity O(n+m), where n is the number of nodes,
  // m is the number of edges,
  // since in bst there are n-1 edges for n number of nodes
  // complexity is O(n)
  // if root is null, ie tree is empty
  if (!root) {
    std::cout << "tree is empty!"  << "\n";
    return;
  }
  // storing the pointer to nodes of the bst
  std::queue<node<T>*> Q;
  // storing the node values to be printe
  std::string print_level;
  // storing the edge symbol ' ', '/' or '\'
  // ' ' for the root
  std::string edge_symbol = " ";
  // storing all the edge symbols at current level
  std::string print_edge;
  // storing the padding at each level
  std::string padding = "";
  Q.push(root);
  bool not_all_null = true;
  // to check if all remaining nodes in the Q are not_null
  // null nodes are displayed as space for padding
  int j = 1;
  // j is used to know the number of nodes in the current level
  int current_height = root->height;
  // used for proper padding
  while (not_all_null) {
    // while all nodes in the Q are not null
    // reinitializing not_all_null to false for every itteration
    not_all_null = false;
    // storing all node at the current level
    print_level = "";
    // storing all node at the current level
    print_edge = "";
    // considereing each subtree as a box
    // taking height of box = current level
    // then total breadth is taken as = 2 ^ height -1
    // hence padding from left side = half of breadth
    // and padding to right side = half of breadth
    // plus an extra space at the end, for its parent
    // since we are moving from left to right, leaving space for
    // parent considereing the current node to be its left child
    padding = "";
    for (int z = 1; z <= (std::pow(2.0, current_height)-1)/2; z++) {
      padding += " ";
    }    
    for (int i = 1; i <= j; i++) {
      // can also be expressed as i < = 2 ^ log(j)
      // i increments by 1, j increments by powers of 2
      // this loop extracts all the nodes that are in the current level
      // current level = i, number of max nodes in this level
      // = 2 ^ log(j) or simply j
      // if the node is null, displayed as space/star and
      // two null childeren are added in the Q for padding.
      std::ostringstream oss;
      // for string concatination
      // removing the node from the queue
      node<T>* current_node = Q.front();
      Q.pop();  // pops and returns void
      // checking if the node is not NULL
      if (current_node != NULL) {
        not_all_null = true;
        // atleast one node in this level is not null
        oss << current_node->value;
        // casting int value to string then concatinating
        // adding the value of node poped into the string
        // containg all nodes at current level
        print_level += padding + oss.str() +  padding + " ";
        // adding current edge symbol to the print_edge string
        print_edge += padding + edge_symbol + padding + " ";
        // pushing the childeren of current_node
        // note: if the childeren are null,
        // they will be displayed as space/star
        Q.push(current_node->left_child);
        Q.push(current_node->right_child);
      }
      else {
        // the current_node is NUll
        // space/star is used to display the nodes
        print_level += padding + " " + padding + " ";
        // adding space insted of current edge symbol to the print_edge string
        print_edge += padding + " " + padding + " ";
        // pushing null as childeren, for padding
        // will appear as space/star
        Q.push(NULL);
        Q.push(NULL);
      }
      // changing the edge symbol after every itteration
      if (edge_symbol == " " || edge_symbol == "\\")
        edge_symbol = "/";
      else
        edge_symbol = "\\";
    }
    if (not_all_null) {
      // print only if no space/star in here
      // the space before print edge/level is the distance of the tree box from
      // the left of the screen
      std::cout << "  " << print_edge  << "\n";
      std::cout << "  " <<  print_level  << "\n";
    }
    j *= 2;
    // j is incremented by power of 2 as
    // the number of nodes in each level increment by 2
    current_height--;
    // the height decreses by 1
  }
}
#endif // my_avl_tree_oop
