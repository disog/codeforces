/**
 * https://codeforces.com/contest/1971/submission/270393853
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
  Str s;
  int ans = 1, c0 = 0;
  for (int i = 1; i < s.size(); i++) {
    if (s[i] != s[i - 1]) {
      ans++;
      if (s[i] == '1') {
        c0 = 1;
      }
    }
  }
  cout << ans - c0 << endl;
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
