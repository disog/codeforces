/**
 * https://codeforces.com/contest/1990/submission/273050842
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug(...)
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

void solve(int t) {
  Int n;
  vector<Int> a(n);
  int ans = 0;
  for (int i = 0, j = 0, k = 2; i < n; i++) {
    if (a[i] > j) {
      ans++; // dye row or square
    }
    if (a[i] <= j || a[i] > k) {
      j = 0, k = 2; // reset
    } else {
      j = 2 - j, k = 4; // alternate square
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