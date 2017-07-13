#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

typedef vector<vector<char> > Board;

typedef pair<int, int> Point;

vector<Point> solve(Board & b, const Point & p1, const Point & p2) {
  int m = b.size();
  int n = b[0].size();
  int s = p1.first * n + p1.second;
  int t = p2.first * n + p2.second;
  int total = m * n;
  vector<int> pred(total, -1);
  vector<bool> found(total);
  vector<int> turn(total, INT_MAX);
  queue<int> q;
  q.push(s);
  found[s] = true;
  turn[s] = -1;

  //Temporarily set target point to '.' so that it can be reached by the alg.
  char ch = b[p2.first][p2.second];
  b[p2.first][p2.second] = '.';

  while (!q.empty()) {
    int p = q.front();
    q.pop();
    if (p == t) { //Optionally: (... || turn[p] > 2)
      break;
    }
    else {
      int i = p / n;
      int j = p % n;
      //to left
      for (int k = j - 1; k >= 0; k--) {
        int l = i * n + k;
        if (b[i][k] == '.' && !found[l]) {
          q.push(l);
          found[l] = true;
          turn[l] = turn[p] + 1;
          pred[l] = p;
        }
        else {
          break;
        }
      }
      //to right
      for (int k = j + 1; k < n; k++) {
        int l = i * n + k;
        if (b[i][k] == '.' && !found[l]) {
          q.push(l);
          found[l] = true;
          turn[l] = turn[p] + 1;
          pred[l] = p;
        }
        else {
          break;
        }
      }
      //to top
      for (int k = i - 1; k >= 0; k--) {
        int l = k * n + j;
        if (b[k][j] == '.' && !found[l]) {
          q.push(l);
          found[l] = true;
          turn[l] = turn[p] + 1;
          pred[l] = p;
        }
        else {
          break;
        }
      }
      //to bottom
      for (int k = i + 1; k < m; k++) {
        int l = k * n + j;
        if (b[k][j] == '.' && !found[l]) {
          q.push(l);
          found[l] = true;
          turn[l] = turn[p] + 1;
          pred[l] = p;
        }
        else {
          break;
        }
      }
    }
  }
  //Set the old content back to target.
  b[p2.first][p2.second] = ch;

  //build path
  vector<Point> res;
  if (pred[t]) {
    int p = t;
    while (p != s) {
      res.push_back(make_pair(p / n, p % n));
      p = pred[p];
    }
    reverse(res.begin(), res.end());
  }
  return res;
}

int main() {
  int m, n;
  cin >> m >> n;
  Board b(m);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      char ch;
      cin >> ch;
      b[i].push_back(ch);
    }
  }
  int p1i, p1j, p2i, p2j;
  while (cin >> p1i >> p1j >> p2i >> p2j) {
    vector<Point> res = solve(b, make_pair(p1i, p1j), make_pair(p2i, p2j));
    if (res.empty()) {
      cout << "Impossible!";
    }
    else {
      for (int i = 0; i < res.size(); i++) {
        cout << "(" << res[i].first << "," << res[i].second << ") ";
      }
    }
    cout << endl;
  }
  return 0;
}
