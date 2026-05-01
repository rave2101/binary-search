# Search in rotated sorted array-II

## Problem

Given a sorted array `nums` that may contain **duplicates** and has been rotated at some unknown pivot, and a target `k`, return whether `k` exists in `nums` (`true` / `false`).

This is the duplicates-allowed variant of problem 08. We only need a boolean — not the index — because with duplicates the answer index isn't unique.

```
nums = [2, 5, 6, 0, 0, 1, 2], k = 0   →  true
nums = [2, 5, 6, 0, 0, 1, 2], k = 3   →  false
nums = [1, 0, 1, 1, 1],       k = 0   →  true
nums = [3, 1, 2, 3, 3, 3, 3], k = 2   →  true
```

---

## The Core Insight

Problem 08 assumes `nums[low] <= nums[mid]` reliably tells us the left half is sorted. With duplicates that inference can break:

```
nums = [3, 1, 2, 3, 3, 3, 3]   low=0  mid=3  high=6
       3              3     3
       └── nums[low] = nums[mid] = nums[high] = 3 ──┘
```

The array **is** rotated (left half `[3, 1, 2, 3]` is not sorted), but the three sampled positions look identical, so the standard check is fooled.

When that ambiguous case shows up, the only safe move is to drop both endpoints by one and retry — both are equal to `nums[mid]` and `nums[mid] != k` was already checked, so neither can be the answer.

Whenever the triple-equality does **not** hold, problem 08's invariant holds again and the standard branches are sound.

---

## Approach — Problem 08 + a "Shrink Boundaries" Step

```cpp
bool searchInARotatedSortedArrayII(vector<int>& nums, int k) {
    int low = 0, high = nums.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == k) return true;

        if (nums[low] == nums[mid] && nums[mid] == nums[high]) {
            low++;  high--;  continue;             // ambiguous — shrink and retry
        }

        if (nums[low] <= nums[mid]) {              // LEFT half is sorted
            if (k >= nums[low] && k < nums[mid]) high = mid - 1;
            else                                  low  = mid + 1;
        }
        else {                                     // RIGHT half is sorted
            if (k > nums[mid] && k <= nums[high]) low  = mid + 1;
            else                                   high = mid - 1;
        }
    }
    return false;
}
```

**Time: O(log n) average, O(n) worst case | Space: O(1)**

The `O(n)` worst case (e.g. `[1, 1, …, 1, 0]` rotated) is unavoidable — no constant-size sample of indices can reveal the rotation point when most values are identical.

### Trace for `nums = [3, 1, 2, 3, 3, 3, 3]`, `k = 2`

```
low=0  high=6  mid=3  nums = [3, 3, 3]            triple-equal → shrink
low=1  high=5  mid=3  nums[1,3,5] = [1, 3, 3]     left sorted [1..3], 2 ∈ [1, 3) → go left
low=1  high=2  mid=1  nums[1,1,2] = [1, 1, 2]     left sorted [1..1], 2 ∉ [1, 1) → go right
low=2  high=2  mid=2  nums[2] = 2                 match → return true
```

---

## Common Bugs

### 1. Skipping the triple-equality check

Reusing problem 08 directly fails on `[1, 0, 1, 1, 1]` searching for `0` — `nums[low] <= nums[mid]` is true but the left half `[1, 0, 1]` isn't sorted, so the range check sends the search the wrong way.

### 2. Shrinking only one side

```cpp
// WRONG — wastes an iteration; on adversarial inputs can loop in the same ambiguous state
low++;

// CORRECT — both endpoints are equal to nums[mid] and already ruled out
low++;  high--;
```

### 3. Forgetting `continue`

```cpp
// WRONG — falls through into the sorted-half branch with stale boundaries
if (nums[low] == nums[mid] && nums[mid] == nums[high]) { low++; high--; }

// CORRECT
if (nums[low] == nums[mid] && nums[mid] == nums[high]) { low++; high--; continue; }
```

### 4. Returning the index

With duplicates the "index of `k`" isn't unique. The problem asks for a boolean — don't try to extend this solution to "first index of `k`"; that's a different (harder) problem.

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Iterative | O(log n) avg, O(n) worst | O(1) |
