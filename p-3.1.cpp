#include <iostream>
#include <string>
#include <cstring>

using namespace std;

bool contain(const string & s1, const string & s2) {
  //Suppose that i points to the head of a "rotated" string from s1.
  for (int i = 0; i < s1.size(); i++) {
    if (s1[i] == s2[0]) {
      int k = i;
      int l = 0;
      while (k < s1.size() && l < s2.size() && s1[k] == s2[l]) {
        k++;
        l++;
      }
      if (l == s2.size())
        return true;
      if (k != s1.size())
        continue;
      //Continue comparing with s1 from index 0 to i but not including i.
      k = 0;
      while (k < i && l < s2.size() && s1[k] == s2[l]) {
        k++;
        l++;
      }
      if (l == s2.size())
        return true;
    }
  }
  return false;
}

int main() {
  string s1, s2;
  while (cin >> s1 >> s2) {
    cout << (contain(s1, s2) ? "true" : "false") << endl;
  }
  return 0;
}
