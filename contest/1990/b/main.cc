/**
 * https://codeforces.com/contest/1990/submission/271604282
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void solve(int t) {
  Int n, x, y;
  vector<int> a(n);
  x--, y--;
  for (int i = y, v = 1; i >= 0; i--, v = -v) {
    a[i] = v;
  }
  for (int i = y + 1; i < x; i++) {
    a[i] = 1;
  }
  for (int i = x, v = 1; i < n; i++, v = -v) {
    a[i] = v;
  }
  for (auto &&ai : a) {
    cout << ai << ' ';
  }
  cout << endl;
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
