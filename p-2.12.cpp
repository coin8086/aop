#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;

pair<int, int> find_pair(vector<int> a, int sum) {
  pair<int, int> r;
  sort(a.begin(), a.end());
  typedef vector<int>::iterator It;
  for (It it = a.begin(); it != a.end(); ++it) {
    int first = *it;
    int second = sum - first;
    if (binary_search(it + 1, a.end(), second)) {
      r.first = first;
      r.second = second;
      break;
    }
  }
  return r;
}

int main() {
  int n, s;
  while (cin >> n >> s) {
    vector<int> v;
    v.reserve(n);
    for (int i = 0; i < n; i++) {
      int e;
      cin >> e;
      v.push_back(e);
    }
    pair<int, int> p = find_pair(v, s);
    cout << p.first << ' ' << p.second << endl;
  }
  return 0;
}
