/**
 * https://codeforces.com/contest/1984/submission/267982436
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
  Str x;
  if (x.front() != '1' || x.back() == '9') {
    cout << "NO" << endl;
    return;
  }
  for (int i = 1; i < x.size() - 1; i++) {
    if (x[i] == '0') {
      cout << "NO" << endl;
      return;
    }
  }
  cout << "YES" << endl;
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
