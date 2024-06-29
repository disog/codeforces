/**
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

void solve(int t) {
  int n, m;
  cin >> n >> m;
  map<int, vector<int>> adj;
  for (int i = 0, u, v; i < m; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  vector<int> visited(n + 1);
  int mx = 1;
  function<void(int, int, int)> f = [&](int u, int p, int c) {
    if (!visited[u]) {
      visited[u] = c;
      for (auto &&v : adj[u]) {
        if (v != p) {
          f(v, u, c + 1);
        }
      }
    } else {
      mx = max(mx, c - visited[u]);
    }
  };
  for (int u = 1; u <= n; u++) {
    f(u, -1, 1);
  }
  cout << mx * (mx - 1) / 2 + (n - mx) * (n - mx - 1) / 2 << endl;
}

int main() {
#ifdef LOCAL
  freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}