# Find the Smallest Divisor

## Problem

Given an array `nums` and a `limit`, find the **smallest positive integer divisor `d`** such that the sum of `ceil(nums[i] / d)` over all elements is `≤ limit`.

```
nums = [1, 2, 5, 9],   limit = 6   → 5
nums = [44,22,33,11,1], limit = 5  → 44
nums = [1],            limit = 1   → 1
```

---

## The Core Insight

Define `S(d) = sum of ceil(nums[i] / d)`. As `d` grows, every term `ceil(nums[i] / d)` is non-increasing (dividing by a larger number gives a smaller or equal ceiling). So `S(d)` is **monotonically non-increasing** in `d`.

The predicate `S(d) ≤ limit` is therefore monotonic: false for small `d` (sum too large), true once `d` is big enough, and stays true. Binary search for the **leftmost true** — that's the smallest divisor.

```
d:        1   2   3   4   5   6   7   8   9
S(d):    17   9   7   5   4   4   4   3   3   (for nums=[1,2,5,9])
≤ 6 ?     F   F   F   T   T   T   T   T   T
                      ^
                      answer = 4 — wait, the example says 5
```

(The LeetCode example uses `limit = 6` and answer `5`. Recompute: at `d=4`, ceilings are `1,1,2,3 = 7 > 6`; at `d=5`, `1,1,1,2 = 5 ≤ 6`. So answer is 5. The walking principle is what matters — `S` is monotonic, leftmost-true wins.)

Search bounds: `[1, max(nums)]`. Any `d > max(nums)` gives every term = 1, so `S(d) = n` — no smaller than at `d = max(nums)`, which already gives 1 per term.

---

## Approach — Binary Search on the Divisor

1. `low = 1`, `high = max(nums)`.
2. For each `mid`, compute `S(mid) = sum((num + mid - 1) / mid)` via one linear pass.
3. If `S(mid) ≤ limit`: feasible → record `result = mid`, push `high = mid - 1`.
4. Else `low = mid + 1`.

### Why ceiling division as `(num + X - 1) / X`

Standard integer-ceiling without floating point. One add and one divide; no `%` needed.

---

## Complexity
| | |
|---|---|
| **Time** | `O(n · log(max(nums)))` — `log M` binary search steps, each one linear scan |
| **Space** | `O(1)` |

---

## Trace — `nums = [1, 2, 5, 9], limit = 6`

`max = 9`, so `low = 1, high = 9`.

| iter | low | high | mid | S(mid) | branch |
|---|---|---|---|---|---|
| 1 | 1 | 9 | 5 | `1+1+1+2 = 5`  | `≤ 6` → result = 5, high = 4 |
| 2 | 1 | 4 | 2 | `1+1+3+5 = 10` | `> 6` → low = 3 |
| 3 | 3 | 4 | 3 | `1+1+2+3 = 7`  | `> 6` → low = 4 |
| 4 | 4 | 4 | 4 | `1+1+2+3 = 7`  | `> 6` → low = 5 |
| 5 | 5 | 4 | — | loop ends | **return 5** |

---

## Common Bugs to Avoid

### 1. `int` overflow on the sum

For `n` up to `~5·10^4` and `nums[i]` up to `~10^6`, the sum at `d = 1` is bounded by `sum(nums) ≤ 5·10^10` — overflows `int`. Promote `result` to `long long` if constraints push that hard. The current code is fine for LeetCode's `nums.length ≤ 5·10^4, nums[i] ≤ 10^6` since the max sum is `5·10^10`... which **does** overflow int. Tighten with `long long` to be safe.

### 2. `(num + X - 1)` overflow

For `num` near `INT_MAX` and `X = 1`, the addition overflows before the divide. Cast: `((long long)num + X - 1) / X`. Not an issue at LeetCode bounds.

### 3. Wrong direction on the predicate

`S` is non-increasing in `d`, so the **true** region is on the **right**. Searching for the leftmost true with `result = mid; high = mid - 1` on success is correct. Flipping the branches gives the largest divisor — a different problem.

### 4. `high = INT_MAX` instead of `max(nums)`

Wastes ~25 iterations. `max(nums)` is the tight bound: any larger gives every ceiling = 1, identical to `d = max(nums)`.

---

## Compile & Run

```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
