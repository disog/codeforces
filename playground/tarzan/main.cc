/**
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

void solve(int t) {
  Int n;
  vector<Int> a(n);
  vector<int> dp(n, n - 1);
  dp[0] = 0;
  for (int i = 0, r = 1; r < n; i++) { // O(n)
    for (; r < n && r <= i + a[i]; r++) {
      dp[r] = min(dp[r], dp[i] + 1);
    }
    int j = i + 1 + a[i + 1];
    if (j < n) {
      dp[j] = min(dp[j], dp[i] + 1);
    }
  }
  println(dp[n - 1]);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
