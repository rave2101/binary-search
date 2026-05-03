# Matrix Median

## Problem
Given an `R x C` matrix where each row is sorted and `R*C` is odd, return the median of all `R*C` elements.

```
[[1,3,5],[2,6,9],[3,6,9]] -> 5
[[1,4,9],[2,5,6],[3,7,8]] -> 5
[[1,3,8],[2,3,4],[1,2,5]] -> 3
```

## Approach
Binary search on the **answer value** (not on indices), since values lie in `[min(col 0), max(col C-1)]`.

1. `low = min over column 0`, `high = max over column C-1`.
2. Let `req = (R*C) / 2`. The median is the **(req+1)-th smallest** element — i.e., the smallest value `m` with `count(≤ m) > req`.
3. For each candidate `mid`, compute `countLessThanEqual(mid)` by running `upper_bound` on each row (`O(R log C)`).
4. If `count ≤ req`, median is larger → `low = mid + 1`. Else save `mid` as a candidate and try smaller → `high = mid - 1`.

**Predicate:** `count(≤ x) > req`. Monotone in `x`, so standard binary search applies.

## Complexity
- **Time:** `O(log(max - min) * R * log C)` — outer search over the value range, each step counts in `O(R log C)`.
- **Space:** `O(1)`.

## Why `count > req` and not `count >= req`

Median position is `(N/2 + 1)` from the bottom (1-indexed), where `N = R*C` is odd. With `req = N/2`, "at least `req+1` elements ≤ m" rewrites — since counts are integers — to `count(≤ m) > req`.

Worked example on the sorted view `[1,2,3,4,5,6,7,8,9]`, `req = 4`, true median = 5:

| x | count(≤ x) | count > 4? |
|---|-----------|-----------|
| 4 | 4         | no        |
| 5 | 5         | **yes — first crossing → answer** |
| 6 | 6         | yes       |

Using `>= req` instead would return `4` (the 4th smallest), not the median.

## Common Bugs

- **`upperBound` initialized with `result = SIZE - 1`.** If every element in the row is `≤ X`, the `else` branch never runs and the function returns `SIZE - 1` instead of `SIZE`, undercounting that row by 1. Fix: initialize `result = SIZE`, or just `return low` (which naturally lands at the upper-bound index when the loop exits).
- **Wrong strictness in the predicate** (see section above).

## Template note — prefer "save in the valid branch" over "return low"

```cpp
if (count(≤ mid) > req) {  // condition mirrors the problem statement
    ans = mid;             // candidate found — try smaller
    high = mid - 1;
} else {
    low = mid + 1;
}
return ans;
```

Easier to recall under pressure than reasoning about where `low` ends up after the loop, because `ans` is only ever assigned when the predicate holds — by construction it's the best valid value seen.
