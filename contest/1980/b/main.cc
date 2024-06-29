/**
 * https://codeforces.com/contest/1980/submission/267935947
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
  int n, f, k;
  cin >> n >> f >> k;
  Vec a(n, 1);
  auto ans = "YES";
  if (k < n) {
    auto x = a[f];
    ranges::sort(a, greater<int>());
    ans = a[k - 1] > x ? "NO" : (a[k] < x ? "YES" : "MAYBE");
  }
  cout << ans << endl;
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