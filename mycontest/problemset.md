# My Contest

## A. Absecutive

- Category: Math Teaser
- Expected difficulty: 500
- Expected time complexity: $O(1)$

### Statement

Su is preparing a lesson on integer numbers for her students. She will give each student a **consecutive** number starting from $l$ and ending at $r$. Then, she will ask students to form **pairs** according to the following rule:

- two students can form a pair only if the **magnitudes** of their numbers differ by **one**.

In anticipation of the class, she wants to know how many (possibly **non-disjoint**) pairs could be formed.

### Input

The first line of input contains a single integer $t$ ($1 \le t \le 10^4$) - the number of test cases.

The only line of each test case contains two integers $l$ and $r$ ($-10^9 \le l \le r \le 10^9$) - the lower and upper bounds of the interval, respectively.

### Output

For each test case, output a single integer - the number of pairs of integers within the interval $[l, r]$, such that their magnitudes differ by one.

### Note

In the first test case, there can be no pairs.

In the second test case, only one pair can be formed, namely, $(0,1)$. Note that the pair $(1,0)$ is equivalent.

In the third test case, two pairs can be formed: $(-1,0)$ and $(0,1)$.

### Solution

First, notice that the result will have at least $r - l$ good pairs. Then, if $l < 0$ and $r > 0$, there will be additional pairs: one for each negative value whose magnitude is one less than a positive value; and another for each positive value that is one less than the magnitude of a negative value.

### Code

```cpp
int ans = r - l;
if (l < 0 && r > 0) {
  ans += min(-l, r - 1) + min(-l - 1, r);
}
```

## B1. Longest Interesting Subsequence (Easy)

- Category: Greedy
- Expected difficulty: 750
- Expected time complexity: $O(n\log n)$

### Statement

Su is preparing another lesson for her students. She will give each student a **distinct** number. Then, she will ask students to form groups according to the following rule:

- two or more students can form a group only if the difference between the **maximum** and **minimum** numbers in the group equals the group's **size**.

In anticipation of the class, she wants to know the size of the **largest** possible group.

### Input

The first line of input contains a single integer $t$ ($1 \le t \le 10^4$) - the number of test cases.

The first line of each test case contains a single integer $n$ ($1 \le n \le 2 \cdot 10^5$) - the number of students.

The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le 10^9$) - the number assigned to each student.

### Output

For each test case, output a single integer - the size of the largest group, such that the difference between its maximum and minimum elements equals its size; or $0$ if there is no such group.

### Note

In the first test case, there is no valid group.

In the second test case, the largest group is $\{3,5,6,7\}$.

### Solution

### Code

## B2. Longest Interesting Subsequence (Hard)

- Category: Greedy
- Expected difficulty: 1250
- Expected time complexity: $O(n\log n)$

### Statement

Su is preparing another lesson for her students. She will give each student an **arbitrary** number. Then, she will ask students to form groups according to the following rule:

- two or more students can form a group only if the difference between the **maximum** and **minimum** numbers in the group equals the group's **size**.

In anticipation of the class, she wants to know the size of the **largest** possible group.

### Input

The first line of input contains a single integer $t$ ($1 \le t \le 10^4$) - the number of test cases.

The first line of each test case contains a single integer $n$ ($1 \le n \le 2 \cdot 10^5$) - the number of students.

The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le 10^9$) - the number assigned to each student.

### Output

For each test case, output a single integer - the size of the largest group, such that the difference between its maximum and minimum elements equals its size; or $0$ if there is no such group.

### Note

In the first test case, the largest group is $\{5,5,9,9,10\}$. Note that the group $\{5,5,9,9\}$ is also valid, but smaller.

In the second test case, there are two largest groups, namely, $\{1,1,4,5\}$ and $\{4,5,8,8\}$.

### Solution

### Code

## C. Stringy

- Category: Strings
- Expected difficulty: 1500
- Expected time complexity: $O(n)$

### Statement

Su is eager to play a game with her students. She will give each student a copy of a string of lowercase Latin letters. Then, she will ask students to perform operations on their string, according to the following rule:

- a student can choose any **occurrence** of a letter which is not `'z'` and replace it with the subsequent letter of the alphabet.

After each operation, while two or more **adjecent** characters are equal, they are deleted from the string. Whoever makes their string **empty** in the least number of operations wins. In anticipation of the game, she wants to know the **least** number of operations required to make the string empty.

### Input

The first line of input contains a single integer $t$ ($1 \le t \le 10^4$) - the number of test cases.

