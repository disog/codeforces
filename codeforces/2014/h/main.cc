/**
 * https://codeforces.com/contest/2014/submission/282536533
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using u64 = uint64_t;

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

u64 hilbert(int x, int y) { // O(log max(x,y))
  const unsigned mx = max(x, y) * 2 + 1;
  const int logn = (bit_width(mx) - 1) | 1;
  const int maxn = (1ull << logn) - 1;
  u64 ans = 0;
  for (int s = 1ull << (logn - 1); s; s >>= 1) {
    bool rx = x & s, ry = y & s;
    ans = (ans << 2) | (rx ? ry ? 2 : 1 : ry ? 3 : 0);
    if (!rx) {
      if (ry) {
        x ^= maxn, y ^= maxn;
      }
      swap(x, y);
    }
  }
  return ans;
}

struct Mos {
  vector<int> idx;
  vector<u64> ord;
  function<bool(int, int)> cmp = [&](int i, int j) { return ord[i] < ord[j]; };
  void build(auto &&q) { // O(m*log m)
    idx.resize(q.size());
    ord.resize(q.size());
    iota(idx.begin(), idx.end(), 0);
    for (int i = 0; i < q.size(); i++) {
      auto [l, r] = q[i];
      ord[i] = hilbert(l, r);
    }
    ranges::sort(idx, cmp);
  }
  void visit(auto &&q, auto &&add, auto &&rem, auto &&get,
             int from = 0) const { // O((n + m)*s)
    for (int i = 0, L = from, R = from - 1; i < idx.size(); i++) {
      auto [l, r] = q[idx[i]];
      while (L > l) {
        add(--L);
      }
      while (R < r) {
        add(++R);
      }
      while (L < l) {
        rem(L++);
      }
      while (R > r) {
        rem(R--);
      }
      get(idx[i]);
    }
  }
};

mt19937 rng(random_device{}());

void solve(int t) {
  Int n, m;
  vector<Int> a(n);
  vector<array<Int, 2>> q(m);
  unordered_map<int, int> ids;
  for (auto &&ai : a) { // O(n)
    if (!ids.contains(ai)) {
      ids[ai] = rng();
    }
  }
  vector<bool> ans(m);
  int acc = 0;
  auto add = [&](int i) { acc ^= ids[a[i - 1]]; };
  auto rem = [&](int i) { acc ^= ids[a[i - 1]]; };
  auto get = [&](int j) { ans[j] = acc; };
  Mos mos;
  mos.build(q);                   // O(m*log m)
  mos.visit(q, add, rem, get, 1); // O((n + m)*sqrt n)
  for (int i = 0; i < m; i++) {   // O(m)
    println(ans[i] ? "NO" : "YES");
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
