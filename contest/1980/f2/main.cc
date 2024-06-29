/**
 * https://codeforces.com/contest/1980/submission/267982003
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

struct Int {
  int x;
  Int() { cin >> x; }
  operator int() { return x; }
};

void solve(int t) {
  Int n, m, k;
  map<int, map<int, int>> frows;
  for (int i = 0; i < k; i++) { // O(k*log k)
    Int r, c;
    auto &rows = frows[c];
    rows[r] = i;
    if (rows.size() > 2) {
      rows.erase(rows.begin());
    }
  }
  vector<i64> ans(k);
  i64 a = 0;
  int pra = 0, prb = 0, pca = 1, pcb = 1, pi = 0;
  auto f = [&](int c) { a += i64(n - prb) * (c - pcb); };
  auto g = [&](int c) { ans[pi] += i64(prb - pra) * (c - max(pca, pcb)); };
  for (auto &[c, map] : frows) { // O(k)
    auto [rb, i] = *map.rbegin();
    if (rb > prb) {
      f(c), g(c);
      auto ra = map.size() > 1 ? map.begin()->first : 0;
      pra = ra > prb ? ra : prb;
      pca = ra > prb ? c : pcb;
      prb = rb, pcb = c, pi = i;
    } else if (rb > pra) {
      g(c);
      pra = rb, pca = c;
    }
  }
  f(m + 1), g(m + 1);
  cout << a << endl;
  for (auto &&ai : ans) {
    cout << ai << ' ';
  }
  cout << endl;
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
