/**
 * https://codeforces.com/contest/1984/submission/270568292
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
  Mod &operator/=(int rhs) { return x = operator/(rhs), *this; }
  Mod operator+(int rhs) const {
    return rhs < 0 ? operator-(-rhs) : Mod((x + rhs >= m ? x - m : x) + rhs, m);
  }
  Mod operator-(int rhs) const {
    return rhs < 0 ? operator+(-rhs) : Mod((x - rhs < 0 ? x + m : x) - rhs, m);
  }
  Mod operator*(int rhs) const { return Mod(i64(x) * rhs, m); }
  Mod operator/(int rhs) const { return operator*(Mod(rhs, m).inv()); }
  Mod pow(int y) const {
    Mod b(x, m), ans(!!x, m);
    for (; b && y; y >>= 1, b *= b) {
      ans *= (y & 1) ? b.x : 1;
    }
    return ans;
  }
  Mod inv() const { return pow(m - 2); } // inv of zero gives zero
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
  Point reflect() const { return {y, x}; }  // reflect about y=x
  Point perpend() const { return {-y, x}; } // rotate 90 degrees
  Point rotate(T rad) const {
    auto s = sin(rad), c = cos(rad);
    return {x * c - y * s, x * s + y * c};
  }
  Point unit() const { return *this / norm(); }
  Point normal() const { return perpend().unit(); }
  auto cross(const Point<T> &p) const { return x * p.y - y * p.x; }
  auto dot(const Point<T> &p) const { return x * p.x + y * p.y; }
  auto norm2() const { return dot(*this); }
  auto norm() const { return sqrt(norm2()); }
  auto slope() const { return y / f64(x); }
  auto angle() const { return atan2(y, x); }
  auto operator<=>(const Point<T> &p) const {
    return tie(x, y) <=> tie(p.x, p.y);
  }
};

template <typename T = int> struct Circle {
  T r;
  Point<T> c;
  auto area() const { return numbers::pi * r * r; }
  auto perim() const { return numbers::pi * r * 2; }
  auto dist(const Point<T> &p) const { return r - (p - c).norm(); }
  auto dist2(const Point<T> &p) const { return r * r - (p - c).norm2(); }
};

template <typename T = int> struct Triangle {
  Point<T> a, b, c;
  auto circum() const {
    auto v1 = b - a, v2 = c - a;
    f64 n1 = v1.norm2(), n2 = v2.norm2();
    f64 ux = v2.y * n1 - v1.y * n2;
    f64 uy = v1.x * n2 - v2.x * n1;
    auto u = Point<f64>(ux, uy) / (2.0 * v1.cross(v2));
    return Circle<f64>(u.norm(), u + Point<f64>(a.x, a.y));
  }
};

struct Hull : vector<int> {
  template <typename T> Hull(const vector<Point<T>> &set) {
    assert(set.size());
    auto cmp = [&](const auto &a, const auto &b) {
      return a.reflect() < b.reflect();
    };
    auto j = ranges::min_element(set, cmp) - set.begin();
    vector<tuple<f64, T, int>> slopes;
    for (int i = 0; i < set.size(); i++) {
      auto r = i == j ? INFINITY : (set[i] - set[j]).reflect().slope();
      slopes.emplace_back(-r, set[i].x, i);
    }
    ranges::sort(slopes);
    for (auto &[_, _x, i] : slopes) {
      for (int k = size() - 1; k > 1; k--) {
        auto &p1 = set[(*this)[k]];
        auto &p0 = set[(*this)[k - 1]];
        if ((p1 - p0).cross(set[i] - p0) >= 0) {
          break; // colinear or left turn
        }
        pop_back(); // right turn
      }
      push_back(i);
    }
  }
};

struct Fac : vector<Mod> {
  Fac(int n, int m = _mod) : vector<Mod>(n, {1, m}) {
    for (int i = 1; i < n; i++) {
      (*this)[i] = (*this)[i - 1] * i;
    }
  }
};

void solve(int t) {
  Int n;
  vector<Point<Int>> p(n);
  Point<int> a;
  Hull hull(p);       // O(n*log n)
  ranges::sort(hull); // O(n*log n)
  if (hull[1] != 1) {
    cout << 0 << endl;
    return;
  }
  int m = hull.size();
  vector<int> sizes(m);
  sizes[0] = sizes[1] = -1;
  auto f = [&](auto &self, int i, int j, int k) {
    if (sizes[k]) {
      return;
    }
    auto &a = p[hull[i]];
    auto &b = p[hull[j]];
    auto &c = p[hull[k]];
    Triangle tri(a, b, c);
    auto circle = tri.circum();
    bool bad = false;
    for (int l = 0; l < m && !bad; l++) {
      if (l != i && l != j && l != k) {
        auto &d = p[hull[l]];
        bad = circle.dist2(Point<f64>(d.x, d.y)) < 0;
      }
    }
    if (!bad) {
      sizes[k] = 1; // visited
      for (int l = 0; l < m; l++) {
        if (!sizes[l]) {
          self(self, i, k, l);
          self(self, j, k, l);
          sizes[k] += sizes[l];
        }
      }
    }
  };
  for (int k = 2; k < m; k++) {
    f(f, 0, 1, k);
  }
  Fac fac(m);
  Mod ans = fac[m - 2];
  for (int i = 2; i < m; i++) {
    ans /= sizes[i];
  }
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
