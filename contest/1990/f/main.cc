/**
 * https://codeforces.com/contest/1990/submission/273632039
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
  for (int i = 0; i < n; i++) {
    seg[i] = {a[i], a[i], i};
  }
  seg.update(joinseg);
  auto query = [&](auto &self, int l, int r) -> int { // O(n*log n)
    while (r - l >= 2) {
      auto el = seg.query(l, r, joinseg);
      if (el.good()) {
        return r - l + 1;
      }
      return max(self(self, l, el.pos - 1), self(self, el.pos + 1, r));
    }
    return -1;
  };
  for (auto &[type, x, y] : qs) {
    if (type == 1) {
      println(query(query, x - 1, y - 1));
    } else {
      seg[x - 1] = {y, y, x - 1};
      seg.update(x - 1, joinseg);
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
