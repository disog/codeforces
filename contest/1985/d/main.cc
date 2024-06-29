/**
 * https://codeforces.com/contest/1985/submission/267290240
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
  int h1 = 0, h2 = 0, k = 0;
  for (int i = 0; i < n; ++i) {
    string row;
    cin >> row;
    auto pos = row.find('#');
    if (pos != string::npos) {
      if (!k) {
        k = pos + 1;
        h1 = i + 1;
      }
      h2 = i + 1;
    }
  }
  cout << (h1 + h2) / 2 << ' ' << k << endl;
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