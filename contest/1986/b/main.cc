/**
 * https://codeforces.com/contest/1986/submission/273049238
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

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

template <typename T> struct Mat : vector<vector<T>> {
  int n, m;
  Mat(int n, int m) : vector<vector<T>>(n), n(n), m(m) {
    for (auto &row : *this) {
      row.resize(m);
    }
  }
};

void solve(int t) {
  Int n, m;
  Mat<Int> a(n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      auto u = i > 0 ? (int)a[i - 1][j] : 0;
      auto l = j > 0 ? (int)a[i][j - 1] : 0;
      auto d = i < n - 1 ? (int)a[i + 1][j] : 0;
      auto r = j < m - 1 ? (int)a[i][j + 1] : 0;
      auto mx = max(u, max(l, max(d, r)));
      auto &cell = a[i][j];
      if (cell > mx) {
        cell.x = mx;
      }
    }
    println(a[i]);
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
