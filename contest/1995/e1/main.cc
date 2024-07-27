/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define debug println
#else
#define debug
#endif

void println(const auto &...args) { ((cout << args << ' '), ...) << endl; }

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}

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
  if (n == 1) {
    println(0);
    return;
  }
  if (n % 2 == 0) {
    int mn = INT_MAX, mx = 0;
    for (int i = 0; i < n; i += 2) {
      vector<int> sums = {
          a[i] + a[i + 1],
          a[i] + a[i + n + 1],
          a[i + n] + a[i + 1],
          a[i + n] + a[i + n + 1],
      };
      ranges::sort(sums);
      mn = min(mn, sums[1]);
      mx = max(mx, sums[2]);
    }
    println(mx - mn);
    return;
  }
  vector<array<int, 3>> edges;
  vector<array<array<bool, 2>, 2>> desks(n);
  auto add = [&](int i, int j) { edges.push_back({a[i] + a[j], i, j}); };
  auto cmp = [](auto &e1, auto &e2) { return e1[0] < e2[0]; };
  auto use = [&](int k, bool val) {
    auto [_, i, j] = edges[k];
    desks[i % n][i < n][j < n] = val;
  };
  auto chk = [&](int l, int r) {
    TwoSat sat(n);
    for (int i = 0; i < n; i++) {
      auto [u, v] = desks[i];
      auto a = i % n + 1, b = (i + 1) % n + 1; // a/b are the students
      switch (u[0] + u[1] + v[0] + v[1]) { // v/1 is original, u/0 is swapped
      case 0:
        return false; // desk would be empty
      case 1:
        sat.set(v[0] || v[1] ? a : -a);
        sat.set(v[1] || u[1] ? b : -b);
        break;
      case 2:
        if (v[0] && v[1]) {
          sat.set(a);
        } else if (v[1] && u[1]) {
          sat.set(b);
        } else if (u[0] && u[1]) {
          sat.set(-a);
        } else if (v[0] && u[0]) {
          sat.set(-b);
        } else if (v[1] && u[0]) {
          sat.equal(a, b);
        } else /* v[0] && u[1] */ {
          sat.notequal(a, b);
        }
        break;
      case 3:
        sat.either(v[0] && v[1] ? a : -a, v[1] && u[1] ? b : -b);
        break;
      }
    }
    return sat();
  };
  int ans = INT_MAX, total = 0;
  for (int i = 0; i < 2 * n; i++) {
    add(i, (i + 1) % (2 * n));
    add(i, (i + n + 1) % (2 * n));
    total += a[i];
  }
  ranges::sort(edges, cmp);
  debug(edges);
  for (int l = 0, r = 0, e = edges.size(); r < e; l++) {
    for (; r < e; r++) {
      use(r, true);
      if (r - l + 1 >= n && edges[r][0] * n >= total && chk(l, r)) {
        ans = min(ans, edges[r][0] - edges[l][0]);
        break;
      }
    }
    use(l, false);
  }
  println(ans);
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
