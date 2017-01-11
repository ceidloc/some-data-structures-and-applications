// Copyright 2017 1) Given an array of arbitrary size and having
// arbitrary values. Find unique values and print them.
#include <iostream>
#include <queue>
#include <algorithm>
#include <sstream>
#include <cmath>

// creating struct for a balanced binary search tree
typedef struct binary_search_tree {
  int value;
  int height;
  struct binary_search_tree* parent;
  struct binary_search_tree* left_child;
  struct binary_search_tree* right_child;
} Bst;

// has complexity O(n*log(n))
void find_unique(int[], int);
// has complexity O(log(n))
Bst* insert_in_Bst(Bst*, Bst*, int);
// all remaing have complexity O(1)
Bst* create_Bst_node(int);
Bst* rebalence(Bst*, Bst*);
Bst* rotate_left(Bst*, Bst*);
Bst* rotate_right(Bst*, Bst*);
int readjust_height(Bst*);
// has complexity O(n)
void print_inorder(Bst*);
void print_Bst(Bst*);

int main() {
  // to check the standard of current c++
  if ( __cplusplus == 201103L )
    std::cout << "C++11\n";
  else if ( __cplusplus == 199711L )
    std::cout << "C++98\n";
  else
    std::cout << "pre-standard C++\n";
  int n;
  // stores the size of the array
  std::cout << "enter the size of the array"  << "\n";
  std::cin >> n;
  // creating an array of given size 'n' in heap memory
  int* arr = ( int* ) malloc (sizeof(int)*n );
  // input
  for (int i = 0; i < n; i++) {
    std::cout << "enter value no: " << i+1 << " :"  << "\n";
    std::cin >> arr[i];
  }
  // calling find_unique function,
  // finds all the unique elements in the array
  // and calls the print function
  find_unique(arr, n);
  // passing address of the array
  return 0;
}

void find_unique(int* arr, int n) {
  // creating a Bst, that stores only unique elemets
  // inserting the elements of the array into the Bst
  // each insertion cost = height of tree
  // n such insertions, where n is the size of array,
  // hence complexity is O(n*height of tree)
  // using avl trees, to maintain balance in the tree after every insertion
  // makes height of tree equal to log(nodes_in_the_tree)
  Bst* root = create_Bst_node(arr[0]);
  // creating a pointer in stack that will point to the root of Bst in heap
  for (int i = 1; i < n; i++) {
    // trying to insert every element in Bst
    // if the element is unique it will be inserted
    root = insert_in_Bst(root, root, arr[i]);
    // have to pass root twice because of recursive call inside the funtion
    // returns the value of new root after rebalancing the tree
  }
  // the resulting Bst pointed by the root will contain only unique elements
  print_Bst(root);
  // or we can print the inorder
  //  print_inorder(root);
}

// creating funtions for Bst
// to create a new node in Bst
Bst* create_Bst_node(int value) {
  // create a new node in heap, and returns its address
  Bst* new_node = ( Bst* )malloc(sizeof(Bst ) );
  new_node->value = value;
  new_node->height = 1;
  new_node->parent = NULL;
  new_node->left_child = NULL;
  new_node->right_child = NULL;
  return new_node;
}

// scans the Bst and inserts value if it's unique
Bst* insert_in_Bst(Bst* tracer, Bst* root, int new_value ) {
  if (tracer->value > new_value) {
    // the new_value should be the left child of tracer
    if (tracer->left_child == NULL) {
      // no left child, hence creating a new left child
      Bst* new_node = create_Bst_node(new_value);
      new_node->parent = tracer;
      tracer->left_child = new_node;
    }
    else {
      // insert in the left branch of tracer
      insert_in_Bst(tracer->left_child, root, new_value);
    }
  }
  else if (tracer->value < new_value) {
    // the new_value should be the right child of tracer
    if (tracer->right_child == NULL) {
      // no right child,hence creating a new right child
      Bst* new_node = create_Bst_node(new_value);
      new_node->parent = tracer;
      tracer->right_child = new_node;
    }
    else {
      // insert in the right branch of tracer
      insert_in_Bst(tracer->right_child, root, new_value);
    }
  }
  else {
    // no insertion in this tracer
    return root;
  }
  // this part is executed AFTER
  // insertion of a child in current tracer
  // rebalencing the tree
  root = rebalence(tracer, root);
  // has complexity O(1)
  // readjusting the heigth of tracer
  readjust_height(tracer);
  // has complexity O(1)
  return root;
}

