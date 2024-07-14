/**
 * https://codeforces.com/contest/1980/submission/270394611
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
  Int n;
  vector<Int> a(n), b(n);
  Int m;
  vector<Int> d(m);
  map<int, int> count;
  for (auto &&di : d) {
    count[di]++;
  }
  auto ans = "NO";
  for (int i = 0; i < n; ++i) {
    if (b[i] != a[i] && !count[b[i]]--) {
      ans = "NO";
      break;
    }
    if (b[i] == d.back()) {
      ans = "YES";
    }
  }
  cout << ans << endl;
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
