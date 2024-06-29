/**
 * https://codeforces.com/contest/1980/submission/267936524
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

template <typename T = int> struct Vec : vector<T> {
  Vec(int n, int s = 0) : vector<int>(n + s) {
    for (int i = s; i < n + s; i++) {
      cin >> (*this)[i];
    }
  }
};

void solve(int t) {
  int n, m;
  cin >> n;
  Vec a(n), b(n);
  cin >> m;
  map<int, int> count;
  int d;
  for (int i = 0; i < m; ++i) {
    cin >> d;
    count[d]++;
  }
  auto ans = "NO";
  for (int i = 0; i < n; ++i) {
    if (b[i] != a[i] && !count[b[i]]--) {
      ans = "NO";
      break;
    }
    if (b[i] == d) {
      ans = "YES";
    }
  }
  cout << ans << endl;
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