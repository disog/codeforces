/**
 * https://codeforces.com/contest/1984/submission/273048222
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init(__FILE__);
#endif

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

constexpr int _mod = 1000000007;

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

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

pair<int, int> invshift(auto &a, int sa = 0, int sp = 1) {
  int inv = 0, shift = a[sa] - sp, n = a.size();
  for (int i = sa, sum = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (a[i] > a[j]) {
        inv++;
      }
    }
    if (shift >= 0) {
      auto d = a[i] - sp - (i - sa);
      if (shift != (n - sa + d) % (n - sa)) {
        shift = -1;
      }
    }
  }
  return {inv, shift};
}

void solve(int t) {
  Int n;
  vector<Int> a(n);
  vector<array<int, 2>> ops;
  auto [inv, shift] = invshift(a);
  int ans = n;
  if (shift > 0) {
    for (ans--; shift--;) {
      ops.push_back({1, 2});
    }
  } else if (shift < 0) {
    ans -= 2;
    if (n % 2 == 0) {
      ans -= inv % 2;
      int m = n - ans;
      auto it = find(a.begin(), a.end(), int(n));
      int i = it - a.begin() + 1, k = (n - i) % m;
      if (k > 0) {
        int j = max(0, i - ans);
        ops.push_back({j + 1, j + 1 + k});
        auto it1 = a.begin() + j;
        ranges::rotate(it1, it1 + ans, it1 + ans + k);
        it += k;
      }
      for (int j = 0; j < (n - i) / m; j++) {
        ops.push_back({1, m + 1});
      }
      ranges::rotate(a.begin(), it + 1, a.end());
      n -= inv % 2;
    }
    const array<int, 2> fwd1{2, 1}, bwd1{1, 2}, fwd2{3, 1}, bwd2{1, 3};
    Mod c(n - 1, n);
    auto findpos = [&](int i, int d) {
      int k = 0;
      for (; a[c - (k - d)] != i && a[c + (k + d)] != i && k < n; k += 2)
        ;
      return a[c - (k - d)] == i ? make_pair(-k, bwd2) : make_pair(k, fwd2);
    };
    auto f = [&](int i, bool move) {
      auto [dist, op] = findpos(i, 0);
      auto fix = abs(dist) == n;
      if (fix) {
        tie(dist, op) = findpos(i, -1);
      }
      c += dist;
      for (int j = abs(dist); j > 0; j -= 2) {
        ops.push_back(op);
      }
      if (move) {
        if (fix) {
          for (; a[c] != i + 1; c += 1) {
            swap(a[c], a[c - 1]);
            ops.push_back(bwd1);
            ops.push_back(fwd2);
          }
        } else {
          for (; a[c + 1] != i + 1; c += 1) {
            swap(a[c + 1], a[c]);
            ops.push_back(fwd1);
          }
        }
      }
    };
    f(n, false);
    for (int i = n - 1; i > 1; i--) {
      for (int j = 1; a[c - j] == i && i > 1; j++, i--)
        ;
      if (i > 1) {
        f(i, true);
      }
    }
    f(n, false);
  }
  println(ans);
  println(ops.size());
  println(ops);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
