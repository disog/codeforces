/**
 * https://codeforces.com/contest/1971/submission/267970514
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using MinHeap = priority_queue<int, vector<int>, greater<int>>;

struct Int {
  int x;
  Int() { cin >> x; }
  operator int() { return x; }
};

void solve(int t) {
  Int n;
  vector<Int> a(n);
  map<int, MinHeap> groups;
  for (auto &ai : a) {
    groups[ai >> 2].push(ai);
  }
  for (auto &ai : a) {
    auto &heap = groups[ai >> 2];
    cout << heap.top() << ' ';
    heap.pop();
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
