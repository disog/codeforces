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
  Zfn(const auto &s) : Zfn(s, s.size()) {}
  Zfn(const auto &s, int n) : vector<int>(n) {
    auto &z = *this;
    for (int i = 1, j = 1; i < n; i++) {
      auto &c = z[i] = max(0, min(j + z[j] - i, z[i - j]));
      for (; i + c < n && s[i + c] == s[c]; c++, j = i)
        ;
    }
  }
};

void solve(int t) {
  Str s;
  auto n = s.size();
  vector<int> p;
  string s2;
  for (int i = 0; i < n; i++) {
    if (s[i] != 'a') {
      p.push_back(i);
      s2 += s[i];
    }
  }
  auto m = p.size();
  if (!m) {
    cout << n - 1 << endl;
    return;
  }
  Zfn z(s2);
  int ans = 0;
  for (int j = 1; j <= m; j++) {
    if (m % j) {
      continue;
    }
    int a = n, b = n, l = p[j - 1] - p[0] + 1;
    for (int i = j; i < m; i += j) {
      if (z[i] < j) {
        a = b = -1;
        break;
      }
      int r = p[i + j - 1] - p[i] + 1;
      if (l != r) {
        a = b = -1;
        break;
      }
      l = r;
    }
    ans += max(0, 1 + a + b);
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
