# Find peak element

## Problem

Given an integer array `nums`, return the index of **any** peak element. A peak is an index `i` where `nums[i] > nums[i-1]` and `nums[i] > nums[i+1]`. By convention, `nums[-1] = nums[n] = -∞` (so endpoints can be peaks).

You may assume `nums[i] != nums[i+1]` for all valid `i` (no equal adjacent values). The array is **not** required to be sorted — it can have multiple peaks; return any one. Required time complexity: `O(log n)`.

```
nums = [1, 2, 3, 1]                          →  2          (nums[2]=3 is a peak)
nums = [1, 2, 1, 3, 5, 6, 4]                 →  1 or 5     (both are peaks)
nums = [1, 2, 1, 1, 4, 5, 6, 7, 1, 2, 3, 4]  →  1, 7, or 11
nums = [5, 4, 3, 2, 1]                       →  0          (endpoint peak)
```

---

## The Core Insight

Even though the whole array isn't monotonic, we can always find a peak by **walking uphill**. From any non-peak `mid`, at least one neighbor is greater — move toward that side and a peak is guaranteed to exist in that half.

Why? Both ends of the array are virtual `-∞`. If we keep climbing in the rising direction, the values either keep rising until we hit a peak, or they eventually drop — and the drop point is itself a peak. Either way:

```
nums[mid] > nums[mid-1]   ⇒   a peak exists in [mid, high]
nums[mid] < nums[mid-1]   ⇒   a peak exists in [low, mid-1]
```

Each step halves the window while preserving the invariant "a peak exists in `[low, high]`".

---

## Approach — "Climb Uphill" Binary Search

Pre-check the endpoints so the inner loop can dereference `mid - 1` and `mid + 1` without bounds guards.

```cpp
int findPeakElement(vector<int>& nums) {
    int n = nums.size();
    if (n == 1 || nums[0] > nums[1])         return 0;
    if (nums[n-1] > nums[n-2])               return n - 1;

    int low = 1, high = n - 2;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1])
            return mid;
        if (nums[mid] > nums[mid-1]) low  = mid + 1;   // climbing right
        else                         high = mid - 1;   // climbing left
    }
    return -1;
}
```

**Time: O(log n) | Space: O(1)**

### Trace for `nums = [1, 2, 1, 1, 4, 5, 6, 7, 1, 2, 1]`

```
Pre-checks: nums[0]=1 > nums[1]=2 ? no.   nums[10]=1 > nums[9]=2 ? no.
            → search on [1, 9]

low=1  high=9  mid=5  nums[4,5,6]=[4,5,6]   not a peak; rising right   → low = 6
low=6  high=9  mid=7  nums[6,7,8]=[6,7,1]   peak! return 7
```

→ `nums[7] = 7` is a peak.

---

## Common Bugs

### 1. No pre-checks before the loop

```cpp
// WRONG — out-of-bounds when a peak sits at index 0 or n-1
int low = 0, high = n - 1;

// CORRECT — handle endpoints up front
if (n == 1 || nums[0] > nums[1])  return 0;
if (nums[n-1] > nums[n-2])        return n - 1;
int low = 1, high = n - 2;
```

### 2. Climbing the wrong way

```cpp
// WRONG — descends, can land in a valley with no peak
if (nums[mid] > nums[mid-1]) high = mid - 1;

// CORRECT — go in the direction the values are rising
if (nums[mid] > nums[mid-1]) low  = mid + 1;
```

### 3. Trying to find the *largest* peak

This problem asks for *any* peak. Finding the global max needs `O(n)` — there's no way to shortcut a global comparison.

### 4. Assuming the array is sorted

No monotonicity assumption is needed — the climbing argument is what makes binary search work here. Several inputs look sorted-then-rotated, but the algorithm doesn't care.

### 5. Using `<=` instead of `<` in the comparisons

The problem guarantees no equal adjacent values, so equality doesn't matter on valid inputs. On adversarial inputs with plateaus, `<=` would silently send the search into a flat region with no peak. Strict `<` makes the algorithm fail loudly rather than wander.

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Iterative | O(log n) | O(1) |
