#pragma once

#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;
using Triplet = array<int, 3>;
using MaxHeap = priority_queue<int>;
using MinHeap = priority_queue<int, vector<int>, greater<int>>;

template <int N> struct Mint {
  int x;
  Mint(int a = 0) : x(a) {}
  operator int() { return x; }
  Mint &operator+=(int rhs) {
    if ((x += rhs) >= N) {
      x -= N;
    }
    return *this;
  }
  Mint &operator-=(int rhs) {
    if ((x -= rhs) < 0) {
      x += N;
    }
    return *this;
  }
};

vector<vector<int>> matrix(int n, int m) {
  vector<vector<int>> ans(n);
  for (int i = 0; i < n; i++) {
    auto &row = ans[i];
    row.resize(m);
    for (int j = 0; j < m; j++) {
      cin >> row[j];
    }
  }
  return ans;
}

vector<int> zfunc(const string &s) {
  const int n = s.size();
  vector<int> z(n);
  for (int i = 1, j = 1; i < n; i++) {
    if (i < j + z[j]) {
      z[i] = min(j + z[j] - i, z[i - j]);
    }
    for (; i + z[i] < n && s[i + z[i]] == s[z[i]]; z[i]++, j = i)
      ;
  }
  return z;
}

vector<int> factor(int x) {
  vector<int> ans;
  for (; x && x & 1 == 0; x >>= 1) {
    ans.push_back(2);
  }
  for (int i = 3; x > 1; i += 2) {
    for (int r = x / i; r * i == x; x = r, r /= i) {
      ans.push_back(i);
    }
  }
  return ans;
}

namespace std {
string to_string(const string &s) { return s; }
} // namespace std

// cout << fixed << setprecision(20);
