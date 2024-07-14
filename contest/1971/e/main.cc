/**
 * https://codeforces.com/contest/1971/submission/270394156
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void solve(int t) {
  Int n, k, q;
  vector<Int> a(k), b(k), d(q);
  auto f = [&](int d) -> int {
    int j = upper_bound(a.begin(), a.end(), d) - a.begin();
    if (j == a.size()) {
      return b.back();
    }
    int a0 = j ? (int)a[j - 1] : 0;
    int b0 = j ? (int)b[j - 1] : 0;
    return b0 + (i64(d - a0) * (b[j] - b0)) / (a[j] - a0);
  };
  for (auto &di : d) {
    cout << f(di) << ' ';
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
