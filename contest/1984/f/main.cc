/**
 * https://codeforces.com/contest/1984/submission/273048144
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

void println(const auto &...args) { ((cout << args << ' '), ...) << endl; }

constexpr int _mod = 998244353;

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

void solve(int t) {
  Int n, m;
  Str s;
  s.assign('P' + s + 'S');
  vector<I64> b(1, 0);
  b.resize(n + 1);
  b.push_back(0);
  auto f = [&](i64 sum) {
    array<Mod, 2> dp = {1, 0};
    for (int i = 1; i < n + 2; i++) {
      array<Mod, 2> dp1 = {0, 0};
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
  Mod ans = 0;
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
