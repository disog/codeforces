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

template <typename T = int> struct VecP : vector<T> {
  VecP(int n, int s = 0) : vector<int>(n + s) {
    for (int i = s, x; i < n + s; i++) {
      cin >> x;
      (*this)[x] = i;
    }
  }
};

template <typename T = int> struct Vec2 : vector<array<T, 2>> {
  Vec2(int n, int s = 0) : vector<array<T, 2>>(n + s) {
    for (int i = s, x, y; i < n + s; i++) {
      cin >> x >> y;
      (*this)[i] = {x, y};
    }
  }
};

template <typename T = int> struct Vec2I : vector<array<T, 3>> {
  Vec2I(int n, int s = 0) : vector<array<T, 2>>(n + s) {
    for (int i = s, x, y; i < n + s; i++) {
      cin >> x >> y;
      (*this)[i] = {x, y, i};
    }
  }
};

template <typename T = int> struct MatP : vector<array<int, 2>> {
  MatP(int n, int m, int s = 0) : : vector<array<int, 2>>(n * m + s) {
    for (int i = 0; i < n; i++) {
      for (int j = 0, x; j < m; j++) {
        cin >> x;
        (*this)[x] = {i, j};
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
