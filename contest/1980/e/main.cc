/**
 * https://codeforces.com/contest/1980/submission/267825080
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
  int a[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  pair<int, int> b[n * m + 1];
  for (int i = 0; i < n; i++) {
    for (int j = 0, x; j < m; j++) {
      cin >> x;
      b[x] = {i, j};
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if ((j < m - 1 && b[a[i][j]].first != b[a[i][j + 1]].first) ||
          (i < n - 1 && b[a[i][j]].second != b[a[i + 1][j]].second)) {
        cout << "NO" << endl;
        return;
      }
    }
  }
  cout << "YES" << endl;
}

int main() {
#ifdef LOCAL
  freopen(path(__FILE__).replace_filename("input.txt").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}