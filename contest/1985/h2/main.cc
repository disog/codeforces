/**
 * https://codeforces.com/contest/1985/submission/269890684
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
  vector<set<int>> rows(n), cols(m), rowcol(n * m);
  vector<int> rows1(n), cols1(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      auto v = i * m + j + 1;
      auto &rc = rowcol[v - 1];
      if (g[i][j] == '#') {
        auto p = dsu.find(v);
        rows[i].insert(p);
        cols[j].insert(p);
        rc.insert(p);
      } else {
        rows1[i]++;
        cols1[j]++;
      }
      if (j > 0 && g[i][j - 1] == '#') {
        rc.insert(dsu.find(v - 1));
      }
      if (j < m - 1 && g[i][j + 1] == '#') {
        rc.insert(dsu.find(v + 1));
      }
      if (i > 0) {
        if (j > 0 && g[i - 1][j - 1] == '#') {
          rc.insert(dsu.find(v - m - 1));
        }
        if (g[i - 1][j] == '#') {
          rc.insert(dsu.find(v - m));
        }
        if (j < m - 1 && g[i - 1][j + 1] == '#') {
          rc.insert(dsu.find(v - m + 1));
        }
      }
      if (i < n - 1) {
        if (j > 0 && g[i + 1][j - 1] == '#') {
          rc.insert(dsu.find(v + m - 1));
        }
        if (g[i + 1][j] == '#') {
          rc.insert(dsu.find(v + m));
        }
        if (j < m - 1 && g[i + 1][j + 1] == '#') {
          rc.insert(dsu.find(v + m + 1));
        }
      }
    }
  }
  for (int i = 1; i < n; i++) {
    rows[i - 1].insert(rows[i].begin(), rows[i].end());
    rows[n - i].insert(rows[n - i - 1].begin(), rows[n - i - 1].end());
  }
  for (int j = 1; j < m; j++) {
    cols[j - 1].insert(cols[j].begin(), cols[j].end());
    cols[m - j].insert(cols[m - j - 1].begin(), cols[m - j - 1].end());
  }
  for (int i = 0; i < n; i++) {
    for (auto p : rows[i]) {
      rows1[i] += dsu.size[p];
    }
  }
  for (int j = 0; j < m; j++) {
    for (auto p : cols[j]) {
      cols1[j] += dsu.size[p];
    }
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int count = rows1[i] + cols1[j] + (g[i][j] == '.' ? -1 : 0);
      for (auto p : rowcol[i * m + j]) {
        count -= dsu.size[p];
      }
      ans = max(ans, count);
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
