/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

/**
 * Common compilation flags
 */
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,popcnt")

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
 * Modular integer
 */
struct Mod {
  int x, m;
  Mod(i64 x = 0, int m = _mod) : x(x % m), m(m) {}
  operator int() const { return x; }
  Mod operator+(int rhs) const { return Mod(x, m) += rhs; }
  Mod operator-(int rhs) const { return Mod(x, m) -= rhs; }
  Mod operator*(int rhs) const { return Mod(x, m) *= rhs; }
  Mod operator/(int rhs) const { return Mod(x, m) /= rhs; }
  Mod &operator+=(int rhs) {
    return rhs < 0 ? operator-=(-rhs) : ((x += rhs) >= m ? x -= m : x, *this);
  }
  Mod &operator-=(int rhs) {
    return rhs < 0 ? operator+=(-rhs) : ((x -= rhs) < 0 ? x += m : x, *this);
  }
  Mod &operator*=(int rhs) { return x = (i64(x) * rhs) % m, *this; }
  Mod &operator/=(int rhs) { return operator*=(Mod(rhs, m).inv()); }
  Mod inv() const { return pow(m - 2); } // inv of zero gives zero
  Mod pow(int rhs) const {
    Mod base(x, m), ans(!!x, m);
    for (; base && rhs; rhs >>= 1, base *= base) {
      if (rhs & 1) {
        ans *= base;
      }
    }
    return ans;
  }
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
};

/**
 * Directed Graph
 */
struct Digraph : vector<vector<int>> {
  int n, m;
  Digraph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v); }
};

/**
 * Undirected Graph
 */
struct Graph : vector<vector<int>> {
  int n, m;
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { _add(u, v), _add(v, u); }
  void _add(int u, int v) { (*this)[u].push_back(v); }
};

/**
 * Weighed Directed Graph
 */
struct WDigraph : vector<vector<array<int, 2>>> {
  int n, m;
  WDigraph(int n, int m = 0)
      : vector<vector<array<int, 2>>>(n + 1), n(n), m(m) {
    for (auto &[u, v, w] : vector<array<Int, 3>>(m)) {
      add(u, v, w);
    }
  }
  void add(int u, int v, int w) { (*this)[u].push_back({v, w}); }
};

/**
 * Weighed Undirected Graph
 */
struct WGraph : vector<vector<array<int, 2>>> {
  int n, m;
  WGraph(int n, int m = 0) : vector<vector<array<int, 2>>>(n + 1), n(n), m(m) {
    for (auto &[u, v, w] : vector<array<Int, 3>>(m)) {
      add(u, v, w);
    }
  }
  void add(int u, int v, int w) { _add(u, v, w), _add(v, u, w); }
  void _add(int u, int v, int w) { (*this)[u].push_back({v, w}); }
};

/**
 * Tree
 */
struct Tree : Graph {
  struct Info {
    int par, dep, siz, hei;
  };
  vector<Info> info;
  Tree(int n) : Graph(n), info(n + 1) {} // no edges
  Tree(int n, int s) : Graph(n, n - 1), info(n + 1) { dfs(s, s); }
  void dfs(int u, int p, int d = 1) {
    auto &cur = info[u] = {p, d, 1, 1};
    for (auto &v : (*this)[u]) {
      if (v != p) {
        dfs(v, u, d + 1);
        cur.siz += info[v].siz;
        cur.hei = max(cur.hei, 1 + info[v].hei);
      }
    }
  }
};

/**
 * Matching (of tree)
 */
struct Match : vector<int> {
  int count = 0;
  vector<bool> vis;
  Match(const Graph &g, int s) : vector<int>(g.size(), -1), vis(g.size()) {
    dfs(g, s, s);
  }
  void dfs(const Graph &g, int u, int p) {
    vis[u] = true;
    for (auto v : g[u]) {
      if (v != p && !vis[v]) {
        dfs(g, v, u); // post-order (visit leaves first)
        if ((*this)[u] == (*this)[v]) {
          (*this)[u] = v;
          (*this)[v] = u;
          count++;
        }
      }
    }
  }
};

