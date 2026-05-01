# Find First or Last Occurrence in Sorted Array

## Problem
Given a sorted array `nums` (with possible duplicates) and a `target`, return `[first, last]` where:
- **first** = the smallest index `i` with `nums[i] == target`
- **last**  = the largest  index `i` with `nums[i] == target`

If `target` doesn't appear, return `[-1, -1]`.

**Examples**
```
nums = [2, 4, 4, 4, 7], target = 4   ->  [1, 3]
nums = [2, 4, 4, 4, 7], target = 2   ->  [0, 0]
nums = [2, 4, 4, 4, 7], target = 5   ->  [-1, -1]
nums = [1, 1, 1, 1, 1], target = 1   ->  [0, 4]
```

---

## Approach — Two Binary Searches via a Shared Helper

Both queries share structure — only the direction we move *after a match* flips. The solution wraps both in `util(nums, x, isFirst)`:

```
On every step:
  if nums[mid] == x:
      result = mid                       // candidate
      if isFirst:  high = mid - 1        // try to find an earlier match
      else:        low  = mid + 1        // try to find a later match
  else if nums[mid] < x:  low  = mid + 1 // go right
  else:                   high = mid - 1 // go left
```

`result = -1` initialization handles the "not found" case automatically.

### Why this works
The predicate "`nums[mid] >= target`" is monotonic on a sorted array, and so is "`nums[mid] > target`". The first occurrence is the leftmost index where the first predicate flips true; the last occurrence is one before the leftmost index where the second flips true. This solution finds both directly by saving on equality and continuing in the chosen direction.

> **Equivalent shortcut:** `first = lowerBound(target)` and `last = upperBound(target) - 1` (when the result lies in range). The two helpers from problems 02–03 give the same answer in two lines.

---

## Complexity
| | |
|---|---|
| **Time** | `O(log n)` — two independent binary searches |
| **Space** | `O(1)` aux. *(See note below.)* |

> **Minor inefficiency:** `util` takes `nums` by value — each call copies the whole vector. Switching to `const vector<int>& nums` removes the copy without changing the algorithm.

---

## Trace — `nums = [2, 4, 4, 4, 7]`, `target = 4`

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

→ Result: `[1, 3]` ✓

---

## Common Bugs to Avoid
- **Returning `mid` immediately on equality.** That gives *some* match but not necessarily the first or last — you have to keep searching.
- **Forgetting `result = -1` init.** Without it, the "not found" output is undefined.
- **Sliding `low`/`high` by `mid` instead of `mid ± 1`** in this `<=` style — causes infinite loops at `low == high`.
- **Computing `last = first + count − 1`** as a shortcut — that requires you to *also* compute count, which is exactly what `upperBound − lowerBound` gives you. Just do the second binary search.

---

## Bonus — One-Liner via Lower / Upper Bound
If problems 02 and 03 are imported, this whole problem collapses to:

```cpp
int first = lowerBound(nums, target);
int last  = upperBound(nums, target) - 1;
if (first == (int)nums.size() || nums[first] != target) return {-1, -1};
return {first, last};
```

Same `O(log n)` time, fewer custom branches.

---

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
