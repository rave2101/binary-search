# Search in rotated sorted array-I

## Problem

Given a sorted array `nums` of **distinct** integers that has been rotated at some unknown pivot, and a target `k`, return the index of `k` in `nums`. If `k` is not present, return `-1`.

The rotation means the array looks like `[A_p, A_{p+1}, …, A_{n-1}, A_0, A_1, …, A_{p-1}]` for some pivot `p`. Required time complexity: `O(log n)`.

```
nums = [4, 5, 6, 7, 0, 1, 2], k = 0   →  4
nums = [4, 5, 6, 7, 0, 1, 2], k = 3   →  -1
nums = [5, 1, 2, 3, 4],       k = 1   →  1
nums = [1],                   k = 0   →  -1
```

---

## The Core Insight

A rotated sorted array, when split at any `mid`, has **at least one half that is fully sorted**. We can identify which half is sorted in `O(1)`:

```
If nums[low] <= nums[mid]:   left half [low..mid] is sorted
otherwise:                   right half [mid..high] is sorted
```

Once we know the sorted half, we know its closed value range. Checking whether `k` lies in that range is another `O(1)` test, telling us which side to recurse into. Each step halves the window.

```
nums = [4, 5, 6, 7, 0, 1, 2], k = 0,  mid = 3 (nums[mid] = 7)

  left  [4, 5, 6, 7]   sorted ✓   range [4, 7)   0 ∉ range  → search RIGHT
  right [7, 0, 1, 2]   not sorted (contains rotation)
```

---

## Approach — Identify the Sorted Half, Then Decide

```cpp
int search(vector<int>& nums, int k) {
    int low = 0, high = nums.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == k) return mid;

        if (nums[low] <= nums[mid]) {                           // LEFT half is sorted
            if (k >= nums[low] && k < nums[mid]) high = mid - 1; // k in sorted left
            else                                  low  = mid + 1;
        }
        else {                                                  // RIGHT half is sorted
            if (k > nums[mid] && k <= nums[high]) low  = mid + 1; // k in sorted right
            else                                   high = mid - 1;
        }
    }
    return -1;
}
```

**Time: O(log n) | Space: O(1)**

### Why `<=` (not `<`) on the sorted-half check

The pivot can sit at the half's edge. Using `<=` on `nums[low]` (and `nums[high]` on the symmetric side) keeps single-element segments and exact-boundary cases in the correct branch.

### Why strict on one side of the range check

Inside the sorted left half, `k` must satisfy `nums[low] <= k < nums[mid]` — the upper bound is *strict* because `nums[mid]` was just checked and isn't equal to `k`. Mirror that on the right: `nums[mid] < k <= nums[high]`.

### Trace for `nums = [4, 5, 6, 7, 0, 1, 2]`, `k = 0`

```
low=0  high=6  mid=3  nums[mid]=7
  left  [4..7] sorted   k=0 in [4, 7)? no   → go right

low=4  high=6  mid=5  nums[mid]=1
  left  [0..1] sorted   k=0 in [0, 1)? yes  → go left

low=4  high=4  mid=4  nums[mid]=0
  match → return 4
```

---

## Common Bugs

### 1. Strict `<` on the sorted-half check

```cpp
// WRONG — drops the low == mid case (single-element window)
if (nums[low] < nums[mid]) { ... }

// CORRECT
if (nums[low] <= nums[mid]) { ... }
```

### 2. Wrong inequality on the range check

```cpp
// WRONG — k == nums[mid] was already handled by the early return,
//         so the upper bound must be strict here
if (k >= nums[low] && k <= nums[mid]) { ... }

// CORRECT
if (k >= nums[low] && k < nums[mid]) { ... }
```

### 3. Forgetting the `nums[mid] == k` early return

The algorithm still terminates without it, but the range checks rely on `nums[mid] != k` — drop the early return and the strict inequalities can misroute equal values.

### 4. Applying this to arrays with duplicates

```
[3, 1, 3, 3, 3]   nums[low] == nums[mid] == 3
```

The "left half is sorted" inference fails. That case needs an extra "shrink boundaries" step — handled in problem 09.

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Iterative | O(log n) | O(1) |
