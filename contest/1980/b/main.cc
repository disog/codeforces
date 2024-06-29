/**
 * https://codeforces.com/contest/1980/submission/267972719
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
  Int n, f, k;
  vector<Int> a(n);
  auto ans = "YES";
  if (k < n) {
    auto x = a[f - 1];
    greater<int> cmp;
    ranges::sort(a, cmp);
    ans = a[k - 1] > x ? "NO" : (a[k] < x ? "YES" : "MAYBE");
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
