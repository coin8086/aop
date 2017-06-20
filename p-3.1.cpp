#include <iostream>
#include <string>
#include <cstring>

using namespace std;

bool contain(const string & s1, const string & s2) {
  if (s1.size() < s2.size())
    return false;
  string s3 = s1 + s1;
  return strstr(s3.c_str(), s2.c_str());
}

int main() {
  string s1, s2;
  while (cin >> s1 >> s2) {
    cout << (contain(s1, s2) ? "true" : "false") << endl;
  }
  return 0;
}
