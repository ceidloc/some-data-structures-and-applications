// To implement circular doubly linked list
#include <iostream>
typedef struct node {
  int value;
  node* prev;
  node* next;
}node;
typedef struct linked_list {
  int length;
  node* head;
  node* tail;
}L;
void insert_node(L*, int);
void delete_node(L*, int);
int linked_list_head(L*);
int linked_list_tail(L*);
void print_linked_list(L*);
int main() {
  bool key = true;
  int n;
  // creating a struct linked_list var in stack memory
  L l = {0, NULL, NULL};
  while (key) {
    std::cout << "0)insert multiple 1)insert_node, 2)delete_node 3)head, 4)tail, 5)length -1)quit" << "\n";
    std::cin >> n;
    switch (n) {
      case 0: {
        std::cout << "enter number of elements:" << "\n";
        std::cin >> n;
        int value;
        for (int i = 0; i < n; i++) {
          std::cout << "enter value" << i+1 << ":\n";
          std::cin >> value;
          insert_node(&l, value);
        }
        print_linked_list(&l);
        break;
      }
      case 1: {
        std::cout << "enter number:" << "\n";
        std::cin >> n;
        insert_node(&l, n);
        print_linked_list(&l);
        break;
      }
      case 2: {
        std::cout << "enter value to be deleted:" << "\n";
        std::cin >> n;
        delete_node(&l, n);
        print_linked_list(&l);
        break;
      }
      case 3: {
        std::cout << "head is:" << linked_list_head(&l) << "\n";
        break;
      }
      case 4: {
        std::cout << "tail is:" << linked_list_tail(&l) << "\n";
        break;
      }
      case 5: {
        std::cout << "length is:" << l.length << "\n";
        break;
      }
      case -1: {
        std::cout << "exiting.." << "\n";
        key = false;
        break;
      }
      default:
        std::cout << "wrong choice try again!"  << "\n";
        break;
    }
  }
  return 0;
}

// to insert in the linked_list
void insert_node(L* l, int n) {
  // creating a new node in heap
  node* new_node = ( node* ) malloc(sizeof (node));
  new_node->value = n;
  // new node is peceded by tail
  new_node->prev = l->tail;
  // if linked list is empty
  if (!l->tail) {
    l->tail = new_node;
    l->head = new_node;
    l->head->prev = new_node;
    l->head->next = new_node;
  }
  else {
    // new node is succeded by head
    new_node->next = l->head;
    // current head of linked list is now preceded by new node
    l->head->prev = new_node;
    // head of linked list is now new node
    l->head = new_node;
  }
  // next of tail is new node
  l->tail->next = new_node;
  l->length += 1;
}

// to remove a node from linked_list
void delete_node(L* l, int value) {
  node* tracer = l->head;
  // finding value in linked list
  while (tracer) {
    if (tracer->value == value) {
      tracer->prev->next = tracer->next;
      tracer->next->prev = tracer->prev;
      // if linked list has only one node
      if (l->tail == l->head) {
        l->tail = NULL;
        l->head = NULL;
        return;
      }
      // if tracer is the tail of linked list
      if (tracer == l->tail) {
        l->tail = tracer->prev;
      }
      // if tracer is the head of linked list
      if (tracer == l->head) {
        l->head = tracer->next;
      }
      l->length -= 1;
      return;
    }
    tracer = tracer->next;
  }
}

int linked_list_head(L* l) {
  // if linked_list is empty
  if (!l->head)
    // return -1
    return -1;
  // else returing the value of the node in heap
  // pointed by head of the linked_list
  return l->head->value;
}


int linked_list_tail(L* l) {
  // if linked_list is empty
  if (!l->tail)
    // return -1
    return -1;
  // else returing the value of the node in heap
  // pointed by head of the linked_list
  return l->tail->value;
}

// printing linked_list
void print_linked_list(L* l) {
  node* tracer = l->head;
  // if linked_list is empty
  if (!tracer) {
    std::cout << "linked_list is empty!" << "\n";
    return;
  }
  std::cout << "linked_list:";
  while (tracer != l->tail) {
    std::cout << tracer->value << ", ";
    tracer = tracer->next;
  }
  std::cout << l->tail->value <<"\n";
}
