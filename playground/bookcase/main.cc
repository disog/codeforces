/**
 * Bookcase
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct Graph : vector<set<int>> {
  vector<array<Int, 2>> e;
  Graph(int n, int m = 0) : vector<set<int>>(n), e(m) {
    for (auto &[u, v] : e) {
      add(u, v);
    }
  }
  void add(int u, int v) {
    (*this)[u].insert(v);
    (*this)[v].insert(u);
  }
};

const greater<int> gt1;

int len1(auto &&b, int n, int k) {
  vector<int> s(k, -1), c(k);
  auto lte = [&](int i, int j) {
    return b[i][0] <= b[j][0] && b[i][1] <= b[j][1];
  };
  int ans = n;
  auto f = [&](auto &self, int i) -> void {
    if (i == n) {
      ans = min(ans, *ranges::max_element(c));
      return;
    }
    for (int j = 0; j < k; j++) {
      if (s[j] < 0 || lte(s[j], i)) {
        auto saved = s[j];
        s[j] = i, c[j]++;
        self(self, i + 1);
        s[j] = saved, c[j]--; // backtrack
      }
    }
  };
  f(f, 0);
  return ans;
}

int len2(auto &&b, int n, int k) {
  Graph g(n);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (b[i][1] <= b[j][1]) {
        g.add(i, j);
      }
    }
  }
  int m = (n + k - 1) / k;
  vector<bool> vis(n);
  for (int i = n - 1, c = k; i >= 0; i--) {
    if (!vis[i]) {
      vis[i] = true;
      if (c) {
        c--;
        int u = i;
        for (int s = m - 1; s > 0 && g[u].size(); s--) {
          auto v = *g[u].rbegin();
          while (g[v].size() && *g[v].rbegin() > v) {
            g[*g[v].rbegin()].erase(v);
            g[v].erase(prev(g[v].end()));
          }
          while (g[u].size()) {
            g[*g[u].rbegin()].erase(u);
            g[u].erase(prev(g[u].end()));
          }
          vis[v] = true;
          u = v;
        }
        while (g[u].size()) {
          g[*g[u].rbegin()].erase(u);
          g[u].erase(prev(g[u].end()));
        }
      } else {
        m++;
      }
    }
  }
  return m;
}

void solve(int t) {
  Int n;
  vector<array<Int, 2>> b(n);
  // int n = 10;
  // vector<array<int, 2>> b(n);
  // for (auto &&bi : b) {
  //   bi[0] = rand() % n + 1;
  //   bi[1] = rand() % n + 1;
  // }
  ranges::sort(b); // O(n*log n)
  vector<int> heights;
  for (int i = 0; i < n; i++) { // O(n*log n)
    int h = b[i][1];
    int j = ranges::lower_bound(heights, h, gt1) - heights.begin();
    if (j == heights.size()) {
      heights.push_back(h);
    } else {
      heights[j] = h;
    }
  }
  int k = heights.size();
  int l1 = len1(b, n, k);
  int l2 = len2(b, n, k);
  // assert(l1 == l2);
  cout << k << ' ' << l1 << ' ' << l2 << endl;
}

int main() {
#ifdef LOCAL
  using filesystem::path;
  freopen(path(__FILE__).replace_filename("input").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  // int t = 10;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}
