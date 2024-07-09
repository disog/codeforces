/**
 * https://codeforces.com/contest/1971/submission/269630411
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

struct DGraph : vector<vector<int>> {
  vector<array<Num<>, 2>> e;
  DGraph(int n, int m) : vector<vector<int>>(n), e(m) {
    for (auto &[u, v] : e) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v); }
};

struct SCC : vector<int> {
  int count = 0;
  SCC(DGraph g) : vector<int>(g.size()), low(g.size()) {
    for (int i = 0, t = 1; i < g.size(); i++) {
      if (low[i] == 0) {
        dfs(g, i, t);
      }
    }
  }

private:
  void dfs(DGraph &g, int u, int &t) {
    auto tx = low[u] = t++;
    visited.push_back(u);
    for (auto v : g[u]) {
      if (low[v] == 0) {
        dfs(g, v, t);
      }
      low[u] = min(low[u], low[v]);
    }
    if (low[u] == tx) { // root
      count++;
      for (int v = -1; v != u; visited.pop_back()) {
        v = visited.back();
        low[v] = g.size();
        (*this)[v] = count;
      }
    }
  }
  vector<int> low, visited;
};

void solve(int t) {
  Num n;
  vector<Num<>> a(n), b(n), c(n);
  DGraph g(n * 2 + 1, 0);
  auto f = [&](int x, int y) {
    g.add(n - x, n + y); // !x -> y
    g.add(n - y, n + x); // !y -> x
  };
  for (int i = 0; i < n; i++) {
    f(a[i], b[i]);
    f(a[i], c[i]);
    f(b[i], c[i]);
  }
  SCC scc(g);
  for (int i = 0; i < n; i++) {
    if (scc[i] == scc[2 * n - i]) {
      cout << "NO" << endl;
      return;
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
  Num t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}
