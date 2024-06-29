/**
 * https://codeforces.com/contest/1971/submission/267934966
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
  int n, k, q;
  cin >> n >> k >> q;
  Vec a(k, 1), b(k, 1);
  auto f = [&](int d) -> int {
    int j = ranges::upper_bound(a, d) - a.begin() - 1;
    if (j >= a.size() - 1) {
      return b.back();
    }
    return b[j] + i64(d - a[j]) * (b[j + 1] - b[j]) / (a[j + 1] - a[j]);
  };
  for (int i = 0, d; i < q; ++i) {
    cin >> d;
    cout << f(d) << ' ';
  }
  cout << endl;
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