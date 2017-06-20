#include <iostream>
#include <cctype>

using std::istream;
using std::ios_base;
using std::cin;
using std::cout;
using std::endl;

class Node {
public:
  int value;
  Node * left;
  Node * right;

  Node(int v) : value(v), left(0), right(0) {}

  void cascade_del() {
    if (left)
      left->cascade_del();
    if (right)
      right->cascade_del();
    delete this;
  }

  static Node * unserialize(istream & is) {
    char d;
    while (isspace(d = is.get()));
    if (d != '(') {
      is.setstate(ios_base::failbit);
      return 0;
    }
    while (isspace(d = is.get()));
    if (d == ')') {
      return 0;
    }
    is.unget();
    int v;
    if (!(is >> v)) {
      return 0;
    }
    Node * n = new Node(v);
    n->left = unserialize(is);  //To be strict, "is" needs some check here
    n->right = unserialize(is); //The same with above.
    while (isspace(d = is.get()));
    if (d != ')') {
      is.setstate(ios_base::failbit);
      n->cascade_del();
      return 0;
    }
    return n;
  }

private:
  Node(const Node & n);
  Node & operator = (const Node & n);
};

class Tree {
friend istream & operator >>(istream & is, Tree & t) {
  t.clear();
  Node * n = Node::unserialize(is);
  t._root = n;
  return is;
}

public:
  Tree() : _root(0) {}

  ~Tree() { clear(); }

  bool empty() const { return !_root; }

  const Node * root() const { return _root; }

  void clear() {
    if (_root) {
      _root->cascade_del();
      _root = 0;
    }
  }

private:
  Node * _root;
};

int max = 0;

int depth(const Node * n) {
  int ld = n->left ? depth(n->left) + 1 : 0;
  int rd = n->right ? depth(n->right) + 1 : 0;
  int m = ld + rd;
  if (m > max)
    max = m;
  return ld >= rd ? ld : rd;
}

int main() {
  Tree t;
  while (cin >> t) {
    max = 0;
    depth(t.root());
    cout << max << endl;
  }
  return 0;
}
