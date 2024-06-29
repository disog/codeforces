/**
 * https://codeforces.com/contest/1971/submission/267966200
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
  for (int i = 1; i < s.size(); ++i) {
    if (s[i] != s[0]) {
      swap(s[i], s[0]);
      cout << "YES" << endl << s << endl;
      return;
    }
  }
  cout << "NO" << endl;
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
