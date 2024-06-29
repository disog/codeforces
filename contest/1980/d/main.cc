/**
 * https://codeforces.com/contest/1980/submission/267938691
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
  int n;
  cin >> n;
  Vec a(n, 1);
  a[0] = 1;
  auto f = [&](int k) {
    for (int i = 0, prev = 1; i < n && k < n; i++) {
      auto a0 = a[i], a1 = a[(i + 1 == k ? ++i : i) + 1];
      auto cur = gcd(a0, a1);
      if (cur < prev) {
        return i;
      }
      prev = cur;
    };
    return 0;
  };
  auto ans = "YES";
  int j = f(0);
  if (j > 0) {
    ans = "NO";
    for (int k = 0; k < 3; k++) {
      if (f(j + k - 1) == 0) {
        ans = "YES";
        break;
      }
    }
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