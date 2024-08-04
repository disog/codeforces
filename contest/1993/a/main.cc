/**
 * https://codeforces.com/contest/1993/submission/274347283
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

constexpr int M = 'D' - 'A' + 1;

void solve(int t) {
  Int n;
  Str s;
  array<int, M> cnt = {};
  for (auto &&c : s) {
    if (c != '?') {
      cnt[c - 'A']++;
    }
  }
  int ans = 0;
  for (int i = 0; i < M; i++) {
    ans += min<int>(n, cnt[i]);
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
