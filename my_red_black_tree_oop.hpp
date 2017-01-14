// creating a templater for red black tree
// including required operations for red black tree
// such as insert, delete, rebalence, print
// adding gaurd
#ifndef my_red_black_tree_oop
#define my_red_black_tree_oop
// including required operations for red black tree
// such as insert, delete, rebalence, print
#include <queue>
#include <algorithm>
#include <sstream>
#include <cmath>

// creating name space myrbt
// creating template for node struct
template <typename T>
struct node {
  // to store value of user specified type
  T value;
  // to store the colour of node
  // if colour is false, node is black, else red
  // note, black is taken as false as NULL nodes are also black
  bool colour;
  // pointer of type node to store parent
  node<T>* parent;
  // pointer of type node to store left_child
  node<T>* left_child;
  // pointer of type node to store right_child
  node<T>* right_child;
};

// creating template for red black tree
// contains pointer to root of currentNode tree object
// and non recurssive functions to perform operations
// on tree object
template <class T>
class myrbt {
 public:
  // a pointer to keep track of root
  // of currentNode instance of tree object
  node<T>* root;
  // to keep track the size, ie the number of nodes in the tree
  int size_of_tree;
 public:
  // constructor
  myrbt() {
    // creating a new red black tree object
    // the root points to null
    root = NULL;
    // size is set to zero
    size_of_tree = 0;
  }
  node<T>* Create_node(T);
  // following operations have complexity O(log(n))
  void Insert_node(T);
  void Delete_node(T);
  node<T>* Find_node(T);
  T Find_min(node<T>*);
  T Find_max(node<T>*);
  T Find_min();
  T Find_max();
  T Predecessor(node<T>*);
  T Successor(node<T>*);
  T Predecessor(T);
  T Successor(T);
  // following operations have complexity O(1)
  int Height();
  node<T>* Grandparent(node<T>*);
  node<T>* Uncle(node<T>*);
  node<T>* Sibling(node<T>*);
  void Rotate_left(node<T>*);
  void Rotate_right(node<T>*);
  // has complexity O(log(n))
  void Print_inorder(node<T>*);
  void Print_inorder();
  // has complexity O(log(N))
  // where N is the number of nodes in
  // a full/complete tree of height h
  void Print_model();
};

// creating funtions for rbt
// to create a new node in rbt
template <class T>
node<T>* myrbt<T>::Create_node(T value) {
  // create a new node in heap, and return its address
  node<T>* new_node = ( node<T>* )malloc(sizeof(node<T> ) );
  new_node->value = value;
  // creating a node of red colour
  new_node->colour = true;
  new_node->parent = NULL;
  new_node->left_child = NULL;
  new_node->right_child = NULL;
  // increasing the size, ie number of nodes in the tree
  size_of_tree += 1;
  return new_node;
}

