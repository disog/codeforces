/**
 * https://codeforces.com/contest/1992/submission/273051439
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug(...)
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
  Int n, x;
  vector<Int> a(n);
  set<int> divs = {x};
  int ans = 1;
  for (auto &&ai : a) {
    if (divs.contains(ai)) {
      ans++;
      divs = {x, x / ai};
    } else if (x % ai == 0) {
      vector<int> add;
      for (auto &&di : divs) {
        if (di % ai == 0) {
          add.push_back(di / ai);
        }
      }
      divs.insert(add.begin(), add.end());
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
