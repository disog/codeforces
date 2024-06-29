/**
 * https://codeforces.com/contest/1986/submission/267295953
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

void solve(int t) {
  int n;
  string s;
  cin >> n >> s;
  int ans = INT_MAX;
  for (int i = 0; i < n - 1; i++) {
    int sum = (s[i] - '0') * 10 + s[i + 1] - '0';
    for (int j = 0; j < n; j++) {
      if (j == i) {
        j++;
        continue;
      }
      if (s[j] == '0') {
        cout << 0 << endl;
        return;
      }
      if (s[j] != '1') {
        if (sum == 1) {
          sum = 0;
        }
        sum += s[j] - '0';
      }
    }
    ans = min(ans, sum);
  }
  cout << ans << endl;
}

int main() {
#ifdef LOCAL
  freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}