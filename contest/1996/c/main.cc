/**
 * https://codeforces.com/contest/1996/submission/273628213
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

template <typename T> struct Fen {
  vector<T> nodes;
  Fen(int n) : nodes(n + 1) {}
  T &operator[](int i) { return nodes[i + 1]; } // O(1)
  void query(int i, auto &&f) const {           // O(log n)
    for (i++; i > 0; i -= i & -i) {
      f(nodes[i]);
    }
  }
  void update(int i, auto &&f) { // O(log n)
    for (i++; i < nodes.size(); i += i & -i) {
      f(nodes[i]);
    }
  }
  void update(auto &&f) { // O(n)
    for (int i = 1, j = 2; j < nodes.size(); i++, j = i + (i & -i)) {
      f(nodes[i], nodes[j]);
    }
  }
};

auto nodeinc = [](auto &node) { node++; };
auto ansadd = [](auto &ans, auto &node) { ans += node; };
auto anssub = [](auto &ans, auto &node) { ans -= node; };

constexpr int c = 'z' - 'a' + 1;

void solve(int t) {
  Int n, q;
  Str a, b;
  vector<array<Int, 2>> qs(q);
  vector<Fen<int>> ca(c, {n}), cb(c, {n});
  for (int i = 0; i < n; i++) {
    ca[a[i] - 'a'].update(i, nodeinc);
    cb[b[i] - 'a'].update(i, nodeinc);
  }
  for (auto &[l, r] : qs) {
    int ans = 0, sum = 0;
    auto add = bind(ansadd, ref(sum), _1);
    auto sub = bind(anssub, ref(sum), _1);
    for (int j = 0; j < c; j++, sum = 0) {
      cb[j].query(r - 1, add);
      cb[j].query(l - 2, sub);
      sum = -sum;
      ca[j].query(r - 1, add);
      ca[j].query(l - 2, sub);
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
