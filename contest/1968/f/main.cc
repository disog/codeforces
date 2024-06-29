/**
 * https://codeforces.com/contest/1968/submission/267964756
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

struct Int {
  int x;
  Int() { cin >> x; }
  operator int() { return x; }
};

void solve(int t) {
  Int n, q;
  vector<int> b(n + 1);
  map<int, vector<int>> p;
  p[0].push_back(0);
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
    b[i] ^= b[i - 1];
    p[b[i]].push_back(i);
  }
  auto f = [&](int l, int r) {
    auto bl = b[l - 1], br = b[r];
    if (bl == br) {
      return true;
    }
    auto s = ranges::lower_bound(p[br], l);
    auto t = ranges::lower_bound(p[bl], r);
    return *s < *prev(t);
  };
  for (int i = 0; i < q; ++i) {
    Int l, r;
    cout << (f(l, r) ? "YES" : "NO") << endl;
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
