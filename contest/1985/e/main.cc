/**
 * https://codeforces.com/contest/1985/submission/267987237
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

struct Int {
  int x;
  Int() { cin >> x; }
  operator int() { return x; }
};

void solve(int t) {
  Int x, y, z;
  i64 k;
  cin >> k;
  i64 ans = 0;
  for (int a = 1; a <= x; a++) {
    for (int b = 1; b <= y; b++) {
      if (k % (a * b)) {
        continue;
      }
      auto c = k / (a * b);
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
  using filesystem::path;
  freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}