template <class T>
void myrbt<T>::Insert_node(T value) {
  // using non recursive method
  // checking if the tree is empty
  if (!root) {
    // this node/sub-tree is empty
    // creating a new node and make the root point to it
    root = Create_node(value);
    // changing the colour of new node from red to black
    // as root is always black
    root->colour = false;
    // return void
    return;
  }
  // creating a pointer to point to the current node
  // starting from the root of the tree
  node<T>* currentNode = root;
  bool inserted = false;
  // this loop has complexity O(log(n))
  while (!inserted) {
    if (currentNode->value > value) {
      // the entered value will be left child of currentNode node
      // if currentNodes left child doesnt exit, create new node with
      // inserted value and add it as the left child of currentNode node
      if (!currentNode->left_child) {
        node<T>* new_node = Create_node(value);
        new_node->parent = currentNode;
        currentNode->left_child = new_node;
        // the currentNode now points to its left child
        currentNode = currentNode->left_child;
        // setting inserted to true to break the loop
        inserted = true;
      }
      else {
        // the currentNode now points to its left child
        currentNode = currentNode->left_child;
      }
    }
    else if (currentNode->value < value) {
      // the entered value will be right child of currentNode node
      // if currentNodes right child doesnt exit, create new node with
      // inserted value and add it as the right child of currentNode node
      if (!currentNode->right_child) {
        node<T>* new_node = Create_node(value);
        new_node->parent = currentNode;
        currentNode->right_child = new_node;
        // the currentNode now points to its right child
        currentNode = currentNode->right_child;
        // setting inserted to true to break the loop
        inserted = true;
      }
      else {
        // the currentNode now points to its right child
        currentNode = currentNode->right_child;
      }
    }
    else {
      // value = currentNode-> value
      // not inserting duplicate values
      // returning void
      return;
    }
  }
  // rebalencing the heights tree
  // has complexity O(h/2), where h is the height of the tree
  // in a balanced tree h = log(n)
  while (inserted) {
    // if currentNodes parent is null, ie currentNode is root
    if (!currentNode->parent) {
      // changing the colour of root to black
      // as it may change to red due to case 3
      currentNode->colour = false;
      // return void
      return;
    }
    // if currentNodes parent is black
    if (!currentNode->parent->colour) {
      // no violation, ie tree is balanced
      // return void
      return;
    }
    // since parent is red and current node is red then the property
    // that red node must only have black childeren is violated
    // this also implies that the grandparent of current node exits and is black
    // the grandparent exits as root node is always black
    node<T>* grandparent = Grandparent(currentNode);
    node<T>* uncle = Uncle(currentNode);
    // if uncle of currentNode is red
    if (uncle != NULL && uncle->colour == true) {
      // changing the colour of parent to black
      // now red node has black parent, no violation of colour
      currentNode->parent->colour = false;
      // since the black height of current branch of grandparent is increased
      // changing the colour of grandparent from black to red will decrease it
      grandparent->colour = true;
      // now we have to increase the height of its other branch
      // since uncle is red we change it to black to increase black height
      uncle->colour = false;
      // both the branches of grandparent are now same
      // and the black height of grandparent is same as before
      // the only violation of red black tree rules is violated by changing
      // the colour of grandparent, this is fixed by recursively checking all
      // cases of this loop on grandparent
      currentNode = grandparent;
      // note this case is the only one which causes itteration of this loop
    }
    // if uncle is black, note null nodes are considered black
    // note this case may exit as a side effet of the above case, ie after
    // changing the colour of inserted nodes grandparent to red
    // or when the uncle is null
    else {
      // rotatating "<", ">" patterns of branch of tree to "/", "\" respectively
      // this will swap the positons of currentNode and its parent
      // since both currentNode and parent are red, this rotation wont affect
      // the black height of respective subtrees.
      // for left rotation at parnet, ie for branch with pattern ">"
      if (grandparent->left_child == currentNode->parent && currentNode->parent->right_child == currentNode) {
        Rotate_left(currentNode->parent);
        // the currentNode should now point to its parent
        // which is now its left child
        currentNode = currentNode->left_child;
      }
      // else for left rotation at parent
      else  if (grandparent->right_child == currentNode->parent && currentNode->parent->left_child == currentNode) {
        Rotate_right(currentNode->parent);
        // the currentNode should now point to its parent
        // which is now its right child
        currentNode = currentNode->right_child;
      }
      // at this stage the currentNode may or may not have changed
      // we need to rediscover the grandparent of currentNode
      grandparent = Grandparent(currentNode);
      // changing the colour of parent to black, will increase black height
      currentNode->parent->colour = false;
      // changing colour of grandparent to red to reduce black height
      grandparent->colour = true;
      // since the black height of uncle is one less than parent
      // rotation is needed to balance the tree
      // for right rotation at grandparent
      if (grandparent->left_child == currentNode->parent) {
        Rotate_right(grandparent);
      }
      // for left rotation at grandparent
      else {
        Rotate_left(grandparent);
      }
      // the tree is now balanced
      return;
    }
  }
}