// readjusts height by using height of it's subtrees,
// returns slope of the give node
// has complexity O(1)
int readjust_height(Bst* tracer) {
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
Bst* rebalence(Bst* tracer, Bst* root) {
  Bst* child;
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
      root = rotate_left(child, root);
    }
    // rotate the tracer to right
    root = rotate_right(tracer, root);
  }
  // symmetrical rotating for slope == -2
  else if (slope == -2) {
    // calculating the slope of its left subtree
    child = tracer->right_child;
    slope = readjust_height(child);
    // if it is -1 or 0, rotate left, else rotate it's
    // right child to right then rotate tracer to left
    if (slope == 1) {
      // rotate right child to right
      root = rotate_right(child, root);
    }
    // rotate the tracer to left
    root = rotate_left(tracer, root);
  }
  return root;
}

// rotate right by rehooking
// has complexity O(1)
Bst* rotate_right(Bst* tracer, Bst* root) {
  Bst* left_child = tracer->left_child;
  Bst* parent = tracer->parent;
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
  return root;
}

// rotate left by rehooking
// has complexity O(1)
Bst* rotate_left(Bst* tracer, Bst* root) {
  Bst* right_child = tracer->right_child;
  Bst* parent = tracer->parent;
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
  return root;
}

// prints the tree
void print_inorder(Bst* root) {
  if (root == NULL)
    return;
  print_inorder(root->left_child);
  std::cout << " " << root->value;
  std::cout << " :height :" << root->height << "\n";
  print_inorder(root->right_child);
 }

// prints the tree
void print_Bst(Bst* root) {
  // has complexity O(n+m), where n is the number of nodes,
  // m is the number of edges,
  // since in bst there are n-1 edges for n number of nodes
  // complexity is O(n)
  std::queue<Bst*> Q;
  // stores the pointer to nodes of the bst
  std::string print_level;
  // stores the node values to be printed
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
    not_all_null = false;
    // reinitializing not_all_null to false for every itteration
    print_level = "";
    // stores all node at the current level
    std::string padding = "";
    // considereing each subtree as a box
    // taking height of box = current level
    // then total breadth is taken as = 2 ^ height -1
    // hence padding from left side = half of breadth
    // and padding to right side = half of breadth
    // plus an extra space at the end, for its parent
    // since we are moving from left to right, leaving space for
    // parent considereing the current node to be its left child
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
      // two childeren are added in the Q for padding.
      std::ostringstream oss;
      // for string concatination
      // removing the node from the queue
      Bst* current_node = Q.front();
      Q.pop();  // pops and returns void
      // checking if the node is not NULL
      if (current_node != NULL) {
        not_all_null = true;
        // atleast one node in this level is not null
        oss << current_node->value;
        // casting int value to string then concatinating
        print_level += padding + oss.str() +  padding + " ";
        // adding the value of node poped into the string
        // containg all nodes at current level
        Q.push(current_node->left_child);
        Q.push(current_node->right_child);
        // pushing the childeren of current_node
        // note: if the childeren are null,
        // they will be displayed as space/star
      }
      else {
        // the current_node is NUll
        print_level += padding + "*" + padding + " ";
        //        std::cout << " NULL ";
        // space/star is used to display the nodes
        Q.push(NULL);
        Q.push(NULL);
        // pushing null as childeren, for padding
        // will appear as space/star
      }
    }
    if (not_all_null)
      // print only if no space/star in here
      std::cout << print_level  << "\n";
    j *= 2;
    // j is incremented by power of 2 as
    // the number of nodes in each level increment by 2
    current_height--;
    // the height decreses by 1
  }
}
