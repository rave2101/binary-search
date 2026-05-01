# Search Insert Position

## Problem
Given a sorted array `nums` of distinct integers and a `target`, return:
- the **index of `target`** if it exists, or
- the **index where it would be inserted** while keeping the array sorted.

**Examples**
```
nums = [1, 3, 5, 6], target = 5  ->  2     (found at index 2)
nums = [1, 3, 5, 6], target = 2  ->  1     (would insert between 1 and 3)
nums = [1, 3, 5, 6], target = 7  ->  4     (would append at the end)
nums = [1, 3, 5, 6], target = 0  ->  0     (would prepend)
```

---

## Approach — Binary Search (= Lower Bound)

The "insert position" is precisely the **lower bound** of `target` — the smallest index `i` with `nums[i] >= target`. So this problem is the same algorithm as `lowerBound` from problem 02.

This implementation adds one micro-optimization: an early `return mid` when `nums[mid] == target` so equal elements don't have to bubble down to the end of the loop.

```
1. result = n               // "would insert at end" default
2. while low <= high:
     mid = low + (high - low) / 2
     if nums[mid] == target  -> return mid           (early exit)
     if nums[mid] <  target  -> low  = mid + 1       (go right)
     else                    -> result = mid;
                                high   = mid - 1     (candidate, go left)
3. return result
```

### Why early-exit is safe here
The problem says the input contains **distinct** integers. So when `nums[mid] == target`, no smaller index can also equal `target` — returning immediately is correct.

> If duplicates were allowed and the problem asked for the **first** occurrence, drop the early return and rely on lower bound's "save and keep going left" behavior.

---

## Complexity
| | |
|---|---|
| **Time** | `O(log n)` |
| **Space** | `O(1)` |

---

## Trace — `nums = [1, 3, 5, 6]`, `target = 2`

| iter | low | high | mid | nums[mid] | branch | result |
|---|---|---|---|---|---|---|
| start | 0 | 3 | — | — | — | 4 |
| 1 | 0 | 3 | 1 | 3 | `>2` → save, go left | **1** |
| 2 | 0 | 0 | 0 | 1 | `<2` → go right | 1 |
| 3 | 1 | 0 | — | — | exit | **1** |

## Trace — `nums = [1, 3, 5, 6]`, `target = 7`

| iter | low | high | mid | nums[mid] | branch | result |
|---|---|---|---|---|---|---|
| start | 0 | 3 | — | — | — | 4 |
| 1 | 0 | 3 | 1 | 3 | `<7` → go right | 4 |
| 2 | 2 | 3 | 2 | 5 | `<7` → go right | 4 |
| 3 | 3 | 3 | 3 | 6 | `<7` → go right | 4 |
| 4 | 4 | 3 | — | — | exit | **4** |

`result` was never updated — it stayed at the initial `n = 4`, exactly the "insert at the end" case.

---

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
