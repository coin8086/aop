#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

//TODO: I thought 4000 should be enough, because C(4, 2) * C(3, 2) * C(2, 2) * 6 ^ 3 = 3888
//but the fact is sometimes 4000 is not enough. I wonder why.
#define BUF_SIZE 5000

using namespace std;

char ops[] = {'+', '-', '*', '/'};

class Node {
public:
  explicit Node(double av, char aop = 0, Node * aleft = 0, Node * aright = 0)
    : v(av), op(aop), left(aleft), right(aright) {}

  double v;
  char op; //'+', '-', '*', or '/'
  Node * left;
  Node * right;
};

inline bool calc(double a, double b, char op, double & r) {
  bool valid = true;
  switch (op) {
    case '+':
      r = a + b;
      break;
    case '-':
      r = a - b;
      break;
    case '*':
      r = a * b;
      break;
    default:
      valid = b;
      if (valid)
        r = a / b;
  }
  return valid;
}

bool bt(vector<Node *> & trees, vector<Node> & buf);

bool f(vector<Node *> & trees, vector<Node> & buf, int i, int j, int op) {
  double r;
  if (calc(trees[i]->v, trees[j]->v, op, r)) {
    vector<Node *> news;
    for (int l = 0; l < trees.size(); l++) {
      if (l != i && l != j)
        news.push_back(trees[l]);
    }
    buf.push_back(Node(r, op, trees[i], trees[j]));
    assert(buf.size() < BUF_SIZE);
    news.push_back(&buf.back());
    if (bt(news, buf)) {
      trees[0] = news[0];
      return true;
    }
  }
  return false;
}

bool bt(vector<Node *> & trees, vector<Node> & buf) {
  if (trees.size() == 1)
    return abs(trees[0]->v - 24) < 1e-6;

  for (int i = 0; i < trees.size(); i++) {
    for (int j = i + 1; j < trees.size(); j++) {
      for (int k = 0; k < 4; k++) {
        if (f(trees, buf, i, j, ops[k]) ||
          ((ops[k] == '-' || ops[k] == '/') && f(trees, buf, j, i, ops[k])))
          return true;
      }
    }
  }
  return false;
}

inline void output(const Node * n) {
  if (!n->left) {
    assert(!n->right && !n->op);
    cout << n->v;
  }
  else {
    assert(n->right && n->op);
    bool leaf = !n->left->left;
    if (!leaf)
      cout << '(';
    output(n->left);
    if (!leaf)
      cout << ')';
    cout << ' ' << n->op << ' ';
    leaf = !n->right->left;
    if (!leaf)
      cout << '(';
    output(n->right);
    if (!leaf)
      cout << ')';
  }
}

void expr(const vector<int> & n) {
  vector<Node> buf;
  vector<Node *> trees;
  //It's critical to reserve enough space, otherwise pointers to buf elements
  //may be invalid when it resizes.
  buf.reserve(BUF_SIZE);
  for (int i = 0; i < n.size(); i++) {
    buf.push_back(Node(n[i]));
    trees.push_back(&buf.back());
  }
  if (bt(trees, buf)) {
    output(trees[0]);
  }
  else {
    cout << "Impossible.";
  }
  cout << endl;
}

int main() {
  vector<int> v(4);
  while (true) {
    for (int i = 0; i < v.size(); i++) {
      int n;
      cin >> n;
      v[i] = n;
    }
    if (v.front() == 0)
      break;
    expr(v);
  }
  return 0;
}
