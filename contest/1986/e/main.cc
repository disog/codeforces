/**
 * https://codeforces.com/contest/1986/submission/273049366
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init();
#endif

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void solve(int t) {
  Int n, k;
  vector<Int> a(n);
  map<int, vector<int>> mods;
  for (auto &&ai : a) {
    mods[ai % k].push_back(ai);
  }
  int ans = 0, odd = 0;
  for (auto &[_, b] : mods) {
    ranges::sort(b);
    if (b.size() % 2) {
      if (odd++) {
        ans = -1;
        break;
      }
      vector<vector<int>> sums = {{0}, {0}};
      for (int i = 0; i < b.size() - 1; i++) {
        sums[i % 2].push_back(sums[i % 2].back() + (b[i + 1] - b[i]) / k);
      }
      int mn = INT_MAX;
      for (int i = 0, j = 0; i < b.size(); i += 2, j++) {
        mn = min(mn, sums[0][j] + sums[1].back() - sums[1][j]);
      }
      ans += mn;
    } else {
      for (int i = 0; i < b.size(); i += 2) {
        ans += (b[i + 1] - b[i]) / k;
      }
    }
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
