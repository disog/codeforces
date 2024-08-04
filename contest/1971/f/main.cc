/**
 * https://codeforces.com/contest/1971/submission/273046233
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

void solve(int t) {
  Int r;
  int ans = 0;
  for (i64 i = 1, a = i64(r) * r, b = i64(r + 1) * (r + 1); i <= r; i++) {
    ans += ceil(sqrt(b - i * i)) - ceil(sqrt(a - i * i));
  }
  println(ans * 4);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
