/**
 * https://codeforces.com/contest/1985/submission/274274338
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug
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

struct Str : string {
  Str() { cin >> *this; }
};

void solve(int t) {
  Int n, m;
  vector<Str> g(n);
  DSU dsu(n * m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j] == '#') {
        auto v = i * m + j;
        dsu.add(v);
        if (i > 0 && g[i - 1][j] == '#') {
          dsu.merge(v, v - m);
        }
        if (j > 0 && g[i][j - 1] == '#') {
          dsu.merge(v, v - 1);
        }
      }
    }
  }
  int ans = 0;
  auto f = [&](int x, int y, auto &gg, auto &vv) {
    for (int i = 0; i < x; i++) {
      set<int> roots;
      int total = 0;
      for (int j = 0; j < y; j++) {
        if (gg(i, j) == '#') {
          roots.insert(dsu.find(vv(i, j)));
        } else {
          total++;
        }
        if (i > 0 && gg(i - 1, j) == '#') {
          roots.insert(dsu.find(vv(i - 1, j)));
        }
        if (i < x - 1 && gg(i + 1, j) == '#') {
          roots.insert(dsu.find(vv(i + 1, j)));
        }
      }
      for (auto r : roots) {
        total += dsu.siz[r];
      }
      ans = max(ans, total);
    }
  };
  auto g1 = [&](int i, int j) { return g[i][j]; };
  auto g2 = [&](int i, int j) { return g[j][i]; };
  auto v1 = [&](int i, int j) { return i * m + j; };
  auto v2 = [&](int i, int j) { return v1(j, i); };
  f(n, m, g1, v1);
  f(m, n, g2, v2);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
