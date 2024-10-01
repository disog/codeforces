/**
 * https://codeforces.com/contest/2020/submission/283952705
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

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

template <typename T, auto M>
  requires unsigned_integral<T>
struct Mod {
  using U = conditional<is_same<T, u64>::value, u128, u64>::type;
  static T inv(T x, U m) { return x > 1 ? m - inv(m % x, x) * m / x : 1; }
  static T norm(T x) { return rotl(x, 1) & 1 ? x + M : x < M ? x : x - M; }
  T x;
  Mod() : x(0) {}
  Mod(i64 y) : x(norm(y % i64(M))) {}
  operator T() const { return x; }
  Mod operator+(auto rhs) const { return Mod(*this) += rhs; }
  Mod operator-(auto rhs) const { return Mod(*this) -= rhs; }
  Mod operator*(auto rhs) const { return Mod(*this) *= rhs; }
  Mod operator/(auto rhs) const { return Mod(*this) /= rhs; }
  Mod &operator+=(Mod rhs) { return x = norm(x + rhs.x), *this; }
  Mod &operator-=(Mod rhs) { return x = norm(x - rhs.x), *this; }
  Mod &operator*=(Mod rhs) { return x = U(x) * rhs.x % M, *this; }
  Mod &operator/=(Mod rhs) { return *this *= inv(rhs.x, M); }
  Mod pow(i64 y) const { // O(log y) / 0^(-inf,0] -> 1
    Mod ans(1), base(y < 0 ? inv(x, M) : x);
    for (y = abs(y); y; y >>= 1, base *= base) {
      y & 1 ? ans *= base : ans;
    }
    return ans;
  }
};
using Mint = Mod<u32, 1000000007u>;

constexpr int logmaxa = 10, maxp = 1e4;

void solve(int t) {
  Int n;
  vector<Int> a(n), p(n);
  Mint ans = 0;
  for (int b1 = 0; b1 < logmaxa; b1++) { // O(n*log^2 max(a))
    for (int b2 = 0; b2 < logmaxa; b2++) {
      array<array<Mint, 2>, 2> dp = {};
      dp[0][0] = 1;
      for (int i = 0; i < n; i++) {
        auto a1 = a[i] >> b1 & 1;
        auto a2 = a[i] >> b2 & 1;
        auto prev = dp; // don't use swap here
        dp = {};
        for (int c1 = 0; c1 < 2; c1++) {
          for (int c2 = 0; c2 < 2; c2++) {
            dp[c1][c2] += prev[c1][c2] * (maxp - p[i]);
            dp[c1 ^ a1][c2 ^ a2] += prev[c1][c2] * +p[i];
          }
        }
      }
      ans += dp[1][1] * (1 << (b1 + b2)); // contrib. of pair of bits in f(S)^2
    }
  }
  ans /= Mint(maxp).pow(n);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
