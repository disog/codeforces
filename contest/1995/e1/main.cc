/**
 * https://codeforces.com/contest/1995/submission/273051789
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init(__FILE__);
#endif

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(const auto &...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct Digraph : vector<vector<int>> {
  int n, m;
  Digraph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v); }
};

struct SCC : vector<int> {
  int count = 0;
  vector<int> low, vis;
  SCC(const Digraph &g) : vector<int>(g.size()), low(g.size()) {
    for (int i = 0, t = 1; i < g.size(); i++) {
      if (low[i] == 0) {
        dfs(g, i, t);
      }
    }
  }
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
      int i = vis.size();
      do {
        auto v = vis[--i];
        low[v] = g.size();
        (*this)[v] = count;
      } while (vis[i] != u);
      vis.resize(i);
    }
  }
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
    for (int i = 1; i <= n; i++) {
      if (scc[n + i] == scc[n - i]) {
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
  vector<int> sums;
  vector<array<array<int, 2>, 2>> desks(n);
  auto add = [&](int i, int j) {
    sums.push_back(a[i] + a[j]);
    desks[i % n][i % 2 == 0][j % 2] = a[i] + a[j];
  };
  i64 total = 0;
  for (int i = 0; i < 2 * n; i++) {
    add(i, (i + 1) % (2 * n));
    add(i, (i + n + 1) % (2 * n));
    total += a[i];
  }
  ranges::sort(sums);
  debug(sums);
  auto chk = [&](int l, int r) {
    if (sums[l] * i64(n) > total || sums[r] * i64(n) < total) {
      return false;
    }
    TwoSat sat(n);
    array<array<bool, 2>, 2> good;
    for (int i = 0; i < n; i++) {
      for (auto a : {0, 1}) {
        for (auto b : {0, 1}) {
          good[a][b] = desks[i][a][b] >= sums[l] && desks[i][a][b] <= sums[r];
        }
      }
      auto [u, v] = good;                      // v is original, u is swapped
      auto a = i % n + 1, b = (i + 1) % n + 1; // a and b are the students
      switch (u[0] + u[1] + v[0] + v[1]) {     // 1 is original, 0 is swapped
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
        } else /* (v[0] && u[1]) */ {
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
  int ans = INT_MAX;
  int e = ranges::unique(sums).begin() - sums.begin();
  for (int l = 0, r = 0; l <= r && r < e; l++) {
    while (r < e && sums[r] - sums[l] < ans && !chk(l, r)) {
      r++;
    }
    if (r < e) {
      ans = min(ans, sums[r] - sums[l]);
    }
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
