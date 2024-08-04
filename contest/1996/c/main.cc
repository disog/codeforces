/**
 * https://codeforces.com/contest/1996/submission/274276789
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

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

struct Str : string {
  Str() { cin >> *this; }
};

template <typename T> struct FenTree {
  const int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  FenTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(n + 1, val) {}
  T &operator[](int i) { return nodes[i + 1]; } // O(1)
  T query(int i) const {                        // O(log n)
    assert(i < n);
    T ans = nodes[0];
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
};

const auto tadd = [](auto &a, auto &b) { return a + b; };

constexpr int c = 'z' - 'a' + 1;

void solve(int t) {
  Int n, q;
  Str a, b;
  vector<array<Int, 2>> qs(q);
  vector<FenTree<int>> ca(c, {n, tadd}), cb(c, {n, tadd});
  for (int i = 0; i < n; i++) {
    ca[a[i] - 'a'].update(i, 1);
    cb[b[i] - 'a'].update(i, 1);
  }
  auto f = [&](int j, int l, int r) {
    int sum = ca[j].query(r - 1);
    sum -= ca[j].query(l - 2);
    sum -= cb[j].query(r - 1);
    sum += cb[j].query(l - 2);
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
