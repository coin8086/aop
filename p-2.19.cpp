#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> Range;

bool cmp(const Range & a, const Range & b) {
  return a.first < b.first;
}

bool in_ranges(vector<Range> & ranges, const Range & target) {
  sort(ranges.begin(), ranges.end(), cmp);
  vector<Range> merged;
  int i = 0;
  while (i < ranges.size()) {
    int first = ranges[i].first;
    int second = ranges[i].second;
    for (i += 1; i < ranges.size(); i++) {
      if (ranges[i].first <= second) {
        if (second < ranges[i].second)
          second = ranges[i].second;
      }
      else
        break;
    }
    merged.push_back(make_pair(first, second));
  }
  bool in = false;
  typedef vector<Range>::iterator It;
  It it = upper_bound(merged.begin(), merged.end(), target, cmp);
  if (it != merged.begin()) {
    --it;
    if (it->first <= target.first && it->second >= target.second)
      in = true;
  }
  return in;
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
    cout << (in_ranges(ranges, t) ? "Yes" : "No") << endl;
  }
  return 0;
}
