/**
 * https://codeforces.com/contest/1984/submission/267983773
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

struct Int {
  int x;
  Int() { cin >> x; }
  operator int() { return x; }
};

template <int N> struct Mint {
  int x;
  Mint(int a = 0) : x(a) {}
  operator int() { return x; }
  int operator+=(int rhs) { return (x += rhs) >= N ? x -= N : x; }
  int operator-=(int rhs) { return (x -= rhs) < 0 ? x += N : x; }
};

using Mint1 = Mint<998244353>;

void solve(int t) {
  Int n;
  vector<Int> a(n);
  map<i64, Mint1> dp = {{0, 1}};
  for (auto &&ai : a) {
    map<i64, Mint1> dp1;
    for (auto &&[c, u] : dp) {
      dp1[c + ai] += u;
      dp1[abs(c + ai)] += u;
    }
    dp = {*dp1.begin(), *dp1.rbegin()};
  }
  cout << dp.rbegin()->second << endl;
}

int main() {
#ifdef LOCAL
  using filesystem::path;
  freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}
