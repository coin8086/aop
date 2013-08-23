#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Node {
public:
  Node(char av) : v(av), left(0), right(0) {}
  char v;
  Node * left;
  Node * right;
};

inline int search(const vector<char> & in, int s, int e, char v) {
  int k = s;
  for (; k < e; k++) {
    if (in[k] == v)
      break;
  }
  assert(k != e);
  return k;
}

Node * build(const vector<char> & pre, int & i, const vector<char> & in, int s, int e) {
  if (i >= pre.size())
    return 0;
  char v = pre[i];
  Node * n = new Node(v);
  int k = search(in, s, e, v);
  if (k != s)
    n->left = build(pre, ++i, in, s, k);
  if (k != e - 1)
    n->right = build(pre, ++i, in, k + 1, e);
  return n;
}

inline Node * build(const vector<char> & pre, const vector<char> & in) {
  int i = 0;
  return build(pre, i, in, 0, in.size());
}

void destroy(Node * p) {
  if (p->left)
    destroy(p->left);
  if (p->right)
    destroy(p->right);
  delete p;
}

void output(const Node * p) {
  if (p->left)
    output(p->left);
  if (p->right)
    output(p->right);
  cout << p->v << ' ';
}

inline void output_postorder(const Node * p) {
  if (p->left)
    output(p->left);
  if (p->right)
    output(p->right);
  cout << p->v << endl;
}

int main() {
  int n;
  while (cin >> n) {
    vector<char> pre;
    pre.reserve(n);
    for (int i = 0; i < n; i++) {
      char v;
      cin >> v;
      pre.push_back(v);
    }
    vector<char> in;
    in.reserve(n);
    for (int i = 0; i < n; i++) {
      char v;
      cin >> v;
      in.push_back(v);
    }
    Node * tree = build(pre, in);
    output_postorder(tree);
    destroy(tree);
  }
  return 0;
}
