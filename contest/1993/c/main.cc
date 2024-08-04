/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

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
  Int n, k;
  vector<Int> a(n);
  int m = 2 * k;
  vector<int> b(m, INT_MAX), c(m);
  for (auto &ai : a) {
    auto &bi = b[ai % m];
    bi = min<int>(bi, ai);
    c[ai % m]++;
  }
  vector<int> sum(m + k);
  for (int i = 0; i < m + k - 1; i++) {
    sum[i + 1] += sum[i] + c[i % m];
  }
  bool ok = false;
  for (int i = 0; i < m && !ok; i++) {
    if (sum[i + k] - sum[i] == n) {
      ok = true;
    }
  }
  int ans = ok ? 0 : -1;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
