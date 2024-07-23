/**
 * https://codeforces.com/contest/1995/submission/272133688
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

const greater<int> gt1;

void solve(int t) {
  Int n;
  I64 m;
  vector<Int> a(n);
  ranges::sort(a);
  vector<i64> b(n + 1);
  i64 ans = 0;
  auto f = [&](int last, int i) {
    for (int j = i; j > last; j--) {
      if (b[i] - b[j - 1] <= m) {
        ans = max(ans, b[i] - b[j - 1]);
      } else {
        i--; // remove one flower from right
      }
    }
  };
  int last1 = 0, last2 = 0;
  for (int i = 0; i < n; i++) {
    b[i + 1] += a[i] + b[i];
    if (a[i] != a[last1]) {
      if (a[last1] - a[last2] == 1) {
        f(last2, i); // take two flowers
      } else {
        f(last1, i); // take one flower
      }
      last2 = last1;
      last1 = i;
    }
  }
  if (a[last1] - a[last2] == 1) {
    f(last2, n); // take two flowers
  } else {
    f(last1, n); // take one flower
  }
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
