/**
 * https://codeforces.com/contest/1980/submission/267942169
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

template <typename T = int> struct Vec2I : vector<array<T, 3>> {
  Vec2I(int n, int s = 0) : vector<array<T, 3>>(n + s) {
    for (int i = s, x, y; i < n + s; i++) {
      cin >> x >> y;
      (*this)[i] = {x, y, i};
    }
  }
};

auto cmp = [](Vec2I<int>::value_type &a, Vec2I<int>::value_type &b) {
  auto [ra, ca, _a] = a;
  auto [rb, cb, _b] = b;
  return ra > rb || (ra == rb && ca < cb);
};

void solve(int t) {
  int n, m, k;
  cin >> n >> m >> k;
  Vec2I fs(k);
  ranges::sort(fs, cmp); // O(k*log k)
  vector<int> ans(k);
  i64 a = 0;
  int x = n, y = m + 1;
  for (auto &&[r, c, i] : fs) { // O(k)
    if (c < y) {
      a += i64(x - r) * (y - 1);
      x = r, y = c;
      ans[i] = 1;
    }
  }
  a += i64(x) * (y - 1);
  cout << a << endl;
  for (auto &&ai : ans) {
    cout << ai << ' ';
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