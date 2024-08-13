/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Vector Multiply-and-add
 */
inline void madd(auto &lhs, const auto &rhs, const auto &c) {
  for (int i = 0; i < lhs.size(); i++) {
    lhs[i] += rhs[i] * c;
  }
}

/**
 * Static Matrix (2-D Array)
 */
template <typename T, size_t N, size_t M = N>
using SMat = array<array<T, M>, N>;

/**
 * Static Matrix-array multiplication
 */
template <typename T, size_t N, size_t M, typename U>
array<U, M> operator*(const SMat<T, N, M> &lhs, const array<U, M> &rhs) {
  array<U, M> ans = {};
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      ans[i] += lhs[i][j] * rhs[j];
    }
  }
  return ans;
}

/**
 * Static Matrix multiplication
 */
template <typename T, size_t N, size_t M1, typename U, size_t M2>
SMat<U, N, M2> operator*(const SMat<T, N, M1> &lhs,
                         const SMat<U, M1, M2> &rhs) {
  SMat<U, N, M2> ans = {};
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M1; j++) {
      madd(ans[i], rhs[j], lhs[i][j]);
    }
  }
  return ans;
}

/**
 * Dynamic Matrix (2-D Vector)
 */
template <typename T> struct Mat : vector<vector<T>> {
  const int n, m;
  Mat(int n, int m) : vector<vector<T>>(n), n(n), m(m) {
    for (auto &row : *this) {
      row.resize(m);
    }
  }
  Mat(int n, int m, T s) : vector<vector<T>>(n, vector<T>(m, s)), n(n), m(m) {}
};

/**
 * Dynamic Matrix-vector multiplication
 */
template <typename T, typename U>
vector<U> operator*(const Mat<T> &lhs, const vector<U> &rhs) {
  assert(lhs.m == rhs.size());
  vector<U> ans(lhs.n);
  for (int i = 0; i < lhs.n; i++) {
    for (int j = 0; j < lhs.m; j++) {
      ans[i] += lhs[i][j] * rhs[j];
    }
  }
  return ans;
}

/**
 * Dynamic Matrix multiplication
 */
template <typename T, typename U>
Mat<U> operator*(const Mat<T> &lhs, const Mat<U> &rhs) {
  assert(lhs.m == rhs.n);
  Mat<U> ans(lhs.n, rhs.m);
  for (int i = 0; i < lhs.n; i++) {
    for (int j = 0; j < lhs.m; j++) {
      madd(ans[i], rhs[j], lhs[i][j]);
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
  void visit(auto &&f) {
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
 * Inclusion Walk
 */
void inclusion(int n, int m, int w, int h, auto &&f) {
  int rmx = min(h, n - h + 1); // window size vs number of windows
  int cmx = min(w, m - w + 1); // idem for columns
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int rc = min({rmx, i + 1, n - i}); // number of inclusions
      int cc = min({cmx, j + 1, m - j}); // idem for columns
      f(i, j, rc * cc);
    }
  }
}

/**
 * Spiral Walk
 * @see https://stackoverflow.com/a/33639875/4725347
 */
void spiral(auto &&f) {
  for (int x = 0, y = 0, d = 1, m = 1; true; d = -d, m++) {
    for (; 2 * x * d < m; x += d) {
      if (!f(x, y)) {
        return;
      }
    }
    for (; 2 * y * d < m; y += d) {
      if (!f(x, y)) {
        return;
      }
    }
  }
}
