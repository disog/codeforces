/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Vector Indices
 */
struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

/**
 * Binary Search
 */
int binsearch(auto &&f, int s, int e) { // (s, e] O(log n)
  while (s < e) {
    auto m = (s + e + 1) / 2;
    f(m) ? s = m : e = m - 1;
  }
  return e; // last such that f is true
}

/**
 * Longest Increasing Subsequence
 */
int lis(auto &&f, int s, int e) { // [s, e) O(n*log n)
  vector<int> inc = {s};
  for (int i = s + 1; i < e; i++) {
    if (f(inc.back(), i)) {
      inc.push_back(i);
    } else {
      *ranges::lower_bound(inc, i, f) = i;
    }
  }
  return inc.size() - (s >= e);
}

/**
 * Maximum Sum of Subsequences of Length R Mod K
 * A good subsequence is one where there are a multiple of k elements in between
 * any 2 elements.
 * @see https://cfstep.com/codeforces/contests/contest-1993/problem-d/code/
 */
int max_sum_subseq_mod_k(const vector<int> &a, int k, int r) {
  vector<int> dp(k + 1);
  for (int i = 0; i < a.size(); i++) {
    int len = 1 + i % k;
    dp[len] = max(dp[len], dp[len - 1] + a[i]);
  }
  return dp[r];
}

/**
 * Inversion Count
 */
int invcount(auto &&f, int s, int e) { // [s, e) O(n^2)
  int ans = 0;
  for (int i = s; i < e; i++) {
    for (int j = i + 1; j < e; j++) {
      ans += f(j, i);
    }
  }
  return ans;
}

/**
 * Cyclic Shift (of sorted array, rightwise)
 */
int cyclicshift(auto &&f, int s, int e) { // [s, e) O(n)
  int ans = 0;
  for (int i = s + 1; i < e; i++) {
    if (f(i, i - 1)) {
      if (ans) {
        return -1; // array must contain at most one such inversion
      }
      ans = i;
    }
  }
  return ans && s < e - 2 && f(s, e - 1) ? -1 : ans;
}

/**
 * Minimum Queue (not preserving elements)
 */
template <typename T> struct MinQueue {
  deque<T> queue;
  function<bool(const T &, const T &)> f;
  MinQueue(auto &&f) : f(f) {}
  const T &top() const { return queue.front(); } // O(1)
  void push(const T &val) {                      // O(1)
    while (queue.size() && f(val, queue.back())) {
      queue.pop_back();
    }
    queue.push_back(val);
  };
  void pop(const T &val) { // O(1)
    if (queue.size() && !f(queue.front(), val)) {
      queue.pop_front();
    }
  };
};

/**
 * Minimum Stack
 */
template <typename T> struct MinStack {
  stack<pair<T, T>> st;
  function<bool(const T &, const T &)> f;
  MinStack(auto &&f) : f(f) {}
  size_t size() const { return st.size(); };       // O(1)
  const T &top() const { return st.top().second; } // O(1)
  bool _chk(const T &val) const { return st.empty() || f(val, top()); }
  void push(const T &val) { st.emplace(val, _chk(val) ? val : top()); }; // O(1)
  T pop() {                                                              // O(1)
    auto val = st.top().first;
    return st.pop(), val;
  };
};

/**
 * Minimum Queue (preserving elements)
 */
template <typename T> struct MinQueue2 {
  MinStack<T> s1, s2;
  MinQueue2(auto &&f) : s1(f), s2(f) {}
  size_t size() const { return s1.size() + s2.size(); };                 // O(1)
  const T &top() const { return (s1.size() && _chk() ? s1 : s2).top(); } // O(1)
  bool _chk() const { return !s2.size() || s2.f(s1.top(), s2.top()); }
  void push(const T &val) { s1.push(val); } // O(1)
  T pop() {                                 // O(1)
    if (!s2.size()) {
      while (s1.size()) {
        s2.push(s1.pop());
      }
    }
    return s2.pop();
  };
};

/**
 * Median Queue (using one set)
 */
template <typename T> struct MedQueue {
  function<bool(const T &, const T &)> f;
  multiset<T, decltype(f)> set;
  decltype(set)::iterator mid;
  MedQueue(auto &&f) : f(f), set(f), mid(set.end()) {}
  size_t size() const { return set.size(); }; // O(1)
  const T &top() const { return *mid; }       // O(1)
  int _inc(const T &val) {
    return size() == 1 ? -1 : size() % 2 - f(val, *mid);
  }
  void push(const T &val) { // O(log n)
    set.insert(val);
    mid = next(mid, _inc());
  }
  void pop(const T &val) { // O(log n)
    mid = next(mid, -_inc());
    auto it = set.find(val);
    assert(it != set.end());
    set.erase(it);
  }
};

/**
 * Median Queue (using two sets)
 */
template <typename T> struct MedQueue2 {
  function<bool(const T &, const T &)> f;
  multiset<T, decltype(f)> s1, s2;
  MedQueue(auto &&f) : f(f), s1(bind(f, _2, _1)), s2(f) {}
  size_t size() const { return s1.size() + s2.size(); }; // O(1)
  const T &top() const { return *s1.begin(); }           // O(1)
  bool _chk(const T &val) const { return !s2.size() || f(val, *s2.begin()); }
  void push(const T &val) { // O(log n)
    (_chk(val) ? s1 : s2).insert(val);
    _rebalance();
  }
  void pop(const T &val) { // O(log n)
    auto &set = _chk(val) ? s1 : s2;
    auto it = set.find(val);
    assert(it != set.end());
    set.erase(it);
    _rebalance();
  }
  void _rebalance() { // O(1)
    if (s1.size() > s2.size() + 1) {
      s2.insert(s2.begin(), s1.extract(s1.begin()));
    } else if (s1.size() < s2.size()) {
      s1.insert(s1.begin(), s2.extract(s2.begin()));
    }
  }
};

// consider using ranges::nth_element

// Comparison operators
const less<int> lt1;
const greater<int> gt1;
const equal_to<int> eq1;
const less<array<int, 2>> lt2;
const greater<array<int, 2>> gt2;
const equal_to<array<int, 2>> eq2;

// Custom comparison
const auto lta1 = [](auto &lhs, auto &rhs) { return lhs[0] < rhs[0]; };
const auto gta1 = [](auto &lhs, auto &rhs) { return lhs[0] > rhs[0]; };
const auto lta2 = [](auto &lhs, auto &rhs) {
  return lhs[0] < rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
};
const auto gta2 = [](auto &lhs, auto &rhs) {
  return lhs[0] > rhs[0] || (lhs[0] == rhs[0] && lhs[1] > rhs[1]);
};
