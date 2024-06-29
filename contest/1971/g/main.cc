/**
 * https://codeforces.com/contest/1971/submission/267935175
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;
using MinHeap = priority_queue<int, vector<int>, greater<int>>;

template <typename T = int> struct Vec : vector<T> {
  Vec(int n, int s = 0) : vector<int>(n + s) {
    for (int i = s; i < n + s; i++) {
      cin >> (*this)[i];
    }
  }
};

void solve(int t) {
  int n;
  cin >> n;
  Vec a(n);
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
  freopen(path(__FILE__).replace_filename("input.txt").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}