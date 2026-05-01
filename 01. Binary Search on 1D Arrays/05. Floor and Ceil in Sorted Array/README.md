# Floor and Ceil in Sorted Array

## Problem

Given a sorted array `nums` and an integer `x`, return `[floor, ceil]` where:

- **Floor** = the largest element `<= x` (or `-1` if no element is `<= x`).
- **Ceil**  = the smallest element `>= x` (or `-1` if no element is `>= x`).

If `x` itself is in the array, both floor and ceil equal `x`.

```
nums = [3, 4, 4, 7, 8, 10], x = 5    →  [4, 7]
nums = [3, 4, 4, 7, 8, 10], x = 4    →  [4, 4]    (x is present)
nums = [3, 4, 4, 7, 8, 10], x = 2    →  [-1, 3]   (no element <= 2)
nums = [3, 4, 4, 7, 8, 10], x = 11   →  [10, -1]  (no element >= 11)
```

---

## The Core Insight

Both queries are monotonic predicates on a sorted array:

- **Floor** — walk as far right as possible while staying `<= x`. The predicate `nums[i] <= x` is true on a prefix; we want its **last** `true` index, then read the value there.
- **Ceil** — walk as far left as possible while staying `>= x`. The predicate `nums[i] >= x` is true on a suffix; we want its **first** `true` index.

Each is binary-searchable in `O(log n)`. The two only differ in which direction we drift on a `==` match (immediately satisfying both).

---

## Approach — Two Binary Searches via a Shared Helper

A single `util(nums, x, isFloor)` runs the appropriate variant. `result = -1` initialization handles the "no valid element" case.

```cpp
int util(vector<int>& nums, int x, bool isFloor) {
    int low = 0, high = nums.size() - 1, result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == x) return nums[mid];        // both floor and ceil equal x
        if (isFloor) {
            if (nums[mid] < x) {
                result = nums[mid];                  // candidate, try for larger
                low = mid + 1;
            }
            else high = mid - 1;
        }
        else {
            if (nums[mid] > x) {
                result = nums[mid];                  // candidate, try for smaller
                high = mid - 1;
            }
            else low = mid + 1;
        }
    }
    return result;
}

vector<int> getFloorAndCeil(vector<int>& nums, int x) {
    return { util(nums, x, true), util(nums, x, false) };
}
```

**Time: O(log n) | Space: O(1)**

### Trace for `nums = [3, 4, 4, 7, 8, 10]`, `x = 5`

```
Floor:
  start                                        result = -1
  mid=2  nums[2]=4   <5   → save, go right     result = 4
  mid=4  nums[4]=8   >5   → go left
  mid=3  nums[3]=7   >5   → go left
  exit                                         return 4

Ceil:
  start                                        result = -1
  mid=2  nums[2]=4   <5   → go right
  mid=4  nums[4]=8   >5   → save, go left      result = 8
  mid=3  nums[3]=7   >5   → save, go left      result = 7
  exit                                         return 7

→ [4, 7]
```

---

## Edge Cases

| Input | Why interesting | Output |
|---|---|---|
| `x` smaller than every element | Floor branch never fires | `[-1, nums[0]]` |
| `x` larger than every element  | Ceil branch never fires  | `[nums[n-1], -1]` |
| `x` is in the array | Equality short-circuits both searches | `[x, x]` |
| Empty array | Loop never enters | `[-1, -1]` |

---

## Common Bugs

### 1. Saving `mid` instead of `nums[mid]`

The problem asks for the *value*, not the index. Saving `result = mid` returns an index — wrong contract.

### 2. Wrong direction after saving

```cpp
// WRONG for floor — moving left after a < x match throws away a possible larger candidate
if (nums[mid] < x) { result = nums[mid]; high = mid - 1; }

// CORRECT — go right to look for an even larger value still <= x
if (nums[mid] < x) { result = nums[mid]; low  = mid + 1; }
```

Mirror this for ceil — after a `> x` match, go **left** to look for a smaller value still `>= x`.

### 3. Pass-by-value `vector<int> nums`

Each call copies the whole vector. Algorithmically harmless, but wasteful. Use `const vector<int>&` if performance matters.

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Two binary searches | O(log n) | O(1) |
