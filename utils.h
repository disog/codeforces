#pragma once

#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;
using Triplet = array<int, 3>;
using MaxHeap = priority_queue<int>;
using MinHeap = priority_queue<int, vector<int>, greater<int>>;

template <typename T = int> struct Vec : vector<T> {
  Vec(int n, int s = 0) : vector<int>(n + s) {
    for (int i = s; i < n + s; i++) {
      cin >> (*this)[i];
    }
  }
};

template <typename T = int> struct Mat : vector<vector<T>> {
  Mat(int n, int m) : vector<vector<T>>(n) {
    for (int i = 0; i < n; i++) {
      (*this)[i] = Vec(m);
    }
  }
};

template <typename T = int, int M = 2> struct VecM : vector<array<T, M>> {
  Vec(int n, int s = 0) : vector<int>(n + s) {
    for (int i = s; i < n + s; i++) {
      for (int j = 0; i < M; j++) {
        cin >> (*this)[i][j];
      }
    }
  }
};

template <typename T> struct Zfn : vector<int> {
  Zfn(const T &s) : vector<int>(s.size()) {
    for (int i = 1, j = 1; i < s.size(); i++) {
      auto &c = (*this)[i];
      auto r = j + (*this)[j];
      if (i < r) {
        c = min(r - i, (*this)[i - j]);
      }
      for (; i + c < s.size() && s[i + c] == s[c]; c++, j = i)
        ;
    }
  }
};

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

// cout << fixed << setprecision(20);
