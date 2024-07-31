/**
 * https://codeforces.com/contest/1996/submission/273779605
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using namespace placeholders;

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

struct Str : string {
  Str() { cin >> *this; }
};

template <typename T, T unit = T{}> struct Fen {
  int n;
  vector<T> nodes;
  Fen(int n) : n(n), nodes(n + 1, unit) {}
  T &operator[](int i) { return nodes[i + 1]; } // O(1)
  T query(int i, auto &&f) const {              // O(log n)
    assert(i < n);
    T ans = unit;
    for (i++; i > 0; i -= i & -i) {
      ans = f(ans, nodes[i]);
    }
    return ans;
  }
  void update(int i, auto &&f, const T &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) {
      nodes[i] = f(nodes[i], val);
    }
  }
  void update(auto &&f) { // O(n)
    for (int i = 1, j = 2; j <= n; i++, j = i + (i & -i)) {
      nodes[j] = f(nodes[j], nodes[i]);
    }
  }
};

auto tadd = [](auto &a, auto &b) { return a + b; };

constexpr int c = 'z' - 'a' + 1;

void solve(int t) {
  Int n, q;
  Str a, b;
  vector<array<Int, 2>> qs(q);
  vector<Fen<int>> ca(c, {n}), cb(c, {n});
  for (int i = 0; i < n; i++) {
    ca[a[i] - 'a'].update(i, tadd, 1);
    cb[b[i] - 'a'].update(i, tadd, 1);
  }
  auto f = [&](int j, int l, int r) {
    int sum = ca[j].query(r - 1, tadd);
    sum -= ca[j].query(l - 2, tadd);
    sum -= cb[j].query(r - 1, tadd);
    sum += cb[j].query(l - 2, tadd);
    return max(0, sum);
  };
  for (auto &[l, r] : qs) {
    int ans = 0;
    for (int j = 0; j < c; j++) {
      ans += f(j, l, r);
    }
    println(ans);
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
