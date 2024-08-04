/**
 * https://codeforces.com/contest/1993/submission/274451250
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
  Int n, k;
  vector<Int> a(n);
  int mx = *ranges::max_element(a);
  int mnb = INT_MAX, mxb = 0;
  for (auto &ai : a) {
    int r = (mx - ai) / k;
    int b = ai + k * (r + r % 2);
    mnb = min(mnb, b);
    mxb = max(mxb, b);
  }
  println(mxb - mnb < k ? mxb : -1);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
