/**
 * https://codeforces.com/contest/1986/submission/267989431
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

struct Str : string {
  Str() { cin >> *this; }
};

void solve(int t) {
  Int n, m;
  Str s;
  vector<Int> ind(m);
  Str c;
  less<int> cmp;
  ranges::sort(ind, cmp);
  ranges::sort(c, cmp);
  for (int i = 0, j = 0, prev = -1; i < m; i++) {
    if (ind[i] != prev) {
      prev = ind[i];
      s[prev - 1] = c[j++];
    }
  }
  cout << s << endl;
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
