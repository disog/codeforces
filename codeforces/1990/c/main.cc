/**
 * https://codeforces.com/contest/1990/submission/273050765
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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
  i64 ans = 0;
  auto f = [&]() {
    vector<bool> b(n + 1);
    for (int i = 0, mx = 0; i < n; i++) { // O(n)
      ans += a[i];
      if (b[a[i]] && a[i] > mx) {
        mx = a[i];
      } else {
        b[a[i]] = true;
        a[i] = mx;
      }
    }
  };
  f(), f(); // O(n)
  for (int i = 0; i < n; i++) {
    ans += i64(n - i) * a[i]; // sum of prefix sums
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
