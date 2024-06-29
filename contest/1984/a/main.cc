/**
 * https://codeforces.com/contest/1984/submission/267982240
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
  Int n;
  vector<Int> a(n);
  if (a.front() == a.back()) {
    cout << "NO" << endl;
    return;
  }
  string s(n, 'B');
  s[1] = 'R';
  cout << "YES" << endl << s << endl;
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
