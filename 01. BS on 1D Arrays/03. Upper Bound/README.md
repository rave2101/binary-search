# Upper Bound

## Problem

Given a sorted array `nums` and an integer `x`, return the **smallest index `i`** such that `nums[i] > x` (strictly greater). If no such index exists, return `n`.

Same contract as `std::upper_bound` — the position *just past* the last occurrence of `x`.

```
nums = [1, 2, 3, 3, 5], x = 3   →  4     (first index strictly > 3 is the 5)
nums = [1, 2, 3, 3, 5], x = 4   →  4     (5 is the first > 4)
nums = [1, 2, 3, 3, 5], x = 5   →  5     (no element > 5)
nums = [1, 2, 3, 3, 5], x = 0   →  0     (every element > 0)
```

---

## The Core Insight

The predicate `nums[i] > x` is monotonic on a sorted array — once true, stays true. The array splits into a `false` prefix and a `true` suffix:

```
nums = [1, 2, 3, 3, 5], x = 3
         F  F  F  F  T
                     ^
                     upper bound
```

Binary search lands on the leftmost `true` index. The only difference from lower bound is the strict `>` (vs. `>=`), which slides the boundary one position to the right whenever `x` is present in the array.

---

## Approach — Iterative Binary Search with Candidate Tracking

```cpp
int upperBound(vector<int>& nums, int x) {
    int n = nums.size();
    int low = 0, high = n - 1, result = n;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] > x) {
            result = mid;
            high = mid - 1;
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
mid=2  nums[2]=3  <=3  → go right
mid=3  nums[3]=3  <=3  → go right
mid=4  nums[4]=5   >3  → save, go left          result = 4
exit                                            return 4
```

---

## Lower Bound vs Upper Bound

The implementations are identical except for one comparison:

| Function | "Save candidate" predicate |
|---|---|
| `lowerBound(x)` | `nums[mid] >= x` |
| `upperBound(x)` | `nums[mid]  > x` |

A useful identity that falls out:

```
count of x in nums = upperBound(x) - lowerBound(x)
```

When `x` is absent both bounds collapse to the same insertion point, so the difference is `0`.

---

## Common Bugs

### 1. Using `<` instead of `<=` in the "go right" branch

```cpp
// WRONG — equal values get misrouted, breaks on duplicates
if (nums[mid] < x) low = mid + 1;

// CORRECT — equal values must go right (we want strictly >)
if (nums[mid] <= x) low = mid + 1;
```

On a duplicate-free array this happens to behave like lower bound on integer inputs, but on duplicates it returns the wrong index.

### 2. Forgetting `result = n`

```cpp
// WRONG — undefined when x >= max(nums)
int result;

// CORRECT
int result = n;
```

### 3. `high = mid` in a `<=` style loop

Same trap as lower bound — produces an infinite loop at `low == high`. Use `high = mid - 1`.

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Iterative | O(log n) | O(1) |
