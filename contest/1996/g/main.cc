/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
// #define debug
#else
#include "debug.h"
init();
#endif

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void solve(int t) {
  Int n, m;
  vector<array<Int, 2>> edges(m);
  auto f = [&](auto &self, int i, int l, int r) -> int { // O(m)
    if (i == m) {
      return 0;
    }
    int c1, c2;
    auto [a, b] = edges[i];
    if (a >= l && a <= r && b >= l && b <= r) {
      c1 = (a - l) + (r - b) + self(self, i + 1, a, b);
      c2 = b - a + self(self, i + 1, l, a) + self(self, i + 1, b, r);
    } else if (a >= l && a <= r) {
      c1 = r - a + self(self, i + 1, l, a);
      c2 = a - l + self(self, i + 1, a, r);
    } else if (b >= l && b <= r) {
      c1 = r - b + self(self, i + 1, l, b);
      c2 = b - l + self(self, i + 1, b, r);
    } else {
      c1 = c2 = self(self, i + 1, l, r);
    }
    return min(c1, c2);
  };
  int ans = f(f, 0, 1, n + 1);
  cout << ans << endl;
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
