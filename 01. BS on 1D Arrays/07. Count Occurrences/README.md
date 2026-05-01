# Count Occurrences in Sorted Array

## Problem
Given a sorted array `arr` (with possible duplicates) and a `target`, return the number of times `target` appears.

If `target` doesn't appear, return `0`.

**Examples**
```
arr = [2, 4, 4, 4, 7], target = 4   ->  3
arr = [2, 4, 4, 4, 7], target = 2   ->  1
arr = [2, 4, 4, 4, 7], target = 5   ->  0
arr = [1, 1, 1, 1, 1], target = 1   ->  5
```

---

## Approach — `last − first + 1` via the Same Helper as Problem 06

This problem reuses the `util(nums, x, isFirst)` helper from problem 06 verbatim:

```
On every step:
  if nums[mid] == x:
      result = mid                       // candidate
      if isFirst:  high = mid - 1        // try to find an earlier match
      else:        low  = mid + 1        // try to find a later match
  else if nums[mid] < x:  low  = mid + 1
  else:                   high = mid - 1
```

Then the count is just:

1. `first = util(arr, target, true)` — leftmost match.
2. If `first == -1`, return `0` (target absent).
3. `last  = util(arr, target, false)` — rightmost match.
4. Return `last - first + 1`.

### Why this works
On a sorted array all occurrences of `target` form a contiguous run `[first .. last]`. The length of any contiguous integer range is `(last − first) + 1`. The early `-1` check is a guard so we don't run the second binary search (and don't subtract a sentinel `-1` from another sentinel).

> **Equivalent shortcut:** `count = upperBound(target) − lowerBound(target)`. Same `O(log n)` time, no early-exit guard needed — when `target` is absent, both bounds collide and the difference is `0`.

---

## Complexity
| | |
|---|---|
| **Time** | `O(log n)` — at most two binary searches |
| **Space** | `O(1)` aux. *(See note below.)* |

> **Minor inefficiency:** `util` takes `nums` by value — each call copies the whole vector. Switching to `const vector<int>& nums` removes the copy without changing the algorithm.

---

## Trace — `arr = [2, 4, 4, 4, 7]`, `target = 4`

### First occurrence
| iter | low | high | mid | nums[mid] | branch | result |
|---|---|---|---|---|---|---|
| start | 0 | 4 | — | — | — | -1 |
| 1 | 0 | 4 | 2 | 4 | `==` → save, go left | 2 |
| 2 | 0 | 1 | 0 | 2 | `<4` → go right | 2 |
| 3 | 1 | 1 | 1 | 4 | `==` → save, go left | **1** |
| 4 | 1 | 0 | — | — | exit | **1** |

### Last occurrence
| iter | low | high | mid | nums[mid] | branch | result |
|---|---|---|---|---|---|---|
| start | 0 | 4 | — | — | — | -1 |
| 1 | 0 | 4 | 2 | 4 | `==` → save, go right | 2 |
| 2 | 3 | 4 | 3 | 4 | `==` → save, go right | **3** |
| 3 | 4 | 4 | 4 | 7 | `>4` → go left | 3 |
| 4 | 4 | 3 | — | — | exit | **3** |

→ Count = `3 − 1 + 1 = 3` ✓

---

## Common Bugs to Avoid
- **Skipping the `first == -1` guard.** Without it, when `target` is absent both calls return `-1` and you compute `(-1) - (-1) + 1 = 1` — a wrong, non-zero count.
- **Using `last - first` (off by one).** A run from index 1 to 3 contains 3 elements, not 2.
- **Returning `mid` immediately on equality** in `util` — gives some match but not the boundary, so the count comes out too small.
- **Linear scan from `first`** to count duplicates — degrades to `O(n)` on inputs like `[1,1,1,…,1]`, defeating the whole point of binary search.

---

## Bonus — One-Liner via Lower / Upper Bound
If problems 02 and 03 are imported, the whole thing collapses to:

```cpp
int countOccurrences(vector<int>& arr, int target) {
    return upperBound(arr, target) - lowerBound(arr, target);
}
```

No `-1` sentinel, no guard — the difference is naturally `0` when the target is missing.

---

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
