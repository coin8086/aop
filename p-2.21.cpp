#include <iostream>
#include <cstring>
#include <csignal>
#include <cstdlib>

using namespace std;

typedef unsigned long long ull;

/*
 * If x is the sum of a sequence of continuous positve integers, say
 * x = a + (a + 1) + (a + 2) + ... + (a + n - 1)
 * in which a >= 1, n >= 2
 * Then x = a * n + n * (n - 1) / 2
 *
 * Let s(n) = 1 + 2 + 3 + ... + n = (1 + n) * n / 2, then
 * x = a * n + s(n - 1)
 * Thus if (x - s(n - 1)) % n == 0, then a is such an integer. So we can
 * compute all such sequences for x starting given n = 2, 3, 4, ...
 *
 * To get the upper bound of n, let a = 1 and x as big as possible within 2^63
 * (if x is of type long long, or 2^64 if x is of type unsigned long long. For
 * easy computing as below, we choose 2^63).
 *
 * When a = 1, then
 * x = n + n * (n - 1) / 2 =>
 * n = sqr(2 * x + 1 / 4) - 1 / 2 =>
 * n < sqr(2 * x) =>
 * n < sqr(2 * 2^63) = 2^32
 */
void solve(ull x) {
  ull N = 1;
  N = N << 32;
  ull n;
  ull a;
  ull s;
  bool not_found = true;
  for (n = 2, s = 1; n < N && x > s; s += n, n++) {
    //s = 1 + 2 + ... + (n - 1)
    if ((x - s) % n == 0) {
      not_found = false;
      ull a = (x - s) / n;
      cout << a << ' ' << n << endl;
    }
  }
  if (not_found) {
    cout << "Not found!" << endl;
  }
  cout << endl;
}

ull max_x;
ull max_count = 0;

void solve3() {
  ull X = 1;
  X = (X << 63) - 1;
  ull N = 1;
  N = N << 32;
  for (ull x = X; x > 1; x--) {
    clog << x << endl;
    ull n;
    ull a;
    ull s;
    ull count = 0;
    for (n = 2, s = 1; n < N && x > s; s += n, n++) {
      //s = 1 + 2 + ... + (n - 1)
      if ((x - s) % n == 0) {
        count++;
      }
    }
    if (count > max_count) {
      max_count = count;
      max_x = x;
    }
  }
  cout << max_x << ' ' << max_count << endl;
}

void signalHandler(int signum) {
  cout << "Interrupt signal (" << signum << ") received.\n";
  cout << "Max count of sequences: " << max_count << " for: " << max_x << endl;
  exit(signum);
}

int main(int argc, char ** argv) {
  signal(SIGINT, signalHandler);
  if (argc > 1 && !strcmp(argv[1], "-i")) {
    ull x;
    while (cin >> x) {
      solve(x);
    }
  }
  else {
    solve3();
  }
}