// to return the grandparent of currentNode
template <class T>
node<T>* myrbt<T>::Grandparent(node<T>* currentNode) {
  if (currentNode != NULL && currentNode->parent != NULL) {
    return currentNode->parent->parent;
  }
  return NULL;
}

// to return the uncle of currentNode
template <class T>
node<T>* myrbt<T>::Uncle(node<T>* currentNode) {
  node<T>* grandparent = Grandparent(currentNode);
  // if no grandparent exits than no uncle exits
  if (!grandparent) {
    return NULL;
  }
  if (grandparent->left_child == currentNode->parent) {
    return grandparent->right_child;
  }
  else {
    return grandparent->left_child;
  }
}

// to return the uncle of currentNode
template <class T>
node<T>* myrbt<T>::Sibling(node<T>* currentNode) {
  node<T>* parent = currentNode->parent;
  // if no grandparent exits than no sibling exits
  if (!parent) {
    return NULL;
  }
  if (parent->left_child == currentNode) {
    return parent->right_child;
  }
  else {
    return parent->left_child;
  }
}

// rotate right by rehooking
// has complexity O(1)
template <class T>
void myrbt<T>::Rotate_right(node<T>* currentNode) {
  node<T>* left_child = currentNode->left_child;
  node<T>* parent = currentNode->parent;
  // rehooking
  currentNode->left_child = left_child->right_child;
  left_child->right_child = currentNode;
  left_child->parent = parent;
  currentNode->parent = left_child;
  // rehooking left child to the old parent of currentNode
  if (!parent) {
    // if parent is null,
    // meaning the currentNode is root,
    // changing the root to left child
    root = left_child;
  }
  else if (parent->left_child == currentNode) {
    parent->left_child = left_child;
  }
  else {
    parent->right_child = left_child;
  }
}

// rotate left by rehooking
// has complexity O(1)
template <class T>
void myrbt<T>::Rotate_left(node<T>* currentNode) {
  node<T>* right_child = currentNode->right_child;
  node<T>* parent = currentNode->parent;
  // rehooking
  currentNode->right_child = right_child->left_child;
  right_child->left_child = currentNode;
  right_child->parent = parent;
  currentNode->parent = right_child;
  // rehooking right child to the old parent of currentNode
  if (!parent) {
    // if parent is null,
    // meaning the currentNode is root,
    // changing the root to right child
    root = right_child;
  }
  else if (parent->left_child == currentNode) {
    parent->left_child = right_child;
  }
  else {
    parent->right_child = right_child;
  }
}


// finding minimum of given node
// complexity O(log(n))
template <class T>
T myrbt<T>::Find_min(node<T>* currentNode) {
  // minimum value of a subtree is the leftmost
  // child of this subtree, if no left child then currentNode
  // is the minimum of this subtree
  node<T>* left_child = currentNode->left_child;
  while (left_child) {
    currentNode = left_child;
    left_child = left_child->left_child;
  }
  return currentNode->value;
}

// finding maximum of given node
// complexity O(log(n))
template <class T>
T myrbt<T>::Find_max(node<T>* currentNode) {
  // maximum value of a subtree is the rightmost
  // child of this subtree, if no right child then currentNode
  // is the maximum of this subtree
  node<T>* right_child = currentNode->right_child;
  while (right_child) {
    currentNode = right_child;
    right_child = right_child->right_child;
  }
  return currentNode->value;
}

// finding maximum of tree
// complexity O(log(n))
template <class T>
T myrbt<T>::Find_max() {
  return Find_max(root);
}

// finding minmum of tree
// complexity O(log(n))
template <class T>
T myrbt<T>::Find_min() {
  return Find_min(root);
}

// finding the node address in heap,
// whoes value is passed as argument
// complexity O(log(n))
template <class T>
node<T>* myrbt<T>::Find_node(T value) {
  node<T>* currentNode = root;
  while (currentNode) {
    if (currentNode->value == value) {
      // found
      return currentNode;
    }
    if (currentNode->value > value) {
      // on left subtree
      currentNode = currentNode->left_child;
    }
    else {
      currentNode = currentNode->right_child;
    }
  }
  // value not found
  // returning NULL
  return NULL;
}

