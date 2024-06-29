/**
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

template <typename T> struct Zfn : vector<int> {
  Zfn(const T &s) : vector<int>(s.size()) {
    auto n = s.size();
    for (int i = 1, j = 1; i < n; i++) {
      auto &c = (*this)[i], r = j + (*this)[j];
      if (i < r) {
        c = min(r - i, (*this)[i - j]);
      }
      while (i + c < n && s[i + c] == s[c]) {
        c++, j = i;
      }
    }
  }
};

void solve(int t) {}

int main() {
#ifdef LOCAL
  freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}