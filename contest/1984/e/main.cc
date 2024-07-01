/**
 * https://codeforces.com/contest/1984/submission/268319555
 *
 * Inspired by jiangly's solution:
 * https://codeforces.com/contest/1984/submission/264894399
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

struct Int {
  int x;
  Int() { cin >> x; }
  operator int() { return x; }
};

struct Graph : vector<vector<int>> {
  vector<array<Int, 2>> e;
  Graph(int n, int m) : vector<vector<int>>(n), e(m) {
    auto &g = *this;
    for (auto &[u, v] : e) {
      g[u].push_back(v);
      g[v].push_back(u);
    }
  }
};

struct Match : vector<int> {
  int c = 0;
  Match(Graph &g, int u) : vector<int>(g.size(), -1) { dfs(g, u); }
  void dfs(Graph &g, int u, int p = -1) {
    auto &m = *this;
    for (auto &v : g[u]) {
      if (v != p) {
        dfs(g, v, u); // post-order (visit leaves first)
        if (m[u] == m[v]) {
          m[u] = v;
          m[v] = u;
          c++;
        }
      }
    }
  }
};

void solve(int t) {
  Int n;
  Graph g(n + 1, n - 1);
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
  int ans = n - match.c;
  for (int i = 1; i <= n; i++) {
    if (!vis[i] && g[i].size() == 1) {
      ans++;
      break;
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
  Int t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}
