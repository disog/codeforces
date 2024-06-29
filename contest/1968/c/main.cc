/**
 * https://codeforces.com/contest/1968/submission/267255425
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

void solve(int t) {
  int n;
  cin >> n;
  int a = 501;
  for (int i = 0, x; i < n - 1; i++, a += x) {
    cout << a << ' ';
    cin >> x;
  }
  cout << a << endl;
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