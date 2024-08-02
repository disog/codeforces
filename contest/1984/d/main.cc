/**
 * https://codeforces.com/contest/1984/submission/274024711
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

struct Zfn : vector<int> {
  Zfn(auto &&a, int s = 0) : Zfn(a, s, a.size()) {}
  Zfn(auto &&a, int s, int e) : vector<int>(e - s) {
    auto &z = *this;
    for (int i = 1, j = 1; i + s < e; i++) {
      auto &c = z[i] = max(0, min(j + z[j] - i, z[i - j]));
      for (; i + c < e && a[i + c + s] == a[c + s]; c++, j = i)
        ;
    }
  }
};

i64 choices_lte(int a1, int a2, int b1, int b2, i64 m) {
  assert(a1 <= a2 && b1 <= b2);
  i64 ans = 0;
  for (int i = min<i64>(a2, m - b1); i >= a1; i--) {
    ans += min<i64>(b2, m - i) - b1 + 1;
  }
  return ans;
}

void solve(int t) {
  Str s;
  int n = s.size();
  vector<int> pos;
  for (int i = 0; i < n; i++) {
    if (s[i] != 'a') {
      pos.push_back(i);
    }
  }
  auto m = pos.size();
  if (!m) {
    println(n - 1);
    return;
  }
  Zfn z(s, pos[0]);
  auto f = [&](int j, int len) {
    for (int i = j; i < m; i += j) {
      if (z[pos[i] - pos[0]] < len) {
        return false;
      }
    }
    return true;
  };
  i64 ans = 0;
  for (int j = 1; j <= m; j++) {
    if (m % j == 0 && f(j, pos[j - 1] - pos[0] + 1)) {
      int a = pos[0], b = n - pos[m - 1] - 1, c = n;
      for (int i = j; i < m; i += j) {
        c = min(c, pos[i] - pos[i - 1] - 1);
      }
      ans += choices_lte(0, a, 0, b, c);
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
