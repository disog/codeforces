/**
 * https://codeforces.com/contest/1980/submission/267978668
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

struct Int {
  int x;
  Int() { cin >> x; }
  operator int() { return x; }
};

void solve(int t) {
  Int n;
  vector<Int> a(n);
  auto f = [&](int k) {
    for (int i = !k, prev = 1; i < n - 1; i++) {
      auto &a0 = a[i], &a1 = a[(i + 1 == k ? ++i : i) + 1];
      auto cur = gcd<int, int>(a0, a1);
      if (cur < prev) {
        return i;
      }
      prev = cur;
    };
    return 0;
  };
  auto j = f(n);
  auto ans = !j || j == n - 2 || !f(j - 1) || !f(j) || !f(j + 1) ? "YES" : "NO";
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
