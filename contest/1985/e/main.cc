/**
 * https://codeforces.com/contest/1985/submission/270398364
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
  Int x, y, z;
  I64 k;
  i64 ans = 0;
  for (int a = 1; a <= x; a++) {
    for (int b = 1; b <= y; b++) {
      if (k % (a * b) == 0) {
        auto c = k / (a * b);
        if (c <= z) {
          ans = max(ans, i64(x - a + 1) * (y - b + 1) * (z - c + 1));
        }
      }
    }
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
