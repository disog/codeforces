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
    for (auto &[u, v] : e) {
      add(u, v);
    }
  }
  void add(int u, int v) {
    (*this)[u].push_back(v);
    (*this)[v].push_back(u);
  }
};

struct WGraph : vector<vector<array<int, 2>>> {
  vector<array<Num<>, 3>> e;
  WGraph(int n, int m) : vector<vector<array<int, 2>>>(n), e(m) {
    for (auto &[u, v, w] : e) {
      add(u, v, w);
    }
  }
  void add(int u, int v, int w) {
    (*this)[u].push_back({v, w});
    (*this)[v].push_back({u, w});
  }
};

struct DGraph : vector<vector<int>> {
  vector<array<Num<>, 2>> e;
  DGraph(int n, int m) : vector<vector<int>>(n), e(m) {
    for (auto &[u, v] : e) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v); }
};

struct Match : vector<int> {
  int count = 0;
  vector<pair<int, int>> bridges;
  Match(Graph g, int s = 0) : vector<int>(g.size(), -1), low(g.size()) {
    int t = 1;
    dfs(g, s, s, t);
  }
  void dfs(Graph &g, int u, int p, int &t) {
    auto &match = *this;
    auto tx = low[u] = t++;
    for (auto v : g[u]) {
      if (v != p) {
        if (low[v] == 0) {
          dfs(g, v, u, t);   // post-order (visit leaves first)
          if (low[v] > tx) { // new bridge
            bridges.emplace_back(u, v);
          }
          if (match[u] == match[v]) {
            match[u] = v;
            match[v] = u;
            count++;
          }
        }
        low[u] = min(low[u], low[v]);
      }
    }
  }

private:
  vector<int> low;
};

struct SCC : vector<int> {
  int count = 0;
  SCC(DGraph g) : vector<int>(g.size()), low(g.size()) {
    for (int i = 0, t = 1; i < g.size(); i++) {
      if (low[i] == 0) {
        dfs(g, i, t);
      }
    }
  }

private:
  void dfs(DGraph &g, int u, int &t) {
    auto tx = low[u] = t++;
    visited.push_back(u);
    for (auto v : g[u]) {
      if (low[v] == 0) {
        dfs(g, v, t);
      }
      low[u] = min(low[u], low[v]);
    }
    if (low[u] == tx) { // component root
      count++;
      for (int v = -1; v != u; visited.pop_back()) {
        v = visited.back();
        low[v] = g.size();
        (*this)[v] = count;
      }
    }
  }
  vector<int> low, visited;
};

template <typename T, int N> struct Trie : vector<pair<T, array<int, N>>> {
  Trie(int cap = 1) : vector<pair<T, array<int, N>>>(1) { this->reserve(cap); }
  void visit(const auto &f, const auto &x) {
    for (int i = 0, j = 0;; j++) {
      int k = f((*this)[i], j, x);
      if (k < 0) {
        break;
      }
      assert(k < N);
      auto &child = (*this)[i].second[k];
      if (!child) {
        child = this->size();
        this->emplace_back(); // might invalidate references
      }
      i = (*this)[i].second[k];
    }
  }
};

auto bit = [](int j, int x) { return x & (1 << j); };
auto pget = [](int j, int x) { return j < 32 ? bit(31 - j, x) != 0 : -1; };
auto padd = [](auto &node, int j, int x) { return node.first++, pget(j, x); };
auto prem = [](auto &node, int j, int x) { return node.first--, pget(j, x); };
auto sget = [](int j, int x) { return j >= 0 ? bit(j, x) != 0 : -1; };
auto sadd = [](auto &node, int j, int x) { return node.first++, sget(j, x); };
auto srem = [](auto &node, int j, int x) { return node.first--, sget(j, x); };

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

void debugn(int n) { cout << n << ';'; }

void debuga(auto &a) {
  for (auto &ai : a) {
    cout << ai << ',';
  }
  cout << ';';
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
