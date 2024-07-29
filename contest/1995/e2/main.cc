/**
 * https://codeforces.com/contest/1995/submission/273272745
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
init(__FILE__);
#endif

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(const auto &...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

template <typename T, size_t N, size_t M = N>
struct SMat : array<array<T, M>, N> {
  SMat(T s = {}) {
    for (auto &row : *this) {
      row.fill(s);
    }
  }
};

template <typename T, size_t N, typename U>
SMat<T, N> &operator*=(SMat<T, N> &lhs, const SMat<U, N> &rhs) {
  for (int i = 0; i < N; i++) {
    auto row = lhs[i]; // copy
    for (int j = 0; j < N; j++) {
      lhs[i][j] = 0; // reset
      for (int k = 0; k < N; k++) {
        lhs[i][j] += row[k] * rhs[k][j];
      }
    }
  }
  return lhs;
}

constexpr int lssb(unsigned x) { return countr_zero(x); }
constexpr int mssb(unsigned x) { return 31 - countl_zero(x); }

template <typename T> struct Seg {
  int n;
  vector<T> nodes;
  Seg(int n, bool sorted)
      : n(n), nodes(sorted ? 1 << (2 + mssb(n - 1)) : 2 * n) {}
  Seg(const vector<T> &a, bool sorted) : Seg(a.size(), sorted) { // O(n)
    ranges::copy(a, nodes.begin() + n);
    for (int i = n - 1; i > 0; i--) {
      (nodes[i] = nodes[2 * i]).join(nodes[2 * i + 1]);
    }
  }
  void update(int i) { // O(log n)
    for (i = (i + n) / 2; i > 0; i /= 2) {
      (nodes[i] = nodes[2 * i]).join(nodes[2 * i + 1]);
    }
  }
  const T &full() const { return nodes[1]; }    // O(1)
  T &operator[](int i) { return nodes[i + n]; } // O(1)
  T query(int i, int j) const {                 // O(log n)
    T ans = {};
    range(i, j, [&](int k) { return ans.join(nodes[k]); });
    return ans;
  }
  void range(int i, int j, const auto &f) const { // O(log n)
    i += n - 1, j += n;
    int mask = (1 << mssb(i ^ j)) - 1;
    for (int v = ~i & mask; v != 0; v &= v - 1) {
      if (!f((i >> lssb(v)) + 1)) {
        return; // early return
      }
    }
    for (int v = j & mask; v != 0; v ^= 1 << mssb(v)) {
      if (!f((j >> mssb(v)) - 1)) {
        return; // early return
      }
    }
  }
};

struct Desk : SMat<bool, 2> {
  void join(const Desk &other) { *this *= other; }
  bool good() const { return (*this)[0][0] || (*this)[1][1]; }
};

void solve(int t) {
  Int n;
  vector<Int> a(2 * n);
  if (n == 1) {
    println(0);
    return;
  }
  if (n % 2 == 0) {
    int mn = INT_MAX, mx = 0;
    for (int i = 0; i < n; i += 2) {
      vector<int> sums = {
          a[i] + a[i + 1],
          a[i] + a[i + n + 1],
          a[i + n] + a[i + 1],
          a[i + n] + a[i + n + 1],
      };
      ranges::sort(sums);
      mn = min(mn, sums[1]);
      mx = max(mx, sums[2]);
    }
    println(mx - mn);
    return;
  }
  vector<array<int, 3>> edges;
  auto add = [&](int i, int j) { edges.push_back({a[i] + a[j], i, j}); };
  auto cmp = [&](auto &e1, auto &e2) { return e1[0] < e2[0]; };
  for (int i = 0; i < 2 * n; i++) {
    add(i, (i + 1) % (2 * n));
    add(i, (i + n + 1) % (2 * n));
  }
  ranges::sort(edges, cmp);
  Seg<Desk> seg(n, true);
  auto use = [&](int k, bool val) { // O(log n)
    auto [_, i, j] = edges[k];
    auto &desk = seg[i % n];
    desk[i % 2 == 0][j % 2] = val;
    seg.update(i % n);
  };
  int ans = INT_MAX;
  for (int l = 0, r = 0, e = edges.size(); ans > 0 && r < e;) {
    while (r < e && !seg.full().good()) {
      use(r++, true);
    }
    if (seg.full().good()) {
      ans = min(ans, edges[r - 1][0] - edges[l][0]);
      while (l < r && edges[r - 1][0] - edges[l][0] >= ans) {
        use(l++, false);
      }
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
