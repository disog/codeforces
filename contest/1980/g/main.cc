/**
 * https://codeforces.com/contest/1980/submission/274282774
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using namespace placeholders;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init();
#endif

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;
using Chr = Num<char>;

struct WGraph : vector<vector<array<int, 2>>> {
  WGraph(int n, int m = 0) : vector<vector<array<int, 2>>>(n + 1) {
    for (auto &[u, v, w] : vector<array<Int, 3>>(m)) {
      add(u, v, w);
    }
  }
  void add(int u, int v, int w) { _add(u, v, w), _add(v, u, w); }
  void _add(int u, int v, int w) { (*this)[u].push_back({v, w}); }
};

struct Query {
  Chr type;
  Int y, x = 0;
  Query() {
    if (type == '?') {
      x = {};
    }
  }
};

template <typename T, size_t N> struct Trie {
  vector<pair<T, array<int, N>>> nodes;
  Trie(int cap = 1) : nodes(1) { nodes.reserve(cap); }
  void visit(auto &&f, auto &&x) {
    for (int i = 0, j = 0;; j++) {
      int k = f(nodes[i], j, x);
      if (k < 0) {
        break;
      }
      assert(k < N);
      auto &child = nodes[i].second[k];
      if (!child) {
        child = nodes.size();
        nodes.emplace_back(); // might invalidate references
      }
      i = nodes[i].second[k];
    }
  }
};

const auto nodeinc = [](auto &node) { node++; };
const auto nodedec = [](auto &node) { node--; };
const auto nodevis = [](auto &&fn, auto &&fx, auto &node, int j, auto &&x) {
  return fn(node.first), fx(j, x);
};
const auto bitpref = [](int j, unsigned x) {
  return j < 32 ? (x & (1 << (31 - j))) != 0 : -1;
};
const auto bpinc = bind(nodevis, nodeinc, bitpref, _1, _2, _3);
const auto bpdec = bind(nodevis, nodedec, bitpref, _1, _2, _3);

const auto findmax = [](auto &trie, int x) {
  if (!trie.nodes[0].first) {
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
    if (c1 && trie.nodes[c1].first) {
      res |= bit;
      return off;
    }
    return 1 - off;
  };
  trie.visit(f, x);
  return res;
};

void solve(int t) {
  Int n, m;
  WGraph g(n, n - 1);
  vector<Query> q(m);
  vector<int> a(n + 1), b(n + 1);
  array<Trie<int, 2>, 2> tries;
  auto f1 = [&](auto &self, int u, int p, int x, int h) -> void {
    a[u] = x;
    b[u] = h & 1;
    tries[b[u]].visit(bpinc, x);
    for (auto [v, w] : g[u]) {
      if (v != p) {
        self(self, v, u, x ^ w, h + 1);
      }
    }
  };
  f1(f1, 1, 1, 0, 0);
  int y = 0;
  auto f2 = [&](int v, int x) {
    tries[b[v]].visit(bpdec, a[v]);
    auto w1 = findmax(tries[b[v]], a[v] ^ x);
    auto w2 = findmax(tries[1 - b[v]], a[v] ^ x ^ y);
    tries[b[v]].visit(bpinc, a[v]);
    return max(w1, w2);
  };
  vector<int> ans;
  for (auto &qi : q) {
    if (qi.type == '^') {
      y ^= qi.y;
    } else {
      ans.push_back(f2(qi.y, qi.x));
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
