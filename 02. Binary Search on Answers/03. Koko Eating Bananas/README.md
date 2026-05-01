# Koko Eating Bananas

## Problem

Koko has `n` piles of bananas (`piles[i]` bananas in pile `i`) and `h` hours before the guards return. Each hour she picks one pile and eats up to `k` bananas from it; if the pile has fewer than `k`, she eats the rest and stops for that hour (no carry-over). Return the **minimum integer `k`** such that she finishes all piles within `h` hours.

```
piles = [3, 6, 7, 11], h = 8         → 4
piles = [30, 11, 23, 4, 20], h = 5   → 30   (one pile per hour, k must clear the biggest)
piles = [30, 11, 23, 4, 20], h = 6   → 23
```

---

## The Core Insight

Define `hours(k) = sum over piles of ceil(p / k)` — the time Koko takes at rate `k`. Two facts:

1. `hours(k)` is **monotonically non-increasing** in `k`. Faster eating never costs more time.
2. The feasibility predicate `hours(k) ≤ h` is therefore **monotonic**: false for small `k`, true once `k` is big enough, and stays true.

So the valid `k`'s form a sorted boolean tail `F F F … F T T T`. Binary search for the **leftmost T**.

```
k:           1   2   3   4   5   6   ...   max(piles)
hours(k):   27  14  10   8   7   6
≤ 8 ?        F   F   F   T   T   T
                         ^
                         answer = 4
```

The search bounds are `[1, max(piles)]`: rate 0 is meaningless, and any `k > max(piles)` finishes every pile in 1 hour — no faster than `k = max(piles)`.

---

## Approach — Binary Search on the Rate

1. `low = 1`, `high = max(piles)`.
2. For each `mid`, compute `hours(mid)` using ceiling division `(p + mid - 1) / mid`.
3. If `hours(mid) > h`: too slow → `low = mid + 1`.
4. Otherwise feasible → record `result = mid`, push `high = mid - 1` to look for something smaller.

### Why the ceiling-division form

`(p + k - 1) / k` is the textbook integer-ceiling of `p / k` without floating point. The alternative `p / k + (p % k != 0)` works too but does two ops; the `+k-1` form is one add then one divide.

### Why `hours` returns `long long`

`piles[i]` can be up to `10^9` and there can be up to `10^4` piles. The sum of ceilings at `k = 1` is bounded by `sum(piles)`, which fits in `long long` but not `int`. Returning `int` from `hours` would overflow on adversarial inputs.

---

## Complexity
| | |
|---|---|
| **Time** | `O(n · log(max(piles)))` — `log M` binary search steps, each scans all `n` piles |
| **Space** | `O(1)` |

---

## Trace — `piles = [3, 6, 7, 11], h = 8`

`max = 11`, so `low = 1, high = 11`.

| iter | low | high | mid | hours(mid) | branch |
|---|---|---|---|---|---|
| 1 | 1  | 11 | 6 | `1+1+2+2 = 6` | `≤ 8` → result = 6, high = 5 |
| 2 | 1  | 5  | 3 | `1+2+3+4 = 10` | `> 8` → low = 4 |
| 3 | 4  | 5  | 4 | `1+2+2+3 = 8`  | `≤ 8` → result = 4, high = 3 |
| 4 | 4  | 3  | — | loop ends | **return 4** |

---

## Common Bugs to Avoid

### 1. Using `int` for the hours accumulator

```cpp
// WRONG — sum of ceilings can exceed INT_MAX when k is small
int result = 0;
for (int& num : nums) result += (num + X - 1) / X;
```

The individual term `(num + X - 1) / X` is at most `num`, but summed across `~10^4` piles of size `~10^9` it overflows `int` easily. Use `long long`.

### 2. `(num + X - 1)` itself overflowing

For `num` near `INT_MAX` and `X = 1`, `num + X - 1` overflows `int`. Safer to cast: `((long long)num + X - 1) / X`. The current code dodges this only because the constraints keep `num ≤ 10^9 < INT_MAX − 1`.

### 3. Setting `high` too high

`high = INT_MAX` works but wastes ~20 iterations. `high = max(piles)` is the tight bound — any larger `k` gives identical hours (always 1 per pile).

### 4. Forgetting `result` is uninitialized on infeasible inputs

If somehow `hours(max(piles)) > h` (i.e. `n > h`, no valid rate exists), `result` is never assigned and the function returns garbage. The problem guarantees `n ≤ h`, so it's fine here — but worth noting. Initializing `result = high` defensively is a one-character safety net.

### 5. Linear scan instead of binary search

The naive `for k = 1 to max(piles)` is `O(n · max(piles))` — up to `10^13` ops. Times out instantly. The whole point is the monotonic predicate.

---

## Compile & Run

```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
