/**
 * https://codeforces.com/contest/1996/submission/273970965
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

int binsearch(auto &&f, int s, int e) {
  while (s < e) {
    auto m = (s + e + 1) / 2;
    f(m) ? s = m : e = m - 1;
  }
  return e; // last such that f is true
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
  auto f = [&](int x) -> pair<i64, i64> { // O(n)
    i64 cnt = 0, sum = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] >= x) {
        i64 c = (a[i] - x) / b[i] + 1;
        sum += c * a[i] - c * (c - 1) * b[i] / 2;
        cnt += c;
      }
    }
    return {cnt, sum};
  };
  auto chk = [&](int x) { return f(x).first >= k; };
  int amx = *ranges::max_element(a);
  int best = binsearch(chk, 0, amx); // O(n*log amx)
  auto [cnt, sum] = f(best);
  i64 ans = sum - (cnt - k) * best;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
