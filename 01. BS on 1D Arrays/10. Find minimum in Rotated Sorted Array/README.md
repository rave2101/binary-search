# Find minimum in Rotated Sorted Array

## Problem

Given a sorted array `nums` of **distinct** integers that has been rotated at some unknown pivot, return the minimum element. Required time complexity: `O(log n)`.

```
nums = [4, 5, 6, 7, 0, 1, 2]   →  0
nums = [3, 4, 5, 1, 2]         →  1
nums = [11, 13, 15, 17]        →  11   (no rotation)
nums = [2, 1]                  →  1
```

---

## The Core Insight

Same "one half is always sorted" invariant as problem 08. The sorted half's **minimum is its left endpoint** (no rotation inside that half), so we can read it off in `O(1)` and then throw the sorted half away — the global minimum is either that endpoint (already captured) or it lives in the other half.

```
nums = [4, 5, 6, 7, 0, 1, 2]   mid = 3 (nums[mid] = 7)

  left  [4, 5, 6, 7]   sorted ✓   min = 4   ← capture, discard
  right [7, 0, 1, 2]   contains rotation, search continues here
```

Each iteration halves the search space.

---

## Approach — Capture the Sorted Half's Endpoint, Discard the Half

```cpp
int findMin(vector<int>& nums) {
    int ans = INT_MAX;
    int low = 0, high = nums.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[low] <= nums[mid]) {              // LEFT half sorted
            ans = min({ans, nums[low], nums[mid]});
            low = mid + 1;                          // discard left
        }
        else {                                     // RIGHT half sorted
            ans = min({ans, nums[mid], nums[high]});
            high = mid - 1;                         // discard right
        }
    }
    return ans;
}
```

**Time: O(log n) | Space: O(1)**

The implementation passes `nums[low]`, `nums[mid]`, `nums[high]` all into the `min({...})` call. Strictly only the sorted-half endpoint is needed for correctness; the extras are harmless.

### No-rotation case

If the array is already sorted, the first iteration takes the left branch (whole array is sorted), captures `nums[0]` (the true minimum), and walks the search to the right. Every later half is also "sorted left", so `ans` never gets overwritten.

### Trace for `nums = [4, 5, 6, 7, 0, 1, 2]`

```
start                                          ans = INT_MAX
low=0  high=6  mid=3  nums[0,3,6]=[4,7,2]      left sorted [4..7]   capture 4   ans=4
low=4  high=6  mid=5  nums[4,5,6]=[0,1,2]      left sorted [0..2]   capture 0   ans=0
low=6  high=6  mid=6  nums[6,6,6]=[2,2,2]      left sorted [2..2]   capture 2   ans=0
exit                                           return 0
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

### 2. Capturing after shrinking

```cpp
// WRONG — discards the half whose endpoint you needed
low = mid + 1;
ans = min(ans, nums[low - 1]);

// CORRECT — capture first, then shrink
ans = min(ans, nums[low]);
low = mid + 1;
```

### 3. Initializing `ans = nums[0]`

Brittle — works on most standard inputs but `ans = INT_MAX` is the safe identity for `min`. Using `nums[0]` also subtly biases against ever updating when the rotation point lands exactly at `mid + 1` and the loop terminates early.

### 4. Applying this to arrays with duplicates

`[3, 3, 1, 3]` breaks the sorted-half inference (the same trap as problem 08 → 09). Handling needs the triple-equality shrink step from problem 09.

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Iterative | O(log n) | O(1) |
