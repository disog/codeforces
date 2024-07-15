/**
 * Utils
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

/**
 * Common namespaces
 */
using namespace std;
using namespace placeholders;

/**
 * Common types
 */
using i64 = int64_t;
using f64 = double;
using str = const string &;
using MaxHeap = priority_queue<int>;
using MinHeap = priority_queue<int, vector<int>, greater<int>>;

/**
 * Common constants
 */
constexpr int _mod = 1000000007;
// constexpr int _mod = 998244353;

/**
 * Input number
 */
template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

/**
 * Common input types
 */
using Int = Num<int>;
using Chr = Num<char>;
using I64 = Num<i64>;
using F64 = Num<f64>;

/**
 * Input string
 */
struct Str : string {
  Str() { cin >> *this; }
};

/**
 * Matrix (2-D Vector)
 */
template <typename T> struct Mat : vector<vector<T>> {
  Mat(int n, int m) : vector<vector<T>>(n) {
    for (auto &&row : *this) {
      row.resize(m);
    }
  }
};

/**
 * Modular integer
 */
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

/**
 * (Modular) Factorial
 */
struct Fac : vector<Mod> {
  Fac(int m = _mod) : vector<Mod>(1, {1, m}) {}
  Mod operator[](int n) {
    while (size() <= n) {
      push_back(back() * (int)size());
    }
    return vector<Mod>::operator[](n);
  }
};

/**
 * (Modular) Binomial coefficient
 */
struct Bin : Fac {
  vector<Mod> inv;
  Mod operator()(int n, int k) {
    if (k < 0 || k > n) {
      return front() * 0;
    }
    auto ans = (*this)[n];
    if (inv.size() <= n) {
      int s = inv.size();
      inv.resize(n + 1);
      inv[n] = ans.inv();
      for (int i = n; i > s; i--) {
        inv[i - 1] = inv[i] * i;
      }
    }
    return ans * inv[k] * inv[n - k];
  }
} bin;

/**
 * (Undirected) Graph
 */
struct Graph : vector<vector<int>> {
  vector<array<Int, 2>> e;
  Graph(int n, int m = 0) : vector<vector<int>>(n), e(m) {
    for (auto &[u, v] : e) {
      add(u, v);
    }
  }
  void add(int u, int v) {
    (*this)[u].push_back(v);
    (*this)[v].push_back(u);
  }
};

/**
 * (Undirected) Weighed Graph
 */
struct WGraph : vector<vector<array<int, 2>>> {
  vector<array<Int, 3>> e;
  WGraph(int n, int m = 0) : vector<vector<array<int, 2>>>(n), e(m) {
    for (auto &[u, v, w] : e) {
      add(u, v, w);
    }
  }
  void add(int u, int v, int w) {
    (*this)[u].push_back({v, w});
    (*this)[v].push_back({u, w});
  }
};

/**
 * Directed Graph
 */
struct DGraph : vector<vector<int>> {
  vector<array<Int, 2>> e;
  DGraph(int n, int m = 0) : vector<vector<int>>(n), e(m) {
    for (auto &[u, v] : e) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v); }
};

/**
 * Weighed Directed Graph
 */
struct WDGraph : vector<vector<array<int, 2>>> {
  vector<array<Int, 3>> e;
  WDGraph(int n, int m = 0) : vector<vector<array<int, 2>>>(n), e(m) {
    for (auto &[u, v, w] : e) {
      add(u, v, w);
    }
  }
  void add(int u, int v, int w) { (*this)[u].push_back({v, w}); }
};

/**
 * Matching & bridges (of undirected graph)
 */
struct Match : vector<int> {
  int count = 0;
  vector<pair<int, int>> bridges;
  Match(Graph g, int s = 0) : vector<int>(g.size(), -1), low(g.size()) {
    int t = 1;
    dfs(g, s, s, t);
  }

private:
  void dfs(Graph &g, int u, int p, int &t) {
    auto &match = *this;
    auto tx = low[u] = t++;
    for (auto v : g[u]) {
      if (v != p) {
        if (low[v] == 0) {
          dfs(g, v, u, t);   // post-order (visit leaves first)
          if (low[v] > tx) { // new bridge
            bridges.emplace_back(u, v);
          }
          if (match[u] == match[v]) {
            match[u] = v;
            match[v] = u;
            count++;
          }
        }
        low[u] = min(low[u], low[v]);
      }
    }
  }
  vector<int> low;
};

/**
 * Strongly-connected components (of directed graph)
 */
struct SCC : vector<int> {
  int count = 0;
  SCC(DGraph g) : vector<int>(g.size()), low(g.size()) {
    for (int i = 0, t = 1; i < g.size(); i++) {
      if (low[i] == 0) {
        dfs(g, i, t);
      }
    }
  }

private:
  void dfs(DGraph &g, int u, int &t) {
    auto tx = low[u] = t++;
    visited.push_back(u);
    for (auto v : g[u]) {
      if (low[v] == 0) {
        dfs(g, v, t);
      }
      low[u] = min(low[u], low[v]);
    }
    if (low[u] == tx) { // component root
      count++;
      for (int v = -1; v != u; visited.pop_back()) {
        v = visited.back();
        low[v] = g.size();
        (*this)[v] = count;
      }
    }
  }
  vector<int> low, visited;
};

