/**
 * https://codeforces.com/contest/1995/submission/273294535
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

#pragma GCC optimize("O3,unroll-loops")

using namespace std;
using namespace placeholders;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init(__FILE__);
#endif

void println(const auto &...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void madd(auto &lhs, const auto &rhs, const auto &c) {
  for (int i = 0; i < lhs.size(); i++) {
    lhs[i] += rhs[i] * c;
  }
}

template <typename T, size_t N, size_t M = N>
using SMat = array<array<T, M>, N>;

template <typename T, size_t N, size_t M1, typename U, size_t M2>
SMat<U, N, M2> operator*(const SMat<T, N, M1> &lhs,
                         const SMat<U, M1, M2> &rhs) {
  SMat<U, N, M2> ans = {};
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M1; j++) {
      madd(ans[i], rhs[j], lhs[i][j]);
    }
  }
  return ans;
}

constexpr int lssb(unsigned x) { return countr_zero(x); }
constexpr int mssb(unsigned x) { return 31 - countl_zero(x); }

template <typename T> struct Seg {
  int n;
  vector<T> nodes;
  Seg(int n) : n(n), nodes(2 * n) {}
  Seg(int n, bool sorted) : Seg(sorted ? 1 << (1 + mssb(n - 1)) : n) {}
  const T &full() const { return nodes[1]; }    // O(1)
  T &operator[](int i) { return nodes[i + n]; } // O(1)
  void copy(const vector<T> &a) { ranges::copy(a, nodes.begin() + n); }
  void update(const auto &f) { // O(n)
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

struct Desk : SMat<bool, 2> {
  Desk join(const Desk &other) const {
    return static_cast<Desk>(*this * other);
  }
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
  Seg<Desk> seg(n);
  auto use = [&](int k, bool val) { // O(log n)
    auto [_, i, j] = edges[k];
    auto &desk = seg[i % n];
    desk[i % 2 == 0][j % 2] = val;
    seg.update(i % n, bind(&Desk::join, _1, _2));
  };
  int ans = INT_MAX;
  for (int l = 0, r = 0; ans > 0 && r < edges.size();) {
    if (seg.full().good()) {
      ans = min(ans, edges[r - 1][0] - edges[l][0]);
      use(l++, false);
    } else {
      use(r++, true);
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
