/**
 * Utils
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using f64 = double;
using MaxHeap = priority_queue<int>;
using MinHeap = priority_queue<int, vector<int>, greater<int>>;

template <typename T = int> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
};

struct Str : string {
  Str() { cin >> *this; }
};

template <int N = 998244353> struct Mint {
  int x;
  Mint(int a) : x(a % N) {}
  operator int() { return x; }
  int operator+=(int rhs) { return (x += rhs) >= N ? x -= N : x; }
  int operator-=(int rhs) { return (x -= rhs) < 0 ? x += N : x; }
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

struct DGraph : vector<vector<int>> {
  vector<array<Num<>, 2>> e;
  DGraph(int n, int m) : vector<vector<int>>(n), e(m) {
    auto &g = *this;
    for (auto &[u, v] : e) {
      g[u].push_back(v);
    }
  }
};

struct WGraph : vector<vector<array<int, 2>>> {
  vector<array<Num<>, 3>> e;
  WGraph(int n, int m) : vector<vector<array<int, 2>>>(n), e(m) {
    auto &g = *this;
    for (auto &[u, v, w] : e) {
      g[u].emplace_back(v, w);
      g[v].emplace_back(u, w);
    }
  }
};

struct WDGraph : vector<vector<array<int, 3>>> {
  vector<array<Num<>, 3>> e;
  WDGraph(int n, int m) : vector<vector<array<int, 3>>>(n), e(m) {
    auto &g = *this;
    for (auto &[u, v, w] : e) {
      g[u].emplace_back(v, w);
    }
  }
};

struct Zfn : vector<int> {
  Zfn(const auto &v, int s = 0) : Zfn(v, s, v.size()) {}
  Zfn(const auto &v, int s, int e) : vector<int>(e - s) {
    auto &z = *this;
    for (int i = 1, j = 1; i + s < e; i++) {
      auto &c = z[i] = max(0, min(j + z[j] - i, z[i - j]));
      for (; i + c < e && v[i + c + s] == v[c + s]; c++, j = i)
        ;
    }
  }
};

struct Fact : vector<int> {
  Fact(i64 x) {
    for (; x && x & 1 == 0; x >>= 1) {
      push_back(2);
    }
    for (int i = 3; x > 1; i += 2) {
      for (int r = x / i; r * i == x; x = r, r /= i) {
        push_back(i);
      }
    }
  }
};

void solve(int t) {}

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
