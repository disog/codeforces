/**
 * https://codeforces.com/contest/1986/submission/270399101
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

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

void solve(int t) {
  Int n;
  Str s;
  int ans = INT_MAX;
  for (int i = 0; i < n - 1; i++) {
    int sum = (s[i] - '0') * 10 + s[i + 1] - '0';
    for (int j = 0; j < n; j++) {
      if (j == i) {
        j++;
        continue;
      }
      if (s[j] == '0') {
        cout << 0 << endl;
        return;
      }
      if (s[j] != '1') {
        if (sum == 1) {
          sum = 0;
        }
        sum += s[j] - '0';
      }
    }
    ans = min(ans, sum);
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
