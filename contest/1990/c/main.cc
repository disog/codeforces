/**
 * Copyright (c) 2024 Diego Sogari
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
  Int n;
  vector<Int> a(n);
  i64 ans = 0;
  auto f = [&]() {
    map<int, int> cnt;
    for (int i = 0, mx = 0; i < n; i++) {
      ans += a[i];
      if (cnt[a[i]]++ && a[i] > mx) {
        mx = a[i];
      } else {
        a[i] = mx;
      }
    }
  };
  f(), f();
  for (int i = 0; i < n; i++) {
    ans += i64(n - i) * a[i];
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
