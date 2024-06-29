/**
 * Submission
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using f64 = double;
using MaxHeap = priority_queue<int>;
using MinHeap = priority_queue<int, vector<int>, greater<int>>;

struct Int {
  int x;
  Int() { cin >> x; }
  operator int() { return x; }
};

struct Str : string {
  Str() { cin >> *this; }
};

template <int N> struct Mint {
  int x;
  Mint(int a = 0) : x(a) {}
  operator int() { return x; }
  int operator+=(int rhs) { return x += rhs >= N ? x -= N : x; }
  int operator-=(int rhs) { return x -= rhs < 0 ? x += N : x; }
};

struct Graph : vector<vector<int>> {
  Graph(int n, int m) : vector<vector<int>>(n) {
    for (int i = 0; i < m; i++) {
      Int u, v;
      (*this)[u].push_back(v);
      (*this)[v].push_back(u);
    }
  }
};

struct DGraph : vector<vector<int>> {
  DGraph(int n, int m) : vector<vector<int>>(n) {
    for (int i = 0; i < m; i++) {
      Int u, v;
      (*this)[u].push_back(v);
    }
  }
};

struct WGraph : vector<vector<pair<int, int>>> {
  WGraph(int n, int m) : vector<vector<pair<int, int>>>(n) {
    for (int i = 0; i < m; i++) {
      Int u, v, w;
      (*this)[u].emplace_back(v, w);
      (*this)[v].emplace_back(u, w);
    }
  }
};

struct WDGraph : vector<vector<pair<int, int>>> {
  WDGraph(int n, int m) : vector<vector<pair<int, int>>>(n) {
    for (int i = 0; i < m; i++) {
      Int u, v, w;
      (*this)[u].emplace_back(v, w);
    }
  }
};

struct Zfn : vector<int> {
  Zfn(const string &s) : vector<int>(s.size()) {
    auto n = s.size();
    for (int i = 1, j = 1; i < n; i++) {
      auto &c = (*this)[i], r = j + (*this)[j];
      if (i < r) {
        c = min(r - i, (*this)[i - j]);
      }
      while (i + c < n && s[i + c] == s[c]) {
        c++, j = i;
      }
    }
  }
};

struct Fact : vector<int> {
  Fact(i64 x) {
    for (; x && x & 1 == 0; x >>= 1) {
      push_back(2);
    }
    for (int i = 3; x > 1; i += 2) {
      for (int r = x / i; r * i == x; x = r, r /= i) {
        push_back(i);
      }
    }
  }
};

void solve(int t) {}

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
