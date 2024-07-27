/**
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

i64 choices(int a1, int a2, int b1, int b2, i64 m) {
  i64 ans = 0;
  for (int i = a1; i <= a2; i++) {
    ans += max<i64>(0, b1 + min<i64>(b2, m - i));
  }
  return ans;
}

void solve(int t) {
  Int n, x;
  i64 ans = 0;
  i64 cnt1 = choices(1, x - 2, 2, 2 * x - 4, x);
  i64 cnt2 = choices(1, (x - 2) * (x - 2), 2, (x - 2) * (2 * x - 4), n);
  cout << min<i64>(cnt1, cnt2) << endl;
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
