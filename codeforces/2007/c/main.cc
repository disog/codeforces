/**
 * https://codeforces.com/contest/2007/submission/280251016
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init();
#endif

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void solve(int t) { // O(n*log n + log V)
  Int n, a, b;
  vector<Int> c(n);
  auto d = gcd<int, int>(a, b); // O(log V)
  for (auto &&ci : c) {
    ci %= d;
  }
  ranges::sort(c); // O(n*log n)
  int ans = c[n - 1] - c[0];
  for (int i = 1; i < n; i++) { // O(n)
    ans = min(ans, c[i - 1] + d - c[i]);
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}