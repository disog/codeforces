/**
 * https://codeforces.com/contest/1992/submission/270399555
 *
 * (c) 2024 Diego Sogari
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
  int n = 3, m = 5;
  vector<Int> a(n);
  sort(a.begin(), a.end());
  a.push_back(INT_MAX);
  for (int i = 0, k = 1; m > 0; i++) {
    if (a[i % k] < a[k]) {
      a[i % k]++, m--;
    } else {
      k++;
    }
  }
  a.pop_back();
  int ans = 1;
  for (auto &&ai : a) {
    ans *= ai;
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
