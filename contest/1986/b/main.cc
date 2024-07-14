/**
 * https://codeforces.com/contest/1986/submission/270399005
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void solve(int t) {
  Int n, m;
  vector<vector<Int>> a(n);
  for (auto &&row : a) {
    row.resize(m);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      auto u = i > 0 ? (int)a[i - 1][j] : 0;
      auto l = j > 0 ? (int)a[i][j - 1] : 0;
      auto d = i < n - 1 ? (int)a[i + 1][j] : 0;
      auto r = j < m - 1 ? (int)a[i][j + 1] : 0;
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
