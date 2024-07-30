/**
 * https://codeforces.com/contest/1990/submission/273634673
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

template <typename T> struct IntTree {
  struct Node {
    int L, R, M; // [L, R)
    set<array<int, 2>> by_l, by_r;
    void ins(int l, int r) {
      by_l.insert({l, r});
      by_r.insert({r, l});
    }
    void del(int l, int r) {
      by_l.erase({l, r});
      by_r.erase({r, l});
    }
  };
  int n;
  vector<Node> nodes;
  map<array<int, 2>, T> cache;
  IntTree(int n) : n(n), nodes(4 * n) { build(0, 0, n); }
  void build(int i, int l, int r) { // [l, r)
    int mid = (l + r) / 2;
    nodes[i] = {l, r, mid};
    if (l + 1 != r) {
      build(2 * i + 1, l, mid);
      build(2 * i + 2, mid, r);
    }
  }
  void insert(int i, int l, int r) { // [l, r)
    if (nodes[i].L + 1 == nodes[i].R) {
      nodes[i].ins(l, r);
    } else if (l >= nodes[i].M) {
      insert(2 * i + 2, l, r);
    } else if (r <= nodes[i].M) {
      insert(2 * i + 1, l, r);
    } else {
      nodes[i].ins(l, r);
    }
  }
  void delpref(int i, int x) {
    auto &st = nodes[i].by_l;
    while (!st.empty()) {
      auto [l, r] = *begin(st);
      if (l <= x) {
        nodes[i].del(l, r);
        cache.erase({l, r});
      } else {
        break;
      }
    }
  }
  void delsuff(int i, int x) {
    auto &st = nodes[i].by_r;
    while (!st.empty()) {
      auto [r, l] = *rbegin(st);
      if (r > x) {
        nodes[i].del(l, r);
        cache.erase({l, r});
      } else {
        break;
      }
    }
  }
  void erase(int i, int x) { // all covering point x
    if (x < nodes[i].M) {
      delpref(i, x);
    } else {
      delsuff(i, x);
    }
    if (nodes[i].L + 1 != nodes[i].R) {
      if (x < nodes[i].M) {
        erase(2 * i + 1, x);
      } else {
        erase(2 * i + 2, x);
      }
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
    auto [it, ok] = intervals.cache.emplace(array<int, 2>{l, r + 1}, 0);
    auto &ans = it->second;
    if (!ok) {
      return ans;
    }
    intervals.insert(0, l, r + 1);
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
      intervals.erase(0, x - 1);
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
