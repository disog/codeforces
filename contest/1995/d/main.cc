/**
 * https://codeforces.com/contest/1995/submission/273051741
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

void solve(int t) {
  Int n, c, k;
  Str s;
  unsigned m = 1 << c;
  vector<int> cnt(c);
  vector<bool> bad(m);
  for (int i = 0, mask = 0; i < n; i++) {
    cnt[s[i] - 'A']++;
    mask |= 1 << (s[i] - 'A');
    if (i >= k - 1) {
      if (i >= k && !--cnt[s[i - k] - 'A']) {
        mask ^= 1 << (s[i - k] - 'A');
      }
      bad[(m - 1) ^ mask] = true;
    }
  }
  bad[(m - 1) ^ (1 << (s.back() - 'A'))] = true;
  int ans = c;
  for (unsigned i = m - 1; i > 0; i--) {
    if (!bad[i]) {
      ans = min(ans, popcount(i));
      continue;
    }
    for (int b = 1; b < m; b <<= 1) {
      if (i & b) {
        bad[i ^ b] = true;
      }
    }
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
