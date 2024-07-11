/**
 * https://codeforces.com/contest/1992/submission/269985581
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

const less<int> lt1;

void solve(int t) {
  Num n, k;
  vector<Num<>> a(k);
  int ans = 0;
  int mx = *ranges::max_element(a, lt1);
  for (auto &&ai : a) {
    if (ai != mx) {
      ans += ai - 1 + ai;
    } else {
      mx = 0;
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
  Num t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}
