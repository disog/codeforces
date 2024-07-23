/**
 * https://codeforces.com/contest/1990/submission/272022756
 *
 * (c) 2024 Diego Sogari
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
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { _add(u, v), _add(v, u); }
  void _add(int u, int v) { (*this)[u].push_back(v); }
};

struct Tree : Graph {
  struct Info {
    int par, dep, siz, hei;
  };
  vector<Info> info;
  Tree(int n) : Graph(n), info(n + 1) {} // no edges
  Tree(int n, int s) : Graph(n, n - 1), info(n + 1) { dfs(s, s); }
  void dfs(int u, int p, int d = 1) {
    auto &cur = info[u] = {p, d, 1, 1};
    for (auto &v : (*this)[u]) {
      if (v != p) {
        dfs(v, u, d + 1);
        cur.siz += info[v].siz;
        cur.hei = max(cur.hei, 1 + info[v].hei);
      }
    }
  }
};

int simulate(Tree &g, int &mole, int x) {
  int i = mole;
  while (i != 1 && i != x) {
    i = g.info[i].par;
  }
  if (i == x) {
    return true;
  }
  mole = g.info[mole].par;
  return false;
}

void solve(int t) {
  Int n;
#ifdef LOCAL
  Int mole;
#endif
  int rem = 160;
  Tree g(n, 1);
  auto q = [&](int x) {
    assert(rem--);
    cout << "? " << x << endl;
#ifdef LOCAL
    return simulate(g, mole, x);
#else
    return Int();
#endif
  };
  vector<bool> vis(n + 1);
  auto f = [&](auto &self, int u, int p) -> void {
    vis[u] = true;
    for (auto &v : g[u]) {
      if (v != p) {
        self(self, v, u);
      }
    }
  };
  vector<int> ids(n);
  iota(ids.begin(), ids.end(), 1);
  auto cmp = [&](int i, int j) { return g.info[i].dep > g.info[j].dep; };
  ranges::sort(ids, cmp);
  for (int u : ids) {
    if (!vis[u]) {
      int v = u;
      for (int i = 0; i < (rem - 1) / 2 - 1 && v != 1; i++) {
        v = g.info[v].par;
      }
      if (q(v)) {
        int d = g.info[u].dep - g.info[v].dep + 1;
        for (int i = 0; i < d; i++) { // drive out of subtree
          if (q(u)) {
            v = u;
            break;
          }
          if (!q(v)) {
            v = g.info[g.info[v].par].par;
            break;
          }
        }
        cout << "! " << v << endl;
        return;
      }
      f(f, v, g.info[v].par); // cut subtree
    }
  }
  assert(false);
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
