/**
 * https://codeforces.com/contest/1986/submission/267295609
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

void solve(int t) {
  int n, m;
  string s, c;
  cin >> n >> m >> s;
  vector<int> ind(m);
  for (auto &&i : ind) {
    cin >> i;
  }
  cin >> c;
  ranges::sort(ind);
  ranges::sort(c);
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
  freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}