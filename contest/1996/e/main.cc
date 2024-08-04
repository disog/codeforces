/**
 * https://codeforces.com/contest/1996/submission/274148616
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

constexpr int _mod = 1000000007;

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
  Mod ans = 0;
  for (auto &idx : idx_by_sum) { // O(n) because there are at most n indices
    int m = idx.size();
    vector<Mod> cnt(m); // one less, because the first index doesn't count
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
