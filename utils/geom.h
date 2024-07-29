/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Cartesian point
 */
template <typename T = int> struct Point {
  T x, y;
  Point &operator+=(const Point &p) { return x += p.x, y += p.y, *this; }
  Point &operator-=(const Point &p) { return x -= p.x, y -= p.y, *this; }
  Point &operator*=(T scale) { return x *= scale, y *= scale, *this; }
  Point &operator/=(T scale) { return x /= scale, y /= scale, *this; }
  Point operator+(const Point &p) const { return Point(x, y) += p; }
  Point operator-(const Point &p) const { return Point(x, y) -= p; }
  Point operator*(T scale) const { return Point(x, y) *= scale; }
  Point operator/(T scale) const { return Point(x, y) /= scale; }
  Point operator-() const { return {-x, -y}; } // reflect about y=-x
  Point reflect() const { return {y, x}; }     // reflect about y=x
  Point rotate() const { return {-y, x}; }     // rotate 90 degrees
  Point rotate(T rad) const {
    auto s = sin(rad), c = cos(rad);
    return {x * c - y * s, x * s + y * c};
  }
  Point unit() const { return *this / norm(); }
  Point normal() const { return rotate().unit(); }
  auto cross(const Point<T> &p) const { return x * p.y - y * p.x; }
  auto dot(const Point<T> &p) const { return x * p.x + y * p.y; }
  auto norm2() const { return dot(*this); }
  auto norm() const { return sqrt(norm2()); }
  auto slope() const { return y / f64(x); }
  auto angle() const { return atan2(y, x); }
  auto operator<=>(const Point &p) const { return tie(x, y) <=> tie(p.x, p.y); }
};

int sign(auto x) { return (x > 0) - (x < 0); };

/**
 * Circle
 */
template <typename T = int> struct Circle {
  T r;
  Point<T> c;
  auto area() const { return numbers::pi * r * r; }
  auto perim() const { return numbers::pi * r * 2; }
  auto dist(const Point<T> &p) const { return r - (p - c).norm(); }
  auto side(const Point<T> &p) const { return sign(r * r - (p - c).norm2()); }
};

/**
 * Triangle
 */
template <typename T = int> struct Triangle {
  Point<T> a, b, c;
  auto area() const {
    return abs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0;
  }
  auto perim() const {
    return (a - b).norm() + (b - c).norm() + (c - a).norm();
  }
  auto orient() const { return (b - a).cross(c - a); }
  auto side(const Point<T> &p) const {
    auto s1 = sign((a - b).cross(p - b));
    auto s2 = sign((b - c).cross(p - c));
    auto s3 = sign((c - a).cross(p - a));
    auto sum = abs(s1 + s2 + s3);
    return sum >= 2 ? sum - 2 : -!!(s1 * s2 * s3);
  }
  auto circle() const {
    auto v1 = b - a, v2 = c - a;
    i64 n1 = v1.norm2(), n2 = v2.norm2();
    auto ux = v2.y * n1 - v1.y * n2;
    auto uy = v1.x * n2 - v2.x * n1;
    auto u = Point<f64>(ux, uy) / (2.0 * v1.cross(v2));
    return Circle<f64>(u.norm(), u + Point<f64>(a.x, a.y));
  }
  bool circum(const Point<T> &p) const {
    auto a1 = a - p, b1 = b - p, c1 = c - p;
    auto x = (i64)a1.norm2() * b1.cross(c1);
    auto y = (i64)b1.norm2() * c1.cross(a1);
    auto z = (i64)c1.norm2() * a1.cross(b1);
    return (x + y + z) * sign(orient()) >= 0;
  }
};

/**
 * Convex Hull
 */
struct Hull : vector<int> {
  template <typename T>
  Hull(const vector<Point<T>> &p) : vector<int>(p.size()) {
    assert(size() > 2);
    auto cmp1 = [&](int i, int j) { return p[i].reflect() < p[j].reflect(); };
    auto cmp2 = [&](int i, int j) {
      auto r = (p[i] - p[front()]).cross(p[j] - p[front()]);
      return r > 0 || (r == 0 && p[i].x < p[j].x);
    };
    iota(begin(), end(), 0);
    ::swap(front(), *min_element(begin(), end(), cmp1));
    sort(begin() + 1, end(), cmp2);
    auto i = begin() + 3;
    for (auto j = i; j != end(); *i++ = *j++) {
      for (; (p[*(i - 1)] - p[*(i - 2)]).cross(p[*j] - p[*(i - 2)]) < 0; i--)
        ;
    }
    resize(i - begin());
  }
};
