#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef map<int, map<int, map<int, int> > > Memo;

inline bool get(Memo & memo, int s, int k, int n, int & r) {
  r = memo[s][k][n];
  return r != 0;
}

inline void set(Memo & memo, int s, int k, int n, int r) {
  memo[s][k][n] = r;
}

int bt(const vector<int> & v, const int S, Memo & memo, int s = 0, int k = -1, int n = 0) {
  int r;
  if (get(memo, s, k, n, r))
    return r;
  if (s > S)
    return -1;
  if (n == v.size() / 2)
    return s;
  r = 0;
  for (int i = k + 1; i < v.size(); i++) {
    int x = bt(v, S, memo, s + v[i], i, n + 1);
    if (x >= 0) {
      if (x == S) {
        r = x;
        break;
      }
      else if (x > r)
        r = x;
    }
  }
  set(memo, s, k, n, r);
  return r;
}

int sum(const vector<int> & v) {
  int S = 0;
  for (int i = 0; i < v.size(); i++)
    S += v[i];
  //clog << "SUM: " << S << endl;
  Memo memo;
  return bt(v, S / 2, memo);
}

int main() {
  int n;
  while (cin >> n) {
    vector<int> v;
    v.reserve(n);
    for (int i = 0; i < n; i++) {
      int e;
      cin >> e;
      v.push_back(e);
    }
    cout << sum(v) << endl;
  }
  return 0;
}
