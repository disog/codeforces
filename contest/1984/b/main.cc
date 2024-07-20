/**
 * https://codeforces.com/contest/1984/submission/270395949
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

struct Str : string {
  Str() { cin >> *this; }
};

void solve(int t) {
  Str x;
  if (x.front() != '1' || x.back() == '9' ||
      x.rfind('0', x.size() - 2) != string::npos) {
    cout << "NO" << endl;
    return;
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
