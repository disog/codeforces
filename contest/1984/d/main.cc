/**
 * Submission
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

struct Int {
  int x;
  Int() { cin >> x; }
  Int(int a) : x(a) {}
  operator int &() { return x; }
};

struct Str : string {
  Str() { cin >> *this; }
};

struct Zfn : vector<int> {
  Zfn(const auto &s) : vector<int>(s.size()) {
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

void solve(int t) {
  // Str s;
  // Zfn z(s);
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