// finding Predecessor
// complexity O(log(n))
template <class T>
T myrbt<T>::Predecessor(node<T>* currentNode) {
  // Predecessor is the immediate smallest value in the entire tree
  // if current node has a left sub tree, then its Predecessor is the node
  // with maximum value in this left subtree, else current node is the max
  // valued child of this subtree and its Predecessor will be the node whose
  // right child is the current subtree, if there is no such node whose
  // right child is the current subtree, then the current node is the
  // smallest value in the entire tree, hence no Predecessor,
  // returns currentNode->value
  if (currentNode->left_child) {
    // if left child exits
    // Predecessor is the max valued child of left subtree
    return Find_max(currentNode->left_child);
  }
  node<T>* parent = currentNode->parent;
  // if the parent exits
  while (parent) {
    // if currentNode is the right child of parent
    if (parent->right_child == currentNode) {
      // then parent is the Predecessor
      return parent->value;
    }
    // if not then finding parent of currentNode's parent
    currentNode = parent;
    parent = parent->parent;
  }
  // if currentNode has no node acting as the right child of
  // currentNode's subtree then its the smallest value in the entire tree
  // returning root value
  return currentNode->value;
}

// finding Successor
// complexity O(log(n))
template <class T>
T myrbt<T>::Successor(node<T>* currentNode) {
  // Predecessor is the immediate largest value in the entire tree
  // if current node has a right sub tree, then its Successor is the node
  // with minimum value in this right subtree, else current node is the min
  // valued child of this subtree and its Successor will be the node whose
  // left child is the current subtree, if there is no such node whose
  // left child is the current subtree, then the current node is the
  // largest value in the entire tree, hence no Successor, returns currentNode->value
  if (currentNode->right_child) {
    // if right child exits
    // Successor is the min valued child of left subtree
    return Find_min(currentNode->right_child);
  }
  node<T>* parent = currentNode->parent;
  // if the parent exits
  while (parent) {
    // if currentNode is the left child of parent
    if (parent->left_child == currentNode) {
      // then parent is the Predecessor
      return parent->value;
    }
    // if not then finding parent of currentNode's parent
    currentNode = parent;
    parent = parent->parent;
  }
  // if currentNode has no node acting as the right child of
  // currentNode's subtree then its the smallest value in the entire tree
  // returning root value
  return currentNode->value;
}

// finding Predecessor
// complexity O(log(n))
template <class T>
T myrbt<T>::Predecessor(T value) {
  node<T>* currentNode = Find_node(value);
  if (currentNode)
    return Predecessor(Find_node(value));
  else
    return value;
}

// finding Successor
// complexity O(log(n))
template <class T>
T myrbt<T>::Successor(T value) {
  node<T>* currentNode = Find_node(value);
  if (currentNode)
    return Successor(Find_node(value));
  else
    return value;
}

// finding height of value
template <class T>
int myrbt<T>::Height() {
  // gives approximate height of tree
  return std::log(size_of_tree)/std::log(2)+1;
}

