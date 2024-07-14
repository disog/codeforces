/**
 * https://codeforces.com/contest/1986/submission/270399063
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct Str : string {
  Str() { cin >> *this; }
};

void solve(int t) {
  Int n, m;
  Str s;
  vector<Int> ind(m);
  Str c;
  ranges::sort(ind);
  ranges::sort(c);
  for (int i = 0, j = 0, prev = -1; i < m; i++) {
    if (ind[i] != prev) {
      prev = ind[i];
      s[prev - 1] = c[j++];
    }
  }
  cout << s << endl;
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
