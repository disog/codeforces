#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef DEBUG
auto in = ifstream(filesystem::path(__FILE__).replace_filename("input"));
auto &out = cout << fixed << setprecision(20);
#else
auto &in = (cin.tie(nullptr)->sync_with_stdio(false), cin);
auto &out = cout << fixed << setprecision(20);
#endif

using Book = array<int, 2>;

void solve(int t) {
  int n;
  in >> n;
  vector<Book> books(n);
  for (int i = 0; i < n; ++i)
    in >> books[i][0] >> books[i][1];
  ranges::sort(books);
  vector<int> heights;
  greater<int> comp;
  for (auto &book : books) {
    auto it = ranges::lower_bound(heights, book[1], comp);
    if (it == heights.end())
      heights.push_back(book[1]);
    else
      *it = book[1];
  }
  out << heights.size() << endl;
}

int main() {
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}