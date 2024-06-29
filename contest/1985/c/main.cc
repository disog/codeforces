/**
 * https://codeforces.com/contest/1985/submission/267287839
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
  int ans = 0;
  i64 sum = 0;
  for (int i = 0, a, mx = 0; i < n; ++i) {
    cin >> a;
    sum += a;
    mx = max(mx, a);
    if (sum == 2 * mx) {
      ++ans;
    }
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