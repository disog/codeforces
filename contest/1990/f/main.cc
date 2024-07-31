/**
 * https://codeforces.com/contest/1990/submission/273639773
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using namespace placeholders;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init(__FILE__);
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

struct IntNode {
  int left, right, mid; // [left, right)
  set<array<int, 2>> by_l, by_r;
  void insert(int l, int r) {
    by_l.insert({l, r});
    by_r.insert({r, l});
  }
  void erase(int l, int r, auto &&f) {
    f(l, r);
    by_l.erase({l, r});
    by_r.erase({r, l});
  }
  void erase(int x, auto &&f) {
    bool isleft = x < mid;
    auto &set = isleft ? by_l : by_r;
    while (set.size()) {
      auto [l, r] = isleft ? *set.begin() : *set.rbegin();
      if ((l > x) ^ isleft) {
        isleft ? erase(l, r, f) : erase(r, l, f);
      } else {
        break;
      }
    }
  }
};

template <typename T> struct IntTree {
  int n;
  vector<IntNode> nodes;
  map<array<int, 2>, T> values;
  function<void(int, int)> prune = [&](int l, int r) { values.erase({l, r}); };
  IntTree(int n) : n(n), nodes(4 * n) { build(0, n); }
  void build(int l, int r, int i = 0) { // [l, r)
    int mid = (l + r) / 2;
    nodes[i] = {l, r, mid};
    if (l + 1 != r) {
      build(l, mid, 2 * i + 1);
      build(mid, r, 2 * i + 2);
    }
  }
  void insert(int l, int r, int i = 0) { // [l, r)
    if (l < nodes[i].mid && r > nodes[i].mid) {
      nodes[i].insert(l, r);
    } else {
      insert(l, r, 2 * i + 1 + (l >= nodes[i].mid));
    }
  }
  void erase(int x, int i = 0) { // all covering point x
    nodes[i].erase(x, prune);
    if (nodes[i].left + 1 != nodes[i].right) {
      erase(x, 2 * i + 1 + (x >= nodes[i].mid));
    }
  }
};

constexpr int lssb(unsigned x) { return countr_zero(x); }
constexpr int mssb(unsigned x) { return 31 - countl_zero(x); }

template <typename T, T unit = T{}> struct SegTree {
  int n;
  vector<T> nodes;
  SegTree(int n) : n(n), nodes(2 * n, unit) {}
  SegTree(int n, bool stable) : SegTree(stable ? 1 << (1 + mssb(n - 1)) : n) {}
  const T &full() const { return nodes[1]; }    // O(1)
  T &operator[](int i) { return nodes[i + n]; } // O(1)
  void update(auto &&f) {                       // O(n)
    for (int i = n - 1; i > 0; i--) {
      nodes[i] = f(nodes[2 * i], nodes[2 * i + 1]);
    }
  }
  void update(int i, auto &&f) { // O(log n)
    for (i = (i + n) / 2; i > 0; i /= 2) {
      nodes[i] = f(nodes[2 * i], nodes[2 * i + 1]);
    }
  }
  T query(int l, int r, auto &&f) const { // O(log n)
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

struct Seg {
  i64 sum, mx;
  int pos;
  Seg join(const Seg &other) const {
    auto ans = mx < other.mx ? other : *this;
    ans.sum = sum + other.sum;
    return ans;
  }
  bool good() const { return 2 * mx < sum; }
};

auto joinseg = bind(&Seg::join, _1, _2);

struct Query {
  Int type, x;
  I64 y;
};

void solve(int t) {
  Int n, q;
  vector<I64> a(n);
  vector<Query> qs(q);
  SegTree<Seg> seg(n);
  IntTree<int> intervals(n);
  for (int i = 0; i < n; i++) {
    seg[i] = {a[i], a[i], i};
  }
  seg.update(joinseg);
  auto query = [&](auto &self, int l, int r) -> int { // O(log n)
    if (r - l < 2) {
      return -1;
    }
    auto [it, ok] = intervals.values.emplace(array<int, 2>{l, r + 1}, 0);
    auto &ans = it->second;
    if (!ok) {
      return ans;
    }
    intervals.insert(l, r + 1);
    auto el = seg.query(l, r, joinseg);
    if (el.good()) {
      return ans = r - l + 1;
    }
    auto ansl = self(self, l, el.pos - 1);
    auto ansr = self(self, el.pos + 1, r);
    return ans = max(ansl, ansr);
  };
  for (auto &[type, x, y] : qs) {
    if (type == 1) {
      println(query(query, x - 1, y - 1));
    } else {
      seg[x - 1] = {y, y, x - 1};
      seg.update(x - 1, joinseg);
      intervals.erase(x - 1);
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
