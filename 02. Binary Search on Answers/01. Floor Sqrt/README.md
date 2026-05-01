# Floor Sqrt

## Problem

Given a non-negative integer `n`, return `floor(sqrt(n))` — the largest integer `x` such that `x * x <= n`. Required time complexity: `O(log n)`.

```
n = 0           →  0
n = 1           →  1
n = 28          →  5    (5*5 = 25 ≤ 28 < 36 = 6*6)
n = 36          →  6
n = 2147395600  →  46340
```

---

## The Core Insight

The predicate `mid * mid <= n` is **monotonic** over `mid ∈ [1, n]`: once it flips from true to false, it stays false. That makes the search space a sorted boolean sequence, so binary search applies — we're looking for the **last** `mid` where the predicate holds.

```
mid:        1   2   3   4   5   6   7   8   ...
mid*mid:    1   4   9  16  25  36  49  64
≤ 28 ?      T   T   T   T   T   F   F   F
                            ^
                            answer = 5 (rightmost T)
```

---

## Approach — Binary Search on the Answer

Track the best feasible `mid` seen so far in `result`. Whenever `mid*mid <= n`, the answer is at least `mid`, so record it and push `low` rightward to look for something bigger.

```cpp
int floorSqrt(int n) {
    if (n == 0 || n == 1) return n;
    int low = 1, high = n, result = 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        long long square = (long long)mid * mid;
        if (square == n) return mid;
        if (square > n)  high = mid - 1;
        else {
            result = mid;
            low = mid + 1;
        }
    }
    return result;
}
```

**Time: O(log n) | Space: O(1)**

A tighter starting `high = n / 2 + 1` (for `n ≥ 2`) shrinks the window, but `high = n` is fine — it adds at most one extra iteration.

### Trace for `n = 28`

```
low=1  high=28  mid=14  14*14=196  > 28   → high = 13
low=1  high=13  mid=7   7*7  =49   > 28   → high = 6
low=1  high=6   mid=3   3*3  =9    < 28   → result=3, low = 4
low=4  high=6   mid=5   5*5  =25   < 28   → result=5, low = 6
low=6  high=6   mid=6   6*6  =36   > 28   → high = 5
low=6  high=5   loop ends                 → return 5
```

---

## Common Bugs

### 1. `mid * mid` overflowing `int`

```cpp
// WRONG — for n near INT_MAX, mid can be ~46340, and mid*mid as int overflows
if (mid * mid > n) high = mid - 1;

// CORRECT — promote to long long before multiplying
long long square = (long long)mid * mid;
```

`(long long)(mid * mid)` is **also wrong** — the multiplication happens in `int` first and overflows before the cast.

### 2. `(low + high) / 2` overflowing

For large `n`, `low + high` can overflow `int`. Use `low + (high - low) / 2`.

### 3. Forgetting to record the candidate

Returning `low - 1` or `high` at the end works in clean binary searches, but only if the loop invariants are airtight. Tracking `result` on every successful step is the bug-resistant version — it makes the answer explicit.

### 4. Starting `low = 0`

Harmless here (the `n == 0` early return covers it), but `mid = 0` would force a special case for the `square == 0` branch. Cleaner to early-return 0/1 and binary search on `[1, n]`.

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Binary search on answer | O(log n) | O(1) |
