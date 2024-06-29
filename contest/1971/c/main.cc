/**
 * https://codeforces.com/contest/1971/submission/267966555
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

void solve(int t) {
  map<int, int> lines;
  for (int i = 1; i <= 2; i++) {
    Int a, b;
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
  using filesystem::path;
  freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}
