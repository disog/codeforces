/**
 * https://codeforces.com/contest/1996/submission/273966787
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

int binsearch(auto &&f, int s, int e) {
  while (s < e) {
    auto m = (s + e + 1) / 2;
    f(m) ? s = m : e = m - 1;
  }
  return e;
}

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void solve(int t) {
  Int n, k;
  vector<Int> a(n), b(n);
  i64 ans = 0, ck = -k;
  int amx = 0;
  for (int i = 0; i < n; i++) {
    i64 c = (a[i] - 1) / b[i] + 1;
    ans += c * a[i] - c * (c - 1) * b[i] / 2;
    amx = max<int>(amx, a[i]);
    ck += c;
  }
  auto f = [&](int m) {
    i64 count = 0;
    for (int i = 0; i < n; i++) {
      auto mn = (a[i] - 1) % b[i] + 1;
      if (m >= mn) {
        count += (min<int>(m, a[i]) - mn) / b[i] + 1;
      }
    }
    return count < ck;
  };
  auto m = binsearch(f, 1, amx);
  vector<int> idx(n);
  iota(idx.begin(), idx.end(), 0);
  auto cmp = [&](int i, int j) { return b[i] < b[j]; };
  ranges::sort(idx, cmp);
  if (m > 0) {
    for (int i = 0; i < n && ck > 0; i++) {
      int ai = a[idx[i]], bi = b[idx[i]];
      auto mn = (ai - 1) % bi + 1;
      if (m >= mn) {
        i64 c = min<i64>(ck, (min<int>(m, ai) - mn) / bi + 1);
        ans -= c * mn + c * (c - 1) * bi / 2;
        ck -= c;
      }
    }
  }
  m++;
  for (int i = 0; i < n && ck > 0; i++) {
    int ai = a[idx[i]], bi = b[idx[i]];
    auto mn = (ai - 1) % bi + 1;
    if (m >= mn && m <= ai && (m - mn) % bi == 0) {
      i64 c = (m - mn) / bi + 1;
      ans -= mn + (c - 1) * bi;
      ck--;
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