/**
 * Bridges (of undirected connected graph)
 */
struct Bridges : vector<array<int, 2>> {
  vector<int> low, siz;
  Bridges(const Graph &g, int s) : low(g.size()), siz(g.size()) {
    int t = 1;
    dfs(g, s, s, t);
  }
  void dfs(const Graph &g, int u, int p, int &t) {
    auto tx = low[u] = t++;
    siz[u] = 1;
    for (auto v : g[u]) {
      if (v != p) {
        if (low[v] == 0) {
          dfs(g, v, u, t); // post-order (visit leaves first)
          siz[u] += siz[v];
          if (low[v] > tx) {
            push_back({u, v});
          }
        }
        low[u] = min(low[u], low[v]);
      }
    }
  }
};

/**
 * Strongly-connected components (of directed graph)
 */
struct SCC : vector<int> {
  int count = 0;
  vector<int> low, vis;
  SCC(const Digraph &g) : vector<int>(g.size()), low(g.size()) {
    for (int i = 0, t = 1; i < g.size(); i++) {
      if (low[i] == 0) {
        dfs(g, i, t);
      }
    }
  }
  void dfs(const Digraph &g, int u, int &t) {
    auto tx = low[u] = t++;
    vis.push_back(u);
    for (auto v : g[u]) {
      if (low[v] == 0) {
        dfs(g, v, t);
      }
      low[u] = min(low[u], low[v]);
    }
    if (low[u] == tx) { // component root
      count++;
      int i = vis.size();
      do {
        auto v = vis[--i];
        low[v] = g.size();
        (*this)[v] = count;
      } while (vis[i] != u);
      vis.resize(i);
    }
  }
};

/**
 * 2-Satisfiability solver
 */
struct TwoSat {
  int n;
  Digraph g;
  TwoSat(int n) : g(2 * n), n(n) {}
  void add(int a, int b) { g.add(n + a, n + b); }
  void either(int a, int b) { implies(-a, b); }
  void notequal(int a, int b) { equal(-a, b); }
  void set(int a) { add(-a, a); }
  void equal(int a, int b) {
    implies(a, b);
    implies(-a, -b);
  }
  void implies(int a, int b) {
    add(a, b);   //  a ->  b
    add(-b, -a); // !b -> !a
  }
  bool operator()() const {
    SCC scc(g);
    for (int i = 1; i <= n; i++) {
      if (scc[n + i] == scc[n - i]) {
        return false;
      }
    }
    return true;
  }
};

/**
 * Trie (N-ary prefix or suffix tree)
 */
template <typename T, size_t N> struct Trie : vector<pair<T, array<int, N>>> {
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
        swap(a, b);
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
  Fen(int n) : nodes(n + 1) {}
  void query(int y, const auto &f) {
    for (; y > 0; y -= y & -y) {
      f(y, nodes[y]);
    }
  }
  void update(int x, const auto &f) {
    assert(x > 0);
    for (; x < nodes.size(); x += x & -x) {
      f(x, nodes[x]);
    }
  }
};

/**
 * Matrix (2-D Vector)
 */
template <typename T> struct Mat : vector<vector<T>> {
  int n, m;
  Mat(int n, int m) : vector<vector<T>>(n), n(n), m(m) {
    for (auto &row : *this) {
      row.resize(m);
    }
  }
};

/**
 * Matrix-vector multiplication
 */
template <typename T, typename U>
vector<U> operator*(const Mat<T> &mat, const vector<U> &rhs) {
  assert(mat.m == rhs.size());
  vector<U> ans(n);
  for (int i = 0; i < mat.n; i++) {
    for (int j = 0; j < mat.m; j++) {
      ans[i] += (*this)[i][j] * rhs[i];
    }
  }
  return ans;
}

/**
 * Matrix multiplication
 */
