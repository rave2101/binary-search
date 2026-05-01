# Floor and Ceil in Sorted Array

## Problem
Given a sorted array `nums` and an integer `x`, return `[floor, ceil]` where:
- **Floor** = the **largest** element `<= x` (or `-1` if no element is `<= x`).
- **Ceil**  = the **smallest** element `>= x` (or `-1` if no element is `>= x`).

If `x` itself is in the array, both floor and ceil equal `x`.

**Examples**
```
nums = [3, 4, 4, 7, 8, 10], x = 5    ->  [4, 7]
nums = [3, 4, 4, 7, 8, 10], x = 4    ->  [4, 4]   (x is present)
nums = [3, 4, 4, 7, 8, 10], x = 2    ->  [-1, 3]  (no element <= 2)
nums = [3, 4, 4, 7, 8, 10], x = 11   ->  [10, -1] (no element >= 11)
```

---

## Approach — Two Binary Searches via a Shared Helper

Both floor and ceil follow the same template — only the comparison and the direction we move flip. The solution captures this with a single `util(nums, x, isFloor)`:

```
On every step:
  if nums[mid] == x   -> return nums[mid]   (same answer for both floor and ceil)

  Floor (largest <= x):
    nums[mid] < x  -> candidate, save and search RIGHT for a larger one
    nums[mid] > x  -> too big, search LEFT

  Ceil (smallest >= x):
    nums[mid] > x  -> candidate, save and search LEFT for a smaller one
    nums[mid] < x  -> too small, search RIGHT
```

`result` is initialized to `-1`, so the "no valid element exists" case falls out naturally.

### Mental model
Think of the predicate as monotonic on a sorted array:
- For **floor**, walk as far right as possible while staying `<= x`.
- For **ceil**, walk as far left as possible while staying `>= x`.

Each is binary-searchable in `O(log n)`.

---

## Complexity
| | |
|---|---|
| **Time** | `O(log n)` — two independent binary searches |
| **Space** | `O(1)` aux. *(See note on pass-by-value below.)* |

> **Minor inefficiency:** `util` and `getFloorAndCeil` accept `nums` by value (`vector<int> nums`) instead of by const reference. Each call copies the entire vector. For a more competitive setup, change to `const vector<int>& nums` — the algorithm is unchanged, but the per-call copy goes away.

---

## Trace — `nums = [3, 4, 4, 7, 8, 10]`, `x = 5`

### Floor
| iter | low | high | mid | nums[mid] | branch | result |
|---|---|---|---|---|---|---|
| start | 0 | 5 | — | — | — | -1 |
| 1 | 0 | 5 | 2 | 4  | `<5` → save, go right | **4** |
| 2 | 3 | 5 | 4 | 8  | `>5` → go left | 4 |
| 3 | 3 | 3 | 3 | 7  | `>5` → go left | 4 |
| 4 | 3 | 2 | — | — | exit | **4** |

### Ceil
| iter | low | high | mid | nums[mid] | branch | result |
|---|---|---|---|---|---|---|
| start | 0 | 5 | — | — | — | -1 |
| 1 | 0 | 5 | 2 | 4  | `<5` → go right | -1 |
| 2 | 3 | 5 | 4 | 8  | `>5` → save, go left | 8 |
| 3 | 3 | 3 | 3 | 7  | `>5` → save, go left | **7** |
| 4 | 3 | 2 | — | — | exit | **7** |

→ Result: `[4, 7]` ✓

---

## Edge Cases Worth Eyeballing

| Input | Why interesting | Output |
|---|---|---|
| `x` smaller than every element | Floor branch never fires | `[-1, nums[0]]` |
| `x` larger than every element | Ceil branch never fires | `[nums[n-1], -1]` |
| `x` is in the array | Equality short-circuits both searches | `[x, x]` |
| Empty array | Loop never enters | `[-1, -1]` |

---

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