// deleting a node
// complexity O(log(n))
template <class T>
void myrbt<T>::Delete_node(T value) {
  // using non recursive method
  // if tree is empty
  if (!root) {
    return;
  }
  // checking if value to be deleted is the root
  if (root->value == value) {
    // changing the size of tree to 0
    size_of_tree = 0;
    root = NULL;
    // return void
    return;
  }
  // pointer which points to current node, stating from root
  node<T>* currentNode = root;
  bool key = false;
  // finding the node with value = given value
  // this loop has complexity O(log(n))
  while (!key) {
    if (currentNode->value > value) {
      // the entered value will be left child of current node
      // if currentNodes left child doesnt exit, value is not in the tree
      // return void
      if (!currentNode->left_child) {
        return;
      }
      else {
        // else currentNode will point to its left child
        currentNode = currentNode->left_child;
      }
    }
    else if (currentNode->value < value) {
      // the entered value will be right child of current node
      // if currentNodes right child doesnt exit, value is not in the tree
      // return void
      if (!currentNode->right_child) {
        return;
      }
      else {
        // else currentNode will point to its right child
        currentNode = currentNode->right_child;
      }
    }
    else {
      // value = currentNode-> value
      // if node has 2 childeren, swapping value of current
      // node with its Successor/Predecessor and deleting it's
      // Successor/Predecessor
      if (currentNode->left_child && currentNode->right_child) {
        // swapping with value in smaller subtree
        // chaning the value to find and delete
        value = Find_min(currentNode->right_child);
        // or value = Successor(currentNode);
        // swapping currentNodes value with its Successor
        currentNode->value = value;
        // changing the node pointed by currentNode
        currentNode = currentNode->right_child;
      }
      else {
        // else found the currentNode that is either a leaf node
        // or node with only one child
        key = true;
      }
    }
  }
  // finding the child of currentNode
  node<T>* child = NULL;
  // if left child is not null
  if (currentNode->left_child) {
    child = currentNode->left_child;
  }
  else {
    child = currentNode->right_child;
  }
  // if current node is black with only one red child
  // swapping colour with its child
  // note null nodes are black!
  if (currentNode->colour == false && child != NULL && child->colour == true) {
    currentNode->colour = true;
    child->colour = false;
  }
  // if the current node is red
  if (currentNode->colour) {
    // hook its child to its parent
    if (child) {
      child->parent = currentNode->parent;
    }
    // finding if currentNode is the left child of its parent
    if (currentNode->parent->left_child == currentNode) {
      currentNode->parent->left_child = child;
    }
    else {
      currentNode->parent->right_child = child;
    }
    // the tree is now balaenced
    return;
  }
  // the currentNode is a black colored leaf node
  // note a black node cant have one black child and one null as
  // the blach height of this null will be one less than other branch
  // the currentNode is stored and will be deleted later
  node<T>* toBeDeleted = currentNode;
  node<T>* sibling = NULL;
  while (key) {
    // if currentNode is root
    if (!currentNode->parent) {
      key = false;
      break;
    }
    sibling = Sibling(currentNode);
    // if sibling is red coloured node
    // implies parent is black
    // change the sibling to black by rotation about currentNodes parent
    // note a null sibling is black
    if (sibling != NULL && sibling->colour == true) {
      // rotating the node at parent will balence this subtree
      // the colour of sibling is changed to black, as parent is black
      // the black height of branch with toBeDleted node will remaing same
      sibling->colour = false;
      // if current node is on left branch
      if (currentNode->parent->left_child == currentNode) {
        // rotating about its parent will add 1 black node to this branch
        // as sibling will be new parent
        Rotate_right(currentNode->parent);
      }
      else {
        Rotate_left(currentNode->parent);
      }
      // after this the new sibling of currentNode will be black
      // new parent of currentNode may be red
    }
    // the sibling is black, if parent is red, then switching colours
    // will balaence the tree
    if (currentNode->parent->colour) {
      if (sibling) {
        sibling->colour = true;
      }
      currentNode->parent->colour = false;
      key = false;
    }
    // if black coloured sibling has null childeren
    // else if childeren of sibling are black
    // note if one child is black then other child cant be null
    else if (sibling == NULL || (sibling->left_child == NULL && sibling->right_child == NULL) ||
             (sibling->left_child != NULL && sibling->left_child->colour == false && sibling->right_child->colour == false)) {
      if (sibling) {
        // decreasing the black height of sibling
        sibling->colour = true;
      }
      currentNode = currentNode->parent;
      // note this is the only case which causes reitteration of this loop
    }
    // if one child is red
    // if left child is red
    else if (sibling->left_child != NULL && sibling->left_child->colour == true) {
      // if currentNode is left child, then "/ <" pattern will exits
      // changing colour of sibling->left_child to black, increases its black height
      sibling->left_child->colour = false;
      if (currentNode->parent->left_child == currentNode) {
        // rotating to make "/ <" pattern to "/ \"
        Rotate_right(sibling);
        // now rotating at the parent
        bool temp_colour =  currentNode->parent->colour;
        // changing the colour of parent to increase or retain
        // the height of current branch
        currentNode->parent->colour = false;
        // swapping colour with its parent will retain the
        // height of siblings branch, note siblings left child is new root
        // of old siblings subtree,
        // making sibling point to new sibling
        sibling = Sibling(currentNode);
        sibling->colour = temp_colour;
        Rotate_left(currentNode->parent);
        // no more violations exit
        key = false;
      }
      else {
        // swaping colour at rotate
        bool temp_colour =  currentNode->parent->colour;
        currentNode->parent->colour = false;
        sibling->colour = temp_colour;
        Rotate_right(currentNode->parent);
        key = false;
      }
    }
    else {
      // symmetrically
      // changing colour of sibling->right_child to black, increases its black height
      sibling->right_child->colour = false;
      if (currentNode->parent->right_child == currentNode) {
        Rotate_left(sibling);
        bool temp_colour =  currentNode->parent->colour;
        currentNode->parent->colour = false;
        // making sibling point to new sibling
        sibling = Sibling(currentNode);
        sibling->colour = temp_colour;
        Rotate_right(currentNode->parent);
        key = false;
      }
      else {
        bool temp_colour =  currentNode->parent->colour;
        currentNode->parent->colour = false;
        sibling->colour = temp_colour;
        Rotate_left(currentNode->parent);
        key = false;
      }
    }
  }
  // to delete the tobedeleted node
  if (toBeDeleted->parent->left_child == toBeDeleted) {
    toBeDeleted->parent->left_child = NULL;
  }
  else {
    toBeDeleted->parent->right_child = NULL;
  }
}

