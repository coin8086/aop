#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int multiply(const vector<int> & a, int except) {
  int r = 1;
  for (int i = 0; i < a.size(); i++) {
    if (i != except)
      r *= a[i];
  }
  return r;
}

int max_product(vector<int> & a) {
  sort(a.begin(), a.end());
  int c = 0;
  int cz = 0;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] < 0)
      c++;
    else if (a[i] == 0)
      cz++;
    else
      break;
  }
  if (cz > 1)
    return 0;
  if (cz == 1)
    return c % 2 ? 0 : multiply(a, c);
  if (!c)
    return multiply(a, 0);
  if (c == a.size())
    return a.size() % 2 ? multiply(a, a.size() - 1) : multiply(a, 0);
  if (c % 2 == 0)
    return multiply(a, c);
  return multiply(a, c - 1);
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
