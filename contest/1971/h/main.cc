/**
 * https://codeforces.com/contest/1971/submission/272715933
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

struct Digraph : vector<vector<int>> {
  Digraph(int n, int m = 0) : vector<vector<int>>(n + 1) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v); }
};

struct SCC : vector<int> {
  int count = 0;
  SCC(const Digraph &g) : vector<int>(g.size()), low(g.size()) {
    for (int i = 0, t = 1; i < g.size(); i++) {
      if (low[i] == 0) {
        dfs(g, i, t);
      }
    }
  }

private:
  void dfs(const Digraph &g, int u, int &t) {
    auto tx = low[u] = t++;
    vis.push_back(u);
    for (auto v : g[u]) {
      if (low[v] == 0) {
        dfs(g, v, t);
      }
      low[u] = min(low[u], low[v]);
    }
    if (low[u] == tx) { // component root
      count++;
      for (int v = -1; v != u; vis.pop_back()) {
        v = vis.back();
        low[v] = g.size();
        (*this)[v] = count;
      }
    }
  }
  vector<int> low, vis;
};

struct TwoSat : Digraph {
  int n;
  TwoSat(int n) : Digraph(2 * n), n(n) {}
  void add(int a, int b) { Digraph::add(n + a, n + b); }
  void either(int a, int b) { implies(-a, b); }
  void notequal(int a, int b) { equal(-a, b); }
  void equal(int a, int b) {
    implies(a, b);
    implies(-a, -b);
  }
  void implies(int a, int b) {
    add(a, b);   // a -> b
    add(-b, -a); // !b -> !a
  }
  bool operator()() const {
    SCC scc(*this);
    for (int i = 0; i < n; i++) {
      if (scc[i] == scc[2 * n - i]) {
        return false;
      }
    }
    return true;
  }
};

void solve(int t) {
  Int n;
  vector<Int> a(n), b(n), c(n);
  TwoSat sat(n);
  for (int i = 0; i < n; i++) {
    sat.either(a[i], b[i]);
    sat.either(a[i], c[i]);
    sat.either(b[i], c[i]);
  }
  cout << (sat() ? "YES" : "NO") << endl;
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
