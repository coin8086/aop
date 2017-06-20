#include <iostream>
#include <vector>

using namespace std;

int bt(const vector<int> & v, const int S, int s = 0, int k = -1, int n = 0) {
  if (s > S)
    return -1;
  if (n == v.size() / 2)
    return s;
  int r = 0;
  for (int i = k + 1; i < v.size(); i++) {
    int x = bt(v, S, s + v[i], i, n + 1);
    if (x >= 0) {
      if (x == S) {
        r = x;
        break;
      }
      else if (x > r)
        r = x;
    }
  }
  return r;
}

int sum(const vector<int> & v) {
  int S = 0;
  for (int i = 0; i < v.size(); i++)
    S += v[i];
  //clog << "SUM: " << S << endl;
  return bt(v, S / 2);
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
