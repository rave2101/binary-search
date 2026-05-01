# Search X in sorted array

## Problem

Given a sorted array `nums` (0-based indexing) and an integer `target`, return the index of `target` if it exists, else return `-1`.

```
nums = [-1, 0, 3, 5, 9, 12], target = 9   →  4
nums = [-1, 0, 3, 5, 9, 12], target = 2   →  -1
nums = [1, 3, 5, 7, 9],      target = 1   →  0
nums = [1, 3, 5, 7, 9],      target = 9   →  4
```

---

## The Core Insight

The array is sorted, so a comparison at a single index splits it into two halves where the answer can live in **at most one** of them:

- If `nums[mid] == target` → done.
- If `nums[mid] > target` → the target, if present, is strictly to the **left**.
- If `nums[mid] < target` → the target, if present, is strictly to the **right**.

Each step throws away half the search space — `O(log n)` work.

---

## Approach 1 — Recursive Binary Search

Recurse on the half that can contain the target. Base case: empty window (`low > high`) → not found.

```cpp
int util(vector<int>& nums, int target, int low, int high) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if (nums[mid] == target) return mid;
    if (nums[mid] > target)  return util(nums, target, low, mid - 1);
    return util(nums, target, mid + 1, high);
}
```

**Time: O(log n) | Space: O(log n) call stack**

### Why `low + (high - low) / 2` instead of `(low + high) / 2`

For very large `low + high`, the sum can overflow a 32-bit `int`. The subtractive form computes the same midpoint without the risk.

### Trace for `nums = [-1, 0, 3, 5, 9, 12]`, `target = 9`

```
util(low=0, high=5)   mid=2   nums[2]=3   3 < 9   → recurse right
util(low=3, high=5)   mid=4   nums[4]=9   match   → return 4
```

---

## Approach 2 — Iterative Binary Search

Same logic with a loop — drops the recursion stack.

```cpp
int search(vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] > target)  high = mid - 1;
        else                     low  = mid + 1;
    }
    return -1;
}
```

**Time: O(log n) | Space: O(1)**

---

## Common Bugs

### 1. Overflow in midpoint

```cpp
// WRONG — overflows for large low + high
int mid = (low + high) / 2;

// CORRECT
int mid = low + (high - low) / 2;
```

### 2. Wrong loop condition / boundary update

```cpp
// WRONG — infinite loop when low == high
while (low < high) { ... high = mid; ... }

// CORRECT — single-element window is checked, then exits
while (low <= high) { ... high = mid - 1; ... }
```

The `<=` style requires `mid - 1` and `mid + 1` for the boundary updates; `mid` alone leaves the same element in the window forever.

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Recursive | O(log n) | O(log n) |
| Iterative | O(log n) | O(1) |
