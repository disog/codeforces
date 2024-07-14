/**
 * https://codeforces.com/contest/1971/submission/270393758
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

void solve(int t) {
  vector<array<Int, 2>> a(2);
  map<int, int> lines;
  for (int i = 0; i < 2; i++) {
    auto [x, y] = a[i];
    lines[x] = lines[y] = i;
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
