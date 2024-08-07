## A. Absecutive

Two numbers are considered magnitude-consecutive if their magnitude differ by one. For example, the pairs $(1,2)$, $(-2,1)$, $(1,-2)$ and $(-1,-2)$ are all magnitude-consecutive. Given an interval $[l,r]$, count the magnitude-consecutive pairs from $l$ to $r$.

     0..1: (0,1)
     0..2: (0,1), (1,2)
    -1..1: (-1,0), (0,1)
    -1..2: (-1,0), (0,1), (1,2), (-1,2)
    -2..2: (-2,1), (-2,-1), (-1,0), (0,1), (1,2), (-1,2)

Solution:

```cpp
int ans = r - l;
if (l < 0 && r > 0) {
  ans += min(-l, r - 1) + min(-l - 1, r);
}
```

## B. Tarzan of The Apes

Tarzan is exploring the jungle when he suddenly encounters a series of lined up trees of integer heights. He now wants to travel from the first tree to the last one. Due to Tarzan's abilities, at each step he can perform one of the following actions:

1. Jump from tree $i$ to _any_ tree up to $i+a_i$.
2. Grab a vine from tree $i+1$ and swing _directly_ to tree $i+1+a_{i+1}$, if it exists.

Since all trees have positive height, it is guaranteed that Tarzan can reach the last tree. What is the minimum number of hops he can make?

## C1. Bookcase (Easy)

Bookcase with minimum number of shelves such that a shelf must hold books in non-decreasing size

## C2. Bookcase (Hard)

Bookcase with minimum width (number of books)
