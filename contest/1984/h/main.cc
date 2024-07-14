/**
 * Submission
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using f64 = double;

constexpr int _mod = 998244353;

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct Mod {
  int x, m;
  Mod(i64 x = 0, int m = _mod) : x(x % m), m(m) {}
  operator int() const { return x; }
  Mod &operator+=(int rhs) { return x = operator+(rhs), *this; }
  Mod &operator-=(int rhs) { return x = operator-(rhs), *this; }
  Mod &operator*=(int rhs) { return x = operator*(rhs), *this; }
  Mod operator+(int rhs) const {
    return rhs < 0 ? operator-(-rhs) : Mod((x + rhs >= m ? x - m : x) + rhs, m);
  }
  Mod operator-(int rhs) const {
    return rhs < 0 ? operator+(-rhs) : Mod((x - rhs < 0 ? x + m : x) - rhs, m);
  }
  Mod operator*(int rhs) const { return Mod(i64(x) * rhs, m); }
  Mod pow(int y) const {
    Mod b(x, m), ans(!!x, m);
    for (; b && y; y >>= 1, b *= b) {
      ans *= (y & 1) ? b.x : 1;
    }
    return ans;
  }
  Mod inv() const { return pow(m - 2); }
};

template <typename T = int> struct Point {
  T x, y;
  Point &operator+=(const Point<T> &p) { return x += p.x, y += p.y, *this; }
  Point &operator-=(const Point<T> &p) { return x -= p.x, y -= p.y, *this; }
  Point &operator*=(T scale) { return x *= scale, y *= scale, *this; }
  Point &operator/=(T scale) { return x /= scale, y /= scale, *this; }
  Point operator+(const Point<T> &p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point<T> &p) const { return {x - p.x, y - p.y}; }
  Point operator*(T scale) const { return {x * scale, y * scale}; }
  Point operator/(T scale) const { return {x / scale, y / scale}; }
  Point reflect() const { return {y, x}; }
  auto cross(const Point<T> &p) const { return x * p.y - y * p.x; }
  auto dot(const Point<T> &p) const { return x * p.x + y * p.y; }
  auto norm2() const { return dot(*this); }
  auto norm() const { return sqrt(norm2()); }
  auto slope() const { return y / f64(x); }
  auto angle() const { return atan2(y, x); }
  bool operator<(const Point<T> &p) const {
    return x < p.x || (x == p.x && y < p.y);
  }
};

struct Hull : list<int> {
  Hull(const vector<Point<Int>> &set) {
    auto cmp = [&](const auto &a, const auto &b) {
      return a.reflect() < b.reflect();
    };
    auto j = min_element(set.begin(), set.end(), cmp) - set.begin();
    vector<pair<f64, int>> angles(set.size());
    for (int i = 0; i < set.size(); i++) {
      auto r = i == j ? INFINITY : (set[i] - set[j]).reflect().slope();
      angles[i] = {-r, i};
    }
    ::sort(angles.begin(), angles.end());
    for (auto &[_, i] : angles) {
      if (size() > 2) {
        for (auto it = --end(); true;) {
          auto &p1 = set[*it--], &p0 = set[*it];
          if ((p1 - p0).cross(set[i] - p0) >= 0) {
            break; // colinear or left turn
          }
          pop_back(); // right turn
        }
      }
      push_back(i);
    }
  }
};

void solve(int t) {
  Int n;
  vector<Point<Int>> p(n);
  Hull hull(p);
  Mod ans;
  cout << ans << endl;
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
