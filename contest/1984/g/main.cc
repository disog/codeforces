/**
 * https://codeforces.com/contest/1984/submission/268774329
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T = int> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
};

template <typename T = int> struct Vec : vector<Num<T>> {
  Vec(int n, int s = 0) : vector<Num<T>>(s, 0) { this->resize(n + s); }
};

struct Mod {
  int x, m;
  Mod(int a, int b) : x(a % b), m(b) {}
  operator int() { return x; }
  int operator+(int rhs) {
    return rhs < 0 ? operator-(-rhs) : (x + rhs >= m ? x - m : x) + rhs;
  }
  int operator-(int rhs) {
    return rhs < 0 ? operator+(-rhs) : (x - rhs < 0 ? x + m : x) - rhs;
  }
  int operator+=(int rhs) { return x = operator+(rhs); }
  int operator-=(int rhs) { return x = operator-(rhs); }
};

pair<int, int> invshift(auto &a, int sa = 0, int sp = 1) {
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

void solve(int t) {
  Num n;
  Vec a(n);
  auto [inv, shift] = invshift(a);
  vector<array<int, 2>> ops;
  int ans = n;
  if (shift > 0) {
    for (ans--; shift--;) {
      ops.push_back({1, 2});
    }
  } else if (shift < 0) {
    ans -= 2;
    if (n % 2 == 0) {
      ans -= inv % 2;
      int m = n - ans;
      auto it = find(a.begin(), a.end(), int(n));
      int i = it - a.begin() + 1, k = (n - i) % m;
      if (k > 0) {
        int j = max(0, i - ans);
        ops.push_back({j + 1, j + 1 + k});
        auto it1 = a.begin() + j;
        ranges::rotate(it1, it1 + ans, it1 + ans + k);
        it += k;
      }
      for (int j = 0; j < (n - i) / m; j++) {
        ops.push_back({1, m + 1});
      }
      ranges::rotate(a.begin(), it + 1, a.end());
      n -= inv % 2;
    }
    const array<int, 2> fwd1{2, 1}, bwd1{1, 2}, fwd2{3, 1}, bwd2{1, 3};
    Mod c(n - 1, n);
    auto f0 = [&](int i, int d) {
      int k = 0;
      for (; a.at(c - (k - d)) != i && a.at(c + (k + d)) != i && k < n; k += 2)
        ;
      return a.at(c - (k - d)) == i ? make_pair(-k, bwd2) : make_pair(k, fwd2);
    };
    auto f = [&](int i, bool move) {
      auto [dist, op] = f0(i, 0);
      auto fix = abs(dist) == n;
      if (fix) {
        tie(dist, op) = f0(i, -1);
      }
      c += dist;
      for (int j = abs(dist); j > 0; j -= 2) {
        ops.push_back(op);
      }
      if (move) {
        if (fix) {
          for (; a.at(c) != i + 1; c += 1) {
            swap(a.at(c), a.at(c - 1));
            ops.push_back(bwd1);
            ops.push_back(fwd2);
          }
        } else {
          for (; a.at(c + 1) != i + 1; c += 1) {
            swap(a.at(c + 1), a.at(c));
            ops.push_back(fwd1);
          }
        }
      }
    };
    f(n, false);
    for (int i = n - 1; i > 1; i--) {
      for (int j = 1; a.at(c - j) == i && i > 1; j++, i--)
        ;
      if (i > 1) {
        f(i, true);
      }
    }
    f(n, false);
  }
  cout << ans << endl;
  cout << ops.size() << endl;
  for (auto &[x, y] : ops) {
    cout << x << ' ' << y << endl;
  }
}

int main() {
#ifdef LOCAL
  using filesystem::path;
  freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Num t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}
