# Minimum Days to Make M Bouquets

## Problem

`nums[i]` is the day flower `i` blooms. To make a bouquet you need `k` **adjacent** bloomed flowers. Return the minimum number of days you must wait to make `m` bouquets, or `-1` if it's impossible.

```
nums = [1,10,3,10,2],   k=3, m=1   → 3
nums = [7,7,7,7,12,7,7], k=3, m=2  → 12
nums = [1,10,3,10,2],   k=3, m=2   → -1   (only 5 flowers, need 6)
```

A flower is "available" on day `D` iff `nums[i] ≤ D`. Bouquets must use **contiguous** available flowers — a non-bloomed flower in the middle splits the run.

---

## The Core Insight

Let `f(D) = ` "number of bouquets buildable by day `D`". As `D` grows, more flowers become available; available runs only get longer (or stay the same), so `f(D)` is **monotonically non-decreasing**.

The predicate `f(D) ≥ m` is therefore monotonic: false for small `D`, true once enough flowers have bloomed, and stays true. Binary search for the **leftmost true**.

```
D:           1   2   3   4  ...  10
f(D):        0   0   1   1       2
≥ m=1 ?      F   F   T   T       T
                     ^
                     answer = 3
```

Search bounds: `[min(nums), max(nums)]` — before `min`, no flower is open (`f = 0`); past `max`, all flowers are open and `f` plateaus.

---

## Approach — Binary Search on the Day

1. **Feasibility guard**: if `k * m > n`, even with every flower bloomed there aren't enough flowers — return `-1`.
2. Binary search `D ∈ [min(nums), max(nums)]`.
3. For each `D`, count bouquets via one linear pass: walk the array tracking `count` of consecutive available flowers; when you hit a non-available one (or end), add `count / k` to `result` and reset.
4. If `f(D) ≥ m`: feasible → record and try smaller `high`. Else `low = mid + 1`.

### Why `count / k` per run

A maximal contiguous run of length `L` produces `floor(L / k)` bouquets — they're packed left-to-right, leftover `L mod k` flowers can't combine across the gap.

### Why initialize `result = high`

If `f(high) ≥ m` (which the `k*m ≤ n` guard guarantees in valid cases), `high` is itself a feasible answer and the search will only refine downward. Defensive but harmless.

---

## Complexity
| | |
|---|---|
| **Time** | `O(n · log(max − min))` — `log(range)` binary search steps, each one linear scan |
| **Space** | `O(1)` |

---

## Trace — `nums = [1,10,3,10,2], k=3, m=1`

`min = 1, max = 10`, guard `k*m = 3 ≤ 5` passes.

| iter | low | high | mid | f(mid) | branch |
|---|---|---|---|---|---|
| 1 | 1 | 10 | 5 | run lengths: `1,1,1` (only days `≤5` available are positions 0,2,4 — all isolated) → 0 | `< 1` → low = 6 |

Wait — re-examine. At `D = 5`: availability `[T, F, T, F, T]`. Runs of length 1, 1, 1 → `1/3 + 1/3 + 1/3 = 0`. Below.

| iter | low | high | mid | f(mid) | branch |
|---|---|---|---|---|---|
| 1 | 1  | 10 | 5 | 0 | low = 6 |
| 2 | 6  | 10 | 8 | 0 (still `[T,F,T,F,T]`) | low = 9 |
| 3 | 9  | 10 | 9 | 0 | low = 10 |
| 4 | 10 | 10 | 10 | 1 (all bloomed → run of 5 → `5/3 = 1`) | result = 10, high = 9 |

Returns `10`. (For `m = 1` with this array, day 3 isn't enough because positions form an isolated run of length 1 at index 2 — you need 3 *adjacent* bloomed flowers.)

---

## Common Bugs to Avoid

### 1. `k * m > n` overflow

`k` and `m` can each be up to `~10^9` in adversarial framings. The product overflows `int`. Use `(long long)k * m > n`. Current code is fine for LeetCode bounds (`k, m ≤ n ≤ 10^5`) but the cast is safer.

### 2. Forgetting the trailing `result += count / k`

The bouquets from the **last run** are only counted if you flush `count` after the loop. Dropping that line silently undercounts whenever the array ends on an available flower.

### 3. Searching `[1, max]` or `[0, max]`

Lower than `min(nums)` is wasted work — `f` is identically zero there. The tighter `low = min(nums)` saves `log(min)` iterations and makes the bounds carry meaning.

### 4. Treating non-adjacent available flowers as combinable

```cpp
// WRONG — counts total available, ignores adjacency
int avail = 0;
for (int x : nums) if (x <= D) avail++;
return avail / k;
```

Bouquets require **contiguous** flowers; the gap-splitting logic is the whole point of the problem.

### 5. Stray debug `cout` left in submission

The current code prints `mid` and `noBouquet` each iteration. Fine locally — strip before submitting to a judge.

---

## Compile & Run

```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
