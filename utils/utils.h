/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

/**
 * Common pragmas
 */
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt")

/**
 * Common namespaces
 */
using namespace std;
using namespace placeholders;

/**
 * Common types
 */
using i64 = int64_t;
using f64 = double;
using MaxHeap = priority_queue<int>;
using MinHeap = priority_queue<int, vector<int>, greater<int>>;

/**
 * Input redirection
 */
#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init(__FILE__);
#endif

/**
 * Input number
 */
template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

/**
 * Common input types
 */
using Int = Num<int>;
using Chr = Num<char>;
using I64 = Num<i64>;
using F64 = Num<f64>;

/**
 * Input string
 */
struct Str : string {
  Str() { cin >> *this; }
};

/**
 * Precomputed integer factors (Divisors)
 */
struct Div : vector<vector<int>> {
  Div(int n) : vector<vector<int>>(n + 1) {
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j += i) {
        (*this)[j].push_back(i);
      }
    }
  }
};

/**
 * Choices satisfying inequality x + y <= m, for a1 <= x <= a2 and b1 <= y <= b2
 */
i64 choices(int a1, int a2, int b1, int b2, i64 m) {
  i64 ans = 0;
  for (int i = a1; i <= a2; i++) {
    ans += max<i64>(0, min<i64>(b2, m - i) - b1 + 1);
  }
  return ans;
}

/**
 * Maximum sum satisfying inequality a * x + b * y <= m, for x <= ca and y <= cb
 */
i64 maxsum(int a, int ca, int b, int cb, i64 m) {
  assert(a > 0 && a < b);
  auto ua = min<i64>(ca, m / a);
  auto ub = min<i64>(cb, (m - ua * a) / b);
  auto ra = min<i64>({ua, cb - ub, (m - ua * a - ub * b) / (b - a)});
  return (ua - ra) * a + (ub + ra) * b;
}

/**
 * Most/least significant set bits
 */
constexpr int lssb(unsigned x) { return countr_zero(x); }
constexpr int mssb(unsigned x) { return 31 - countl_zero(x); }

/**
 * Printing utilities
 */
template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
template <typename T, size_t N>
ostream &operator<<(ostream &os, const span<T, N> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

/**
 * Test case function
 */
void solve(int t) {
  Int n;
  println(0);
}

/**
 * Main function
 */
int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
