/**
 * https://codeforces.com/contest/2001/submission/283953108
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
#define debug(...)
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

struct Barrett {
  static inline u32 den;
  static inline u64 mu;
  operator u32() const { return den; }
  static void set(u32 d) { den = d, mu = u64(-1) / d; }
  static u64 div(u64 x) { return u128(x) * mu >> 64; }
  static u32 mod(u64 x) { return x -= div(x) * den, x < den ? x : x - den; }
  friend u64 operator/(u64 x, const Barrett &rhs) { return rhs.div(x); }
  friend u32 operator%(u64 x, const Barrett &rhs) { return rhs.mod(x); }
};

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
using Mint = Mod<u32, Barrett{}>;

void solve(int t) {
  Int n, k, p;
  Barrett::set(p);
  vector<Mint> gt(k + 1, 1), lt(k + 1, 1);
  gt[0] = 0;
  for (int i = 1; i < n; i++) {         // O(n*k^2)
    for (int j = k; j > 0; j--) {       // work backwards to reuse the dp vector
      for (int x = 1; x < j - x; x++) { // compute the deterministic choices
        gt[j] += lt[x] * gt[j - x];     // path of the pop operation
        lt[j] += lt[x] * lt[j - x];     // the rest of the tree
      }
      gt[j] *= 2; // adjustment due to the tree symmetry
      lt[j] *= 2;
      if (j % 2 == 0) { // compute the non-deterministic choices
        lt[j] += lt[j / 2] * lt[j / 2];
      }
    }
    for (int j = 1; j <= k; j++) { // accumulate to get the actual values
      gt[j] += gt[j - 1];
      lt[j] += lt[j - 1];
    }
  }
  println(gt[k]);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
