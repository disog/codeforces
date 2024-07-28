/**
 * https://codeforces.com/contest/1980/submission/273047091
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

void solve(int t) {
  Int n, m, k;
  vector<array<Int, 2>> fs(k);
  map<int, map<int, int>> cols;
  for (int i = 0; i < k; i++) { // O(k*log k)
    auto [r, c] = fs[i];
    auto &rows = cols[c];
    rows[r] = i;
    if (rows.size() > 2) {
      rows.erase(rows.begin());
    }
  }
  vector<i64> ans(k);
  i64 a = 0;
  int pra = 0, prb = 0, pca = 1, pcb = 1, pi = 0;
  auto f = [&](int c) { a += i64(n - prb) * (c - pcb); };
  auto g = [&](int c) { ans[pi] += i64(prb - pra) * (c - max(pca, pcb)); };
  for (auto &[c, rows] : cols) { // O(k)
    auto [rb, i] = *rows.rbegin();
    if (rb > prb) {
      f(c), g(c);
      auto ra = rows.size() > 1 ? rows.begin()->first : 0;
      pra = ra > prb ? ra : prb;
      pca = ra > prb ? c : pcb;
      prb = rb, pcb = c, pi = i;
    } else if (rb > pra) {
      g(c);
      pra = rb, pca = c;
    }
  }
  f(m + 1), g(m + 1);
  println(a);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
