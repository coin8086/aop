#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <climits>

using namespace std;

typedef vector<int> Meeting;

inline bool different(const set<int> & people, const Meeting & m) {
  for (int i = 0; i < m.size(); i++) {
    if (people.count(m[i]))
      return false;
  }
  return true;
}

inline void add(set<int> & people, const Meeting & m) {
  for (int i = 0; i < m.size(); i++) {
    people.insert(m[i]);
  }
}

int bt(const vector<Meeting> & meetings, vector<set<int> > & parallels,
  vector<bool> & arranged, int unarranged_count)
{
  if (!unarranged_count) {
    return parallels.size() - 1; //The last is always empty.
  }
  int i = 0;
  for (; i < meetings.size(); i++) {
    if (!arranged[i])
      break;
  }
  arranged[i] = true;
  int m = INT_MAX;
  for (int j = 0; j < parallels.size(); j++) {
    if (different(parallels[j], meetings[i])) {
      set<int> backup = parallels[j];
      add(parallels[j], meetings[i]);
      if (backup.empty()) {
        parallels.resize(parallels.size() + 1); //Ensure the last is empty.
      }
      int r = bt(meetings, parallels, arranged, unarranged_count - 1);
      if (r < m)
        m = r;
      parallels[j] = backup;
      if (backup.empty()) {
        parallels.resize(parallels.size() - 1); //Ensure the last is empty.
      }
    }
  }
  arranged[i] = false;
  return m;
}

int minimum_time(const vector<Meeting> & meetings, int t) {
  vector<set<int> > parallels(1);
  int unarranged_count = meetings.size();
  vector<bool> arranged(unarranged_count, false);

  return bt(meetings, parallels, arranged, unarranged_count) * t;
}

int main() {
  int n, t;
  while (cin >> n >> t) {
    vector<Meeting> meetings(n);
    cin.ignore(); //ignore Enf of Line
    for (int i = 0; i < n; i++) {
      string line;
      getline(cin, line);
      istringstream is(line);
      int person;
      while (is >> person) {
        meetings[i].push_back(person);
      }
    }
    cout << minimum_time(meetings, t) << endl;
  }
  return 0;
}
