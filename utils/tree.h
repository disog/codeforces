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
  vector<int> parent, size;
  DSU(int n) : parent(n), size(n) {}
  int add(int v) { return size[v] = 1, parent[v] = v; }
  int find(int v) { return v == parent[v] ? v : parent[v] = find(parent[v]); }
  int merge(int a, int b) {
    a = find(a), b = find(b);
    if (a != b) {
      if (size[a] < size[b]) {
        swap(a, b);
      }
      size[a] += size[b];
      parent[b] = a;
    }
    return a;
  }
};

/**
 * Fenwick tree (Binary indexed tree)
 */
template <typename T> struct Fen {
  vector<T> nodes;
  Fen(int n) : nodes(n + 1) {}
  void query(int i, const auto &f) { // O(log n)
    for (; i > 0; i -= i & -i) {
      f(nodes[i]);
    }
  }
  void update(int i, const auto &f) { // O(log n)
    assert(i > 0);
    for (; i < nodes.size(); i += i & -i) {
      f(nodes[i]);
    }
  }
};

/**
 * Trie (N-ary prefix or suffix tree)
 */
template <typename T, size_t N> struct Trie {
  vector<pair<T, array<int, N>>> nodes;
  Trie(int cap = 1) : nodes(1) { nodes.reserve(cap); }
  void visit(const auto &f, const auto &x) {
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

// Trie manipulation
auto bit = [](int j, int x) { return x & (1 << j); };
auto chr = [](int j, str s) { return s[j] - 'a'; };

// Bit prefixes
auto bpget = [](int j, int x) { return j < 32 ? bit(31 - j, x) != 0 : -1; };
auto bpadd = [](auto &node, int j, int x) { return node.first++, bpget(j, x); };
auto bprem = [](auto &node, int j, int x) { return node.first--, bpget(j, x); };

// Bit suffixes
auto bsget = [](int j, int x) { return j < 32 ? bit(j, x) != 0 : -1; };
auto bsadd = [](auto &node, int j, int x) { return node.first++, bsget(j, x); };
auto bsrem = [](auto &node, int j, int x) { return node.first--, bsget(j, x); };

// String prefixes
auto spget = [](int j, str s) { return j < s.size() ? chr(j, s) : -1; };
auto spadd = [](auto &node, int j, str s) { return node.first++, spget(j, s); };
auto sprem = [](auto &node, int j, str s) { return node.first--, spget(j, s); };

// String suffixes
auto ssget = [](int j, str s) {
  return j < s.size() ? chr(s.size() - j - 1, s) : -1;
};
auto ssadd = [](auto &node, int j, str s) { return node.first++, ssget(j, s); };
auto ssrem = [](auto &node, int j, str s) { return node.first--, ssget(j, s); };

/**
 * Most/least significant set bits
 */
constexpr int lssb(unsigned x) { return countr_zero(x); }
constexpr int mssb(unsigned x) { return 31 - countl_zero(x); }

/**
 * Segment Tree
 */
template <typename T> struct Seg {
  int n;
  vector<T> nodes;
  Seg(int n) : n(n), nodes(2 * n) {}
  Seg(int n, bool stable) : Seg(stable ? 1 << (1 + mssb(n - 1)) : n) {}
  const T &full() const { return nodes[1]; }    // O(1)
  T &operator[](int i) { return nodes[i + n]; } // O(1)
  void update(const auto &f) {                  // O(n)
    for (int i = n - 1; i > 0; i--) {
      nodes[i] = f(nodes[2 * i], nodes[2 * i + 1]);
    }
  }
  void update(int i, const auto &f) { // O(log n)
    for (i = (i + n) / 2; i > 0; i /= 2) {
      nodes[i] = f(nodes[2 * i], nodes[2 * i + 1]);
    }
  }
  void query(int i, int j, const auto &f) const { // O(log n)
    i += n - 1, j += n;
    int mask = (1 << mssb(i ^ j)) - 1;
    for (int v = ~i & mask; v != 0; v &= v - 1) {
      if (!f(nodes[(i >> lssb(v)) + 1])) {
        return; // early return
      }
    }
    for (int v = j & mask; v != 0; v ^= 1 << mssb(v)) {
      if (!f(nodes[(j >> mssb(v)) - 1])) {
        return; // early return
      }
    }
  }
};
