/**
 * https://codeforces.com/contest/2014/submission/283166955
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
  if (n <= 2) {
    println(-1);
    return;
  }
  ranges::nth_element(a, a.begin() + n / 2);
  auto sum = reduce(a.begin(), a.end(), 0ll);
  auto y = a[n / 2]; // y < (sum + x) / (2 * n)
  auto ans = max(0ll, 2ll * n * y - sum + 1);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