The first line of each test case contains a single integer $n$ ($1 \le n \le 2 \cdot 10^5$) - the length of the string.

The second line of each test case contains a string $s$, consisting of lowercase Latin letters.

### Output

For each test case, output a single integer - the minimum number of operations required to make the string empty, according to the game rules; or $-1$ if it's impossible.

### Note

### Solution

### Code

## D. Tarzan

- Category: Trees, Graphs
- Expected difficulty: 2000
- Expected time complexity: $O(n \log n)$

### Statement

Tarzan is swinging trhough trees in a forest, when he suddenly hears a cry from his Ape friend in a tree far away. He wants to reach that tree as quickly as possible, whilst avoiding the ground. Relying on his abilities, Tarzan can perform the following move:

- swing from a tree to any other tree within a distance equal to the height of his **current** tree

Help him determine the **minimum** (Euclidean plane) distance required to travel from his initial tree to the Ape's tree.

### Input

The first line of input contains a single integer $t$ ($1 \le t \le 10^4$) - the number of test cases.

The first line of each test case contains a single integer $n$ ($1 \le n \le 2 \cdot 10^5$) - the number of trees in the forest.

Then follow $n$ lines of each test case, each with three integers $x_i$, $y_i$ and $h_i$ ($-10^9 \le x_i,y_i \le 10^9$, $1 \le h_i \le 10^9$) - the coordinates of the $i$-th tree, and its height. The first one is Tarzan's initial tree, while the last one is the Ape's tree.

### Output

For each test case, output a single integer - the minimum distance, rounded down, required to travel from Tarzan's initial tree to the Ape's tree; or $-1$ if it's impossible.

### Note

### Solution

### Code

## E1. Bookcase (Easy)

- Category: Sorting & Searching
- Expected difficulty: 1500
- Expected time complexity: $O(n \log n)$

### Statement

Li has a collection of books of various sizes (width and height), and wants to build a bookcase to store them. However, Li is very capricious: she wants books on any shelf to be ordered by size. I.e.:

- there **cannot** be two adjacent books such that one is larger in width **and** smaller in height than the other (or _vice versa_).

In order to save money on materials, she wants to know the **least** number of shelves that the bookcase can have.

### Input

The first line of input contains a single integer $t$ ($1 \le t \le 10^4$) - the number of test cases.

The first line of each test case contains a single integer $n$ ($1 \le n \le 2 \cdot 10^5$) - the number of books.

Then follow $n$ lines of each test case, each with two integers $w_i$ and $h_i$ ($1 \le w_i,h_i \le 10^9$) - the width and height of the $i$-th book.

### Output

For each test case, output a single integer - the minimum number of shelves that the bookcase can have, such that it will accomodate all of the books and satisfy Li's whim.

### Note

### Solution

If we sort the books by width, then by height, we can safely ignore the width and see that the heights form a sawtooth pattern. When we take a book from this series, we can add it to the shelf whose top book has the closest height that is less than or equal to the current one. Once the height becomes less than the smallest height among all shelves so far, we need to create another shelf. This algorithm is also known as the longest (de/in)creasing subsequence (LIS).

### Code

```cpp
ranges::sort(a);
greater<int> gt;
vector<int> heights = {INT_MAX};
for (auto [w, h] : a) {
  if (h < heights.back()) {
    heights.push_back(h);
  } else {
    *ranges::lower_bound(heights, h, gt) = h;
  }
}
cout << heights.size() - 1 << endl;
```

## E2. Bookcase (Hard)

- Category: Combinatorial Optimization
- Expected difficulty: 2500
- Expected time complexity: $O(?)$

### Statement

Now that Li has determined the minimum number of shelves for her bookcase, she is eager to build it. However, she wants to save even more on materials, by minimizing the bookcase length. In order to do so, she needs to know the minimum length (in number of books) that the **longest** shelf can have.

### Input

The first line of input contains a single integer $t$ ($1 \le t \le 10^4$) - the number of test cases.

The first line of each test case contains two integers $n$ and $k$ ($1 \le n \le ?$, $1 \le k \le ?$) - the number of books and the number of shelves.

Then follow $n$ lines of each test case, each with two integers $w_i$ and $h_i$ ($1 \le w_i,h_i \le 10^9$) - the width and height of the $i$-th book.

### Output

For each test case, output a single integer - the minimum length that the longest shelf can have, such that the bookcase will accomodate all of the books and satisfy Li's whim.

### Note

### Solution

### Code