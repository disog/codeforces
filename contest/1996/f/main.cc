/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init(__FILE__);
#endif

void println(const auto &...args) { ((cout << args << ' '), ...) << endl; }

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
  vector<Int> a(n), b(n);
  multimap<int, int, greater<int>> vals;
  for (int i = 0; i < n; i++) {
    vals.emplace(a[i], b[i]);
  }
  vals.emplace(0, 0);
  i64 ans = 0;
  for (int i = 0; i < k && vals.size() > 1;) {
    auto it = vals.begin();
    auto [val, sub] = *it;
    auto a = val, b = next(it)->first;
    i64 c = min(k - i - 1, (a - b) / sub);
    ans += a * (c + 1) - sub * c * (c + 1) / 2;
    a -= sub * (c + 1);
    i += c + 1;
    vals.erase(it);
    if (a > 0) {
      vals.emplace(a, sub);
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