/**
 * Trie (N-ary prefix or suffix tree)
 */
template <typename T, int N> struct Trie : vector<pair<T, array<int, N>>> {
  Trie(int cap = 1) : vector<pair<T, array<int, N>>>(1) { this->reserve(cap); }
  void visit(const auto &f, const auto &x) {
    for (int i = 0, j = 0;; j++) {
      int k = f((*this)[i], j, x);
      if (k < 0) {
        break;
      }
      assert(k < N);
      auto &child = (*this)[i].second[k];
      if (!child) {
        child = this->size();
        this->emplace_back(); // might invalidate references
      }
      i = (*this)[i].second[k];
    }
  }
};

// Trie manipulation
auto bit = [](int j, int x) { return x & (1 << j); };
auto chr = [](int j, str s) { return s[j] - 'a'; };

// Bit prefixes
auto bpget = [](int j, int x) { return j < 32 ? bit(31 - j, x) != 0 : -1; };
auto bpadd = [](auto &node, int j, int x) { return node.first++, bpget(j, x); };
auto bprem = [](auto &node, int j, int x) { return node.first--, bpget(j, x); };

// Bit suffixes
auto bsget = [](int j, int x) { return j < 32 ? bit(j, x) != 0 : -1; };
auto bsadd = [](auto &node, int j, int x) { return node.first++, bsget(j, x); };
auto bsrem = [](auto &node, int j, int x) { return node.first--, bsget(j, x); };

// String prefixes
auto spget = [](int j, str s) { return j < s.size() ? chr(j, s) : -1; };
auto spadd = [](auto &node, int j, str s) { return node.first++, spget(j, s); };
auto sprem = [](auto &node, int j, str s) { return node.first--, spget(j, s); };

// String suffixes
auto ssget = [](int j, str s) {
  return j < s.size() ? chr(s.size() - j - 1, s) : -1;
};
auto ssadd = [](auto &node, int j, str s) { return node.first++, ssget(j, s); };
auto ssrem = [](auto &node, int j, str s) { return node.first--, ssget(j, s); };

/**
 * Disjoint set union (Union find)
 */
struct DSU {
  vector<int> parent, size;
  DSU(int n) : parent(n), size(n) {}
  int add(int v) { return size[v] = 1, parent[v] = v; }
  int find(int v) { return v == parent[v] ? v : parent[v] = find(parent[v]); }
  int merge(int a, int b) {
    a = find(a), b = find(b);
    if (a != b) {
      if (size[a] < size[b]) {
        std::swap(a, b);
      }
      size[a] += size[b];
      parent[b] = a;
    }
    return a;
  }
};

/**
 * Fenwick tree (Binary indexed tree)
 */
struct Fen {
  vector<int> nodes;
  Fen(int n) : nodes(n) {}
  void query(int x, const auto &f) { range_query(0, x); }
  void update(int x, const auto &f) { range_update(x, size() - 1); }
  void range_query(int x, int y, const auto &f) {
    for (; x <= y; y -= y & -y) {
      f(y, nodes[y]);
    }
  }
  void range_update(int x, int y, const auto &f) {
    for (; x <= y; x += x & -x) {
      f(x, nodes[x]);
    }
  }
};

/**
 * 2-D prefix sums
 */
struct Pref2D {
  int n, m;
  vector<vector<int>> sum;
  Pref2D(int n, int m) : sum(n + 1), n(n), m(m) {
    for (auto &&row : sum) {
      row.resize(m + 1);
    }
  }
  void rect(int x, const array<int, 4> &range) {
    auto [r1, c1, r2, c2] = range;
    sum[r1][c1] += x;
    sum[r2 + 1][c1] -= x;
    sum[r1][c2 + 1] -= x;
    sum[r2 + 1][c2 + 1] += x;
  }
  void rows(int x, const array<int, 2> &range) {
    auto [r1, r2] = range;
    sum[r1][0] += x;
    sum[r2 + 1][0] -= x;
  }
  void cols(int x, const array<int, 2> &range) {
    auto [c1, c2] = range;
    sum[0][c1] += x;
    sum[0][c2 + 1] -= x;
  }
  void cross(int x, const array<int, 4> &range) {
    auto [r1, c1, r2, c2] = range;
    rows(x, {r1, r2});
    cols(x, {c1, c2});
    rect(-x, range);
  }
  void visit(const auto &f) {
    vector<int> cur(m + 1);
    for (int i = 0; i < n; i++) {
      for (int j = 0, prev = 0; j < m; j++) {
        int saved = cur[j + 1];
        cur[j + 1] += sum[i][j] + cur[j] - prev;
        prev = saved;
        f(i, j, cur[j + 1]);
      }
    }
  }
};

/**
 * Z-function
 */
