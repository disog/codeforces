/**
 * https://codeforces.com/contest/1992/submission/273051262
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
  Int n, m, k;
  Str a;
  for (int i = -1, e = m - 1; e < n;) {
    int logi = e;
    for (; logi > i && a[logi] != 'L'; logi--)
      ;
    if (logi > i) {
      i = logi;
      e = i + m;
    } else if (a[e] == 'W' && k) {
      k--;
      i = e++;
    } else {
      println("NO");
      return;
    }
  }
  println("YES");
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
