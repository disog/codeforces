/**
 * https://codeforces.com/contest/1992/submission/270399680
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
  if (n == 1) {
    cout << 9999 << endl;
    for (int i = 1; i < 1e4; i++) {
      cout << i + 1 << ' ' << i << endl;
    }
    return;
  }
  auto s = to_string(n);
  int l = s.size();
  while (s.size() < 6) {
    s += s;
  }
  vector<array<int, 2>> ans;
  for (int d = 1; d <= 6; d++) {
    auto x = stoi(s.substr(0, d));
    if ((x - d) % (n - l) == 0) {
      auto a = (x - d) / (n - l);
      if (a >= 1 && a <= 1e4) {
        auto b = l * a - d;
        if (b >= 1 && b <= 1e4) {
          assert(n * a - b == x);
          ans.push_back({a, b});
        }
      }
    }
  }
  cout << ans.size() << endl;
  for (auto &&[a, b] : ans) {
    cout << a << ' ' << b << endl;
  }
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
