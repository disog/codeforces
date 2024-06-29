/**
 * https://codeforces.com/contest/1971/submission/267966691
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
  Str s;
  int ans = 1, c0 = 0;
  for (int i = 1; i < s.size(); i++) {
    if (s[i] != s[i - 1]) {
      ans++;
      if (!c0 && s[i] == '1') {
        c0 = 1;
      }
    }
  }
  cout << ans - c0 << endl;
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
