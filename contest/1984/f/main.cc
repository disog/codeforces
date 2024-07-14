/**
 * https://codeforces.com/contest/1984/submission/270397385
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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
  Mod &operator+=(int rhs) { return x = operator+(rhs), *this; }
  Mod &operator-=(int rhs) { return x = operator-(rhs), *this; }
  Mod &operator*=(int rhs) { return x = operator*(rhs), *this; }
  Mod operator+(int rhs) const {
    return rhs < 0 ? operator-(-rhs) : Mod((x + rhs >= m ? x - m : x) + rhs, m);
  }
  Mod operator-(int rhs) const {
    return rhs < 0 ? operator+(-rhs) : Mod((x - rhs < 0 ? x + m : x) - rhs, m);
  }
  Mod operator*(int rhs) const { return Mod(i64(x) * rhs, m); }
  Mod pow(int y) const {
    Mod b(x, m), ans(!!x, m);
    for (; b && y; y >>= 1, b *= b) {
      ans *= (y & 1) ? b.x : 1;
    }
    return ans;
  }
  Mod inv() const { return pow(m - 2); }
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
  auto nm = i64(n) * m;
  for (int i = 1; i < n + 2; i++) {
    auto sum = b[i] + b[i - 1];
    if (abs(sum) <= nm && sums.insert(sum).second) {
      ans += f(sum);
    }
  }
  cout << ans << endl;
}

int main() {
#ifdef LOCAL
  using filesystem::path;
  freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}
