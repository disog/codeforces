/**
 * https://codeforces.com/contest/1980/submission/273046649
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

void println(const auto &...args) { ((cout << args), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

const greater<int> gt1;

void solve(int t) {
  Int n, f, k;
  vector<Int> a(n);
  auto ans = "YES";
  if (k < n) {
    auto x = a[f - 1];
    ranges::sort(a, gt1);
    ans = a[k - 1] > x ? "NO" : (a[k] < x ? "YES" : "MAYBE");
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
