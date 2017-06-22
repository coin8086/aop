#include <iostream>

using namespace std;

typedef unsigned char byte;

int solve(byte b) {
  int c = 0;
  while (b) {
    if (b & 0x1)
      c++;
    b >>= 1;
  }
  return c;
}

int main() {
  //b must not be of type byte, that is unsigned char. If that, cin would read
  //in a char, say '1', instead of integer 1.
  int b;
  while (cin >> b) {
    cout << solve(b) << endl;
  }
  return 0;
}
