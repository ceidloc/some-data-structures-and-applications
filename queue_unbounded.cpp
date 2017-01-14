// To Create Unbounded Queue using Dynamic Memory allocation
#include <iostream>
typedef struct node {
  int value;
  node* next;
}node;
typedef struct queue {
  int length;
  node* head;
  node* tail;
}Q;
void enqueue(Q*, int);
void dequeue(Q*);
int queue_head(Q*);
int queue_tail(Q*);
void print_queue(Q*);
int main() {
  bool key = true;
  int n;
  // creating a struct queue var in stack memory
  Q q = {0, NULL, NULL};
  while (key) {
    std::cout << "0)insert multiple 1)enqueue, 2)dequeue 3)head, 4)tail 5)length -1)quit" << "\n";
    std::cin >> n;
    switch (n) {
      case 0: {
        std::cout << "enter number of elements:" << "\n";
        std::cin >> n;
        int value;
        for (int i = 0; i < n; i++) {
          std::cout << "enter value" << i+1 << ":\n";
          std::cin >> value;
          enqueue(&q, value);
        }
        print_queue(&q);
        break;
      }
      case 1: {
        std::cout << "enter number:" << "\n";
        std::cin >> n;
        enqueue(&q, n);
        print_queue(&q);
        break;
      }
      case 2: {
        // if queue is not empty
        if (q.head)
          std::cout << "the head is removed:" << queue_head(&q) << "\n";
        dequeue(&q);
        print_queue(&q);
        break;
      }
      case 3: {
        std::cout << "head is:" << queue_head(&q) << "\n";
        break;
      }
      case 4: {
        std::cout << "tail is:" << queue_tail(&q) << "\n";
        break;
      }
      case 5: {
        std::cout << "length is:" << q.length << "\n";
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

// to insert in the queue
void enqueue(Q* q, int n) {
  // creating a new node in heap
  node* new_node = ( node* ) malloc(sizeof (node));
  new_node->value = n;
  new_node->next = NULL;
  // if tail is null, ie queue is empty
  if (!q->tail) {
    q->head = new_node;
    q->tail = new_node;
  }
  else {
    // tail->next is now pointing to new_node
    q->tail->next = new_node;
    // tail of queue is now pointing to new_node
    q->tail = new_node;
  }
  // length of queue is increased
  q->length += 1;
}

// to remove the head of queue
void dequeue(Q* q) {
  // if head is null, then queue is empty
  if (!q->head)
    // returning void
    return;
  // changing the head of current queue
  q->head = q->head->next;
  // if new head is null, ie queue is empty
  if (!q->head)
    // tail is now also pointing to null
    q->tail = NULL;
  // reducing the length of queue
  q->length -= 1;
}

int queue_head(Q* q) {
  // if queue is empty
  if (!q->head)
    // return -1
    return -1;
  // else returing the value of the node in heap
  // pointed by head of the queue
  return q->head->value;
}

int queue_tail(Q* q) {
  // if queue is empty
  if (!q->tail)
    // returning -1
    return -1;
  // else returing the value of the node in heap
  // pointed by tail of the queue
  return q->tail->value;
}

// printing queue
void print_queue(Q* q) {
  node* tracer = q->head;
  // if queue is empty
  if (!tracer) {
    std::cout << "queue is empty!" << "\n";
    return;
  }
  std::cout << "queue:";
  while (tracer) {
    std::cout << tracer->value << ", ";
    tracer = tracer->next;
  }
  std::cout << "\n";
}
