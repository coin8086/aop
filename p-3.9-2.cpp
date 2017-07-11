#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

struct Node {
  Node(char v) : val(v), left(0), right(0) {}
  char val;
  Node * left;
  Node * right;
};

typedef pair<int, int> Range;

struct NodeAndRange {
  NodeAndRange(Node * n, const Range & l, const Range & r) : parent(n), left(l), right(r) {}
  Node * parent;
  Range left;
  Range right;
};

Node * build(const vector<char> & pre, const vector<char> & in) {
  assert(pre.size() == in.size());

  Node * root = NULL;
  stack<NodeAndRange> s;
  for (int i = 0; i < pre.size(); i++) {
    Node * node = new Node(pre[i]);
    int k;
    if (s.empty()) {
      assert(!root);
      root = node;
      k = find(in.begin(), in.end(), pre[i]) - in.begin();
      s.push(NodeAndRange(node, make_pair(0, k), make_pair(k + 1, in.size())));
    }
    else {
      while (true) {
        const NodeAndRange & elem = s.top();
        if (elem.left.second - elem.left.first > 0) {
          k = find(in.begin() + elem.left.first, in.begin() + elem.left.second, pre[i]) - in.begin();
          if (k < elem.left.second) {
            elem.parent->left = node;
            s.push(NodeAndRange(node, make_pair(elem.left.first, k), make_pair(k + 1, elem.left.second)));
            break;
          }
        }
        if (elem.right.second - elem.right.first > 0) {
          k = find(in.begin() + elem.right.first, in.begin() + elem.right.second, pre[i]) - in.begin();
          if (k < elem.right.second) {
            elem.parent->right = node;
            s.push(NodeAndRange(node, make_pair(elem.right.first, k), make_pair(k + 1, elem.right.second)));
            break;
          }
        }
        s.pop();
      }
    }
  }
  return root;
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
  cout << p->val << ' ';
}

inline void output_postorder(const Node * p) {
  if (p->left)
    output(p->left);
  if (p->right)
    output(p->right);
  cout << p->val << endl;
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
