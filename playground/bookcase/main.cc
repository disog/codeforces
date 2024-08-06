/**
 * Bookcase
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

int len1(auto &&b, int n, int k) {
  vector<int> s(k, -1), c(k);
  auto lte = [&](int i, int j) {
    return b[i][0] <= b[j][0] && b[i][1] <= b[j][1];
  };
  int ans = n;
  auto f = [&](auto &self, int i) -> void {
    if (i == n) {
      ans = min(ans, *ranges::max_element(c));
      return;
    }
    for (int j = 0; j < k; j++) {
      if (s[j] < 0 || lte(s[j], i)) {
        auto saved = s[j];
        s[j] = i, c[j]++;
        self(self, i + 1);
        s[j] = saved, c[j]--; // backtrack
      }
    }
  };
  f(f, 0);
  return ans;
}

int len2(auto &&b, int n, int k) { return 0; }

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
  Int n;
  vector<array<Int, 2>> b(n);
  // int n = 10;
  // vector<array<int, 2>> b(n);
  // for (auto &&bi : b) {
  //   bi[0] = rand() % n + 1;
  //   bi[1] = rand() % n + 1;
  // }
  ranges::sort(b); // O(n*log n)
  auto cmp = [&](int i, int j) { return b[i][1] > b[j][1]; };
  int k = lis(cmp, 0, n); // O(n*log n)
  int l1 = len1(b, n, k);
  int l2 = len2(b, n, k);
  // assert(l1 == l2);
  println(k, l1, l2);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
