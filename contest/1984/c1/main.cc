/**
 * https://codeforces.com/contest/1984/submission/267277536
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
  cin >> n;
  i64 ans = 0, sum = 0;
  for (int i = 0, a; i < n; ++i) {
    cin >> a;
    sum += a;
    ans = max(abs(sum), abs(ans + a));
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