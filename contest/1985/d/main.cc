/**
 * https://codeforces.com/contest/1985/submission/267986572
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
  vector<Str> rows(n);
  int h1 = 0, h2 = 0, k = 0;
  for (int i = 0; i < n; ++i) {
    auto pos = rows[i].find('#');
    if (pos != string::npos) {
      if (!k) {
        k = pos + 1;
        h1 = i + 1;
      }
      h2 = i + 1;
    }
  }
  cout << (h1 + h2) / 2 << ' ' << k << endl;
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
