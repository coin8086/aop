#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class Node {
public:
  Node(const T & av) : v(av), next(0), pred(0), succ(0) {}
  T v;
  Node * next;
  Node * pred;
  Node * succ;
};

template <typename T>
class Queue {
public:
  Queue() : head(0), tail(0), max(0), min(0) {}

  ~Queue() { clear(); }

  void enqueue(const T & v) {
    Node<T> * n = new Node<T>(v);
    if (tail) {
      tail->next = n;
      tail = n;

      Node<T> * p = max;
      while (p && v <= p->v) {
        p = p->succ;
      }
      if (p) {
        Node<T> * pred = p->pred;
        if (pred) {
          pred->succ = n;
          n->pred = pred;
          n->succ = p;
          p->pred = n;
        }
        else {
          n->succ = p;
          p->pred = n;
          max = n;
        }
      }
      else {
        min->succ = n;
        n->pred = min;
        min = n;
      }
    }
    else {
      head = tail = n;
      max = min = n;
    }
  }

  T dequeue() {
    assert(head);
    if (head == max)
      max = max->succ;
    if (head == min)
      min = min->pred;
    if (head->succ)
      head->succ->pred = head->pred;
    if (head->pred)
      head->pred->succ = head->succ;
    T v = head->v;
    Node<T> * p = head->next;
    delete head;
    head = p;
    if (!head)
      tail = 0;
    return v;
  }

  const T & maxElement() const {
    return max->v;
  }

  void clear() {
    while (head) {
      Node<T> * p = head->next;
      delete head;
      head = p;
    }
    tail = 0;
    max = min = 0;
  }

private:
  Queue(const Queue & q);
  Queue & operator =(const Queue & q);

  Node<T> * head;
  Node<T> * tail;
  Node<T> * max;
  Node<T> * min;
};

int main() {
  int n;
  bool first = true;
  while (cin >> n) {
    if (first)
      first = false;
    else
      cout << endl;

    Queue<int> q;
    for (int i = 0; i < n; i++) {
      char ch;
      int v;
      cin >> ch;
      switch (ch) {
        case 'e':
          cin >> v;
          q.enqueue(v);
          break;

        case 'p':
          cout << q.dequeue() << endl;
          break;

        case 'm':
          cout << q.maxElement() << endl;
          break;
      }
    }
  }
  return 0;
}
