/**
 * https://codeforces.com/contest/1968/submission/270393290
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using namespace placeholders;

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct Str : string {
  Str() { cin >> *this; }
};

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

int binsearch(const auto &f, int s, int e) {
  while (s < e) {
    auto m = (s + e + 1) / 2;
    f(m) ? s = m : e = m - 1;
  }
  return e;
}

void solve(int t) {
  Int n, l, r;
  Str s;
  Zfn z(s);
  auto f = [&](int x) {
    int ans = 1;
    for (int i = x; i <= n - x; i++) {
      if (z[i] >= x) {
        i += x - 1;
        ans++;
      }
    }
    return ans;
  };
  auto g = [&f](int k, int m) { return f(m) >= k; };
  int m = sqrt<int>(n);
  vector<int> lcp(n + 1);
  for (int x = 1; x <= m; x++) {
    lcp[f(x)] = x;
  }
  for (int k = 1; k <= m; k++) {
    lcp[k] = binsearch(bind(g, k, _1), 0, n);
  }
  for (int i = n - 1; i > 0; i--) {
    lcp[i] = max(lcp[i], lcp[i + 1]);
  }
  for (int k = l; k <= r; k++) {
    cout << lcp[k] << ' ';
  }
  cout << endl;
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
