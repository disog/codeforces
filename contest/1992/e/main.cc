/**
 * https://codeforces.com/contest/1992/submission/273051391
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init(__FILE__);
#endif

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << endl; }), os;
}
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
  Int n;
  if (n == 1) {
    println(9999);
    for (int i = 1; i < 1e4; i++) {
      println(i + 1, i);
    }
    return;
  }
  auto s = to_string(n);
  int l = s.size();
  while (s.size() < 6) {
    s += s;
  }
  vector<array<int, 2>> ans;
  for (int d = 1; d <= 6; d++) {
    auto x = stoi(s.substr(0, d));
    if ((x - d) % (n - l) == 0) {
      auto a = (x - d) / (n - l);
      if (a >= 1 && a <= 1e4) {
        auto b = l * a - d;
        if (b >= 1 && b <= 1e4) {
          assert(n * a - b == x);
          ans.push_back({a, b});
        }
      }
    }
  }
  println(ans.size());
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
