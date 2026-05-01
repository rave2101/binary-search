# Find Peak Element

## Problem
Given an integer array `nums`, return the index of **any** peak element. A peak is an index `i` where `nums[i] > nums[i-1]` and `nums[i] > nums[i+1]`. By convention, `nums[-1] = nums[n] = -∞` (so endpoints can be peaks).

You may assume `nums[i] != nums[i+1]` for all valid `i` (no equal adjacent values). The array is **not** required to be sorted — it can have multiple peaks; return any one.

Required time complexity: `O(log n)`.

**Examples**
```
nums = [1, 2, 3, 1]                       ->  2          (nums[2]=3 is a peak)
nums = [1, 2, 1, 3, 5, 6, 4]              ->  1 or 5     (both are peaks)
nums = [1, 2, 1, 1, 4, 5, 6, 7, 1, 2, 3, 4] ->  1, 7, or 11
nums = [5, 4, 3, 2, 1]                    ->  0          (endpoint peak)
```

---

## Approach — "Climb Uphill" Binary Search

The key observation: even though the whole array isn't monotonic, we can always find a peak by walking *uphill*. From any non-peak `mid`, at least one of `nums[mid-1]` or `nums[mid+1]` is greater. Move toward that side and a peak must exist in that half — because the half ends at a virtual `-∞` boundary, so something in there has to come back down.

```
Pre-checks (so mid ± 1 is always safe):
  if size == 1 or nums[0] > nums[1]:                  return 0
  if nums[size-1] > nums[size-2]:                     return size - 1

Search on [1, size-2]:
  if nums[mid] > nums[mid-1] and nums[mid] > nums[mid+1]:
      return mid                                       // peak found

  if nums[mid] > nums[mid-1]:  low  = mid + 1          // climbing upward — peak is to the right
  else:                        high = mid - 1          // climbing upward backward — peak is to the left
```

### Why this works (the monotone-walk argument)
After the endpoint pre-checks, the virtual boundaries are `nums[-1] = -∞` and `nums[size] = -∞`. If `nums[mid] > nums[mid-1]`, the values rise from index `mid-1` to `mid`. Continue right: either they keep rising (and we eventually hit a peak before `nums[size] = -∞`), or they drop somewhere — that drop point is a peak. Either way, **some peak lives in `[mid+1, high]`**. Symmetric argument for the left side.

So each iteration halves the window while preserving the invariant "a peak exists in `[low, high]`". The loop terminates when we land exactly on one.

---

## Complexity
| | |
|---|---|
| **Time** | `O(log n)` — one halving per iteration |
| **Space** | `O(1)` |

---

## Trace — `nums = [1, 2, 1, 1, 4, 5, 6, 7, 1, 2, 3, 4]`

Pre-checks: `nums[0]=1 > nums[1]=2`? no. `nums[11]=4 > nums[10]=3`? yes → would return `11`. But say we ignore the trailing-endpoint shortcut to show the loop; here's the loop run on a similar input that doesn't end in a peak, e.g. `[1, 2, 1, 1, 4, 5, 6, 7, 1, 2, 1]`.

Pre-checks: `nums[0]=1 > nums[1]=2`? no. `nums[10]=1 > nums[9]=2`? no. Search on `[1, 9]`.

| iter | low | high | mid | nums[mid-1, mid, mid+1] | both-greater? | branch |
|---|---|---|---|---|---|---|
| 1 | 1 | 9 | 5 | `4, 5, 6` | no — left smaller, right larger | climbing right → `low = 6` |
| 2 | 6 | 9 | 7 | `6, 7, 1` | yes — peak | **return 7** |

→ Result: `7` ✓ (`nums[7] = 7` is a peak)

---

## Common Bugs to Avoid
- **No pre-checks before the loop.** The loop reads `nums[mid-1]` and `nums[mid+1]`; without endpoint handling, a peak at index `0` or `size-1` would either be missed or cause out-of-bounds reads. Pre-handling them lets the loop run on `[1, size-2]` with no boundary worries.
- **Climbing the wrong way.** The rule is "if `nums[mid] > nums[mid-1]` go right" — i.e., go in the direction the values are rising. Reversing this descends instead and can land in a valley with no peak.
- **Trying to find the *largest* peak.** This problem asks for *any* peak. Pursuing the global max needs `O(n)` (you can't shortcut without scanning).
- **Assuming the array is sorted.** Several inputs look sorted-then-rotated, but no monotonicity assumption is needed — the climbing argument is what makes binary search work here.
- **Using `<=` instead of `<` in the comparisons.** The problem guarantees no equal adjacent values, so it doesn't matter on valid inputs — but on adversarial inputs with plateaus, equality breaks the climb-uphill invariant. The strict comparisons make the algorithm fail loudly rather than wander.

---

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
