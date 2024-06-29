/**
 * https://codeforces.com/contest/1985/submission/267294074
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

void solve(int t) {
  int x, y, z;
  i64 k;
  cin >> x >> y >> z >> k;
  i64 ans = 0;
  for (int a = 1; a <= x; a++) {
    for (int b = 1; b <= y; b++) {
      if (k % (a * b)) {
        continue;
      }
      i64 c = k / (a * b);
      if (c > z) {
        continue;
      }
      ans = max(ans, i64(x - a + 1) * (y - b + 1) * (z - c + 1));
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