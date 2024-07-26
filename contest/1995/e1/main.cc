/**
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

struct TwoSat {
  int n;
  Digraph g;
  TwoSat(int n) : g(2 * n), n(n) {}
  void add(int a, int b) { g.add(n + a, n + b); }
  void either(int a, int b) { implies(-a, b); }
  void notequal(int a, int b) { equal(-a, b); }
  void set(int a) { add(-a, a); }
  void equal(int a, int b) {
    implies(a, b);
    implies(-a, -b);
  }
  void implies(int a, int b) {
    add(a, b);   //  a ->  b
    add(-b, -a); // !b -> !a
  }
  bool operator()() const {
    SCC scc(g);
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
  vector<Int> a(2 * n);
  if (n % 2 == 0) {
    int mn = INT_MAX, mx = 0;
    for (int i = 0; i < n; i += 2) {
      multiset<int> sums = {
          a[i] + a[i + 1],
          a[i] + a[i + n + 1],
          a[i + n] + a[i + 1],
          a[i + n] + a[i + n + 1],
      };
      mn = min(mn, *next(sums.begin()));
      mx = max(mx, *next(sums.rbegin()));
    }
    cout << mx - mn << endl;
    return;
  }
  vector<int> sums;
  vector<array<int, 2>> edges;
  auto add = [&](int i, int j) {
    sums.push_back(a[i] + a[j]);
    edges.push_back({i, j});
  };
  for (int i = 0; i < 2 * n; i++) {
    if (n % 2 || i % 2 == 0) {
      add(i, (i + 1) % (2 * n));
      add(i, (i + n + 1) % (2 * n));
    }
  }
  int m = sums.size();
  vector<int> idx(m);
  iota(idx.begin(), idx.end(), 0);
  auto cmp = [&](int i, int j) { return sums[i] < sums[j]; };
  ranges::sort(idx, cmp);
  auto check = [&](int l, int r) {
    TwoSat sat(n);
    for (; l <= r; l++) {
      auto [i, j] = edges[idx[l]];
      i = i < n ? i + 1 : n - (i + 1);
      j = j < n ? j + 1 : n - (j + 1);
      sat.implies(i, j);
    }
    return sat();
  };
  int ans = INT_MAX;
  for (int l = 0, r = 1; l < r && r < m; l++) {
    while (r < m && !check(l, r)) {
      r++;
    }
    if (r < m) {
      ans = min(ans, sums[idx[r]] - sums[idx[l]]);
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
