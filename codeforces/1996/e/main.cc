/**
 * https://codeforces.com/contest/1996/submission/283833173
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using u32 = uint32_t;
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

struct Str : string {
  Str() { cin >> *this; }
};

template <typename T, auto M>
  requires unsigned_integral<T>
struct Mod {
  static T inv(T x, u64 m) { return x > 1 ? m - inv(m % x, x) * m / x : 1; }
  static T norm(T x) { return rotl(x, 1) & 1 ? x + M : x < M ? x : x - M; }
  T x;
  Mod(i64 y = 0) : x(norm(y % i64(M))) {}
  operator T() const { return x; }
  Mod operator+(auto rhs) const { return Mod(*this) += rhs; }
  Mod operator-(auto rhs) const { return Mod(*this) -= rhs; }
  Mod operator*(auto rhs) const { return Mod(*this) *= rhs; }
  Mod operator/(auto rhs) const { return Mod(*this) /= rhs; }
  Mod &operator+=(Mod rhs) { return x = norm(x + rhs.x), *this; }
  Mod &operator-=(Mod rhs) { return x = norm(x - rhs.x), *this; }
  Mod &operator*=(Mod rhs) { return x = u64(x) * rhs.x % M, *this; }
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

void solve(int t) {
  Str s;
  int n = s.size();
  vector<int> sum(n + 1); // will hold values in the range [-n,n]
  for (int i = 0; i < n; i++) {
    sum[i + 1] += sum[i] + 2 * (s[i] - '0') - 1;
  }
  vector<vector<int>> idx_by_sum(2 * n + 1); // will hold 1-based indices
  for (int i = 0; i <= n; i++) {
    idx_by_sum[sum[i] + n].push_back(i);
  }
  Mint ans = 0;
  for (auto &idx : idx_by_sum) { // O(n) because there are at most n indices
    int m = idx.size();
    vector<Mint> cnt(m); // one less, because the first index doesn't count
    for (int i = 0; i < m - 1; i++) {
      cnt[i + 1] += cnt[i] + n - idx[i + 1] + 1;
    }
    for (int i = 0; i < m - 1; i++) {
      ans += (cnt.back() - cnt[i]) * (idx[i] + 1);
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
