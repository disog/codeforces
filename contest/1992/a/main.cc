/**
 * https://codeforces.com/contest/1992/submission/269969378
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
  vector<Num<>> a(3);
  ranges::sort(a, lt1);
  int c = 5;
  auto d1 = min(c, a[1] - a[0]);
  a[0] += d1;
  c -= d1;
  if (c > 0) {
    auto d2 = min(c, a[2] - a[1]);
    a[0] += d2 / 2;
    a[1] += d2 - d2 / 2;
    c -= d2;
    for (int i = 0; c > 0; i++, c--) {
      a[i % 3]++;
    }
  }
  cout << a[0] * a[1] * a[2] << endl;
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
