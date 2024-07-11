/**
 * https://codeforces.com/contest/1992/submission/270067229
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T = int> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
};

struct Str : string {
  Str() { cin >> *this; }
};

void solve(int t) {
  Num n, m, k;
  Str a;
  for (int i = -1, e = m - 1; e < n;) {
    int logi = a.find('L', i + 1);
    if (logi != string::npos && logi <= e) {
      i = logi;
      e = i + m;
    } else if (a[e] == 'W' && k) {
      k--;
      i = e++;
    } else {
      cout << "NO" << endl;
      return;
    }
  }
  cout << "YES" << endl;
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
