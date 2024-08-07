## A. Absecutive

Two numbers are considered magnitude-consecutive if their magnitude differ by one. For example, the pairs $(1,2)$, $(-2,1)$, $(1,-2)$ and $(-1,-2)$ all fit this criteria. Given an interval $[l,r]$, count the magnitude-consecutive pairs from $l$ to $r$.

     0..1: (0,1)
     0..2: (0,1), (1,2)
    -1..1: (-1,0), (0,1)
    -1..2: (-1,0), (0,1), (1,2), (-1,2)
    -2..2: (-2,1), (-2,-1), (-1,0), (0,1), (1,2), (-1,2)

### Solution

First, notice that the result will have at least $r - l$ good pairs. Then, if $l < 0$ and $r > 0$, there will be additional pairs: one for each negative value whose magnitude is one less than a positive value; and another for each positive value that is one less than the magnitude of a negative value.

### Code

```cpp
int ans = r - l;
if (l < 0 && r > 0) {
  ans += min(-l, r - 1) + min(-l - 1, r);
}
```

Complexity: $O(1)$

## B. Tarzan of The Apes

Tarzan is exploring the jungle when he suddenly encounters a series of lined up trees of integer heights. He now wants to travel from the first tree to the last one. Due to Tarzan's abilities, at each step he can perform one of the following actions:

1. Jump from tree $i$ to _any_ tree up to $i+a_i$.
2. Grab a vine from tree $i+1$ and swing _directly_ to tree $i+1+a_{i+1}$, if it exists.

Since all trees have positive height, it is guaranteed that Tarzan can reach the last tree. What is the minimum number of hops he can make?

### Solution

We can create a DP vector that stores the minimum number of hops needed to reach a tree at each position. A naive implementation would have a $O(n^2)$ complexity because of the nested loop that evaluates the result of the first action. However, it can be improved by exploiting the fact that, at each position, we do not need to evaluate further positions that have already been evaluated.

Complexity: $O(n)$

### Code

```cpp
vector<int> dp(n, n - 1);
dp[0] = 0;
for (int i = 0, r = 1; r < n; i++) {
  for (; r < n && r <= i + a[i]; r++) {
    dp[r] = min(dp[r], dp[i] + 1);
  }
  int j = i + 1 + a[i + 1];
  if (j < n) {
    dp[j] = min(dp[j], dp[i] + 1);
  }
}
cout << dp[n - 1] << endl;
```

## C1. Bookcase (Easy)

Su has a collection of books of different sizes, each with an integer width and height $(w,h)$, and wants to build a bookcase to accomodate all of them. However, Su is very capricious: she wants books on a shelf to be ordered by size (i.e., either non-decreasing or non-increasing), such that no book is at the same time wider and shorter than its neighbour (or vice-versa). Su also wants to save on materials, so she wants to know the minimum number of shelves, $k_{min}$, that the bookcase can have.

### Solution

If we sort all books by width then height, we can safely ignore the width and see that the heights form a sawtooth pattern. When we take a book from this series, we can add it to the shelf whose top book has the closest height that is less than or equal to the current one. Once the height becomes less than the smaller height among all shelves so far, we need to create another shelf. This is known as the longest decreasing subsequence (reciprocal of LIS).

Complexity: $O(n \log n)$

### Code

```cpp
ranges::sort(a);
greater<int> gt;
vector<int> heights = {INT_MAX};
for (auto [w, h] : a) {
  if (heights.back() > h) {
    heights.push_back(h);
  } else {
    *ranges::lower_bound(heights, h, gt) = h;
  }
}
cout << heights.size() - 1 << endl;
```

## C2. Bookcase (Hard)

Now that Su knows $k_{min}$, the minimum number of shelves for her bookcase, she is eager to build it. However, she wants to save more on materials. Since Su has so many books of different sizes, she is taking the average book thickness and considering all books to have this same thickness. For simplicity, assume that it is $1$. Su wants to minimize the maximum number of books on a shelf, so that the bookcse will have the minimum possible lenght, $l_{min}$.

### Solution

### Code
