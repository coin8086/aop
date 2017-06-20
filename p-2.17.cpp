#include <iostream>
#include <vector>

using namespace std;

inline int prev(const vector<int> & a, int pos, int k) {
  int r = pos - k;
  if (r < 0)
    r += a.size();
  return r;
}

inline int next(const vector<int> & a, int pos, int k) {
  return (pos + k) % a.size();
}

inline void shift(vector<int> & a, int k, int i) {
  int p = i;
  int t = a[p];
  a[p] = a[prev(a, p, k)];
  p = next(a, p, k);
  while (p != i) {
    swap(t, a[p]);
    p = next(a, p, k);
  }
}

void shift(vector<int> & a, int k) {
  if (a.empty())
    return;
  k %= a.size();
  if (!k)
    return;
  if (a.size() % k == 0) {
    for (int i = 0; i < k; i++) {
      shift(a, k, i);
    }
  }
  else {
    shift(a, k, 0);
  }
}

int main() {
  int n, k;
  while (cin >> n >> k) {
    vector<int> v;
    v.reserve(n);
    int i;
    for (i = 0; i < n; i++) {
      int e;
      cin >> e;
      v.push_back(e);
    }
    shift(v, k);
    for (i = 0; i < v.size(); i++) {
      if (i)
        cout << ' ';
      cout << v[i];
    }
    cout << endl;
  }
  return 0;
}
