#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int ls(const vector<int> & a) {
  int len = a.size();
  vector<int> lis(len);
  for (int i = len - 1; i >= 0; i--) {
    lis[i] = 1;
    for (int k = i + 1; k < len; k++) {
      if (a[k] > a[i] && lis[k] + 1 > lis[i])
        lis[i] = lis[k] + 1;
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
