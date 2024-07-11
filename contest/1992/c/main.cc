/**
 * Submission
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T = int> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
};

void solve(int t) {
  Num n, m, k;
  for (int i = n; i >= k; i--) {
    cout << i << ' ';
  }
  for (int i = k - 1; i > m; i--) {
    cout << i << ' ';
  }
  for (int i = 1; i <= m; i++) {
    cout << i << ' ';
  }
  cout << endl;
}

int main() {
#ifdef LOCAL
  using filesystem::path;
  freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Num t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}