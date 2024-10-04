/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Sieve of Prime numbers (up to 2^32)
 */
struct Sieve : vector<int> {
  Sieve(int n, bool isval) { // max value or min count
    int mx = isval ? n : ceil(n * log(n * log(n + 1) + 1) + 1);
    vector<bool> vis(mx + 1);
    for (int i = 2; i <= mx; i++) { // O(mx*log log mx)
      if (!vis[i]) {
        push_back(i);
        for (int j = 2 * i; j <= mx; j += i) {
          vis[j] = true;
        }
      }
    }
  }
};

/**
 * Sieve of Small Prime numbers (up to 2^16) - ~13KB
 */
constexpr struct SmallPrimes : array<u16, 6542> {
  constexpr SmallPrimes() { // O(N*log log N) = O(2^18)
    array<bool, 1 << 16> vis = {};
    for (int i = 2, cnt = 0; i < vis.size(); i++) {
      if (!vis[i]) {
        (*this)[cnt++] = i;
        for (int j = 2 * i; j < vis.size(); j += i) {
          vis[j] = true;
        }
      }
    }
  }
} primes;

/**
 * Segmented Prime Sieve (from 2^16 up to 2^32)
 */
struct SegSieve : vector<int> {
  SegSieve(int mx) { // O(mx*log log mx)
    reserve(max<int>(0, mx / log(mx) - primes.size()));
    for (int l = 1 << 16; l <= mx; l += 1 << 16) {
      array<bool, 1 << 16> vis = {};
      for (auto p : primes) {
        for (int j = (p - (l % p)) % p; j < vis.size(); j += p) {
          vis[j] = true;
        }
      }
      for (int i = 0; i < vis.size(); i++) {
        if (!vis[i]) {
          push_back(l + i);
        }
      }
    }
  }
};

/**
 * Prime Factors of a number (up to 2^32) - ~51KB
 * https://en.algorithmica.org/hpc/algorithms/factorization/
 */
struct Factors : array<u64, 6542> {
  constexpr Factors() { // O(N*log log N) = O(2^18)
    for (int i = 0; i < size(); i++) {
      (*this)[i] = u64(-1) / primes[i] + 1;
    }
  }
  u32 find(u32 x) const { // O(min(6542,x/log x))
    for (auto m : *this) {
      if (m * x < m) {
        return u64(-1) / m + 1;
      }
    }
    return 1;
  }
};
