/**
 * https://codeforces.com/contest/1984/submission/267277074
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

void solve(int t) {
  string x;
  cin >> x;
  if (x.front() != '1' || x.back() == '9') {
    cout << "NO" << endl;
    return;
  }
  for (int i = 1; i < x.size() - 1; i++) {
    if (x[i] == '0') {
      cout << "NO" << endl;
      return;
    }
  }
  cout << "YES" << endl;
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