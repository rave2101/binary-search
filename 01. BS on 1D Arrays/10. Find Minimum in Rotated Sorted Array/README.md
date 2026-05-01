# Find Minimum in Rotated Sorted Array

## Problem
Given a sorted array `nums` of **distinct** integers that has been rotated at some unknown pivot, return the minimum element.

Required time complexity: `O(log n)`.

**Examples**
```
nums = [4, 5, 6, 7, 0, 1, 2]   ->  0
nums = [3, 4, 5, 1, 2]         ->  1
nums = [11, 13, 15, 17]        ->  11   (no rotation)
nums = [2, 1]                  ->  1
```

---

## Approach — Identify the Sorted Half, Capture Its Minimum, Discard It

The same "one half is always sorted" invariant from problem 08 powers this. Here, instead of looking for a target, we want the global minimum:

```
On every step:
  if nums[low] <= nums[mid]:                   // LEFT half [low..mid] is sorted
      ans = min(ans, nums[low])                // its smallest element is nums[low]
      low = mid + 1                            // discard the sorted left, search the rest
  else:                                        // RIGHT half [mid..high] is sorted
      ans = min(ans, nums[mid])                // its smallest element is nums[mid]
      high = mid - 1                           // discard the sorted right, search the rest
```

Return `ans`, initialized to `INT_MAX`.

(The implementation passes `nums[low]`, `nums[mid]`, `nums[high]` all into the `min({...})` call. Strictly only one endpoint per branch is required for correctness; the extras are harmless.)

### Why this works
At each step the array splits into a sorted half and a possibly-rotated half. The sorted half's minimum is its left endpoint (no rotation in that half), so we can read it off in `O(1)` and then **throw the sorted half away** — the global minimum is either that endpoint (already captured into `ans`) or it lives in the other half. Each iteration halves the search space, giving `O(log n)`.

> **No rotation case:** if the array is already sorted (no rotation), the very first iteration takes the left branch with `low = 0, mid ≈ n/2, high = n-1`, captures `nums[0]` (the true minimum), and walks the search to the right — every subsequent half is also "sorted left", and `ans` never gets overwritten.

---

## Complexity
| | |
|---|---|
| **Time** | `O(log n)` — one halving per iteration |
| **Space** | `O(1)` — iterative, no recursion |

---

## Trace — `nums = [4, 5, 6, 7, 0, 1, 2]`

| iter | low | high | mid | nums[low,mid,high] | sorted half | captured min | branch | ans |
|---|---|---|---|---|---|---|---|---|
| start | 0 | 6 | — | — | — | — | — | INT_MAX |
| 1 | 0 | 6 | 3 | `4, 7, 2` | left `[4..7]` | `4` | discard left | 4 |
| 2 | 4 | 6 | 5 | `0, 1, 2` | left `[0..2]` | `0` | discard left | **0** |
| 3 | 6 | 6 | 6 | `2, 2, 2` | left `[2..2]` | `2` | discard left | 0 |
| 4 | 7 | 6 | — | — | — | — | exit | **0** |

→ Result: `0` ✓

---

## Common Bugs to Avoid
- **Strict `<` instead of `<=`** in the sorted-half check. With `low == mid` (single-element window), `nums[low] < nums[mid]` is false and the algorithm takes the wrong branch. `<=` keeps that case correct.
- **Forgetting to capture before shrinking.** If you write `low = mid + 1` *before* updating `ans`, you've already discarded the half whose endpoint you needed. Capture first, then shrink.
- **Initializing `ans = nums[0]`.** That happens to work for the standard input but is brittle — `ans = INT_MAX` is the safe identity for `min`.
- **Trying to return `low` or `mid` at exit.** This loop terminates with `low > high` and no clean "answer pointer"; the captured `ans` *is* the answer.
- **Applying this to arrays with duplicates.** Just like problem 08 → 09, duplicates break the sorted-half inference (e.g., `[3, 3, 1, 3]`). Handling that needs the same triple-equality shrink step.

---

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
