# First and last occurrence

## Problem

Given a sorted array `nums` (with possible duplicates) and a `target`, return `[first, last]` where:

- **first** = the smallest index `i` with `nums[i] == target`
- **last**  = the largest  index `i` with `nums[i] == target`

If `target` doesn't appear, return `[-1, -1]`.

```
nums = [2, 4, 4, 4, 7], target = 4   →  [1, 3]
nums = [2, 4, 4, 4, 7], target = 2   →  [0, 0]
nums = [2, 4, 4, 4, 7], target = 5   →  [-1, -1]
nums = [1, 1, 1, 1, 1], target = 1   →  [0, 4]
```

---

## The Core Insight

Two monotonic predicates fit the search:

```
nums = [2, 4, 4, 4, 7], target = 4

       2  4  4  4  7
  >=4: F  T  T  T  T   first occurrence = leftmost T = 1
  > 4: F  F  F  F  T   last  occurrence = (leftmost T) - 1 = 3
```

Both are binary-searchable in `O(log n)`. This solution wraps them in one helper — an `isFirst` flag flips the direction we drift after an `==` match.

---

## Approach — Two Binary Searches via a Shared Helper

```cpp
int util(vector<int>& nums, int x, bool isFirst) {
    int low = 0, high = nums.size() - 1, result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == x) {
            result = mid;
            if (isFirst) high = mid - 1;     // try for an earlier match
            else         low  = mid + 1;     // try for a later match
        }
        else if (nums[mid] < x) low  = mid + 1;
        else                    high = mid - 1;
    }
    return result;
}

vector<int> searchRange(vector<int>& nums, int target) {
    return { util(nums, target, true), util(nums, target, false) };
}
```

**Time: O(log n) | Space: O(1)**

### Trace for `nums = [2, 4, 4, 4, 7]`, `target = 4`

```
First occurrence:
  start                                        result = -1
  mid=2  nums[2]=4  ==  → save, go left        result = 2
  mid=0  nums[0]=2  <4  → go right
  mid=1  nums[1]=4  ==  → save, go left        result = 1
  exit                                         return 1

Last occurrence:
  start                                        result = -1
  mid=2  nums[2]=4  ==  → save, go right       result = 2
  mid=3  nums[3]=4  ==  → save, go right       result = 3
  mid=4  nums[4]=7  >4  → go left
  exit                                         return 3

→ [1, 3]
```

---

## Bonus — One-Liner via Lower / Upper Bound

If `lowerBound` and `upperBound` are available (problems 02 and 03), this whole problem collapses:

```cpp
int first = lowerBound(nums, target);
int last  = upperBound(nums, target) - 1;
if (first == (int)nums.size() || nums[first] != target) return {-1, -1};
return {first, last};
```

Same `O(log n)` time, no custom helper.

---

## Common Bugs

### 1. Returning `mid` immediately on equality

```cpp
// WRONG — gives some match, not necessarily the boundary
if (nums[mid] == x) return mid;

// CORRECT — save and keep searching in the chosen direction
if (nums[mid] == x) { result = mid; if (isFirst) high = mid - 1; else low = mid + 1; }
```

### 2. Forgetting `result = -1` init

Without it, the not-found return value is undefined.

### 3. Sliding `low` / `high` to `mid` instead of `mid ± 1`

```cpp
// WRONG — infinite loop at low == high in a <= style loop
high = mid;

// CORRECT
high = mid - 1;
```

### 4. Computing `last = first + count - 1`

That requires you to *also* compute the count, which is exactly what `upperBound − lowerBound` gives you. Just do the second binary search.

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Two binary searches (shared helper) | O(log n) | O(1) |
| Via lower / upper bound | O(log n) | O(1) |
