/**
 * https://codeforces.com/contest/1985/submission/270233567
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T = int> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
};

struct Str : string {
  Str() { cin >> *this; }
};

struct Pref2D {
  int n, m;
  vector<vector<int>> sum;
  Pref2D(int n, int m) : sum(n + 1), n(n), m(m) {
    for (auto &&row : sum) {
      row.resize(m + 1);
    }
  }
  void rect(int x, const array<int, 4> &range) {
    auto [r1, c1, r2, c2] = range;
    sum[r1][c1] += x;
    sum[r2 + 1][c1] -= x;
    sum[r1][c2 + 1] -= x;
    sum[r2 + 1][c2 + 1] += x;
  }
  void rows(int x, const array<int, 2> &range) {
    auto [r1, r2] = range;
    sum[r1][0] += x;
    sum[r2 + 1][0] -= x;
  }
  void cols(int x, const array<int, 2> &range) {
    auto [c1, c2] = range;
    sum[0][c1] += x;
    sum[0][c2 + 1] -= x;
  }
  void cross(int x, const array<int, 4> &range) {
    auto [r1, c1, r2, c2] = range;
    rows(x, {r1, r2});
    cols(x, {c1, c2});
    rect(-x, range);
  }
  void visit(const auto &f) {
    vector<int> cur(m + 1);
    for (int i = 0; i < n; i++) {
      for (int j = 0, prev = 0; j < m; j++) {
        int saved = cur[j + 1];
        cur[j + 1] += sum[i][j] + cur[j] - prev;
        prev = saved;
        f(i, j, cur[j + 1]);
      }
    }
  }
};

void solve(int t) {
  Num n, m;
  vector<Str> g(n);
  int r1, r2, c1, c2, sz;
  function<void(int, int)> f = [&](int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= m || g[i][j] != '#') {
      return;
    }
    sz++;
    g[i][j] = 'x';
    r1 = min(r1, max(0, i - 1));
    c1 = min(c1, max(0, j - 1));
    r2 = max(r2, min(n - 1, i + 1));
    c2 = max(c2, min(m - 1, j + 1));
    f(i - 1, j); // top
    f(i + 1, j); // bottom
    f(i, j - 1); // left
    f(i, j + 1); // right
  };
  vector<int> rows(n), cols(m);
  Pref2D prefsum(n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j] == '#') {
        r1 = i, r2 = i, c1 = j, c2 = j, sz = 0;
        f(i, j);
        prefsum.cross(sz, {r1, c1, r2, c2});
      } else if (g[i][j] == '.') {
        rows[i]++;
        cols[j]++;
      }
    }
  }
  int ans = 0;
  auto f2 = [&](int i, int j, int sum) {
    int count = rows[i] + cols[j] + sum;
    ans = max(ans, count - (g[i][j] == '.'));
  };
  prefsum.visit(f2);
  cout << ans << endl;
}

int main() {
#ifdef LOCAL
  using filesystem::path;
  freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Num t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}
