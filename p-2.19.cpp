#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> Range;

bool cmp(const Range & a, const Range & b) {
  return a.first < b.first;
}

vector<Range> merge(vector<Range> & a) {
  sort(a.begin(), a.end(), cmp);
  vector<Range> a2;
  a2.push_back(a[0]);
  for (int i = 1; i < a.size(); i++) {
    if (a[i].first > a2.back().second) {
      //Push a new Range into a2
      a2.push_back(a[i]);
    }
    else if (a[i].second > a2.back().second) {
      //Extend the last Range in a2
      a2.back().second = a[i].second;
    }
  }
  return a2;
}

bool search(const vector<Range> & a, int i, int j, const Range & r) {
  if (i >= j)
    return false;
  int m = (i + j) / 2;
  if (a[m].first <= r.first) {
    if (a[m].second >= r.second)
      return true;
    else
      return search(a, m + 1, j, r);
  }
  else {
    return search(a, i, m, r);
  }
}

bool solve(vector<Range> & ranges, const Range & target) {
  vector<Range> a = merge(ranges);
  return search(a, 0, a.size(), target);
}

int main() {
  int n;
  while (cin >> n) {
    vector<Range> ranges;
    ranges.reserve(n);
    int first, second;
    for (int i = 0; i < n; i++) {
      cin >> first >> second;
      ranges.push_back(make_pair(first, second));
    }
    cin >> first >> second;
    Range t = make_pair(first, second);
    cout << (solve(ranges, t) ? "Yes" : "No") << endl;
  }
  return 0;
}
