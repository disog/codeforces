/**
 * https://codeforces.com/contest/1986/submission/273050413
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init(__FILE__);
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

struct Graph : vector<vector<int>> {
  int n, m;
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { _add(u, v), _add(v, u); }
  void _add(int u, int v) { (*this)[u].push_back(v); }
};

struct Bridges : vector<array<int, 2>> {
  vector<int> low, siz;
  Bridges(const Graph &g, int s) : low(g.size()), siz(g.size()) {
    int t = 1;
    dfs(g, s, s, t);
  }
  void dfs(const Graph &g, int u, int p, int &t) {
    auto tx = low[u] = t++;
    siz[u] = 1;
    for (auto v : g[u]) {
      if (v != p) {
        if (low[v] == 0) {
          dfs(g, v, u, t); // post-order (visit leaves first)
          siz[u] += siz[v];
          if (low[v] > tx) {
            push_back({u, v});
          }
        }
        low[u] = min(low[u], low[v]);
      }
    }
  }
};

void solve(int t) {
  Int n, m;
  Graph g(n, m);
  Bridges b(g, 1);
  const auto mid = n / 2.0;
  int best = n;
  for (auto [u, v] : b) {
    if (abs(b.siz[v] - mid) < abs(best - mid)) {
      best = b.siz[v]; // bridge with best split
    }
  }
  i64 ans = (i64(best) * (best - 1) + i64(n - best) * (n - best - 1)) / 2;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
