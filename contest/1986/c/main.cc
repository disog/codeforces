/**
 * https://codeforces.com/contest/1986/submission/273049311
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init(__FILE__);
#endif

void println(const auto &...args) { ((cout << args << ' '), ...) << endl; }

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
  println(s);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
