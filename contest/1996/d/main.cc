/**
 * https://codeforces.com/contest/1996/submission/274012109
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init(__FILE__);
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

void solve(int t) {
  Int n, x;
  int amx = min<int>(x - 2, sqrt<int>(n));
  i64 ans = 0;
  for (int a = 1; a <= amx; a++) {
    for (int b = a; b <= amx; b++) {
      auto y = a * b, z = a + b;
      if (b + z <= x && y + b * z <= n) { // a <= b <= c
        auto cmax = min(x - z, (n - y) / z);
        ans += (a == b ? 1 : 3) + (cmax - b) * (a == b ? 3 : 6);
      }
    }
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
