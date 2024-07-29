/**
 * https://codeforces.com/contest/1995/submission/273051709
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
  Int n;
  vector<Int> a(n);
  i64 ans = 0;
  for (int i = 1, count = 0; i < n; i++) {
    i64 x = a[i - 1], y = a[i];
    if (x != 1 && y == 1) {
      ans = -1; // cannot make x <= y
      break;
    }
    for (; x < y && count; x *= x, count--)
      ; // spend previous ops to bring x closer to y
    for (; x > y; y *= y, count++)
      ; // add to current ops to make x <= y
    ans += count;
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
