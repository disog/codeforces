/**
 * https://codeforces.com/contest/1980/submission/267971260
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
  Str a;
  vector<int> hist('G' - 'A' + 1);
  int ans = m * hist.size();
  for (auto &&c : a) {
    if (hist[c - 'A']++ < m) {
      ans--;
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
