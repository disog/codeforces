/**
 * https://codeforces.com/contest/1984/submission/267284912
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

template <int N> struct Mint {
  int x;
  Mint(int a = 0) : x(a) {}
  operator int() { return x; }
  Mint &operator+=(int rhs) {
    if ((x += rhs) >= N) {
      x -= N;
    }
    return *this;
  }
};

using Int = Mint<998244353>;

void solve(int t) {
  int n;
  cin >> n;
  map<i64, Int> dp = {{0, 1}};
  for (int i = 0, a; i < n; ++i) {
    cin >> a;
    map<i64, Int> dp1;
    for (auto &&[c, u] : dp) {
      dp1[c + a] += u;
      dp1[abs(c + a)] += u;
    }
    dp = {*dp1.begin(), *dp1.rbegin()};
  }
  cout << dp.rbegin()->second << endl;
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