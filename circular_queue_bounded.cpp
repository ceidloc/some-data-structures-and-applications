// Copyright 2017 Q)Implement Circular Queue bounded
#include <iostream>
typedef struct queue {
  int nodes[5];
  int head;
  int tail;
  int length = sizeof(nodes)/sizeof(int);
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
  // both the head and tail point to -1'th index of the nodes array
  Q q;
  q.head = -1;
  q.tail = -1;
  while (key) {
    std::cout << "0)insert multiple 1)enqueue, 2)dequeue 3)head, 4)tail -1)quit" << "\n";
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
  // if queue is empty
  if (q->tail == -1) {
    // initializing the queue
    q->nodes[0] = n;
    q->head = 0;
    q->tail = 0;
    // returing void
    return;
  }
  // incrementing tail of queue
  // note will move in cirular motion
  // limited by the length of nodes array
  int tail = (q->tail + 1) % q->length;
  // if the new index of tail points to head
  if (tail == q->head) {
    // queue is full
    std::cout << "queue is full!" << "\n";
    return;
  }
  // incrementing tail
  q->tail = tail;
  // adding value to new postion of tail
  q->nodes[q->tail] = n;
}

// to remove the head of queue
void dequeue(Q* q) {
  // if head is -1, then queue is empty
  if (q->head == -1)
    // returning void
    return;
  // if head is pointing to tail, ie
  // only one node in queue
  if (q->head == q->tail) {
    // emptying the queue
    // both head and tail now point to -1
    q->head = -1;
    q->tail = -1;
  }
  else {
    // head is now incremented
    // note will move in cirular motion
    // limited by the length of nodes array
    q->head = (q->head + 1) % q->length;
  }
}

int queue_head(Q* q) {
  // if queue is empty
  if (q->head == -1)
    // return -1
    return -1;
  // else returing the value at head index in nodes array
  // indexed by head of the queue
  return q->nodes[q->head];
}

int queue_tail(Q* q) {
  // if queue is empty
  if (q->tail == -1)
    // returning -1
    return -1;
  // else returing the value of the node in heap
  // indexed by tail of the queue
  return q->nodes[q->tail];
}

// printing queue
void print_queue(Q* q) {
  int tracer = q->head;
  // if queue is empty
  if (tracer == -1) {
    std::cout << "queue is empty!" << "\n";
    return;
  }
  std::cout << "queue:";
  while (tracer != q->tail) {
    std::cout << q->nodes[tracer] << ", ";
    tracer = (tracer +1) % q->length;
  }
  std::cout << q->nodes[q->tail] << "\n";
}
