/**
 * Submission
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

struct Mod {
  int x, m;
  Mod(int a, int b) : x(a % b), m(b) {}
  operator int() { return x; }
  int operator+(int rhs) {
    return rhs < 0 ? operator-(-rhs) : (x + rhs >= m ? x - m : x) + rhs;
  }
  int operator-(int rhs) {
    return rhs < 0 ? operator+(-rhs) : (x - rhs < 0 ? x + m : x) - rhs;
  }
  int operator*(int rhs) { return (x * i64(rhs)) % m; }
  int operator+=(int rhs) { return x = operator+(rhs); }
  int operator-=(int rhs) { return x = operator-(rhs); }
  int operator*=(int rhs) { return x = operator*(rhs); }
};

template <int N = 998244353> struct Mint : Mod {
  Mint(int a) : Mod(a, N) {}
};

void solve(int t) {
  Num n;
  vector<array<Num<>, 2>> a(n);
  Mint ans = 0;

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
