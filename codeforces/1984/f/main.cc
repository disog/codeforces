/**
 * https://codeforces.com/contest/1984/submission/277676909
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using u64 = uint64_t;

#ifdef ONLINE_JUDGE
#define debug
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
using I64 = Num<i64>;

struct Str : string {
  Str() { cin >> *this; }
};

struct Barret {
  u64 mod, div;
  Barret(u64 m) : mod(m), div(-1llu / m) {}
  operator u64() const { return mod; }
  i64 operator()(i64 x) const {
#ifdef __SIZEOF_INT128__
    x -= (x >= 0 ? __uint128_t(x) * div >> 64 : x / i64(mod)) * mod;
#else
    x %= i64(mod);
#endif
    return x < 0 ? x + mod : x < mod ? x : x - mod;
  }
};

template <typename T> struct Mod {
  inline static Barret mod = 998244353;
  static i64 inv(i64 x, i64 m) { // O(log^2 m) / x and m must be coprime
    return x < 0 ? inv(x % m + m, m) : x > 1 ? m - inv(m % x, x) * m / x : 1;
  } // https://codeforces.com/blog/entry/23365
  T x;
  Mod(i64 y = 0) { x = mod(y); }
  operator T() const { return x; }
  Mod operator+(auto y) const { return Mod(x) += y; }
  Mod operator-(auto y) const { return Mod(x) -= y; }
  Mod operator*(auto y) const { return Mod(x) *= y; }
  Mod operator/(auto y) const { return Mod(x) /= y; }
  Mod &operator+=(i64 y) { return x = mod(x + y), *this; }
  Mod &operator-=(i64 y) { return x = mod(x - y), *this; }
  Mod &operator*=(i64 y) { return x = mod(x * y), *this; }
  Mod &operator/=(i64 y) { return *this *= inv(y, mod); }
  Mod pow(auto y) const { // O(log y) / 0^(-inf,0] -> 1
    Mod ans(1), base(y < 0 ? inv(x, mod) : x);
    for (y = abs(y); y; y >>= 1, base *= base) {
      y & 1 ? ans *= base : ans;
    }
    return ans;
  }
};
using Mint = Mod<int>;

void solve(int t) {
  Int n, m;
  Str s;
  s.assign('P' + s + 'S');
  vector<I64> b(1, 0);
  b.resize(n + 1);
  b.push_back(0);
  auto f = [&](i64 sum) {
    array<Mint, 2> dp = {1, 0};
    for (int i = 1; i < n + 2; i++) {
      array<Mint, 2> dp1 = {0, 0};
      i64 x = b[i - 1] + b[i] - sum;
      i64 y = b[i - 1] - b[i];
      i64 value[2][2] = {{y, x}, {x, y}};
      i64 limit[2][2] = {{m, 0}, {2 * m, m}};
      bool check[2] = {s[i] != 'S', s[i] != 'P'};
      for (int j = 0; j < 2; j++) {   // prev
        for (int k = 0; k < 2; k++) { // curr
          if (check[k]) {
            if (abs(value[j][k]) <= limit[j][k]) {
              dp1[k] += dp[j];
            }
          }
        }
      }
      dp = dp1;
      if (!dp[0] && !dp[1]) {
        break;
      }
    }
    return dp[0] += dp[1];
  };
  Mint ans = 0;
  set<i64> sums;
  i64 nm = i64(n) * m;
  for (int i = 1; i < n + 2; i++) {
    auto sum = b[i] + b[i - 1];
    if (abs(sum) <= nm && sums.insert(sum).second) {
      ans += f(sum);
    }
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}