#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

typedef vector<vector<char> > Board;

typedef pair<int, int> Grid;

vector<Grid> solve(Board & b, const Grid & p1, const Grid & p2) {
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

  //Temporarily set target grid to '.' so that it can be reached by the BFS.
  char ch = b[p2.first][p2.second];
  b[p2.first][p2.second] = '.';

  int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  //The BFS targets at the status of corners and numbers of grids on the path.
  //The algorithm meets the primary dimension(least corners) as the Book says.
  //However, for the secondary one, it ensures that by the enqueuing order of
  //"the same level" of grids.
  while (!q.empty()) {
    int p = q.front();
    q.pop();
    if (p == t) { //Optionally: (... || turn[p] > 2)
      break;
    }
    else {
      int i = p / n;
      int j = p % n;
      bool stop[4] = {0, 0, 0, 0};

      //cout << "Processing (" << i << "," << j << ")..." << endl;

      //Try one step in each of the four directions from (i, j). Then the next
      //step involves grids that are one step further from (i, j).
      for (int s = 1;; s++) {
        //cout << "s=" << s << endl;
        int k;
        for (k = 0; k < 4; k++) {
          //cout << "k=" << k << endl;
          if (stop[k]) {
            continue;
          }
          int x = i + d[k][0] * s;
          int y = j + d[k][1] * s;
          int l = x * n + y;
          if (x >= 0 && x < m && y >= 0 && y < n && b[x][y] == '.' && !found[l]) {
            q.push(l);
            found[l] = true;
            turn[l] = turn[p] + 1;
            pred[l] = p;
          }
          else {
            stop[k] = true;
          }
        }

        for (k = 0; k < 4; k++) {
          if (!stop[k])
            break;
        }
        if (k == 4) { //All stopped.
          break;
        }
      }
    }
  }

  //Set the old content back to target.
  b[p2.first][p2.second] = ch;

  //build path
  vector<Grid> res;
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
    vector<Grid> res = solve(b, make_pair(p1i, p1j), make_pair(p2i, p2j));
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
