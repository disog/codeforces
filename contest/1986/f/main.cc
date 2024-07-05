/**
 * https://codeforces.com/contest/1986/submission/268935068
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

template <typename T = int> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
};

struct Graph : vector<vector<int>> {
  vector<array<Num<>, 2>> e;
  Graph(int n, int m) : vector<vector<int>>(n), e(m) {
    auto &g = *this;
    for (auto &[u, v] : e) {
      g[u].push_back(v);
      g[v].push_back(u);
    }
  }
};

void solve(int t) {
  Num n, m;
  Graph g(n + 1, m);
  vector<int> low(n + 1), size(n + 1);
  int timer = 0, best = n;
  const auto mid = n / 2.0;
  auto f = [&](auto &f, int u, int p) -> void {
    size[u] = 1;
    auto tx = low[u] = timer++;
    for (auto &&v : g[u]) {
      if (v != p) {
        if (!size[v]) {
          f(f, v, u);
          size[u] += size[v];
          if (low[v] > tx && abs(size[v] - mid) < abs(best - mid)) {
            best = size[v]; // bridge with best split
          }
        }
        low[u] = min(low[u], low[v]);
      }
    }
  };
  f(f, 1, 0);
  i64 ans = (i64(best) * (best - 1) + i64(n - best) * (n - best - 1)) / 2;
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