// prints the tree
template <class T>
void myrbt<T>::Print_inorder() {
  Print_inorder(root);
  std::cout << "\n";
}

// prints the tree
template <class T>
void myrbt<T>::Print_inorder(node<T>* root) {
  if (root == NULL)
    return;
  Print_inorder(root->left_child);
  std::cout << " " << root->value << ", ";
  Print_inorder(root->right_child);
}

// prints the model of tree
template <class T>
void myrbt<T>::Print_model() {
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
  // to represent the color of nodes
  // | | for black
  // # # for red
  std::string colour_symbol;
  // storing all the edge symbols at current level
  std::string print_edge;
  // storing the padding at each level
  std::string padding = "";
  Q.push(root);
  bool not_all_null = true;
  // to check if all remaining nodes in the Q are not_null
  // null nodes are displayed as space for padding
  // j is used to know the number of nodes in the current level
  int j = 1;
  // height of balenced tree = log(n),where n is the size of tree
  int current_height = int(std::log(size_of_tree)/std::log(2) ) + 2;
  std::cout << "Legend\tBlack nodes:|, Red nodes:#"  << "\n";
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
        // adding symbol to represent colour of node
        // if colour is red
        if (current_node->colour) {
          colour_symbol = "#";
        }
        else {
          colour_symbol = "|";
        }
        // casting int value to string then concatinating
        // adding the value of node poped into the string
        // containg all nodes at current level
        print_level += padding + colour_symbol + oss.str() + colour_symbol + padding;
        // adding current edge symbol to the print_edge string
        print_edge += padding + " "  +edge_symbol + " " + padding;
        // pushing the childeren of current_node
        // note: if the childeren are null,
        // they will be displayed as space/star
        Q.push(current_node->left_child);
        Q.push(current_node->right_child);
      }
      else {
        // the current_node is NUll
        // space/star is used to display the nodes
        print_level += padding + "   " + padding;
        // adding space insted of current edge symbol to the print_edge string
        print_edge += padding + "   " + padding;
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
#endif // ./my_red_black_tree_oop.hpp
