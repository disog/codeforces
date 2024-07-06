/**
 * https://codeforces.com/contest/1986/submission/269091599
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

struct Fac : vector<vector<int>> {
  Fac(int n) : vector<vector<int>>(n + 1) {
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j += i) {
        (*this)[j].push_back(i);
      }
    }
  }
};

void solve(int t) {
  Num n;
  Vec a(n, 1);
  vector<vector<int>> num(n + 1), den(n + 1);
  int amx = 0, bmx = 0;
  for (int i = 1; i <= n; i++) {
    auto g = gcd<int>(a[i], i);
    auto x = a[i] / g, y = i / g;
    num[x].push_back(y);
    den[y].push_back(x);
    amx = max(amx, x);
    bmx = max(bmx, y);
  }
  vector<int> c(max(amx, bmx) + 1);
  auto f = [&](int bi, int d) {
    for (int aj = bi; aj <= amx; aj += bi) {
      for (auto &bj : num[aj]) {
        c[bj] += d;
      }
    }
  };
  Fac fac(amx);
  i64 ans = -den[1].size();
  for (int bi = 1; bi <= n; bi++) {
    if (den[bi].size()) {
      f(bi, 1);
      for (auto &ai : den[bi]) {
        for (auto &bj : fac[ai]) {
          ans += c[bj];
        }
      }
      f(bi, -1);
    }
  }
  cout << ans / 2 << endl;
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
