/**
 * https://codeforces.com/contest/1985/submission/269799167
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

struct DSU : vector<int> {
  DSU &parent = *this;
  vector<int> size;
  DSU(int n) : vector<int>(n), size(n) {}
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

struct Str : string {
  Str() { cin >> *this; }
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
  int ans = 0;
  auto f = [&](int x, int y, auto &gg, auto &vv) {
    for (int i = 0; i < x; i++) {
      map<int, int> size;
      int total = 0;
      for (int j = 0; j < y; j++) {
        if (gg(i, j) == '.') {
          total++;
        } else {
          auto p = dsu.find(vv(i, j));
          size[p] = dsu.size[p];
        }
        if (i > 0 && gg(i - 1, j) == '#') {
          auto p = dsu.find(vv(i - 1, j));
          size[p] = dsu.size[p];
        }
        if (i < x - 1 && gg(i + 1, j) == '#') {
          auto p = dsu.find(vv(i + 1, j));
          size[p] = dsu.size[p];
        }
      }
      for (auto [_, c] : size) {
        total += c;
      }
      ans = max(ans, total);
    }
  };
  auto g1 = [&](int i, int j) { return g[i][j]; };
  auto g2 = [&](int i, int j) { return g[j][i]; };
  auto v1 = [&](int i, int j) { return i * m + j + 1; };
  auto v2 = [&](int i, int j) { return v1(j, i); };
  f(n, m, g1, v1);
  f(m, n, g2, v2);
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
