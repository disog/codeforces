/**
 * https://codeforces.com/contest/1968/submission/270392071
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

struct Str : string {
  Str() { cin >> *this; }
};

void solve(int t) {
  Int n, m;
  Str a, b;
  int ans = 0;
  for (int i = 0; ans < n && i < m; i++) {
    if (a[ans] == b[i]) {
      ans++;
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
