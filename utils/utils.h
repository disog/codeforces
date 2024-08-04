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

/**
 * Min/Max heap
 */
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T>
using MinHeap = priority_queue<T, vector<int>, greater<int>>;

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
 * Most/least significant set bits/next power of 2
 */
constexpr int lssb(unsigned x) { return countr_zero(x); }
constexpr int mssb(unsigned x) { return 31 - countl_zero(x); }
constexpr int nxp2(unsigned x) { return 1 << (1 + mssb(x - 1)); }

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
