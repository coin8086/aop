#include <iostream>
#include <vector>

using namespace std;

/*
 * Put a[i] directly to its target postion a[j], where j = (i + k) % N. Then
 * put the old a[j] to its target. Repeat the procedure N times and it solves.
 * However, there's a special case in which i's target is j and j's target is
 * i. For example, N = 4 and k = 2. That means the followings:
 * (i + k) % N = j
 * (j + k) % N = i
 * <=>
 * i + k = a * N + j
 * j + k = b * N + i
 * =>
 * 2 * k = (a + b) * N
 * <=> (2 * k) % N == 0 (1)
 * Since 0 <= 2k < 2N, (1) is when and only when 2 * k == N
 */
void solve(vector<int> & a, int k) {
  int N = a.size();
  k %= N;
  if (k * 2 == N) {
    //Just swap a[i] and a[i + k]
    for (int i = 0; i < k; i++) {
      int j = i + k; //target position, i.e. (i + k) % N
      int t = a[j];
      a[j] = a[i];
      a[i] = t;
    }
  }
  else {
    int t = a[0]; //source value
    int i = 0;    //source position
    for (int c = 0; c < N; c++) {
      int j = (i + k) % N; //target position
      int t2 = a[j];
      a[j] = t;
      i = j;
      t = t2;
    }
  }
}

int main() {
  int n, k;
  while (cin >> n >> k) {
    vector<int> v;
    v.reserve(n);
    int i;
    for (i = 0; i < n; i++) {
      int e;
      cin >> e;
      v.push_back(e);
    }
    solve(v, k);
    for (i = 0; i < v.size(); i++) {
      if (i)
        cout << ' ';
      cout << v[i];
    }
    cout << endl;
  }
  return 0;
}
