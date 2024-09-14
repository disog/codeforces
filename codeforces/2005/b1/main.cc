/**
 * https://codeforces.com/contest/2005/submission/281205597
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

void solve(int t) {
  Int n, m, q;
  vector<Int> b(m), a(q);
  ranges::sort(b);
  auto f = [&](int x) {
    return x < b[0] ? b[0] - 1 : x > b[1] ? n - b[1] : (b[1] - b[0]) / 2;
  };
  for (auto &&ai : a) {
    println(f(ai));
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}