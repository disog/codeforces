/**
 * https://codeforces.com/contest/1993/submission/274382621
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

template <typename T>
using MinHeap = priority_queue<T, vector<int>, greater<int>>;

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

void solve(int t) {
  Int n;
  vector<Int> a(n);
  MinHeap<int> even;
  i64 mxodd = 0;
  for (auto &ai : a) {
    if (ai % 2) {
      mxodd = max<int>(mxodd, ai);
    } else {
      even.push(ai);
    }
  }
  int ans = 0;
  if (mxodd && even.size()) {
    ans = even.size();
    while (even.size() && mxodd > even.top()) {
      mxodd += even.top();
      even.pop();
    }
    ans += !even.empty();
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
