/**
 * https://codeforces.com/contest/1984/submission/267982709
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
  Int n;
  vector<Int> a(n);
  i64 ans = 0, sum = 0;
  for (auto &&ai : a) {
    sum += ai;
    ans = max(abs(sum), abs(ans + ai));
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
