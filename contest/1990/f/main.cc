/**
 * https://codeforces.com/contest/1990/submission/273418257
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

template <typename T> struct Seg {
  int n;
  vector<T> nodes;
  Seg(int n) : n(n), nodes(2 * n) {}
  Seg(int n, bool noshift) : Seg(noshift ? 1 << (1 + mssb(n - 1)) : n) {}
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
  void query(int l, int r, auto &&f) const { // O(log n)
    for (l += n, r += n; l <= r; l /= 2, r /= 2) {
      if (l % 2) {
        f(nodes[l++]);
      }
      if (r % 2 == 0) {
        f(nodes[r--]);
      }
    }
  }
};

struct Element {
  i64 sum, mx;
  int mpos, lpos, rpos;
  Element *child;
  ~Element() { delete child; }
  Element join(const Element &other) const {
    return {sum + other.sum, max(mx, other.mx),
            mx < other.mx ? other.mpos : mpos, min(lpos, other.lpos),
            max(rpos, other.rpos)};
  }
  void merge(const Element &other) {
    auto child1 = new Element(mx < other.mx ? *this : other);
    sum += other.sum;
    mx = max(mx, other.mx);
    mpos = mx < other.mx ? other.mpos : mpos;
    lpos = min(lpos, other.lpos);
    rpos = max(rpos, other.rpos);
    child = child1;
  }
  bool good() const { return 2 * mx < sum; }
};

auto joinmax = bind(&Element::join, _1, _2);

struct Query {
  Int type, x;
  I64 y;
};

void solve(int t) {
  Int n, q;
  vector<I64> a(n);
  vector<Query> qs(q);
  Seg<Element> seg(n);
  for (int i = 0; i < n; i++) {
    seg[i] = {a[i], a[i], i, i, i};
  }
  seg.update(joinmax);
  Element el;
  auto reduce = bind(&Element::merge, &el, _1);
  auto query = [&](auto &self, int l, int r) -> int { // O(n)
    el = {};
    seg.query(l, r, reduce);
    auto p = &el;
    for (; p && !p->good(); p = p->child)
      ;
    return p ? p->rpos - p->lpos + 1 : -1;
  };
  for (auto &[type, x, y] : qs) {
    if (type == 1) {
      println(query(query, x - 1, y - 1));
    } else {
      seg[x - 1] = {y, y, x - 1, x - 1, x - 1};
      seg.update(x - 1, joinmax);
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
