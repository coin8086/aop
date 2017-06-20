#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

#define BITS 20

using namespace std;

typedef unsigned long long uint;

vector<uint> fv;

inline void init() {
  fv.reserve(BITS);
  fv.push_back(0);
  for (int i = 1; i < BITS; i++) {
    fv[i] = fv[i - 1] * 10 + pow(10, i - 1);
    //clog << fv[i] << endl;
  }
}

inline vector<uint> dissect(uint n) {
  vector<uint> v;
  while (n) {
    v.push_back(n % 10);
    n /= 10;
  }
  return v;
}

inline uint num(const vector<uint> & v, int i) {
  uint r = 0;
  for (; i >= 0; i--) {
    r *= 10;
    r += v[i];
  }
  return r;
}

uint count(uint n) {
  uint c = 0;
  vector<uint> v = dissect(n);
  assert(v.size() <= BITS);
  for (int i = v.size() - 1; i > 0; i--) {
    if (v[i] == 1) {
      c += fv[i] + num(v, i - 1) + 1;
    }
    else if (v[i] > 1) {
      c += fv[i] * v[i] + pow(10, i);
    }
  }
  if (v[0] >= 1)
    c += 1;
  return c;
}

uint max_n() {
  uint n = 2;
  uint prev = n;
  while (true) {
    uint c = count(n);
    //clog << c << ' ' << n << ' ' << prev << endl;
    if (c == n)
      break;
    else if (c < n) {
      prev = n;
      n += n;
    }
    else {
      n = (prev + n) / 2;
    }
  }
  return n;
}

int main(int argc, char ** argv) {
  init();
  uint n;
  if (argc > 1 && argv[1][0] == 'm' ) {
    n = max_n();
    cout << "f(" << n << ") = " << n << endl;
  }
  else {
    while (cin >> n) {
      cout << count(n) << endl;
    }
  }
  return 0;
}
