/**
 * https://codeforces.com/contest/1980/submission/269773132
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T = int> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
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

struct Query {
  Num<char> type;
  Num<> y, x = 0;
  Query() {
    if (type == '?') {
      x = {};
    }
  }
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

auto findmax = [](auto &trie, int x) {
  if (!trie[0].first) {
    return -1;
  }
  int res = 0;
  auto f = [&](auto &node, int j, int x) {
    if (j == 32) {
      return -1;
    }
    auto [c1, c2] = node.second;
    auto bit = 1 << (31 - j);
    int off = (x & bit) == 0;
    if (off) {
      swap(c1, c2);
    }
    if (c1 && trie[c1].first) {
      res |= bit;
      return off;
    }
    return 1 - off;
  };
  trie.visit(f, x);
  return res;
};

void solve(int t) {
  Num n, m;
  WGraph g(n + 1, n - 1);
  vector<Query> q(m);
  vector<int> a(n + 1), b(n + 1);
  array<Trie<int, 2>, 2> tries;
  function<void(int, int, int, int)> f = [&](int u, int p, int x, int h) {
    a[u] = x;
    b[u] = h & 1;
    tries[b[u]].visit(padd, x);
    for (auto [v, w] : g[u]) {
      if (v != p) {
        f(v, u, x ^ w, h + 1);
      }
    }
  };
  f(1, 1, 0, 0);
  int y = 0;
  auto ans = [&](int v, int x) {
    tries[b[v]].visit(prem, a[v]);
    auto z1 = a[v] ^ x, z2 = z1 ^ y;
    auto w1 = findmax(tries[b[v]], z1);
    auto w2 = findmax(tries[1 - b[v]], z2);
    tries[b[v]].visit(padd, a[v]);
    return max(w1, w2);
  };
  for (auto &qi : q) {
    if (qi.type == '^') {
      y ^= qi.y;
    } else {
      cout << ans(qi.y, qi.x) << ' ';
    }
  }
  cout << endl;
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
