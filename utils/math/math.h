/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Uniform Distribution (using Mersenne Twister engine)
 */
struct Uniform : uniform_int_distribution<int> {
  Uniform(int s, int e) : uniform_int_distribution<int>(s, e) {}
  int operator()() {
    static random_device device;
    static mt19937 engine{device()};
    return uniform_int_distribution<int>::operator()(engine);
  }
};

/**
 * Array hashing function
 */
template <size_t N> struct ArrayHash {
  size_t operator()(const array<int, N> &a) const {
    size_t h = 0;
    for (auto e : a) {
      h ^= hash<int>{}(e) + 0x9e3779b9 + (h << 6) + (h >> 2);
    }
    return h;
  }
};

/**
 * Sum of arithmetic/geometric progressions
 */
auto apsum(auto a, auto b, auto n) { return n * (a + b) / 2; }
auto gpsum(auto a, auto r, auto n) { return a * (1 - pow(r, n)) / (1 - r); }

/**
 * Choices satisfying equality x + y == m, for a1 <= x <= a2 and b1 <= y <= b2
 */
i64 choices_eq(int a1, int a2, int b1, int b2, i64 m) {
  assert(a1 <= a2 && b1 <= b2);
  auto d1 = m - a1, d2 = m - a2;
  return b1 <= d1 && b2 >= d2 ? min<i64>(b2, d1) - max<i64>(b1, d2) + 1 : 0;
}

/**
 * Choices satisfying inequality x + y <= m, for a1 <= x <= a2 and b1 <= y <= b2
 */
i64 choices_lte(int a1, int a2, int b1, int b2, i64 m) {
  assert(a1 <= a2 && b1 <= b2);
  i64 ans = 0;
  for (int i = min<i64>(a2, m - b1); i >= a1; i--) {
    ans += min<i64>(b2, m - i) - b1 + 1;
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
 * Absolute and Reverse modulus (works for negative numbers)
 */
constexpr auto absmod(auto x, auto m) { return (m + x % m) % m; };
constexpr auto revmod(auto x, auto m) { return (m - x % m) % m; };

/**
 * Extended Euclid's algorithm
 */
template <typename T> array<T, 3> exgcd(T m, T n) { // O(log^2 max(m,n))
  T a = 0, b = 1, u = 1, v = 0;
  while (n) {
    T q = m / n;
    m -= q * n, swap(m, n); // (m, n) = (n, m - q * n)
    u -= q * a, swap(u, a); // (u, a) = (a, u - q * a)
    v -= q * b, swap(v, b); // (v, b) = (b, v - q * b)
  }
  return {u, v, m}; // u*m + v*n == gcd(m,n)
}

/**
 * Modular Inverse for non-coprime numbers
 */
template <typename T> array<T, 3> gcdinvmod(T x, T m) { // O(log^2 m)
  auto [u, v, d] = exgcd(x, m);
  return {d, u, m / d}; // u may be negative
};

/**
 * Linear Diophantine equation
 */
template <typename T> array<T, 5> diophantine(T a, T b, T c) {
  auto [s, t, d] = exgcd(a, b);
  if (c % d) {
    return {};
  }
  auto u = a / d, v = b / d;
  auto x = c / d * 1ll * s, y = c / d * 1ll * t, k = x / v;
  return {true, T(x - k * v), T(y + k * u), u, v}; // adjusted for x % v
}

/**
 * Modular Multiplicative Inverse
 */
template <typename T> T invmod(T x, T m) { // O(log^2 m) / x and m are coprime
  return x < 0   ? invmod(x % m + m, m)
         : x > 1 ? m - invmod(m % x, x) * 1ll * m / x
                 : 1;
} // https://codeforces.com/blog/entry/23365

// Utility functions
// minmax

// Bit functions
// rotl: Rotate `x` to the left by `s` bits.
// rotr: Rotate `x` to the right by `s` bits.
// countl_zero: number of contiguous zero bits, starting from the highest bit.
// countl_one: number of contiguous one bits, starting from the highest bit.
// countr_zero: number of contiguous zero bits, starting from the lowest bit.
// countr_one: number of contiguous one bits, starting from the lowest bit.
// popcount: number of bits set in `x`.
// has_single_bit: whether `x` is a power of two.
// bit_ceil: smallest power-of-two not less than `x`.
// bit_floor: largest power-of-two not greater than `x`.
// bit_width: smallest integer greater than the base-2 logarithm of `x`.
