# Lower Bound

## Problem

Given a sorted array `nums` and an integer `x`, return the **smallest index `i`** such that `nums[i] >= x`. If no such index exists, return `n` (the array length).

Same contract as `std::lower_bound` — the position where `x` would be inserted while keeping the array sorted.

```
nums = [1, 2, 3, 3, 5], x = 3   →  2     (first index with value >= 3)
nums = [1, 2, 3, 3, 5], x = 4   →  4     (first index with value >= 4 is the 5)
nums = [1, 2, 3, 3, 5], x = 6   →  5     (no element >= 6, return n)
nums = [1, 2, 3, 3, 5], x = 0   →  0     (every element >= 0)
```

---

## The Core Insight

The predicate `nums[i] >= x` is **monotonic** on a sorted array — once true, it stays true for every larger index. So the array splits into a `false` prefix followed by a `true` suffix:

```
nums = [1, 2, 3, 3, 5], x = 3
         F  F  T  T  T
                ^
                lower bound
```

Binary search drives toward the boundary — the leftmost `true` index — which is exactly the lower bound.

---

## Approach — Iterative Binary Search with Candidate Tracking

Save every valid `mid` into `result`, then keep pushing left to find an earlier one. Initialize `result = n` so the "no element satisfies" case falls out automatically.

```cpp
int lowerBound(vector<int>& nums, int x) {
    int n = nums.size();
    int low = 0, high = n - 1, result = n;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] >= x) {
            result = mid;
            high = mid - 1;          // try for an earlier index
        }
        else low = mid + 1;
    }
    return result;
}
```

**Time: O(log n) | Space: O(1)**

### Trace for `nums = [1, 2, 3, 3, 5]`, `x = 3`

```
start                                          result = 5
mid=2  nums[2]=3  >=3  → save, go left          result = 2
mid=0  nums[0]=1   <3  → go right
mid=1  nums[1]=2   <3  → go right
exit                                            return 2
```

---

## Common Bugs

### 1. Forgetting to initialize `result = n`

```cpp
// WRONG — leaves result unset when x > max(nums)
int result;

// CORRECT — encodes "would insert at end" as the default
int result = n;
```

If `x` exceeds every element, the `nums[mid] >= x` branch never fires and `result` is never assigned. Initializing to `n` makes the not-found case implicit.

### 2. Using `>` instead of `>=`

```cpp
// WRONG — this is upper bound, not lower bound
if (nums[mid] > x) { ... }

// CORRECT
if (nums[mid] >= x) { ... }
```

The `>` predicate finds the position *just past* the last `x`, not the first one.

### 3. `high = mid` in a `<=` style loop

```cpp
// WRONG — infinite loop when low == high and the branch keeps re-entering
high = mid;

// CORRECT
high = mid - 1;
```

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Iterative | O(log n) | O(1) |
