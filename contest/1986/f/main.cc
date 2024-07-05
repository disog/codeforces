/**
 * https://codeforces.com/contest/1986/submission/268929551
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

template <typename T = int> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
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

void solve(int t) {
  Num n, m;
  Graph g(n + 1, m);
  vector<int> times(n + 1);
  int total = 0, best = n;
  const auto mid = n / 2.0;
  function<array<int, 2>(int, int, int)> f = [&](int u, int p, int tx) {
    times[u] = tx;
    array<int, 2> dp = {tx, tx};
    for (auto &&v : g[u]) {
      if (v != p) {
        if (!times[v]) {
          auto before = total;
          auto [tmin, tmax] = f(v, u, dp[1] + 1);
          if (tmin > times[u]) { // bridge
            total += tmax - tmin + 1;
            auto c = total - before;
            if (abs(c - mid) < abs(best - mid)) {
              best = c;
            }
          } else { // component
            dp[0] = min(dp[0], tmin);
            dp[1] = max(dp[1], tmax);
          }
        } else if (times[u] > times[v]) {
          dp[0] = min(dp[0], times[v]);
        }
      }
    }
    return dp;
  };
  f(1, 0, 1);
  i64 ans = (i64(best) * (best - 1) + i64(n - best) * (n - best - 1)) / 2;
  cout << ans << endl;
}

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