template <typename T, typename U>
Mat<U> operator*(const Mat<T> &mat, const Mat<U> &rhs) {
  assert(mat.m == rhs.n);
  Mat<U> ans(mat.n, rhs.m);
  for (int i = 0; i < mat.n; i++) {
    for (int j = 0; j < rhs.m; j++) {
      for (int k = 0; k < mat.m; k++) {
        ans[i][j] += mat[i][k] * rhs[k][j];
      }
    }
  }
  return ans;
}

/**
 * Matrix idendity
 */
template <typename T> Mat<T> ident(int n) {
  Mat<T> ans(n, n);
  for (int i = 0; i < n; i++) {
    ans[i][i] = 1;
  }
  return ans;
}

/**
 * Matrix exponentiation
 */
template <typename T> Mat<T> pow(const Mat<T> &mat, int rhs) {
  auto base = mat, ans = ident<T>(mat.n);
  for (; rhs; rhs >>= 1, base *= base) {
    if (rhs & 1) {
      ans *= base;
    }
  }
  return ans;
}

/**
 * Matrix transpose
 */
template <typename T> Mat<T> trans(const Mat<T> &mat) {
  Mat<T> ans(mat.m, mat.n);
  for (int i = 0; i < mat.n; i++) {
    for (int j = 0; j < mat.m; j++) {
      ans[j][i] = mat[i][j];
    }
  }
  return ans;
}

/**
 * 2-D prefix sums
 */
template <typename T> struct Pref2D {
  Mat<T> sum;
  Pref2D(int n, int m) : sum(n + 1, m + 1) {}
  void rect(T x, const array<int, 4> &range) {
    auto [r1, c1, r2, c2] = range;
    sum[r1][c1] += x;
    sum[r2 + 1][c1] -= x;
    sum[r1][c2 + 1] -= x;
    sum[r2 + 1][c2 + 1] += x;
  }
  void rows(T x, const array<int, 2> &range) {
    auto [r1, r2] = range;
    sum[r1][0] += x;
    sum[r2 + 1][0] -= x;
  }
  void cols(T x, const array<int, 2> &range) {
    auto [c1, c2] = range;
    sum[0][c1] += x;
    sum[0][c2 + 1] -= x;
  }
  void cross(T x, const array<int, 4> &range) {
    auto [r1, c1, r2, c2] = range;
    rows(x, {r1, r2});
    cols(x, {c1, c2});
    rect(-x, range);
  }
  void visit(const auto &f) {
    vector<T> cur(sum.m);
    for (int i = 0; i < sum.n - 1; i++) {
      for (int j = 0, prev = 0; j < sum.m - 1; j++) {
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
 * Choices satisfying inequality x + y <= m, for a1 <= x <= a2 and b1 <= y <= b2
 */
i64 choices(int a1, int a2, int b1, int b2, i64 m) {
  i64 ans = 0;
  for (int i = a1; i <= a2; i++) {
    ans += max<i64>(0, min<i64>(b2, m - i) - b1 + 1);
  }
  return ans;
}

/**
 * Maximum sum satisfying inequality a * x + b * y <= m, for x <= ca and y <= cb
 */
i64 maxsum(int a, int ca, int b, int cb, i64 m) {
  assert(a > 0 && a < b);
  auto ua = min<i64>(ca, m / a);
  auto ub = min<i64>(cb, (m - ua * a) / b);
  auto ra = min<i64>({ua, cb - ub, (m - ua * a - ub * b) / (b - a)});
  return (ua - ra) * a + (ub + ra) * b;
}

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

/**
 * Printing utilities
 */
template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
template <typename T, size_t N>
ostream &operator<<(ostream &os, const span<T, N> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(const auto &...args) { ((cout << args << ' '), ...) << endl; }

/**
 * Test case function
 */
void solve(int t) {
  Int n;
  int ans = 0;
  println(ans);
}

/**
 * Input redirection
 */
#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init(__FILE__);
#endif

/**
 * Main function
 */
int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
