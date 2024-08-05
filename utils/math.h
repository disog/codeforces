/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Common constants
 */
constexpr int _mod = 1000000007;
// constexpr int _mod = 998244353;

/**
 * Modular integer
 */
struct Mod {
  int x, m;
  Mod(i64 x = 0, int m = _mod) : x(x % m), m(m) {}
  operator int() const { return x; }
  Mod operator+(int rhs) const { return Mod(x, m) += rhs; }
  Mod operator-(int rhs) const { return Mod(x, m) -= rhs; }
  Mod operator*(int rhs) const { return Mod(x, m) *= rhs; }
  Mod operator/(int rhs) const { return Mod(x, m) /= rhs; }
  Mod &operator+=(int rhs) {
    return rhs < 0 ? operator-=(-rhs) : ((x += rhs) >= m ? x -= m : x, *this);
  }
  Mod &operator-=(int rhs) {
    return rhs < 0 ? operator+=(-rhs) : ((x -= rhs) < 0 ? x += m : x, *this);
  }
  Mod &operator*=(int rhs) { return x = (i64(x) * rhs) % m, *this; }
  Mod &operator/=(int rhs) { return operator*=(Mod(rhs, m).inv()); }
  Mod inv() const { return pow(m - 2); } // inv of zero gives zero
  Mod pow(int rhs) const {
    Mod base(x, m), ans(!!x, m);
    for (; base && rhs; rhs >>= 1, base *= base) {
      if (rhs & 1) {
        ans *= base;
      }
    }
    return ans;
  }
};

/**
 * (Modular) Factorial
 */
struct Fac : vector<Mod> {
  Fac(int m = _mod) : vector<Mod>(1, {1, m}) {}
  Mod operator[](int n) {
    while (size() <= n) {
      push_back(back() * (int)size());
    }
    return vector<Mod>::operator[](n);
  }
};

/**
 * (Modular) Binomial coefficient
 */
struct Bin : Fac {
  vector<Mod> inv;
  Mod operator()(int n, int k) {
    if (k < 0 || k > n) {
      return front() * 0;
    }
    auto ans = (*this)[n];
    if (inv.size() <= n) {
      int s = inv.size();
      inv.resize(n + 1);
      inv[n] = ans.inv();
      for (int i = n; i > s; i--) {
        inv[i - 1] = inv[i] * i;
      }
    }
    return ans * inv[k] * inv[n - k];
  }
};

/**
 * Precomputed integer factors (Divisors)
 */
struct Div : vector<vector<int>> {
  Div(int n) : vector<vector<int>>(n + 1) { // O(n*log n)
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j += i) {
        (*this)[j].push_back(i);
      }
    }
  }
};

/**
 * Uniform Distribution using Mersenne Twister engine
 */
struct Dist : uniform_int_distribution<int> {
  Dist(int s, int e) : uniform_int_distribution<int>(s, e) {}
  int operator()() {
    static random_device device;
    static mt19937 engine{device()};
    return uniform_int_distribution<int>::operator()(engine);
  }
};

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
