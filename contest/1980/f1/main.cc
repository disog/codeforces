/**
 * https://codeforces.com/contest/1980/submission/273047069
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
init();
#endif

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

using Cell = pair<array<Int, 2>, int>;

const auto cmp = [](const Cell &a, const Cell &b) {
  auto [ra, ca] = a.first;
  auto [rb, cb] = b.first;
  return ra > rb || (ra == rb && ca < cb);
};

void solve(int t) {
  Int n, m, k;
  vector<Cell> fs(k);
  for (int i = 0; i < k; i++) {
    fs[i].second = i;
  }
  ranges::sort(fs, cmp); // O(k*log k)
  vector<int> ans(k);
  i64 a = 0;
  int x = n, y = m + 1;
  for (auto &&[rc, i] : fs) { // O(k)
    auto [r, c] = rc;
    if (c < y) {
      a += i64(x - r) * (y - 1);
      x = r, y = c;
      ans[i] = 1;
    }
  }
  a += i64(x) * (y - 1);
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
