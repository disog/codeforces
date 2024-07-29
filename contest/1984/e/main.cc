/**
 * https://codeforces.com/contest/1984/submission/273048029
 *
 * Inspired by jiangly's solution:
 * https://codeforces.com/contest/1984/submission/264894399
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

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
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { _add(u, v), _add(v, u); }
  void _add(int u, int v) { (*this)[u].push_back(v); }
};

struct Match : vector<int> {
  int count = 0;
  vector<bool> vis;
  Match(const Graph &g, int s) : vector<int>(g.size(), -1), vis(g.size()) {
    dfs(g, s, s);
  }
  void dfs(const Graph &g, int u, int p) {
    vis[u] = true;
    for (auto v : g[u]) {
      if (v != p && !vis[v]) {
        dfs(g, v, u); // post-order (visit leaves first)
        if ((*this)[u] == (*this)[v]) {
          (*this)[u] = v;
          (*this)[v] = u;
          count++;
        }
      }
    }
  }
};

void solve(int t) {
  Int n;
  Graph g(n, n - 1);
  Match match(g, 1);
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (match[i] < 0) {
      q.push(i);
    }
  }
  vector<bool> vis(n + 1);
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    vis[u] = true;
    for (auto &v : g[u]) {
      assert(match[v] >= 0);
      if (!vis[match[v]]) {
        q.push(match[v]);
      }
    }
  }
  int ans = n - match.count;
  for (int i = 1; i <= n; i++) {
    if (!vis[i] && g[i].size() == 1) {
      ans++;
      break;
    }
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
