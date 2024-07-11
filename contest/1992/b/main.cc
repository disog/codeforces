/**
 * https://codeforces.com/contest/1992/submission/270063041
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
  Num n, k;
  vector<Num<>> a(k);
  int ans = 0, mx = 0;
  for (auto &&ai : a) {
    ans += 2 * ai - 1;
    mx = max<int>(mx, ai);
  }
  ans -= 2 * mx - 1;
  cout << ans << endl;
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
