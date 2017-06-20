#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

vector<int> preprocess(const vector<int> & a) {
  vector<int> b;
  bool positive = a[0] > 0 ? true : false;
  int s = 0;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] > 0) {
      if (positive) {
        s+= a[i];
      }
      else {
        b.push_back(s);
        s = a[i];
        positive = true;
      }
    }
    else {
      if (!positive) {
        s += a[i];
      }
      else {
        b.push_back(s);
        s = a[i];
        positive = false;
      }
    }
  }
  b.push_back(s); //Push the last sum
  return b;
}

int process(const vector<int> & b) {
  int i = (b[0] <= 0) ? 1 : 0;
  if (i + 2 >= b.size())
    return i < b.size() ? b[i] : 0;

  int max = b[i]; //max sum
  int sum = b[i]; //accumulative sum
  while (i + 2 < b.size()) {
    int sum2 = sum + b[i + 1] + b[i + 2];
    if (sum2 > std::max(sum, b[i + 2])) {
      if (sum2 > max)
        max = sum2;
      sum = sum2;
    }
    else {
      if (b[i + 2] > max)
        max = b[i + 2];
      sum = b[i + 2];
    }
    i += 2;
  }
  return max;
}

int max_sum(const vector<int> & a) {
  vector<int> b = preprocess(a);
  int max = process(b);
  if (max == 0) {
    max = *max_element(a.begin(), a.end());
  }
  return max;
}

int main() {
  string line;
  while (getline(cin, line)) {
    istringstream is(line);
    vector<int> a;
    int n;
    while (is >> n) {
      a.push_back(n);
    }
    cout << max_sum(a) << endl;
  }
}
