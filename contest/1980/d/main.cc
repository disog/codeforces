/**
 * https://codeforces.com/contest/1980/submission/270394776
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void solve(int t) {
  Int n;
  vector<Int> a(n);
  auto f = [&](int k) {
    for (int i = !k, prev = 1; i < n - 1; i++) {
      int a0 = a[i], a1 = a[(i + 1 == k ? ++i : i) + 1];
      auto cur = gcd(a0, a1);
      if (cur < prev) {
        return i;
      }
      prev = cur;
    };
    return 0;
  };
  auto j = f(n);
  auto ans = !j || j == n - 2 || !f(j - 1) || !f(j) || !f(j + 1) ? "YES" : "NO";
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
