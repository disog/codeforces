/**
 * https://codeforces.com/contest/1993/submission/274447212
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init();
#endif

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

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

const auto gta1 = [](auto &lhs, auto &rhs) { return lhs[0] > rhs[0]; };

void solve(int t) {
  Int n, k;
  vector<Int> a(n);
  int m = 2 * k;
  vector<int> b(m), c(m);
  for (auto &ai : a) {
    auto &bi = b[ai % m];
    bi = max<int>(bi, ai);
    c[ai % m]++;
  }
  MinQueue<array<int, 2>> q(gta1);
  int ans = INT_MAX;
  for (int i = 1, cnt = 0; i < m + k; i++) {
    cnt += c[(i - 1) % m];
    q.push({b[(i - 1) % m], i});
    if (i >= k) {
      if (cnt == n) {
        auto [mx, j] = q.top();
        ans = min(ans, mx + (i - j) % m);
      }
      cnt -= c[i - k];
      q.pop({b[i - k], 0});
    }
  }
  println(ans == INT_MAX ? -1 : ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
