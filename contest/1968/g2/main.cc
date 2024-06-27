/**
 * https://codeforces.com/contest/1968/submission/267605353
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

vector<int> zfunc(const string &s) {
  const int n = s.size();
  vector<int> z(n);
  for (int i = 1, j = 1; i < n; i++) {
    if (i < j + z[j]) {
      z[i] = min(j + z[j] - i, z[i - j]);
    }
    for (; i + z[i] < n && s[i + z[i]] == s[z[i]]; z[i]++, j = i)
      ;
  }
  return z;
}

void solve(int t) {
  int n, l, r;
  string s;
  cin >> n >> l >> r >> s;
  auto z = zfunc(s);
  auto f1 = [&](int x) {
    int ans = 1;
    for (int i = x; i <= n - x; i++) {
      if (z[i] >= x) {
        i += x - 1;
        ans++;
      }
    }
    return ans;
  };
  auto f2 = [&](int k) {
    int ans = 1;
    for (int end = n; ans <= end;) {
      auto mid = (ans + end) / 2;
      if (f1(mid) >= k) {
        ans = mid + 1;
      } else {
        end = mid - 1;
      }
    }
    return ans - 1;
  };
  int m = sqrt(n);
  vector<int> lcp(n + 1);
  for (int x = 1; x <= m; x++) {
    lcp[f1(x)] = x;
  }
  for (int k = 1; k <= m; k++) {
    lcp[k] = f2(k);
  }
  for (int i = n - 1; i > 0; i--) {
    lcp[i] = max(lcp[i], lcp[i + 1]);
  }
  for (int k = l; k <= r; k++) {
    cout << lcp[k] << ' ';
  }
  cout << endl;
}

int main() {
#ifdef LOCAL
  freopen(path(__FILE__).replace_filename("input.txt").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}