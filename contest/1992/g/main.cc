/**
 * https://codeforces.com/contest/1992/submission/270335035
 *
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
};
using Int = Num<int>;

struct Mod {
  int x, m;
  Mod(i64 a, int b) : x(a % b), m(b) {}
  operator int() { return x; }
  Mod &operator+=(int rhs) { return x = operator+(rhs), *this; }
  Mod &operator-=(int rhs) { return x = operator-(rhs), *this; }
  Mod &operator*=(int rhs) { return x = operator*(rhs), *this; }
  Mod operator+(int rhs) {
    return rhs < 0 ? operator-(-rhs) : Mod((x + rhs >= m ? x - m : x) + rhs, m);
  }
  Mod operator-(int rhs) {
    return rhs < 0 ? operator+(-rhs) : Mod((x - rhs < 0 ? x + m : x) - rhs, m);
  }
  Mod operator*(int rhs) { return Mod(i64(x) * rhs, m); }
  Mod pow(int y) {
    Mod b(x, m), ans(!!x, m);
    for (; b && y; y >>= 1, b *= b) {
      ans *= (y & 1) ? b : 1;
    }
    return ans;
  }
  Mod inv() { return pow(m - 2); }
};

struct Mint : Mod {
  Mint(int a) : Mod(a, 1000000007) {}
};

struct Comb {
  vector<Mod> num, den;
  Comb(int n, int m) : num(n, {1, m}), den(n, {1, m}) {
    for (int i = 1; i < n; i++) {
      num[i] = num[i - 1] * i;
    }
    den[n - 1] = num[n - 1].inv();
    for (int i = n - 1; i > 0; i--) {
      den[i - 1] = den[i] * i;
    }
  }
  Mod operator()(int n, int k) {
    return n < 0 || n < k ? Mod(0, num[0].m) : num[n] * (den[k] * den[n - k]);
  }
};

void solve(int t) {
  Int n;
  Comb comb(n + 1, 1000000007);
  Mint ans = 2 * (n + 1); // empty and n-ary sets
  for (int i = 1; 2 * i < n; i++) {
    for (int j = 0; j <= i; j++) {
      int m = j + i + 1; // result of mex
      ans += comb(m - 1, j) * comb(n - m, i - j) * m;
    }
  }
  for (int i = (n + 1) / 2; i < n; i++) {
    ans += comb(n, i) * (2 * i + 1);
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
