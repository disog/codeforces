/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

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

template <typename T, T unit = T{}> struct Fen {
  const int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  Fen(int n, auto &&f) : n(n), f(f), nodes(n + 1, unit) {}
  T &operator[](int i) { return nodes[i + 1]; } // O(1)
  T query(int i) const {                        // O(log n)
    assert(i < n);
    T ans = unit;
    for (i++; i > 0; i -= i & -i) {
      ans = f(ans, nodes[i]);
    }
    return ans;
  }
  void update(int i, const T &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) {
      nodes[i] = f(nodes[i], val);
    }
  }
  void update() { // O(n)
    for (int i = 1, j = 2; j <= n; i++, j = i + (i & -i)) {
      nodes[j] = f(nodes[j], nodes[i]);
    }
  }
};

auto tadd = [](auto &lhs, auto &rhs) { return lhs + rhs; };

void solve(int t) {
  Int n, m;
  vector<array<Int, 2>> fs(m);
  map<int, vector<array<int, 2>>> map;
  for (auto &[a, b] : fs) {
    map[min(b - a, n - b + a)].push_back({a, b});
  }
  vector<bool> taken(n);
  Fen<int> fen(n, tadd);
  int ans = 0;
  auto f = [&](int i) {
    if (!taken[i]) {
      fen.update(i, 1);
      taken[i] = true;
      ans++;
    }
  };
  for (auto &[_, pairs] : map) {
    for (auto &[a, b] : pairs) {
      auto ca = fen.query(a - 1);
      auto cb = fen.query(b - 1);
      auto cn = fen.query(n - 1);
      if ((a + n - b) - (ca + cn - cb) < (b - a) - (cb - ca)) {
        for (int i = 0; i < a; i++) {
          f(i);
        }
        for (int i = b; i < n; i++) {
          f(i);
        }
      } else {
        for (int i = a; i < b; i++) {
          f(i);
        }
      }
    }
  }
  cout << ans << endl;
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
