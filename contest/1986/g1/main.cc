/**
 * https://codeforces.com/contest/1986/submission/268990501
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

template <typename T = int> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
};

template <typename T = int> struct Vec : vector<Num<T>> {
  Vec(int n, int s = 0) : vector<Num<T>>(s, 0) { this->resize(n + s); }
};

void solve(int t) {
  Num n;
  Vec a(n, 1);
  map<int, map<int, int>> num, den;
  int mx = 0;
  for (int i = 1; i <= n; i++) {
    auto g = gcd<int>(a[i], i);
    auto x = a[i] / g, y = i / g;
    num[x][y]++, den[y][x]++;
    mx = max(mx, x);
  }
  i64 ans = 0;
  for (auto &[y1, n1] : den) {
    for (auto &[x1, c1] : n1) {
      for (int x2 = y1, k = 1; x2 <= mx; x2 += y1, k++) {
        if (x1 == x2) {
          ans += i64(c1) * (c1 - 1) / 2;
          continue;
        }
        auto it = num.find(x2);
        if (it != num.end()) {
          for (auto &[y2, c2] : it->second) {
            if ((i64(x1) * k) % y2 == 0) {
              ans += i64(c1) * c2;
            }
          }
        }
      }
      num[x1].erase(y1);
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
  Num t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}
