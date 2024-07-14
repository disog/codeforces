/**
 * https://codeforces.com/contest/1980/submission/270394970
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

template <typename T> struct Mat : vector<vector<T>> {
  Mat(int n, int m) : vector<vector<T>>(n) {
    for (auto &&row : *this) {
      row.resize(m);
    }
  }
};

void solve(int t) {
  Int n, m;
  Mat<Int> a(n, m);
  vector<array<int, 2>> b(n * m + 1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      Int x;
      b[x] = {i, j};
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if ((j < m - 1 && b[a[i][j]][0] != b[a[i][j + 1]][0]) ||
          (i < n - 1 && b[a[i][j]][1] != b[a[i + 1][j]][1])) {
        cout << "NO" << endl;
        return;
      }
    }
  }
  cout << "YES" << endl;
}

int main() {
#ifdef LOCAL
  using filesystem::path;
  freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}
