/**
 * https://codeforces.com/contest/1985/submission/273048582
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
  Int n, m;
  vector<Str> g(n);
  int h1 = 0, h2 = 0, k = 0;
  for (int i = 0; i < n; ++i) {
    auto pos = g[i].find('#');
    if (pos != string::npos) {
      if (!k) {
        k = pos + 1;
        h1 = i + 1;
      }
      h2 = i + 1;
    }
  }
  println((h1 + h2) / 2, k);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
