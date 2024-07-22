/**
 * https://codeforces.com/contest/1990/submission/271882332
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
  vector<array<Int, 2>> e;
  Graph(int n, int m = 0) : vector<vector<int>>(n), e(m) {
    for (auto &[u, v] : e) {
      add(u, v);
      add(v, u);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v); }
};

int binsearch(const auto &f, int s, int e) {
  while (s < e) {
    auto m = (s + e + 1) / 2;
    f(m) ? s = m : e = m - 1;
  }
  return e;
}

void solve(int t) {
  Int n;
  Graph g(n + 1, n - 1);
  vector<int> path, mxdepth(n + 1);
  int limit = n / 300;
  auto p = [](char c, int x) { (cout << c << ' ' << x << endl).flush(); };
  auto q = [&](int x) { return p('?', x), Int(); };
  auto f2 = [&](auto &self, int u, int p) -> void {
    mxdepth[u] = 1;
    for (auto &v : g[u]) {
      if (v != p) {
        self(self, v, u);
        mxdepth[u] = max(mxdepth[u], 1 + mxdepth[v]);
      }
    }
  };
  f2(f2, 1, 1);
  auto f = [&](auto &self, int u, int p) -> void {
    path.push_back(u);
    vector<int> test;
    for (auto &&v : g[u]) {
      if (v != p) {
        if (mxdepth[v] + 1 == mxdepth[u]) {
          test.push_back(v);
        } else if (mxdepth[v] > limit && q(v)) {
          return self(self, v, u);
        }
      }
    }
    bool check = test.size() > 1;
    for (auto &v : test) {
      if (!check || (mxdepth[v] > limit && q(v))) {
        return self(self, v, u);
      }
    }
  };
  if (mxdepth[1] > limit) {
    f(f, 1, 1);
  }
  while (limit && !q(n)) {
    limit--;
  }
  int ans = n;
  if (!limit) {
    ans = 1;
    if (path.size()) {
      auto q2 = [&](int i) { return q(path[i]); };
      int i = binsearch(q2, 0, path.size() - 1);
      while (i > 0 && !q(path[i])) {
        i -= 2;
      }
      ans = path[max(0, i)];
    }
  }
  p('!', ans);
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
