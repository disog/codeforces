/**
 * (c) 2024 Diego Sogari
 */
#include "graph.h"
#include "utils.h"

/**
 * Tree
 */
struct Tree : Graph {
  struct Info {
    int par, dep, siz, hei;
  };
  vector<Info> info;
  Tree(int n) : Graph(n), info(n + 1) {} // no edges
  Tree(int n, int s) : Graph(n, n - 1), info(n + 1) { dfs(s, s); }
  void dfs(int u, int p, int d = 1) {
    auto &cur = info[u] = {p, d, 1, 1};
    for (auto &v : (*this)[u]) {
      if (v != p) {
        dfs(v, u, d + 1);
        cur.siz += info[v].siz;
        cur.hei = max(cur.hei, 1 + info[v].hei);
      }
    }
  }
};

/**
 * Disjoint set union (Union find)
 */
struct DSU {
  vector<int> par, siz;
  DSU(int n) : par(n), siz(n) {}
  int add(int v) { return siz[v] = 1, par[v] = v; }
  int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); }
  int merge(int a, int b) {
    a = find(a), b = find(b);
    if (a != b) {
      if (siz[a] < siz[b]) {
        swap(a, b);
      }
      siz[a] += siz[b];
      par[b] = a;
    }
    return a;
  }
};

/**
 * Fenwick Tree (Binary indexed tree)
 */
template <typename T, T unit = T{}> struct Fen {
  const int n;
  vector<T> nodes;
  Fen(int n) : n(n), nodes(n + 1, unit) {}
  T &operator[](int i) { return nodes[i + 1]; } // O(1)
  T query(int i, auto &&f) const {              // O(log n)
    assert(i < n);
    T ans = unit;
    for (i++; i > 0; i -= i & -i) {
      ans = f(ans, nodes[i]);
    }
    return ans;
  }
  void update(int i, auto &&f, const T &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) {
      nodes[i] = f(nodes[i], val);
    }
  }
  void update(auto &&f) { // O(n)
    for (int i = 1, j = 2; j <= n; i++, j = i + (i & -i)) {
      nodes[j] = f(nodes[j], nodes[i]);
    }
  }
};

/**
 * Trie (N-ary prefix or suffix tree)
 */
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

/**
 * Segment Tree
 */
template <typename T, T unit = T{}> struct SegTree {
  const int n;
  vector<T> nodes;
  SegTree(int n) : n(n), nodes(2 * n, unit) {}
  SegTree(int n, bool stable) : SegTree(stable ? 1 << (1 + mssb(n - 1)) : n) {}
  const T &full() const { return nodes[1]; }         // O(1)
  T &operator[](int i) { return nodes[i + n]; }      // O(1)
  void update(int i, auto &&f, bool single = true) { // O(log n) / O(n)
    assert(i >= 0 && i < n);
    for (i = (i + n) / 2; i > 0; i = single ? i / 2 : i - 1) {
      nodes[i] = f(nodes[2 * i], nodes[2 * i + 1]);
    }
  }
  T query(int l, int r, auto &&f) const { // [l, r] O(log n)
    assert(l >= 0 && l <= r && r < n);
    T ans = unit;
    for (l += n, r += n; l <= r; l /= 2, r /= 2) {
      if (l % 2) {
        ans = f(ans, nodes[l++]);
      }
      if (r % 2 == 0) {
        ans = f(ans, nodes[r--]);
      }
    }
    return ans;
  }
};

/**
 * Interval Tree Node
 */
template <typename T> struct Interval {
  T mid;
  list<array<T, 2>> contained;
  void insert(T l, T r) { contained.push_back({l, r}); } // O(1)
  void visit(T x, auto &&f) {                            // O(n)
    for (auto it = contained.begin(); it != contained.end();) {
      auto [l, r] = *it;
      it = l <= x && x < r && f(l, r) ? contained.erase(it) : next(it);
    }
  }
};

/**
 * Interval Tree
 */
template <typename T> struct IntTree {
  const int n;
  vector<Interval<T>> nodes;
  IntTree(int n) : n(n), nodes(2 * n) {}
  IntTree(int n, T l, T r) : IntTree(n) { build(l, r); }
  void build(T l, T r, int i = 1) { // [l, r) O(n)
    auto mid = nodes[i].mid = (l + r) / 2;
    if (i < n) {
      build(l, mid, 2 * i);
      build(mid, r, 2 * i + 1);
    }
  }
  void insert(T l, T r) { // [l, r) O(log n)
    assert(l < r);
    int i = 1;
    while (i < n && (l >= nodes[i].mid || r <= nodes[i].mid)) {
      i = 2 * i + (l >= nodes[i].mid);
    }
    nodes[i].insert(l, r);
  }
  void visit(T x, auto &&f) { // O(n^2) all covering point x
    int i = 1;
    for (; i < n; i = 2 * i + (x >= nodes[i].mid)) {
      nodes[i].visit(x, f); // internal node
    }
    nodes[i].visit(x, f); // leaf node
  }
};

// Tree manipulation
auto tadd = [](auto &lhs, auto &rhs) { return lhs + rhs; };
auto tmul = [](auto &lhs, auto &rhs) { return lhs * rhs; };
auto tmin = [](auto &lhs, auto &rhs) { return min(lhs, rhs); };
auto tmax = [](auto &lhs, auto &rhs) { return max(lhs, rhs); };

// Trie manipulation
auto nodeinc = [](auto &node) { node++; };
auto nodedec = [](auto &node) { node--; };
auto nodevis = [](auto &&fn, auto &&fx, auto &node, int j, auto &&x) {
  return fn(node.first), fx(j, x);
};

// Bit prefixes
auto bitpref = [](int j, unsigned x) {
  return j < 32 ? (x & (1 << (31 - j))) != 0 : -1;
};
auto bpinc = bind(nodevis, nodeinc, bitpref, _1, _2, _3);
auto bpdec = bind(nodevis, nodedec, bitpref, _1, _2, _3);

// Bit suffixes
auto bitsuff = [](int j, unsigned x) {
  return j < 32 ? (x & (1 << j)) != 0 : -1;
};
auto bsinc = bind(nodevis, nodeinc, bitsuff, _1, _2, _3);
auto bsdec = bind(nodevis, nodedec, bitsuff, _1, _2, _3);

// String prefixes
auto strpref = [](int j, auto &&s) { return j < s.size() ? s[j] - 'a' : -1; };
auto spinc = bind(nodevis, nodeinc, strpref, _1, _2, _3);
auto spdec = bind(nodevis, nodedec, strpref, _1, _2, _3);

// String suffixes
auto strsuff = [](int j, auto &&s) {
  return j < s.size() ? s[s.size() - j - 1] - 'a' : -1;
};
auto ssinc = bind(nodevis, nodeinc, strsuff, _1, _2, _3);
auto ssdec = bind(nodevis, nodedec, strsuff, _1, _2, _3);
