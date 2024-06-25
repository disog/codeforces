/**
 * https://codeforces.com/contest/1968/submission/267254823
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n, m;
  string a, b;
  cin >> n >> m >> a >> b;
  int k = 0;
  for (int i = 0; k < n && i < m; ++i) {
    if (a[k] == b[i]) {
      ++k;
    }
  }
  cout << k << endl;
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