# Binary Search on Answers

Instead of binary searching over an input array, we binary search over the **range of possible answers**.

The pattern applies whenever:
1. The answer is an integer in some bounded range `[low, high]`.
2. There's a feasibility predicate `check(x)` that's **monotonic** — once it flips from false to true (or true to false) as `x` grows, it stays flipped.

Then the valid answers form a sorted boolean tail like `F F F … T T T`, and we binary search for the boundary. Typical `check(x)` asks "can we do the task using `x` as the rate / capacity / day / divisor?" — computed in `O(n)` per call.

```
x:        low …                              high
check:     F   F   F   F   T   T   T   T   T
                           ^
                           leftmost true = minimum valid answer
```

**Time complexity** is generally `O(n · log(range))` — a `log` factor over the answer range, with each step doing a linear feasibility check.

Problems from Striver's A2Z Sheet — *Step 4.2: Binary Search on Answers*.

| # | Problem |
|---|---|
| 1 | Find square root of a number in log n |
| 2 | Find the Nth root of a number using binary search |
| 3 | Koko Eating Bananas |
| 4 | Minimum days to make M bouquets |
| 5 | Find the Smallest Divisor |
| 6 | Capacity to Ship Packages within D Days |
| 7 | Kth Missing Positive Number |
| 8 | Aggressive Cows |
| 9 | Book Allocation Problem |
| 10 | Split Array — Largest Sum |
| 11 | Painter's Partition |
| 12 | Minimize Max Distance to Gas Station |
| 13 | Median of 2 Sorted Arrays |
| 14 | Kth element of 2 Sorted Arrays |
