/**
 * https://codeforces.com/contest/1995/submission/272210377
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;
using I64 = Num<i64>;

void solve(int t) {
  Int n;
  I64 m;
  vector<Int> a(n);
  ranges::sort(a);
  i64 ans = 0;
  auto f1 = [&](int last, int i) {
    i64 sum = 0;
    for (int j = i - 1; j >= last; j--) {
      sum += a[j];
      if (sum <= m) {
        ans = max(ans, sum);
      } else {
        sum -= a[--i]; // remove one flower from right
      }
    }
  };
  int last1 = 0, last2 = 0;
  auto f2 = [&](int i) {
    if (a[last1] - a[last2] == 1) {
      f1(last2, i); // take two flowers
    } else {
      f1(last1, i); // take one flower
    }
  };
  for (int i = 0; i < n; i++) {
    if (a[i] != a[last1]) {
      f2(i);
      last2 = last1;
      last1 = i;
    }
  }
  f2(n);
  cout << ans << endl;
}

int main() {
#ifdef LOCAL
  using filesystem::path;
  freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}
