# Search X in Sorted Array

## Problem
Given a sorted array of integers `nums` (0-based indexing), find the index of a target integer. If found, return its index; otherwise return `-1`.

**Example**
```
Input:  nums = [-1, 0, 3, 5, 9, 12], target = 9
Output: 4
```

---

## Approach — Recursive Binary Search

The array is sorted, so at each step we can throw away half the search space.

1. Pick the middle index `mid = low + (high - low) / 2`.
2. If `nums[mid] == target` → return `mid`.
3. If `nums[mid] > target` → answer (if any) lies strictly to the left → recurse on `[low, mid - 1]`.
4. Otherwise → recurse on `[mid + 1, high]`.
5. Base case: `low > high` means the window is empty → return `-1`.

### Why `low + (high - low) / 2` instead of `(low + high) / 2`?
For very large `low` and `high`, the sum can overflow a 32-bit `int`. The subtractive form computes the same midpoint without the risk.

---

## Complexity
| | |
|---|---|
| **Time** | `O(log n)` — search space halves each call |
| **Space** | `O(log n)` — recursion stack depth |

An iterative version would bring space to `O(1)`; the logic is identical, just a `while (low <= high)` loop.

---

## Trace — `nums = [-1, 0, 3, 5, 9, 12]`, `target = 9`

| Call | low | high | mid | nums[mid] | Action |
|---|---|---|---|---|---|
| 1 | 0 | 5 | 2 | 3  | 3 < 9 → go right |
| 2 | 3 | 5 | 4 | 9  | match → return **4** |

---

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
