/**
 * https://codeforces.com/contest/1986/submission/267295180
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

void solve(int t) {
  int n, m;
  cin >> n >> m;
  int matrix[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> matrix[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      auto u = i > 0 ? matrix[i - 1][j] : 0;
      auto l = j > 0 ? matrix[i][j - 1] : 0;
      auto d = i < n - 1 ? matrix[i + 1][j] : 0;
      auto r = j < m - 1 ? matrix[i][j + 1] : 0;
      auto mx = max(u, max(l, max(d, r)));
      auto &cell = matrix[i][j];
      if (cell > mx) {
        cell = mx;
      }
      cout << cell << ' ';
    }
    cout << endl;
  }
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