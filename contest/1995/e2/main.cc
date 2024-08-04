/**
 * https://codeforces.com/contest/1995/submission/274273786
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

#pragma GCC optimize("O3,unroll-loops")

using namespace std;

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

inline void madd(auto &lhs, const auto &rhs, const auto &c) {
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

struct Seg : SMat<bool, 2> {
  Seg join(const Seg &other) const { return static_cast<Seg>(*this * other); }
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
  SegTree<Seg> desks(n, &Seg::join);
  auto use = [&](int k, bool val) { // O(log n)
    auto [_, i, j] = edges[k];
    auto &desk = desks[i % n];
    desk[i % 2 == 0][j % 2] = val;
    desks.update(i % n);
  };
  int ans = INT_MAX;
  for (int l = 0, r = 0; ans > 0 && r < edges.size();) {
    if (desks.full().good()) {
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
