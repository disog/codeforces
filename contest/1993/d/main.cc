/**
 * https://codeforces.com/contest/1993/submission/274985421
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

array<int, 2> lis(auto &&f, int s, int e) { // [s, e) O(n*log n)
  vector<int> inc = {s};
  for (int i = s + 1; i < e; i++) {
    if (f(inc.back(), i)) {
      inc.push_back(i);
    } else {
      *ranges::lower_bound(inc, i, f) = i;
    }
  }
  return {(int)inc.size() - (s >= e), inc.back()};
}

void solve(int t) {
  Int n, k;
  vector<Int> a(n);
  int m = n % k ? n % k : int(k); // count of resulting elements
  int c = (n - 1) / k + 1;        // count of indices for each resulting index
  vector<int> good(c * m, n);     // indices of elements greater than x
  auto cmp2 = [&](int i, int j) { return good[i] < good[j]; };
  auto cmp1 = [&](int i, int j) { return a[i] < a[j]; };
  auto cmp3 = [&](int i, int j) { return a[i] == a[j]; };
  Iota idx(n, cmp1);    // indices of a in non-decreasing order
  auto f = [&](int x) { // O(n*log n)
    for (int i = 0; i < n; i++) {
      if (i % k < m) {
        int j = (i % k + 1) * c - 1 - i / k;
        good[j] = a[i] >= a[idx[x]] ? i : int(n);
      }
    }
    auto [cnt, j] = lis(cmp2, 0, c * m);
    cnt -= good[j] == n; // hack
    return cnt > m / 2;  // does x lie to the left of median?
  };
  int e = ranges::unique(idx, cmp3).begin() - idx.begin();
  int ans = binsearch(f, 0, e - 1); // O(n*log^2 n)
  println(a[idx[ans]]);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
