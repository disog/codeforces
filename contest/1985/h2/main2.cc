/**
 * https://codeforces.com/contest/1985/submission/270227284
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

struct DSU {
  vector<int> parent, size;
  DSU(int n) : parent(n), size(n) {}
  int add(int v) { return size[v] = 1, parent[v] = v; }
  int find(int v) { return v == parent[v] ? v : parent[v] = find(parent[v]); }
  int merge(int a, int b) {
    a = find(a), b = find(b);
    if (a != b) {
      if (size[a] < size[b]) {
        std::swap(a, b);
      }
      size[a] += size[b];
      parent[b] = a;
    }
    return a;
  }
};

struct Pref2D : vector<vector<int>> {
  int n, m;
  Pref2D &sum = *this;
  Pref2D(int n, int m) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &&row : *this) {
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
};

void solve(int t) {
  Num n, m;
  vector<Str> g(n);
  DSU dsu(n * m + 1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j] == '#') {
        auto v = i * m + j + 1;
        dsu.add(v);
        if (i > 0 && g[i - 1][j] == '#') {
          dsu.merge(v, v - m);
        }
        if (j > 0 && g[i][j - 1] == '#') {
          dsu.merge(v, v - 1);
        }
      }
    }
  }
  vector<int> rows(n), cols(m);
  map<int, array<int, 4>> comp;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j] == '#') {
        auto p = dsu.find(i * m + j + 1);
        auto [it, ok] = comp.emplace(p, array<int, 4>{i, j, i, j});
        if (!ok) {
          auto &range = it->second;
          range[1] = min(range[1], j);
          range[2] = i; // max row
          range[3] = max(range[3], j);
        }
      } else {
        rows[i]++;
        cols[j]++;
      }
    }
  }
  Pref2D prefsum(n, m);
  for (auto &&[p, range] : comp) {
    range[0] = max<int>(0, range[0] - 1);
    range[1] = max<int>(0, range[1] - 1);
    range[2] = min<int>(n - 1, range[2] + 1);
    range[3] = min<int>(m - 1, range[3] + 1);
    prefsum.cross(dsu.size[p], range);
  }
  vector<int> sum(m + 1);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0, prev = 0; j < m; j++) {
      int save = sum[j + 1];
      sum[j + 1] += prefsum[i][j] + sum[j] - prev;
      prev = save;
      int count = rows[i] + cols[j] + sum[j + 1];
      ans = max(ans, count - (g[i][j] == '.'));
    }
  }
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
