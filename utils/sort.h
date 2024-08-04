/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Binary search
 * (assumes that f(s) is true and does not check it)
 */
int binsearch(auto &&f, int s, int e) {
  while (s < e) {
    auto m = (s + e + 1) / 2;
    f(m) ? s = m : e = m - 1;
  }
  return e; // last such that f is true
}

/**
 * Inversion count and cyclic shift (of sorted array)
 */
pair<int, int> invshift(auto &&a, int sa = 0, int sp = 1) {
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
 * Minimum Queue
 */
template <typename T> struct MinQueue {
  deque<T> queue;
  function<bool(const T &, const T &)> f;
  MinQueue(auto &&f) : f(f) {}
  const T &top() const { return queue.front(); }
  void push(const T &val) {
    while (queue.size() && f(val, queue.back())) {
      queue.pop_back();
    }
    queue.push_back(val);
  };
  void pop(const T &val) {
    if (queue.size() && !f(queue.front(), val)) {
      queue.pop_front();
    }
  };
};

// Comparison operators
const less<int> lt1;
const greater<int> gt1;
const less<array<int, 2>> lt2;
const greater<array<int, 2>> gt2;

// Custom comparison
const auto lta1 = [](auto &lhs, auto &rhs) { return lhs[0] < rhs[0]; };
const auto gta1 = [](auto &lhs, auto &rhs) { return lhs[0] > rhs[0]; };
const auto lta2 = [](auto &lhs, auto &rhs) {
  return lhs[0] < rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
};
const auto gta2 = [](auto &lhs, auto &rhs) {
  return lhs[0] > rhs[0] || (lhs[0] == rhs[0] && lhs[1] > rhs[1]);
};
