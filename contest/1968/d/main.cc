/**
 * https://codeforces.com/contest/1968/submission/270392198
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

void solve(int t) {
  Int n, k, pb, ps;
  vector<Int> p(n), a(n);
  auto f = [&](int k, int n, int i) {
    i64 mx = 0;
    for (i64 sum = 0; k && n; --k, --n, sum += a[i], i = p[i] - 1) {
      mx = max(mx, sum + i64(k) * a[i]);
    }
    return mx;
  };
  auto fb = f(k, n, pb - 1);
  auto fs = f(k, n, ps - 1);
  auto ans = fb > fs ? "Bodya" : (fb < fs ? "Sasha" : "Draw");
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
