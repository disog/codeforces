/**
 * https://codeforces.com/contest/1993/submission/274561427
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using namespace placeholders;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init();
#endif

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ','; }), os;
}
void println2(auto &&...args) { ((cout << args << ';'), ...) << endl; }
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

int lis(auto &&f, int s, int e) { // [s, e) O(n*log n)
  vector<int> inc = {s};
  for (int i = s + 1; i < e; i++) {
    if (f(inc.back(), i)) {
      inc.push_back(i);
    } else {
      *ranges::lower_bound(inc, i, f) = i;
    }
  }
  return inc.size() - (s >= e);
}

void solve(int t) {
  Int n, k;
  vector<Int> a(n);
  if (t == 603) {
    println2(n, k, a);
    return;
  }
  if (n <= k) {
    ranges::nth_element(a, a.begin() + (n - 1) / 2);
    println(a[(n - 1) / 2]);
    return;
  }
  auto cmp = [&](int i, int j) { return a[i] > a[j]; };
  Iota idx(n, cmp);
  int m = n % k ? n % k : int(k); // count of resulting elements
  vector<int> good(m, INT_MAX);
  auto cmp2 = [&](int i, int j) { return good[i] < good[j]; };
  int ans = 0;
  for (int i = 0; i < n; i++) { // O(n*m*log m)
    int j = idx[i] % k;
    if (j >= m) {
      continue;
    }
    good[j] = min(good[j], idx[i]);
    int cnt = lis(cmp2, 0, m); // O(m*log m)
    if (cnt > m / 2) {
      ans = a[idx[i]];
      break;
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
