/**
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

template <typename T> struct FenTree {
  int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  FenTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(n + 1, val) {}
  T query(int i) const { // O(log n)
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
      _apply(i, val);
    }
  }
  void _apply(int i, const T &val) { nodes[i] = f(nodes[i], val); }
};

void solveEasy(const vector<int> &a) { // O(n)
  int ans = 0;
  for (int i = 0, j = 1; j < a.size();) {
    auto diff = a[j] - a[i], len = (j - i + 1);
    if (diff == len) {
      ans = max(ans, len);
    }
    diff > len ? i++ : j++;
  }
  println(ans);
}

const auto tmax = [](auto &lhs, auto &rhs) { return max(lhs, rhs); };

void solve(int t) {
  Int n;
  vector<Int> a(n);
  map<int, int> cnt;
  for (auto &&ai : a) { // O(n*log n)
    cnt[ai]++;
  }
  vector<int> b1, b2;
  for (auto &&[ai, c] : cnt) { // O(n)
    b1.push_back(ai);
    b2.push_back(c);
  }
  int m = cnt.size();
  for (int i = 1; i < m; i++) { // O(n)
    b2[i] += b2[i - 1];
  }
  if (b2.back() == m) {
    solveEasy(b1);
    return;
  }
  map<int, int> diff;
  for (int i = 1; i < m; i++) { // O(n*log n)
    diff[b2[i] - (b1[i] - b1[0])] = i;
  }
  FenTree<int> fen(diff.size(), tmax);
  int j = fen.n - 1;
  for (auto &[_, i] : diff) { // O(n*log n)
    fen.update(j, i);
    i = j--;
  }
  int ans = 0;
  for (int i = 0, c1 = 0, c2 = 0; i < n - 1; i++) { // O(n*log n)
    auto it = diff.lower_bound(c2);
    if (it != diff.end()) {
      auto x = fen.query(it->second);
      ans = max(ans, b1[x] - b1[i]);
    }
    c1 += b1[i + 1] - b1[i];
    c2 = b2[i] - c1;
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