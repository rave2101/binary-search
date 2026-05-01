# Count Occurrences in a Sorted Array

## Problem

Given a sorted array `arr` (with possible duplicates) and a `target`, return the number of times `target` appears. If `target` doesn't appear, return `0`.

```
arr = [2, 4, 4, 4, 7], target = 4   →  3
arr = [2, 4, 4, 4, 7], target = 2   →  1
arr = [2, 4, 4, 4, 7], target = 5   →  0
arr = [1, 1, 1, 1, 1], target = 1   →  5
```

---

## The Core Insight

On a sorted array, every occurrence of `target` forms a **contiguous run** `[first .. last]`. The count of any contiguous integer range is:

```
count = (last - first) + 1
```

So the problem reduces to finding `first` and `last` — exactly problem 06.

---

## Approach — `last − first + 1` via the Same Helper

Reuses `util(nums, x, isFirst)` from problem 06 verbatim. The only addition is an early `-1` guard so an absent `target` doesn't subtract two sentinels.

```cpp
int countOccurrences(vector<int>& arr, int target) {
    int first = util(arr, target, true);
    if (first == -1) return 0;
    int last  = util(arr, target, false);
    return last - first + 1;
}
```

**Time: O(log n) | Space: O(1)**

### Trace for `arr = [2, 4, 4, 4, 7]`, `target = 4`

```
first = util(arr, 4, true)  = 1
last  = util(arr, 4, false) = 3
count = 3 - 1 + 1 = 3
```

(See problem 06 for the step-by-step `util` trace.)

---

## Bonus — One-Liner via Lower / Upper Bound

If `lowerBound` and `upperBound` are available (problems 02 and 03):

```cpp
int countOccurrences(vector<int>& arr, int target) {
    return upperBound(arr, target) - lowerBound(arr, target);
}
```

No `-1` sentinel, no guard — when `target` is absent both bounds collide and the difference is `0`.

---

## Common Bugs

### 1. Skipping the `first == -1` guard

```cpp
// WRONG — both calls return -1, computes (-1) - (-1) + 1 = 1
int first = util(arr, target, true);
int last  = util(arr, target, false);
return last - first + 1;

// CORRECT — short-circuit when target is absent
int first = util(arr, target, true);
if (first == -1) return 0;
int last = util(arr, target, false);
return last - first + 1;
```

### 2. Using `last - first` (off by one)

A run from index 1 to 3 contains 3 elements, not 2. Always `+ 1`.

### 3. Linear scan after finding `first`

Walking from `first` until the run ends is `O(n)` on inputs like `[1, 1, …, 1]` — defeats the whole point of binary search. Run the second binary search.

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| `last − first + 1` (shared helper) | O(log n) | O(1) |
| `upperBound − lowerBound` | O(log n) | O(1) |
