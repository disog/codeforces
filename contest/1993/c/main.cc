/**
 * https://codeforces.com/contest/1993/submission/274441961
 *
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
  vector<int> b(m), c(m);
  for (auto &ai : a) {
    auto &bi = b[ai % m];
    bi = max<int>(bi, ai);
    c[ai % m]++;
  }
  vector<int> sum(m + k);
  map<int, int> window;
  int ans = INT_MAX;
  for (int i = 1; i < m + k; i++) {
    sum[i] += sum[i - 1] + c[(i - 1) % m];
    if (b[(i - 1) % m]) {
      window.emplace(b[(i - 1) % m], i);
    }
    if (i >= k) {
      if (sum[i] - sum[i - k] == n) {
        auto [mx, j] = *window.rbegin();
        ans = min(ans, mx + (i - j) % m);
      }
      if (b[(i - k) % m]) {
        window.erase(b[(i - 1) % m]);
      }
    }
  }
  println(ans == INT_MAX ? -1 : ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
