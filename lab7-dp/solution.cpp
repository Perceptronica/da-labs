#include <bits/stdc++.h>

using namespace std;

int main() {
  string s;
  cin >> s;
  size_t s_sz = s.size();
  uint64_t D[s_sz][s_sz];
  for (size_t i = 0; i < s_sz; ++i) {
    for (size_t j = 0; j < s_sz; ++j) {
      if (i == j) { // one char string is a palindrome
        D[i][j] = 1;
      } else if (i > j) {
        D[i][j] = 0;
      }
    }
  }

  for (size_t len = 2; len <= s_sz; ++len) {
    for (size_t i = 0; i <= s_sz - len; ++i) {
      size_t j = i + len - 1;
      if (s[i] == s[j]) {
        D[i][j] = D[i + 1][j] + D[i][j - 1] + 1;
      } else {
        D[i][j] = D[i + 1][j] + D[i][j - 1] - D[i + 1][j - 1];
      }
    }
  } 

  cout << D[0][s_sz - 1] << endl;
}
