/**
 * https://codeforces.com/contest/1984/submission/270396611
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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
  Zfn(const auto &a, int s = 0) : Zfn(a, s, a.size()) {}
  Zfn(const auto &a, int s, int e) : vector<int>(e - s) {
    auto &z = *this;
    for (int i = 1, j = 1; i + s < e; i++) {
      auto &c = z[i] = max(0, min(j + z[j] - i, z[i - j]));
      for (; i + c < e && a[i + c + s] == a[c + s]; c++, j = i)
        ;
    }
  }
};

void solve(int t) {
  Str s;
  int n = s.size();
  vector<int> p;
  for (int i = 0; i < n; i++) {
    if (s[i] != 'a') {
      p.push_back(i);
    }
  }
  auto m = p.size();
  if (!m) {
    cout << n - 1 << endl;
    return;
  }
  Zfn z(s, p[0]);
  auto f = [&](int j, int len) {
    for (int i = j; i < m; i += j) {
      if (z[p[i] - p[0]] < len) {
        return false;
      }
    }
    return true;
  };
  auto g = [&](int a, int b, int c) {
    i64 ans = 0; // choices of x + y <= c, for x <= a and y <= b
    for (int i = 0; i <= a; i++) {
      ans += max(0, 1 + min(b, c - i));
    }
    return ans;
  };
  i64 ans = 0;
  for (int j = 1; j <= m; j++) {
    if (m % j == 0 && f(j, p[j - 1] - p[0] + 1)) {
      int a = p[0], b = n - p[m - 1] - 1, c = n;
      for (int i = j; i < m; i += j) {
        c = min(c, p[i] - p[i - 1] - 1);
      }
      ans += g(a, b, c);
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
