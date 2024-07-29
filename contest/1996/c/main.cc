/**
 * https://codeforces.com/contest/1996/submission/273276195
 *
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

void println(const auto &...args) { ((cout << args << ' '), ...) << endl; }

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

struct Fen {
  vector<int> nodes;
  Fen(int n) : nodes(n + 1) {}
  void query(int i, const auto &f) {
    for (; i > 0; i -= i & -i) {
      f(nodes[i]);
    }
  }
  void update(int i, const auto &f) {
    assert(i > 0);
    for (; i < nodes.size(); i += i & -i) {
      f(nodes[i]);
    }
  }
};

constexpr int c = 'z' - 'a' + 1;

void solve(int t) {
  Int n, q;
  Str a, b;
  vector<array<Int, 2>> qs(q);
  vector<Fen> ca(c, Fen(n)), cb(c, Fen(n));
  auto inc = [&](auto &node) { node++; };
  for (int i = 0; i < n; i++) {
    ca[a[i] - 'a'].update(i + 1, inc);
    cb[b[i] - 'a'].update(i + 1, inc);
  }
  for (auto &[l, r] : qs) {
    int ans = 0, sum = 0;
    auto acc = [&](auto &node) { sum += node; };
    auto dec = [&](auto &node) { sum -= node; };
    for (int j = 0; j < c; j++, sum = 0) {
      cb[j].query(r, acc);
      cb[j].query(l - 1, dec);
      sum = -sum;
      ca[j].query(r, acc);
      ca[j].query(l - 1, dec);
      ans += max(0, sum);
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
