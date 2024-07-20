/**
 * https://codeforces.com/contest/1985/submission/270398534
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void solve(int t) {
  Int h, n;
  vector<Int> a(n), c(n);
  i64 ans = 0;
  if (h > 0) {
    map<i64, vector<int>> turns;
    auto &first = turns[1];
    first.resize(n);
    iota(first.begin(), first.end(), 0);
    while (h > 0) {
      auto next = turns.begin();
      ans = next->first;
      for (auto &i : next->second) {
        turns[ans + c[i]].push_back(i);
        h -= a[i];
        if (h <= 0) {
          break;
        }
      }
      turns.erase(next);
    }
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
