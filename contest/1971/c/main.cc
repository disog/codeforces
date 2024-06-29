/**
 * https://codeforces.com/contest/1971/submission/267934812
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

void solve(int t) {
  int n = 2;
  map<int, int> lines;
  for (int i = 1, a, b; i <= n; i++) {
    cin >> a >> b;
    lines[a] = lines[b] = i;
  }
  int prev = lines.rbegin()->second;
  for (auto &&[_, line] : lines) {
    if (line == prev) {
      cout << "NO" << endl;
      return;
    }
    prev = line;
  }
  cout << "YES" << endl;
}

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