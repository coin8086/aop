#include <iostream>
#include <cctype>
#include <queue>

using namespace std;

class Node {
public:
  int value;
  Node * left;
  Node * right;
  int level;

  Node(int v) : value(v), left(0), right(0), level(0) {}

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

  Node * root() { return _root; }

  void clear() {
    if (_root) {
      _root->cascade_del();
      _root = 0;
    }
  }

private:
  Node * _root;
};

void output_in_level(Node * n) {
  int level = 0;
  queue<Node *> q;
  q.push(n);
  n->level = 0;
  while (!q.empty()) {
    n = q.front();
    q.pop();
    if (level < n->level) {
      cout << endl;
      level++;
    }
    else if (level) {
      cout << ' ';
    }
    cout << n->value;
    if (n->left) {
      n->left->level = n->level + 1;
      q.push(n->left);
    }
    if (n->right) {
      n->right->level = n->level + 1;
      q.push(n->right);
    }
  }
}

int output_in_level(Node * n, int l) {
  int level = 0;
  int r = 0;
  queue<Node *> q;
  q.push(n);
  n->level = 0;
  while (!q.empty()) {
    n = q.front();
    q.pop();
    if (level < n->level) {
      level++;
      if (level > l)
        break;
    }
    else if (level && level == l) {
      cout << ' ';
    }
    if (level == l) {
      cout << n->value;
      r = 1;
    }
    if (n->left) {
      n->left->level = n->level + 1;
      q.push(n->left);
    }
    if (n->right) {
      n->right->level = n->level + 1;
      q.push(n->right);
    }
  }
  return r;
}

int main() {
  Tree t;
  int n;
  while (cin >> t) {
    output_in_level(t.root());
    cout << endl << endl;
    cin >> n;
    for (int i = 0; i < n; i++) {
      int l;
      cin >> l;
      int r = output_in_level(t.root(), l);
      cout << " : " << r << endl;;
    }
    cout << endl;
  }
  return 0;
}
