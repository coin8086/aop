#include <vector>
#include <set>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

class Sudoku {
public:
  typedef vector<vector<int> > Matrix;

  static Matrix generate(int blanks = 40) {
    seed_rand();

    //Generate a full matrix
    Matrix m(9, vector<int>(9));
    bool res = generate(m);
    output(m);
    cout << "------------------" << endl;
    assert(res && check(m));

    //Make some grids blank.
    if (blanks < 10) {
      blanks = 10;
    }
    else if (blanks > 60) {
      blanks = 60;
    }
    set<int> indexes;
    while (indexes.size() < blanks) {
      int x = rand_select(81);
      indexes.insert(x);
    }
    for (set<int>::iterator it = indexes.begin(); it != indexes.end(); ++it) {
      int i = *it / 9;
      int j = *it % 9;
      m[i][j] = 0;
    }

    return m;
  }

  static bool check(const Matrix & m) {
    //check each row
    for (int i = 0; i < 9; i++) {
      vector<int> put(10);
      for (int j = 0; j < 9; j++) {
        if (m[i][j] && ++put[m[i][j]] > 1)
          return false;
      }
    }
    //check each column
    for (int i = 0; i < 9; i++) {
      vector<int> put(10);
      for (int j = 0; j < 9; j++) {
        if (m[j][i] && ++put[m[j][i]] > 1)
          return false;
      }
    }
    //check each 3x3 square
    for (int s = 0; s < 9; s++) {
      int r = (s / 3) * 3;
      int c = (s % 3) * 3;
      vector<int> put(10);
      for (int i = r; i < r + 3; i++) {
        for (int j = c; j < c + 3; j++) {
          if (m[i][j] && ++put[m[i][j]] > 1)
            return false;
        }
      }
    }
    return true;
  }

  static void output(const Matrix & m) {
    for (int i = 0; i < m.size(); i++) {
      for (int j = 0; j < m[i].size(); j++) {
        char ch = m[i][j] > 0 ? '0' + m[i][j] : '?';
        cout << ch << ' ';
      }
      cout << endl;
    }
  }

private:
  static bool generate(Matrix & m, int k = 0) {
    if (k == 81)
      return true;

    int i = k / 9;
    int j = k % 9;
    int r = rand_select(1000);
    for (int n = 0; n < 9; n++) {
      int n2 = (n + r) % 9 + 1;
      m[i][j] = n2;
      if (check(m) && generate(m, k + 1))
        return true;
    }
    m[i][j] = 0;
    return false;
  }

  static inline void seed_rand() {
    srand(time(0));
  }

  static inline int rand_select(int n) {
    return rand() % n;
  }
};

int main() {
  int n;
  while (cin >> n) {
    Sudoku::Matrix m = Sudoku::generate(n);
    Sudoku::output(m);
  }
  return 0;
}

