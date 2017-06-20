#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int multiply(const vector<int> & a, int except) {
  int r = 1;
  for (int i = 0; i < a.size(); i++) {
    if (i != except)
      r *= a[i];
  }
  return r;
}

int max_product(const vector<int> & a) {
  int c = 0;
  int cz = 0;
  int max_i, max = INT_MIN;
  int min_i, min = INT_MAX;
  int min_p_i, min_p = INT_MAX;
  int max_n_i, max_n = INT_MIN;
  int z_i;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] < 0) {
      c++;
      if (a[i] > max_n) {
        max_n = a[i];
        max_n_i = i;
      }
    }
    else if (a[i] == 0) {
      cz++;
      z_i = i;
    }
    else {
      if (a[i] < min_p) {
        min_p = a[i];
        min_p_i = i;
      }
    }
    if (a[i] > max) {
      max = a[i];
      max_i = i;
    }
    if (a[i] < min) {
      min = a[i];
      min_i = i;
    }
  }
  if (cz > 1)
    return 0;
  if (cz == 1)
    return c % 2 ? 0 : multiply(a, z_i);
  if (!c)
    return multiply(a, min_i);
  if (c == a.size())
    return a.size() % 2 ? multiply(a, max_i) : multiply(a, min_i);
  if (c % 2 == 0)
    return multiply(a, min_p_i);
  return multiply(a, max_n_i);
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
    cout << max_product(v) << endl;
  }
  return 0;
}
