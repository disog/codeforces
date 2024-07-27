/**
 * https://codeforces.com/contest/1996/submission/272927788
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

struct Fen {
  vector<int> nodes;
  Fen(int n) : nodes(n + 1) {}
  void query(int y, const auto &f) {
    for (; y > 0; y -= y & -y) {
      f(y, nodes[y]);
    }
  }
  void update(int x, const auto &f) {
    assert(x > 0);
    for (; x < nodes.size(); x += x & -x) {
      f(x, nodes[x]);
    }
  }
};

constexpr int c = 'z' - 'a' + 1;

void solve(int t) {
  Int n, q;
  Str a, b;
  vector<array<Int, 2>> qs(q);
  vector<Fen> ca(c, Fen(n)), cb(c, Fen(n));
  auto inc = [&](int i, auto &c) { c++; };
  for (int i = 0; i < n; i++) {
    ca[a[i] - 'a'].update(i + 1, inc);
    cb[b[i] - 'a'].update(i + 1, inc);
  }
  for (auto &[l, r] : qs) {
    int ans = 0, sum = 0;
    auto acc = [&](int i, auto &c) { sum += c; };
    auto dec = [&](int i, auto &c) { sum -= c; };
    for (int j = 0; j < c; j++, sum = 0) {
      cb[j].query(r, acc);
      cb[j].query(l - 1, dec);
      sum = -sum;
      ca[j].query(r, acc);
      ca[j].query(l - 1, dec);
      ans += max(0, sum);
    }
    cout << ans << endl;
  }
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
