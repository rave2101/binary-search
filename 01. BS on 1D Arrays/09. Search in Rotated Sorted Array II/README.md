# Search in Rotated Sorted Array II

## Problem
Given a sorted array `nums` that may contain **duplicates** and has been rotated at some unknown pivot, and a target `k`, return whether `k` exists in `nums` (`true` / `false`).

This is the duplicates-allowed variant of problem 08. We only need a boolean — not the index — because in the worst case the index isn't well-defined (multiple matches) and uniqueness is gone.

**Examples**
```
nums = [2, 5, 6, 0, 0, 1, 2], k = 0   ->  true
nums = [2, 5, 6, 0, 0, 1, 2], k = 3   ->  false
nums = [1, 0, 1, 1, 1],       k = 0   ->  true
nums = [3, 1, 2, 3, 3, 3, 3], k = 2   ->  true
```

---

## Approach — Same as Problem 08, Plus a "Shrink Boundaries" Step

The problem-08 algorithm assumes `nums[low] <= nums[mid]` reliably tells us the left half is sorted. With duplicates that inference can break: in `[3, 1, 2, 3, 3, 3, 3]` at `low=0, mid=3, high=6` we have `nums[low] == nums[mid] == nums[high] == 3`, but the array is genuinely rotated and the left half **isn't** sorted.

When that ambiguous case shows up, the only safe move is to shrink the window by one on each side and continue:

```
On every step:
  if nums[mid] == k:  return true

  if nums[low] == nums[mid] == nums[high]:    // ambiguous — can't tell which half is sorted
      low++;  high--;  continue              // shrink and retry

  if nums[low] <= nums[mid]:                  // LEFT half is sorted
      if nums[low] <= k < nums[mid]: high = mid - 1
      else:                          low  = mid + 1
  else:                                       // RIGHT half is sorted
      if nums[mid] < k <= nums[high]: low  = mid + 1
      else:                           high = mid - 1
```

Return `false` if the loop exits.

### Why this works
Two observations:
1. The shrink step is safe — both `nums[low]` and `nums[high]` are equal to `nums[mid]` and we already checked `nums[mid] != k`, so neither endpoint can be the answer.
2. Whenever the triple-equality does **not** hold, the problem-08 invariant ("at least one half is sorted, and `nums[low] <= nums[mid]` correctly identifies which") holds again, so the standard branches are sound.

---

## Complexity
| | |
|---|---|
| **Time** | `O(log n)` average; `O(n)` worst case (all-duplicates, e.g. `[1,1,1,1,1,1]`) — the shrink step is linear |
| **Space** | `O(1)` — iterative, no recursion |

The `O(n)` worst case is unavoidable: with `[1,1,…,1,0]` rotated, no subset of three indices alone reveals the rotation point, so any algorithm must look at most positions individually.

---

## Trace — `nums = [3, 1, 2, 3, 3, 3, 3]`, `k = 2`

| iter | low | high | mid | nums[low,mid,high] | branch | window |
|---|---|---|---|---|---|---|
| 1 | 0 | 6 | 3 | `3, 3, 3` | triple-equal → shrink | `[1..5]` |
| 2 | 1 | 5 | 3 | `1, 3, 3` | left sorted `[1..3]`, `2 ∈ [1, 3)` → go left | `[1..2]` |
| 3 | 1 | 2 | 1 | `1, 1, 2` | match? no; left sorted `[1..1]`, `2 ∉ [1, 1)` → go right | `[2..2]` |
| 4 | 2 | 2 | 2 | `2, 2, 2` | match → return | **true** |

→ Result: `true` ✓

---

## Common Bugs to Avoid
- **Skipping the triple-equality check** and reusing problem-08 directly — fails on inputs like `[1, 0, 1, 1, 1]` searching for `0`, because `nums[low] <= nums[mid]` is true but the left half `[1, 0, 1]` isn't sorted, so the range check sends the search the wrong way.
- **Shrinking only one side** (`low++` without `high--`, or vice versa). Both endpoints are equal to `nums[mid]` and already ruled out — discarding only one wastes an iteration and, in adversarial inputs, can leave the same ambiguous state forever.
- **Forgetting `continue`.** Without it, control falls through into the sorted-half branch with stale boundaries and may take the wrong direction.
- **Returning the index.** With duplicates the answer index isn't unique — the problem only asks for a boolean. Don't try to extend this solution to "first index of `k`"; that is a different (and harder) problem.

---

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
