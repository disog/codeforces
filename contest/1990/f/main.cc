/**
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

void println(const auto &...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;
using I64 = Num<i64>;

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

constexpr int lssb(unsigned x) { return countr_zero(x); }
constexpr int mssb(unsigned x) { return 31 - countl_zero(x); }

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

struct Query {
  Int type, a, b;
};

void solve(int t) {
  Int n, q;
  vector<I64> a(n);
  vector<Query> qs(q);
  Fen<int> fen(n);
  Seg<int> seg(n);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
