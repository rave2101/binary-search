# Search insert position

## Problem

Given a sorted array `nums` of **distinct** integers and a `target`, return:

- the index of `target` if it exists, or
- the index where it would be inserted while keeping the array sorted.

```
nums = [1, 3, 5, 6], target = 5   →  2     (found at index 2)
nums = [1, 3, 5, 6], target = 2   →  1     (would insert between 1 and 3)
nums = [1, 3, 5, 6], target = 7   →  4     (would append at the end)
nums = [1, 3, 5, 6], target = 0   →  0     (would prepend)
```

---

## The Core Insight

The insert position is exactly the **lower bound** of `target` — the smallest index `i` with `nums[i] >= target`. Why?

- If `target` is present at index `i`, lower bound returns `i` (the position of the first element `>= target`, which equals `target`).
- If `target` is absent, lower bound returns the first index with a strictly greater element — which is the only place where inserting `target` keeps the array sorted.
- If `target` is greater than every element, lower bound returns `n` — append at the end.

So this problem is `lowerBound` with one micro-optimization: since elements are distinct, an `==` match at any `mid` is **the** answer — no earlier index can also equal `target` — so we can return immediately.

---

## Approach — Binary Search with Early Return

```cpp
int searchInsert(vector<int>& nums, int target) {
    int n = nums.size();
    int low = 0, high = n - 1, result = n;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target)  low = mid + 1;
        else {
            result = mid;
            high = mid - 1;
        }
    }
    return result;
}
```

**Time: O(log n) | Space: O(1)**

### Trace for `nums = [1, 3, 5, 6]`, `target = 2`

```
start                                          result = 4
mid=1  nums[1]=3   >2   → save, go left         result = 1
mid=0  nums[0]=1   <2   → go right
exit                                            return 1
```

### Trace for `nums = [1, 3, 5, 6]`, `target = 7`

```
start                                          result = 4
mid=1  nums[1]=3   <7   → go right
mid=2  nums[2]=5   <7   → go right
mid=3  nums[3]=6   <7   → go right
exit                                            return 4   (initial n, "insert at end")
```

`result` was never updated — the initial `n` *is* the answer.

---

## Common Bugs

### 1. Early return when duplicates are allowed

```cpp
// FINE for distinct elements (this problem)
if (nums[mid] == target) return mid;

// WRONG when duplicates are allowed and the problem wants the FIRST occurrence
// → drop the early return; let the "save and go left" branch handle equality
```

If the problem statement adds duplicates and asks for the leftmost match, switch the predicate to `nums[mid] >= target` (plain lower bound) — the early return would otherwise lock onto an arbitrary middle copy.

### 2. Forgetting `result = n`

If `target` is greater than every element, the "save and go left" branch never fires. Initialize `result = n` so the append-at-end case is implicit.

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Iterative | O(log n) | O(1) |