struct Zfn : vector<int> {
  Zfn(const auto &a, int s = 0) : Zfn(a, s, a.size()) {}
  Zfn(const auto &a, int s, int e) : vector<int>(e - s) {
    auto &z = *this;
    for (int i = 1, j = 1; i + s < e; i++) {
      auto &c = z[i] = max(0, min(j + z[j] - i, z[i - j]));
      for (; i + c < e && a[i + c + s] == a[c + s]; c++, j = i)
        ;
    }
  }
};

/**
 * Precomputed integer factors (Divisors)
 */
struct Div : vector<vector<int>> {
  Div(int n) : vector<vector<int>>(n + 1) {
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j += i) {
        (*this)[j].push_back(i);
      }
    }
  }
};

/**
 * Inversion count and cyclic shift (of sorted array)
 */
pair<int, int> invshift(const auto &a, int sa = 0, int sp = 1) {
  int inv = 0, shift = a[sa] - sp, n = a.size();
  for (int i = sa, sum = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (a[i] > a[j]) {
        inv++;
      }
    }
    if (shift >= 0) {
      auto d = a[i] - sp - (i - sa);
      if (shift != (n - sa + d) % (n - sa)) {
        shift = -1;
      }
    }
  }
  return {inv, shift};
}

/**
 * Comparison operators
 */
const less<int> lt1;
const greater<int> gt1;
const less<array<int, 2>> lt2;
const greater<array<int, 2>> gt2;
const auto lta2 = [](const auto &lhs, const auto &rhs) {
  return lhs[0] < rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
};
const auto gta2 = [](const auto &lhs, const auto &rhs) {
  return lhs[0] > rhs[0] || (lhs[0] == rhs[0] && lhs[1] > rhs[1]);
};

/**
 * Binary search
 */
int binsearch(const auto &f, int s, int e) {
  while (s < e) {
    auto m = (s + e + 1) / 2;
    f(m) ? s = m : e = m - 1;
  }
  return e;
}

/**
 * Choices satisfying inequality x + y <= c, for x <= a and y <= b
 */
i64 choices(int a, int b, int c) {
  i64 ans = 0;
  for (int i = 0; i <= a; i++) {
    ans += max(0, 1 + min(b, c - i));
  }
  return ans;
}

/**
 * Cartesian point
 */
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
  auto operator<=>(const Point<T> &p) const {
    return tie(x, y) <=> tie(p.x, p.y);
  }
};

/**
 * Circle
 */
template <typename T = int> struct Circle {
  T r;
  Point<T> c;
  auto area() const { return numbers::pi * r * r; }
  auto perim() const { return numbers::pi * r * 2; }
  auto dist(const Point<T> &p) const { return r - (p - c).norm(); }
  auto dist2(const Point<T> &p) const { return r * r - (p - c).norm2(); }
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
  auto side(const Point<T> &p) const {
    auto sign = [](T x) { return (x > 0) - (x < 0); };
    auto s1 = sign((a - b).cross(p - b));
    auto s2 = sign((b - c).cross(p - c));
    auto s3 = sign((c - a).cross(p - a));
    auto sum = abs(s1 + s2 + s3);
    return sum >= 2 ? sum - 2 : -!!(s1 * s2 * s3);
  }
  auto circum() const {
    auto v1 = b - a, v2 = c - a;
    f64 n1 = v1.norm2(), n2 = v2.norm2();
    f64 ux = v2.y * n1 - v1.y * n2; // use float, as it may be huge
    f64 uy = v1.x * n2 - v2.x * n1;
    auto u = Point<f64>(ux, uy) / (2.0 * v1.cross(v2));
    return Circle<f64>(u.norm(), u + Point<f64>(a.x, a.y));
  }
};

/**
 * Convex Hull
 */
struct Hull : vector<int> {
  template <typename T> Hull(const vector<Point<T>> &p) {
    auto cmp1 = [&](const auto &a, const auto &b) {
      return a.reflect() < b.reflect();
    };
    auto it = min_element(p.begin(), p.end(), cmp1);
    auto cmp2 = [&](int i, int j) {
      auto r = (p[i] - *it).cross(p[j] - *it);
      return r > 0 || (r == 0 && p[i].x < p[j].x);
    };
    auto &h = *this;
    resize(p.size());
    iota(begin(), end(), 0);
    ::swap(front(), h[it - p.begin()]);
    sort(begin() + 1, end(), cmp2);
    int i = 3;
    for (int j = i; j < size(); h[i++] = h[j++]) {
      for (; (p[h[i - 1]] - p[h[i - 2]]).cross(p[h[j]] - p[h[i - 2]]) < 0; i--)
        ;
    }
    resize(i);
  }
};

/**
 * Debugging utilities
 */
void debugn(int n) { cout << n << ';'; }
void debuga(const auto &a) {
  for (auto &ai : a) {
    cout << ai << ',';
  }
  cout << ';';
}
void debuga2(const auto &a) {
  for (auto &[x, y] : a) {
    cout << x << ',' << y << ',';
  }
  cout << ';';
}

/**
 * Test case function
 */
void solve(int t) { Int n; }

/**
 * Main function
 */
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
