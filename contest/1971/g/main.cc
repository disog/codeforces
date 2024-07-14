/**
 * https://codeforces.com/contest/1971/submission/270394238
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using MinHeap = priority_queue<int, vector<int>, greater<int>>;

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
