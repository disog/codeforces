/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
// #define debug
#else
#include "debug.h"
init();
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
  const int n, m;
  vector<array<Int, 2>> e;
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m), e(m) {
    for (auto &[u, v] : e) {
      add(u, v);
    }
  }
  void add(int u, int v) { _add(u, v), _add(v, u); }
  void _add(int u, int v) { (*this)[u].push_back(v); }
};

struct DSU {
  vector<int> par, siz;
  DSU(int n) : par(n + 1), siz(n + 1) {}
  int add(int v) { return siz[v] = 1, par[v] = v; }
  int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); }
  int merge(int a, int b) {
    a = find(a), b = find(b);
    if (a != b) {
      if (siz[a] < siz[b]) {
        swap(a, b);
      }
      siz[a] += siz[b];
      par[b] = a;
    }
    return a;
  }
};

void solve(int t) {
  Int n, m;
  Graph g(n, m);
  DSU dsu(n);
  for (int u = 1; u <= n; u++) {
    dsu.add(u);
  }
  for (int u = 1; u <= n; u++) {
    for (auto &v : g[u]) {
      dsu.merge(u, v);
    }
  }
  list<int> lst;
  for (int u = 1; u <= n; u++) {
    for (auto &v : g[u]) {
      if (v < u) {
        assert(lst.size());
        auto it = prev(lst.end());
        for (; *it != v; it--) {
          dsu.merge(v, *it);
        }
        lst.erase(it);
      } else {
        lst.push_back(u);
      }
    }
  }
  vector<vector<int>> islets(n + 1);
  int mxcut = 0;
  for (int u = 1, c = 0, streak = 0, last = 0; c <= n; c++, u = u % n + 1) {
    if (g[u].empty()) {
      if (c == 0) {
        c = -1;
        continue; // need to find the first set
      }
      streak++;
    } else {
      auto p = dsu.find(u);
      if (streak > 0) {
        if (p == last) {
          islets[p].push_back(streak);
        } else {
          mxcut += streak + 1; // number of edges to cut
        }
        streak = 0;
      }
      last = p;
    }
  }
  for (auto &sizes : islets) {
    if (sizes.size()) {
      mxcut += *ranges::max_element(sizes) + 1;
    }
  }
  cout << n - max(1, mxcut) << endl;
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
