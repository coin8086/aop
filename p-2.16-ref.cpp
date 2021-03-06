#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int ls(const vector<int> & a) {
  vector<int> lis(a.size());
  for (int i = 0; i < a.size(); i++) {
    lis[i] = 1;
    for (int j = 0; j < i; j++) {
      if (a[i] > a[j] && lis[j] + 1 > lis[i])
        lis[i] = lis[j] + 1;
    }
  }
  return *max_element(lis.begin(), lis.end());
}

int main() {
  int n = 0;
  while (true) {
    cin >> n;
    if (!n)
      break;
    vector<int> a;
    a.reserve(n);
    for (int i = 0; i < n; i++) {
      int v;
      cin >> v;
      a.push_back(v);
    }
    cout << ls(a) << endl;
  }
}
