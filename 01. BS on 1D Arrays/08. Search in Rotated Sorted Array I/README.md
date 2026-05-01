# Search in Rotated Sorted Array I

## Problem
Given a sorted array `nums` of **distinct** integers that has been rotated at some unknown pivot, and a target `k`, return the index of `k` in `nums`. If `k` is not present, return `-1`.

The rotation means the array looks like `[A_p, A_{p+1}, …, A_{n-1}, A_0, A_1, …, A_{p-1}]` for some pivot `p`.

Required time complexity: `O(log n)`.

**Examples**
```
nums = [4, 5, 6, 7, 0, 1, 2], k = 0   ->  4
nums = [4, 5, 6, 7, 0, 1, 2], k = 3   ->  -1
nums = [5, 1, 2, 3, 4],       k = 1   ->  1
nums = [1],                   k = 0   ->  -1
```

---

## Approach — Identify the Sorted Half, Then Decide

A rotated sorted array, when split at any `mid`, has **at least one half that is fully sorted**. The trick is to identify which half is sorted, check whether `k` lies inside its known range, and recurse into the appropriate side.

```
On every step:
  if nums[mid] == k:           return mid

  if nums[low] <= nums[mid]:                    // LEFT half [low..mid] is sorted
      if nums[low] <= k < nums[mid]:  high = mid - 1   // k lies in the sorted left
      else:                            low  = mid + 1   // k must be in the right
  else:                                          // RIGHT half [mid..high] is sorted
      if nums[mid] < k <= nums[high]: low  = mid + 1   // k lies in the sorted right
      else:                            high = mid - 1   // k must be in the left
```

Return `-1` if the loop exits.

### Why this works
For any `mid`, compare `nums[low]` and `nums[mid]`:
- `nums[low] <= nums[mid]` → the left half `[low..mid]` is monotonically increasing (no rotation in this half).
- Otherwise → the rotation point lies in `[low..mid]`, so the **right** half `[mid..high]` must be the sorted one.

Once we know which half is sorted, we have a closed numeric range for it. Membership of `k` in that range is an `O(1)` check, so we recurse into the half guaranteed to contain `k` — or, if `k` is not in the sorted half's range, into the other half (which contains the rotation but might still contain `k`). Either way each step halves the search space.

> **Why `<=` on the left and `<=` on the right boundary?** The pivot can sit at the half's edge. Using `<=` on `nums[low]` (and `nums[high]`) keeps single-element segments and exact-boundary cases in the correct branch.

---

## Complexity
| | |
|---|---|
| **Time** | `O(log n)` — one halving per iteration |
| **Space** | `O(1)` — iterative, no recursion |

---

## Trace — `nums = [4, 5, 6, 7, 0, 1, 2]`, `k = 0`

| iter | low | high | mid | nums[mid] | sorted half | k in sorted range? | branch | result |
|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 6 | 3 | 7 | left `[4..7]` | `0 ∈ [4, 7)`? no | go right | — |
| 2 | 4 | 6 | 5 | 1 | left `[0..1]` | `0 ∈ [0, 1)`? yes | go left | — |
| 3 | 4 | 4 | 4 | 0 | — | match | return | **4** |

→ Result: `4` ✓

---

## Common Bugs to Avoid
- **Wrong inequality on the sorted-half check.** `nums[low] < nums[mid]` (strict) drops the case where `low == mid`, sending single-element windows down the wrong branch. Use `<=`.
- **Wrong inequality on the range check.** Inside the sorted left half, `k` must satisfy `nums[low] <= k < nums[mid]` — the upper bound is *strict* because `nums[mid]` was just checked and isn't equal to `k`. Mirror that on the right: `nums[mid] < k <= nums[high]`.
- **Forgetting the `nums[mid] == k` early return.** Without it the algorithm still terminates, but you lose the cheap match and may overshoot.
- **Applying this to arrays with duplicates.** With duplicates, `nums[low] == nums[mid]` no longer implies the left half is sorted (e.g., `[3, 1, 3, 3, 3]`). That case needs the extra "shrink boundaries" step — handled in problem 09.

---

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
