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
  int operator*(int rhs) { return (x * i64(rhs)) % m; }
  int operator+=(int rhs) { return x = operator+(rhs); }
  int operator-=(int rhs) { return x = operator-(rhs); }
  int operator*=(int rhs) { return x = operator*(rhs); }
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

struct Bridge : vector<pair<int, int>> {
  vector<int> low;
  Bridge(Graph g, int s) : low(g.size(), -1) { dfs(g, s, s, s); }
  void dfs(Graph &g, int u, int p, int &t) {
    auto tx = low[u] = t++;
    for (auto &&v : g[u]) {
      if (v != p) {
        if (low[v] < 0) {
          dfs(g, v, u, t);
          if (low[v] > tx) {
            emplace_back(u, v);
          }
        }
        low[u] = min(low[u], low[v]);
      }
    }
  }
};

struct Match : vector<int> {
  int c = 0;
  Match(Graph &g, int s) : vector<int>(g.size(), -1) { dfs(g, s, s); }
  void dfs(Graph &g, int u, int p) {
    auto &m = *this;
    for (auto &v : g[u]) {
      if (v != p) {
        dfs(g, v, u); // post-order (visit leaves first)
        if (m[u] == m[v]) {
          m[u] = v, m[v] = u, c++;
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

struct Fac : vector<vector<int>> {
  Fac(int n) : vector<vector<int>>(n + 1) {
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j += i) {
        (*this)[j].push_back(i);
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

Mod modpow(Mod x, int y) {
  Mod ans(x != 0, x.m);
  for (; x && y; y = y >> 1, x *= x) {
    if (y & 1) {
      ans *= x;
    }
  }
  return ans;
}

const less<int> lt1;
const greater<int> gt1;
const less<array<int, 2>> lt2;
const greater<array<int, 2>> gt2;
const auto lta2 = [](auto &lhs, auto &rhs) {
  return lhs[0] < rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
};
const auto gta2 = [](auto &lhs, auto &rhs) {
  return lhs[0] > rhs[0] || (lhs[0] == rhs[0] && lhs[1] > rhs[1]);
};

int binsearch(const auto &f, int s, int e) {
  while (s < e) {
    auto m = (s + e + 1) / 2;
    f(m) ? s = m + 1 : e = m - 1;
  }
  return e;
}

void debug(auto &a, int n) {
  cout << n << ';';
  for (auto &ai : a) {
    cout << ai << ',';
  }
  cout << endl;
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
