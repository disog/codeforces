/**
 * https://codeforces.com/contest/1990/submission/274273830
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
init();
#endif

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;
using I64 = Num<i64>;

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

template <typename T> struct SegTree {
  const int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  SegTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(2 * n, val) {}
  const T &full() const { return nodes[1]; }    // O(1)
  T &operator[](int i) { return nodes[i + n]; } // O(1)
  T query(int l, int r) const {                 // O(log n)
    assert(l >= 0 && l <= r && r < n);
    return _inner(l + n, r + n);
  }
  T _inner(int l, int r) const { // [l, r] O(log n)
    return l == r       ? nodes[l]
           : l % 2      ? f(nodes[l], _inner(l + 1, r))
           : r % 2 == 0 ? f(_inner(l, r - 1), nodes[r])
                        : _inner(l / 2, r / 2);
  }
  void update(int i, bool single = true) { // O(log n) / [0, i] O(n)
    assert(i >= 0 && i < n);
    for (i = (i + n) / 2; i > 0; i = single ? i / 2 : i - 1) {
      nodes[i] = f(nodes[2 * i], nodes[2 * i + 1]);
    }
  }
};

struct Seg {
  i64 sum, mx;
  int mpos;
  Seg join(const Seg &other) const {
    auto ans = mx < other.mx ? other : *this;
    ans.sum = sum + other.sum;
    return ans;
  }
};

struct Query {
  Int type, x;
  I64 y;
};

void solve(int t) {
  Int n, q;
  vector<I64> a(n);
  vector<Query> queries(q);
  SegTree<Seg> segments(n, &Seg::join);
  for (int i = 0; i < n; i++) {
    segments[i] = {a[i], a[i], i};
  }
  segments.update(n - 1, false);
  IntTree<int> intervals(n, 0, n);
  map<array<int, 2>, int> cache;
  auto prune = [&](int l, int r) { return cache.erase({l, r}), true; };
  auto query = [&](auto &self, int l, int r) -> int { // O(log n)
    if (r - l < 2) {
      return -1;
    }
    auto [it, ok] = cache.insert({{l, r + 1}, 0});
    auto &ans = it->second;
    if (!ok) {
      return ans;
    }
    intervals.insert(l, r + 1);
    auto [sum, mx, mpos] = segments.query(l, r);
    if (2 * mx < sum) {
      return ans = r - l + 1;
    }
    return ans = max(self(self, l, mpos - 1), self(self, mpos + 1, r));
  };
  for (auto &[type, x, y] : queries) {
    if (type == 1) {
      println(query(query, x - 1, y - 1));
    } else {
      segments[x - 1] = {y, y, x - 1};
      segments.update(x - 1);
      intervals.visit(x - 1, prune);
    }
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
