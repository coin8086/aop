#include <list>
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class Queue {
private:

  class Element {
  public:
    T data;
    int index; //index in heap array h

    Element(const T & t) : data(t), index(0) {}
  };

  //Here is a list as a normal queue and an array-based heap of pointers to
  //elements in the array, since the pointer-based heap is complicated in
  //implementaion(see a paper at
  //https://www.cpp.edu/~ftang/courses/CS241/notes/Building_Heaps_With_Pointers.pdf
  //for details of that).
  list<Element> q;
  vector<Element *> h;

  void heap_adjust_upward(int i) {
    if (i <= 0)
      return;

    int p = (i - 1) / 2;
    if (h[p]->data < h[i]->data) {
      Element * t = h[p];
      h[p] = h[i];
      h[i] = t;
      h[p]->index = p;
      h[i]->index = i;
      heap_adjust_upward(p);
    }
  }

  void heap_adjust_downward(int i) {
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    int max = i;
    if (left < h.size() && h[left]->data > h[max]->data)
      max = left;
    if (right < h.size() && h[right]->data > h[max]->data)
      max = right;
    if (max != i) {
      Element * t = h[i];
      h[i] = h[max];
      h[max] = t;
      h[i]->index = i;
      h[max]->index = max;
      heap_adjust_downward(max);
    }
  }

  //Prohibit copy
  Queue(const Queue & q);
  Queue & operator =(const Queue & q);
public:

  Queue() {}

  T & max() {
    return h[0]->data;
  }

  //O(1)
  const T & max() const {
    return h[0]->data;
  }

  //O(log(N))
  void enqueue(const T & t) {
    q.push_back(Element(t));
    Element & e = q.back();
    h.resize(h.size() + 1);
    h[h.size() - 1] = &e;
    e.index = h.size() - 1;
    if (e.index)
      heap_adjust_upward(e.index);
  }

  //O(log(N))
  T dequeue() {
    Element e = q.front();
    q.pop_front();
    if (h.size() == 1) {
      h.clear();
    }
    else {
      h[e.index] = h[h.size() - 1];
      h[e.index]->index = e.index;
      h.resize(h.size() - 1);
      heap_adjust_downward(e.index);
    }
    return e.data;
  }
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
          cout << q.max() << endl;
          break;
      }
    }
  }
  return 0;
}
