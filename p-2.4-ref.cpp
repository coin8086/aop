#include <iostream>

using namespace std;

typedef unsigned long long uint;

uint count(uint n) {
  uint c = 0;
  uint f = 1;
  uint lower = 0;
  uint curr = 0;
  uint higher = 0;
  while (n / f) {
    lower = n - (n / f) * f;
    curr = (n / f) % 10;
    higher = n / (f * 10);
    switch (curr) {
      case 0:
        c += higher * f;
        break;
      case 1:
        c += higher * f + lower + 1;
        break;
      default:
        c += (higher + 1) * f;
    }
    f *= 10;
  }
  return c;
}

int main(int argc, char ** argv) {
  uint n;
  while (cin >> n) {
    cout << count(n) << endl;
  }
  return 0;
}
