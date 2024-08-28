/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using namespace placeholders;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init();
#endif

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;
using Chr = Num<char>;

struct Str : string {
  Str() { cin >> *this; }
};

template <typename T> struct SegTree {
  int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  SegTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(2 * n, val) {}
  const T &full() const { return nodes[1]; }    // O(1)
  T &operator[](int i) { return nodes[i + n]; } // O(1)
  T query(int l, int r) const { return _check(l, r), _query(l + n, r + n); }
  void update(int i, bool single) { _check(i, i), _build(i + n, single); }
  void _build(int i, bool single) { // O(log n) / [0, i] O(n)
    function<void()> dec[] = {[&]() { i--; }, [&]() { i >>= 1; }};
    for (i >>= 1; i > 0; dec[single]()) {
      _merge(i);
    }
  }
  T _query(int l, int r) const { // [l, r] O(log n)
    return l == r   ? _node(l)
           : l & 1  ? f(_node(l), _query(l + 1, r))
           : ~r & 1 ? f(_query(l, r - 1), _node(r))
                    : _query(l >> 1, r >> 1);
  }
  virtual T _node(int i) const { return nodes[i]; }
  void _merge(int i) { nodes[i] = f(_node(i << 1), _node(i << 1 | 1)); }
  void _check(int l, int r) const { assert(l >= 0 && l <= r && r < n); }
};

template <typename T, typename U> struct LazySegTree : SegTree<T> {
  vector<U> lazy;
  function<T(const T &, const U &)> ftree;
  function<U(const U &, const U &)> flazy;
  LazySegTree(int n, auto &&f, auto &&ft, auto &&fl, T val = {}, U lazyval = {})
      : SegTree<T>(n, f, val), ftree(ft), flazy(fl), lazy(2 * n, lazyval) {}
  using SegTree<T>::update;
  void update(int l, int r, const U &val) { // [l, r] O(log n)
    this->_check(l, r);
    _apply(l + this->n, r + this->n, val);
    this->_build(l + this->n, true);
    this->_build(r + this->n, true);
  }
  void _apply(int l, int r, const U &val) { // [l, r] O(log n)
    return l == r   ? _apply(l, val)
           : l & 1  ? (_apply(l, val), _apply(l + 1, r, val))
           : ~r & 1 ? (_apply(r, val), _apply(l, r - 1, val))
                    : _apply(l >> 1, r >> 1, val);
  }
  void _apply(int i, const U &val) { lazy[i] = flazy(lazy[i], val); }
  virtual T _node(int i) const { return ftree(this->nodes[i], lazy[i]); }

private:
  using SegTree<T>::query; // hide method (only full queries allowed)
};

template <typename T, typename U> struct PushSegTree : LazySegTree<T, U> {
  using LazySegTree<T, U>::LazySegTree;
  T query(int l, int r) { // [l, r] O(log n)
    this->_check(l, r);
    _push(l + this->n, true);
    _push(r + this->n, true);
    return this->_query(l + this->n, r + this->n);
  }
  void pushall(int i) { this->_check(i, i), _push(i + this->n, false); }
  void _push(unsigned i, bool single) { // O(log n) / [0, i] O(n)
    int s = bit_width(i), j = 0, end = single ? i : i / 2 + 1;
    function<void()> inc[] = {[&]() { j++; }, [&]() { s--, j = i >> s; }};
    for (inc[single](); j != end; inc[single]()) {
      _pushone(j);
    }
    this->_build(i, single);
  }
  void _pushone(int i) {                  // O(1)
    if (this->lazy[i] != this->lazy[0]) { // requires operator<=>
      this->_apply(i << 1, this->lazy[i]);
      this->_apply(i << 1 | 1, this->lazy[i]);
      this->lazy[i] = this->lazy[0];
    }
  }
};

template <typename T, typename U> struct Lazy {
  bool set; // add by default
  U val;    // lazy value (T must be constructible from U)
  auto operator<=>(const Lazy &) const = default;
  T merge(const T &prev) const { return set ? T(val) : prev + val; }
  Lazy join(const Lazy &rhs) const {
    return {set || rhs.set, rhs.set ? rhs.val : U(val + rhs.val)};
  }
};

template <typename T, typename U>
struct AssignSegTree : PushSegTree<T, Lazy<T, U>> {
  AssignSegTree(int n, auto &&f, T val = {}, U lazyval = {})
      : PushSegTree<T, Lazy<T, U>>(n, f, bind(&Lazy<T, U>::merge, _2, _1),
                                   &Lazy<T, U>::join, val, {false, lazyval}) {}
  using SegTree<T>::update;
  void update(int l, int r, const U &val, bool set) { // [l, r] O(log n)
    this->_check(l, r);
    this->_push(l + this->n, true);
    this->_push(r + this->n, true);
    this->_apply(l + this->n, r + this->n, {set, val});
    this->_build(l + this->n, true);
    this->_build(r + this->n, true);
  }
};

struct Query {
  Int type, l, r;
  Chr c = 0;
  Query() {
    if (type == 1) {
      c = {};
    }
  }
};

struct Seg {
  char c;
  int cnt;
  Seg join(const Seg &rhs) const { return rhs; }
  Seg operator+(char c) const { return *this; }
};

void solve() {
  Str s;
  Int k, m;
  vector<Query> q(m);
  AssignSegTree<Seg, char> segtree(s.size(), &Seg::join);
  for (int i = 0; i < s.size(); i++) {
    segtree[i] = {s[i], 0};
  }
  vector<int> ans;
  for (auto &[type, l, r, c] : q) {
    if (type == 1) {
      segtree.update(l - 1, r - 1, c, true);
    } else {
      ans.push_back(segtree.query(l, r).cnt);
    }
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  solve();
}
