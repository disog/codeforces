/**
 * https://codeforces.com/contest/1986/submission/267989121
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
  Int n, m;
  vector<vector<Int>> a(n);
  for (auto &&row : a) {
    row.resize(m);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      auto u = i > 0 ? a[i - 1][j] : 0;
      auto l = j > 0 ? a[i][j - 1] : 0;
      auto d = i < n - 1 ? a[i + 1][j] : 0;
      auto r = j < m - 1 ? a[i][j + 1] : 0;
      auto mx = max(u, max(l, max(d, r)));
      auto &cell = a[i][j];
      if (cell > mx) {
        cell.x = mx;
      }
      cout << cell << ' ';
    }
    cout << endl;
  }
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
