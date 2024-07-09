#include <bits/stdc++.h>

using namespace std;

template <typename T = int> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
};

const greater<int> gt1;
const auto lta2 = [](auto &lhs, auto &rhs) {
  return lhs[0] < rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
};

void solve(int t) {
  Num n;
  vector<array<Num<>, 2>> b(n);
  ranges::sort(b, lta2); // O(n*log n)
  vector<int> heights;
  vector<list<int>> shelves;
  for (int i = 0; i < n; i++) { // O(n*log n)
    int h = b[i][1];
    int j = ranges::lower_bound(heights, h, gt1) - heights.begin();
    if (j == heights.size()) {
      heights.push_back(h);
      shelves.push_back({i});
    } else {
      heights[j] = h;
      shelves[j].push_back(i);
    }
  }
  auto f = [&](list<int> &l, list<int> &r, int &c) {
    auto it = l.begin();
    auto [w, h] = b[r.front()];
    for (; it != l.end() && c > 0; it++, c--) { // O(c)
      auto [w1, h1] = b[*it];
      if (w1 > w || h1 > h) {
        break;
      }
    }
    r.splice(r.begin(), l, l.begin(), it); // O(1)
  };
  auto g = [&](list<int> &l, list<int> &r, int &c) {
    auto it = l.end();
    auto [w, h] = b[r.back()];
    for (; it != l.begin() && c > 0; it--, c--) { // O(c)
      auto [w1, h1] = b[*prev(it)];
      if (w1 < w || h1 < h) {
        break;
      }
    }
    r.splice(r.end(), l, it, l.end()); // O(1)
  };
  int k = heights.size();
  for (bool done = false; !done;) { // O(n*k)
    done = true;
    for (int i = 1; i < k; i++) {
      auto &l = shelves[i - 1], &r = shelves[i];
      auto lc = l.size(), rc = r.size();
      if (lc > rc) {
        int c = (lc - rc + 1) / 2;
        f(l, r, c);
        g(l, r, c);
        done = done && lc == l.size();
      }
    }
  }
  int m = 0;
  for (auto &s : shelves) { // O(k)
    m = max<int>(m, s.size());
  }
  cout << k << ' ' << m << endl;
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
