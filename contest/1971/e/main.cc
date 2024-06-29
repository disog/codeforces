/**
 * https://codeforces.com/contest/1971/submission/267971688
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

struct Int {
  int x;
  Int() { cin >> x; }
  operator int() { return x; }
};

void solve(int t) {
  Int n, k, q;
  vector<Int> a(k), b(k);
  less<int> cmp;
  auto f = [&](int d) -> int {
    int j = ranges::upper_bound(a, d, cmp) - a.begin();
    if (j == a.size()) {
      return b.back();
    }
    auto a0 = j ? a[j - 1] : 0, b0 = j ? b[j - 1] : 0;
    return b0 + i64(d - a0) * (b[j] - b0) / (a[j] - a0);
  };
  for (int i = 0; i < q; ++i) {
    Int d;
    cout << f(d) << ' ';
  }
  cout << endl;
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
