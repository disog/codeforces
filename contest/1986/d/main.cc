/**
 * https://codeforces.com/contest/1986/submission/273049350
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

void solve(int t) {
  Int n;
  Str s;
  int ans = INT_MAX;
  for (int i = 0; i < n - 1; i++) {
    int sum = (s[i] - '0') * 10 + s[i + 1] - '0';
    for (int j = 0; j < n; j++) {
      if (j == i) {
        j++;
        continue;
      }
      if (s[j] == '0') {
        println(0);
        return;
      }
      if (s[j] != '1') {
        if (sum == 1) {
          sum = 0;
        }
        sum += s[j] - '0';
      }
    }
    ans = min(ans, sum);
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
