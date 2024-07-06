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
  vector<vector<int>> widths;
  for (auto &[w, h] : b) { // O(n*log n)
    auto i = ranges::lower_bound(heights, int(h), gt1) - heights.begin();
    if (i == heights.size()) {
      heights.push_back(h);
      widths.push_back({w});
    } else {
      heights[i] = h;
      widths[i].push_back(w);
    }
  }
  vector<array<int, 2>> lin; // O(n*log n)
  int k = heights.size();
  for (int i = 0; i < k; i++) {
    for (int j = widths[i].size() - 1; j >= 0; j--) {
      lin.push_back({widths[i][j], k - i});
    }
  }
  ranges::sort(lin);
  vector<int> rows;
  int row = 0, last = 0;
  for (auto &[_, s] : lin) {
    if (s < last) {
      rows[row = 0]++;
    } else if (row == rows.size()) {
      rows.push_back(1);
    } else if (rows[row] < rows[0]) {
      rows[row]++;
    } else {
      row++;
    }
    last = s;
  }
  int m = max<int>(row + 1, rows.size());
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
