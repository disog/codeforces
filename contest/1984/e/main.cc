/**
 * https://codeforces.com/contest/1984/submission/270397160
 *
 * Inspired by jiangly's solution:
 * https://codeforces.com/contest/1984/submission/264894399
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

struct Graph : vector<vector<int>> {
  vector<array<Int, 2>> e;
  Graph(int n, int m = 0) : vector<vector<int>>(n), e(m) {
    for (auto &[u, v] : e) {
      add(u, v);
    }
  }
  void add(int u, int v) {
    (*this)[u].push_back(v);
    (*this)[v].push_back(u);
  }
};

struct Match : vector<int> {
  int count = 0;
  vector<pair<int, int>> bridges;
  Match(Graph g, int s = 0) : vector<int>(g.size(), -1), low(g.size()) {
    int t = 1;
    dfs(g, s, s, t);
  }

private:
  void dfs(Graph &g, int u, int p, int &t) {
    auto &match = *this;
    auto tx = low[u] = t++;
    for (auto v : g[u]) {
      if (v != p) {
        if (low[v] == 0) {
          dfs(g, v, u, t);   // post-order (visit leaves first)
          if (low[v] > tx) { // new bridge
            bridges.emplace_back(u, v);
          }
          if (match[u] == match[v]) {
            match[u] = v;
            match[v] = u;
            count++;
          }
        }
        low[u] = min(low[u], low[v]);
      }
    }
  }
  vector<int> low;
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
  int ans = n - match.count;
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
