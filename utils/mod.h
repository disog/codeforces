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
