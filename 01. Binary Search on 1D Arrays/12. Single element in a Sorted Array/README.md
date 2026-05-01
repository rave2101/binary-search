# Single element in a Sorted Array

## Problem

Given a sorted array `nums` where every element appears **exactly twice** except for one that appears **exactly once**, return the single non-duplicate element. Required time complexity: `O(log n)`.

```
nums = [1, 1, 2, 3, 3, 4, 4, 8, 8]   →  2
nums = [3, 3, 7, 7, 10, 11, 11]      →  10
nums = [1]                           →  1
nums = [1, 2, 2]                     →  1
nums = [1, 1, 2]                     →  2
```

---

## The Core Insight

Before the singleton, every duplicate pair occupies positions `(even, odd)`. After the singleton, the alignment **flips** to `(odd, even)`:

```
nums = [1, 1, 2, 3, 3, 4, 4, 8, 8]
        0  1  2  3  4  5  6  7  8
        └──┘  ↑  └──┘  └──┘  └──┘
       even-odd  │   odd-even pairs
                 singleton at index 2
```

That flip is a monotonic predicate over the index space — `true` (aligned) before the singleton, `false` (misaligned) at and after it. Binary search drives toward the boundary.

At any `mid`, the parity-partner of `mid` (the other half of its pair, **if** alignment still holds) is:

- `nums[mid - 1]` when `mid` is odd
- `nums[mid + 1]` when `mid` is even

If that partner equals `nums[mid]`, alignment still holds → singleton is to the right. Otherwise → singleton is at `mid` or to the left.

---

## Approach — Parity-Based Binary Search

Pre-check the endpoints so the inner loop can dereference `mid - 1` and `mid + 1` without bounds guards.

```cpp
int singleNonDuplicate(vector<int>& nums) {
    int n = nums.size();
    if (n == 1 || nums[0] != nums[1])         return nums[0];
    if (nums[n-1] != nums[n-2])               return nums[n-1];

    int low = 1, high = n - 2;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] != nums[mid-1] && nums[mid] != nums[mid+1])
            return nums[mid];                 // landed exactly on the singleton

        if (mid % 2) {                        // odd mid: partner is mid - 1
            if (nums[mid-1] == nums[mid]) low  = mid + 1;   // aligned → go right
            else                          high = mid - 1;
        }
        else {                                // even mid: partner is mid + 1
            if (nums[mid+1] == nums[mid]) low  = mid + 1;
            else                          high = mid - 1;
        }
    }
    return -1;
}
```

**Time: O(log n) | Space: O(1)**

### Trace for `nums = [1, 1, 2, 3, 3, 4, 4, 8, 8]`

```
Pre-checks: nums[0]==nums[1] ✓   nums[8]==nums[7] ✓   → search on [1, 7]

low=1  high=7  mid=4 (even)
  partner = nums[5] = 4   != nums[4] = 3   → misaligned, go left

low=1  high=3  mid=2 (even)
  nums[1]=1, nums[2]=2, nums[3]=3   neither neighbor matches  → singleton
  return 2
```

---

## Cleaner One-Liner

The parity-partner of `mid` is `mid ^ 1` (XOR with 1 flips the last bit). The whole branching collapses:

```cpp
int low = 0, high = n - 1;
while (low < high) {
    int mid = low + (high - low) / 2;
    if (nums[mid] == nums[mid ^ 1]) low  = mid + 1;
    else                            high = mid;
}
return nums[low];
```

Same `O(log n)`, fewer branches, no endpoint pre-check needed.

---

## Common Bugs

### 1. No pre-checks before the loop

```cpp
// WRONG — singleton at index 0 or n-1 makes mid +/- 1 walk out of bounds
int low = 0, high = n - 1;

// CORRECT — handle endpoints up front, run loop on [1, n-2]
if (n == 1 || nums[0] != nums[1])  return nums[0];
if (nums[n-1] != nums[n-2])        return nums[n-1];
int low = 1, high = n - 2;
```

### 2. Confusing the parity rules

```cpp
// WRONG — at odd mid, partner is mid - 1, not mid + 1
if (mid % 2) {
    if (nums[mid+1] == nums[mid]) ...
}

// CORRECT
if (mid % 2) {
    if (nums[mid-1] == nums[mid]) ...
}
```

Swapping the partner direction inverts the alignment predicate and sends the search the wrong way.

### 3. Skipping the "exact match" check

Without `if (nums[mid] != nums[mid-1] && nums[mid] != nums[mid+1]) return nums[mid]`, the loop can step past the singleton and exit with `low > high`, returning `-1` even though the answer was just inspected.

### 4. Defaulting to XOR over the array

`O(n)` XOR works but ignores the sortedness. Interviewers asking this expect `O(log n)`.

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Parity-based BS | O(log n) | O(1) |
| `nums[mid] == nums[mid ^ 1]` BS | O(log n) | O(1) |
