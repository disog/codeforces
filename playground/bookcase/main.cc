#include <bits/stdc++.h>

using namespace std;

template <typename T = int> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
};

const greater<int> gt1;
const greater<array<int, 2>> gt2;
const auto lta2 = [](auto &lhs, auto &rhs) {
  return lhs[0] < rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
};

void solve(int t) {
  Num n;
  vector<array<Num<>, 2>> b(n);
  ranges::sort(b, lta2);
  vector<int> heights;
  vector<vector<int>> widths;
  for (auto &[w, h] : b) {
    auto i = ranges::lower_bound(heights, int(h), gt1) - heights.begin();
    if (i == heights.size()) {
      heights.push_back(h);
      widths.push_back({w});
    } else {
      heights[i] = h;
      widths[i].push_back(w);
    }
  }
  vector<array<int, 2>> lin;
  int k = heights.size();
  for (int i = 0; i < k; i++) {
    for (int j = widths[i].size() - 1; j >= 0; j--) {
      lin.push_back({widths[i][j], k - i});
    }
  }
  ranges::sort(lin, gt2);
  int m = 1;
  for (int i = 1, c = 1; i < lin.size(); i++) {
    lin[i][1] > lin[i - 1][1] ? c = 1 : c++;
    m = max<int>(m, c);
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
