# Implement Lower Bound

## Problem
Given a sorted array `nums` and an integer `x`, return the **smallest index `i`** such that `nums[i] >= x`. If no such index exists, return `n` (the array length).

This is the same contract as `std::lower_bound` — the position where `x` *would* be inserted while keeping the array sorted.

**Examples**
```
nums = [1, 2, 3, 3, 5], x = 3  ->  2     (first index with value >= 3)
nums = [1, 2, 3, 3, 5], x = 4  ->  4     (first index with value >= 4 is the 5)
nums = [1, 2, 3, 3, 5], x = 6  ->  5     (no element >= 6, return n)
nums = [1, 2, 3, 3, 5], x = 0  ->  0     (every element >= 0)
```

---

## Approach — Iterative Binary Search with Candidate Tracking

Initialize `result = n` so that "no element satisfies the condition" naturally falls out.

At each step:
1. `mid = low + (high - low) / 2` (overflow-safe).
2. If `nums[mid] >= x` → `mid` is a **valid candidate**. Save it (`result = mid`) and try to find an *earlier* one by moving `high = mid - 1`.
3. Otherwise (`nums[mid] < x`) → `mid` and everything to its left are useless → `low = mid + 1`.
4. Loop until `low > high`. Return `result`.

### Why this works
The condition `nums[mid] >= x` is **monotonic** on a sorted array: once it becomes true, it stays true for every larger index. Binary search on this monotonic predicate gives us the leftmost true position — exactly the lower bound.

### Why initialize `result = n`
If `x` is greater than every element, the `nums[mid] >= x` branch never fires and `result` is never assigned. Initializing to `n` encodes the "not found / would be inserted at the end" case directly.

---

## Complexity
| | |
|---|---|
| **Time** | `O(log n)` — halves the search space each iteration |
| **Space** | `O(1)` — iterative, no recursion stack |

---

## Trace — `nums = [1, 2, 3, 3, 5]`, `x = 3`

| iter | low | high | mid | nums[mid] | branch | result |
|---|---|---|---|---|---|---|
| start | 0 | 4 | — | — | — | 5 |
| 1 | 0 | 4 | 2 | 3 | `>=3` → save, go left | **2** |
| 2 | 0 | 1 | 0 | 1 | `<3` → go right | 2 |
| 3 | 1 | 1 | 1 | 2 | `<3` → go right | 2 |
| 4 | 2 | 1 | — | — | exit (low > high) | **2** |

---

## Common Bugs to Avoid
- **Forgetting to initialize `result = n`** — if `x` is larger than all elements, you return whatever garbage `result` held.
- **Using `nums[mid] > x` instead of `>=`** — that gives you *upper bound*, not lower bound.
- **`(low + high) / 2`** — can overflow for large arrays; the subtractive form avoids it.
- **`high = mid` instead of `mid - 1`** in this `<=` style loop — causes infinite loops when `low == high`.

---

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
