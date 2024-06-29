/**
 * https://codeforces.com/contest/1980/submission/267941556
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

template <typename T = int> struct Vec : vector<T> {
  Vec(int n, int s = 0) : vector<int>(n + s) {
    for (int i = s; i < n + s; i++) {
      cin >> (*this)[i];
    }
  }
};

template <typename T = int> struct Mat : vector<vector<T>> {
  Mat(int n, int m) : vector<vector<T>>(n) {
    for (int i = 0; i < n; i++) {
      (*this)[i] = Vec(m);
    }
  }
};

template <typename T = int> struct MatP : vector<array<int, 2>> {
  MatP(int n, int m, int s = 0) : vector<array<int, 2>>(n * m + s) {
    for (int i = 0; i < n; i++) {
      for (int j = 0, x; j < m; j++) {
        cin >> x;
        (*this)[x] = {i, j};
      }
    }
  }
};

void solve(int t) {
  int n, m;
  cin >> n >> m;
  Mat a(n, m);
  MatP b(n, m, 1);
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
  freopen(path(__FILE__).replace_filename("input.txt").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}