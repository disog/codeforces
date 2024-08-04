/**
 * https://codeforces.com/contest/1995/submission/273051685
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
using I64 = Num<i64>;

i64 maxsum(int a, int ca, int b, int cb, i64 m) {
  assert(a > 0 && a < b);
  auto ua = min<i64>(ca, m / a);
  auto ub = min<i64>(cb, (m - ua * a) / b);
  auto ra = min<i64>({ua, cb - ub, (m - ua * a - ub * b) / (b - a)});
  return (ua - ra) * a + (ub + ra) * b;
}

void solve(int t) {
  Int n;
  I64 m;
  vector<Int> a(n), c(n);
  a.push_back(INT_MAX);
  c.push_back(0);
  vector<int> ids(n + 1);
  iota(ids.begin(), ids.end(), 0);
  auto cmp = [&](int i, int j) { return a[i] < a[j]; };
  ranges::sort(ids, cmp);
  i64 ans = 0;
  for (int i = 0; i < n; i++) {
    int j = ids[i], k = ids[i + 1];
    int ck = a[k] - a[j] == 1 ? int(c[k]) : 0;
    ans = max(ans, maxsum(a[j], c[j], a[k], ck, m));
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
