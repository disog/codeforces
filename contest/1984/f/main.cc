/**
 * https://codeforces.com/contest/1984/submission/268425055
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

template <typename T = int> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
};

struct Str : string {
  Str() { cin >> *this; }
};

template <int N = 998244353> struct Mint {
  int x;
  Mint(int a) : x(a % N) {}
  operator int() { return x; }
  int operator+=(int rhs) { return (x += rhs) >= N ? x -= N : x; }
  int operator-=(int rhs) { return (x -= rhs) < 0 ? x += N : x; }
};

void solve(int t) {
  Num n, m;
  Str s;
  s.assign('P' + s + 'S');
  vector<Num<i64>> b(n);
  b.insert(b.begin(), 0);
  b.push_back(0);
  auto f = [&](i64 sum) {
    array<Mint<>, 2> dp = {1, 0};
    for (int i = 1; i < n + 2; i++) {
      array<Mint<>, 2> dp1 = {0, 0};
      i64 x = b[i - 1] + b[i] - sum;
      i64 y = b[i - 1] - b[i];
      bool check[2] = {s[i] != 'S', s[i] != 'P'};
      i64 value[2][2] = {{y, x}, {x, y}};
      i64 limit[2][2] = {{m, 0}, {2 * m, m}};
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
  Mint ans = 0;
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
  Num t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}
