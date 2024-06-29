/**
 * https://codeforces.com/contest/1971/submission/267970325
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
  Int r;
  int ans = 0;
  for (i64 i = 1, a = i64(r) * r, b = i64(r + 1) * (r + 1); i <= r; i++) {
    ans += ceil(sqrt(b - i * i)) - ceil(sqrt(a - i * i));
  }
  cout << ans * 4 << endl;
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
