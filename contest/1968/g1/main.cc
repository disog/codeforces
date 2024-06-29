/**
 * https://codeforces.com/contest/1968/submission/267964997
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

struct Int {
  int x;
  Int() { cin >> x; }
  operator int() { return x; }
};

struct Str : string {
  Str() { cin >> *this; }
};

struct Zfn : vector<int> {
  Zfn(const string &s) : vector<int>(s.size()) {
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
  Int n, k, _;
  Str s;
  Zfn z(s);
  auto f = [&](int x) {
    int ans = 1;
    for (int i = x; i <= n - x; i++) {
      if (z[i] >= x) {
        i += x - 1;
        ans++;
      }
    }
    return ans;
  };
  auto g = [&](int k) {
    int ans = 1;
    for (int end = n; ans <= end;) {
      auto mid = (ans + end) / 2;
      if (f(mid) >= k) {
        ans = mid + 1;
      } else {
        end = mid - 1;
      }
    }
    return ans - 1;
  };
  cout << g(k) << endl;
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
