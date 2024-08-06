/**
 * https://codeforces.com/contest/1993/submission/274988721
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

struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

int binsearch(auto &&f, int s, int e) { // (s, e] O(log n)
  while (s < e) {
    auto m = (s + e + 1) / 2;
    f(m) ? s = m : e = m - 1;
  }
  return e; // last such that f is true
}

void solve(int t) {
  Int n, k;
  vector<Int> a(n);
  auto cmp1 = [&](int i, int j) { return a[i] < a[j]; };
  Iota idx(n, cmp1);              // indices of a in non-decreasing order
  int m = n % k ? n % k : int(k); // length of resulting array
  auto f = [&](int x) {           // O(n)
    vector<int> dp(m + 1);        // count of ai greater or equal to x
    for (int i = 0; i < n; i++) {
      int j = i % k; // index of ai in resulting array
      if (j < m) {   // if ai occurs in resulting array, include it in the count
        dp[j + 1] = max(dp[j + 1], dp[j] + (a[i] >= a[idx[x]]));
      }
    }
    return dp[m] > m / 2; // does x lie to the left of median?
  };
  auto cmp2 = [&](int i, int j) { return a[i] == a[j]; };
  int e = ranges::unique(idx, cmp2).begin() - idx.begin(); // remove duplicates
  int ans = binsearch(f, 0, e - 1);                        // O(n*log n)
  println(a[idx[ans]]);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
