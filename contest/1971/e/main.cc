#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef DEBUG
auto in = ifstream(filesystem::path(__FILE__).replace_filename("input.txt"));
auto &out = cout << fixed << setprecision(20);
#else
auto &in = (cin.tie(nullptr)->sync_with_stdio(false), cin);
auto &out = cout << fixed << setprecision(20);
#endif

void solve(int t)
{
  int n, k, q;
  in >> n >> k >> q;
  vector<int> a(k + 1), b(k + 1);
  for (int i = 1; i <= k; ++i)
    in >> a[i];
  for (int i = 1; i <= k; ++i)
    in >> b[i];
  for (int i = 0; i < q; ++i)
  {
    int q;
    in >> q;
    const auto j = prev(ranges::upper_bound(a, q)) - a.begin();
    if (j < a.size() - 1)
    {
      const auto r = b[j] + (q - a[j]) * ((b[j + 1] - b[j]) / double(a[j + 1] - a[j]));
      out << int(r) << ' ';
    }
    else
    {
      out << b.back() << ' ';
    }
  }
  out << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}