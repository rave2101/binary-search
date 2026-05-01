# Implement Upper Bound

## Problem
Given a sorted array `nums` and an integer `x`, return the **smallest index `i`** such that `nums[i] > x` (strictly greater). If no such index exists, return `n`.

This matches `std::upper_bound` — the position *just past* the last occurrence of `x`.

**Examples**
```
nums = [1, 2, 3, 3, 5], x = 3  ->  4     (first index strictly > 3 is the 5)
nums = [1, 2, 3, 3, 5], x = 4  ->  4     (5 is the first > 4)
nums = [1, 2, 3, 3, 5], x = 5  ->  5     (no element > 5)
nums = [1, 2, 3, 3, 5], x = 0  ->  0     (every element > 0)
```

---

## Approach — Iterative Binary Search

Same shape as lower bound, but the predicate flips to **strict** `>`:

1. Initialize `result = n` (handles the "no element > x" case).
2. `mid = low + (high - low) / 2`.
3. If `nums[mid] <= x` → `mid` is too small, the answer (if any) lies strictly to the right → `low = mid + 1`.
4. Else (`nums[mid] > x`) → `mid` is a valid candidate, save it and try for a smaller index → `result = mid; high = mid - 1`.
5. Loop until `low > high`. Return `result`.

### Why this works
The predicate `nums[mid] > x` is monotonic on a sorted array — once true, stays true. Binary search lands on the leftmost `true` index, which is the upper bound.

---

## Lower Bound vs Upper Bound — One-Line Difference

| Function | Predicate to "save and go left" |
|---|---|
| `lowerBound(x)` | `nums[mid] >= x` |
| `upperBound(x)` | `nums[mid] >  x` |

Everything else (initialization, loop, midpoint, return) is identical.

A useful identity:
```
count of x in nums = upperBound(x) - lowerBound(x)
```

---

## Complexity
| | |
|---|---|
| **Time** | `O(log n)` |
| **Space** | `O(1)` |

---

## Trace — `nums = [1, 2, 3, 3, 5]`, `x = 3`

| iter | low | high | mid | nums[mid] | branch | result |
|---|---|---|---|---|---|---|
| start | 0 | 4 | — | — | — | 5 |
| 1 | 0 | 4 | 2 | 3 | `<=3` → go right | 5 |
| 2 | 3 | 4 | 3 | 3 | `<=3` → go right | 5 |
| 3 | 4 | 4 | 4 | 5 | `>3` → save, go left | **4** |
| 4 | 4 | 3 | — | — | exit | **4** |

---

## Common Bugs to Avoid
- **Using `<` instead of `<=`** in `nums[mid] <= x` — would behave like lower bound on a non-duplicate array but break on duplicates.
- **Forgetting `result = n` init** — wrong answer when `x` is `>= max(nums)`.
- **Off-by-one with `high = mid` instead of `mid - 1`** — infinite loop in this `<=` style.

---

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
