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

template <typename T = int> struct Vec : vector<Num<T>> {
  Vec(int n, int s = 0) : vector<Num<T>>(s, 0) { this->resize(n + s); }
};

struct Str : string {
  Str() { cin >> *this; }
};

struct Mod {
  int x, m;
  Mod(int a, int b) : x(a % b), m(b) {}
  operator int() { return x; }
  int operator+(int rhs) {
    return rhs < 0 ? operator-(-rhs) : (x + rhs >= m ? x - m : x) + rhs;
  }
  int operator-(int rhs) {
    return rhs < 0 ? operator+(-rhs) : (x - rhs < 0 ? x + m : x) - rhs;
  }
  int operator+=(int rhs) { return x = operator+(rhs); }
  int operator-=(int rhs) { return x = operator-(rhs); }
};

template <int N = 998244353> struct Mint : Mod {
  Mint(int a) : Mod(a, N) {}
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
  Zfn(auto &a, int s = 0) : Zfn(a, s, a.size()) {}
  Zfn(auto &a, int s, int e) : vector<int>(e - s) {
    auto &z = *this;
    for (int i = 1, j = 1; i + s < e; i++) {
      auto &c = z[i] = max(0, min(j + z[j] - i, z[i - j]));
      for (; i + c < e && a[i + c + s] == a[c + s]; c++, j = i)
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

pair<int, int> invshift(auto &a, int sa = 0, int sp = 1) {
  int inv = 0, shift = a[sa] - sp, n = a.size();
  for (int i = sa, sum = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (a[i] > a[j]) {
        inv++;
      }
    }
    if (shift >= 0) {
      auto d = a[i] - sp - (i - sa);
      if (shift != (n - sa + d) % (n - sa)) {
        shift = -1;
      }
    }
  }
  return {inv, shift};
}

int binsearch(const auto &f, int s, int e) {
  while (s < e) {
    auto m = (s + e + 1) / 2;
    if (f(m)) {
      s = m + 1;
    } else {
      e = m - 1;
    }
  }
  return e;
}

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
