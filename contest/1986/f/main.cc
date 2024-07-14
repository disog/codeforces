/**
 * https://codeforces.com/contest/1986/submission/270399326
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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

void solve(int t) {
  Int n, m;
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
  f(f, 1, 1);
  i64 ans = (i64(best) * (best - 1) + i64(n - best) * (n - best - 1)) / 2;
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
