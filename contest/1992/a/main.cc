/**
 * https://codeforces.com/contest/1992/submission/270062675
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

void solve(int t) {
  const int n = 3, m = 5;
  vector<Num<>> a(n);
  sort(a.begin(), a.end());
  a.push_back(INT_MAX);
  for (int i = 0, j = 0, k = 1; i < m; j++) {
    if (a[j % k] < a[k]) {
      a[j % k]++, i++;
    } else {
      k++;
    }
  }
  a.pop_back();
  int ans = 1;
  for (auto &&ai : a) {
    ans *= ai;
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
