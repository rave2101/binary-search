# Single Element in a Sorted Array

## Problem
Given a sorted array `nums` where every element appears **exactly twice** except for one element that appears **exactly once**, return the single non-duplicate element.

Required time complexity: `O(log n)`.

**Examples**
```
nums = [1, 1, 2, 3, 3, 4, 4, 8, 8]   ->  2
nums = [3, 3, 7, 7, 10, 11, 11]      ->  10
nums = [1]                           ->  1
nums = [1, 2, 2]                     ->  1
nums = [1, 1, 2]                     ->  2
```

---

## Approach — Parity-Based Binary Search

Before the singleton, every duplicate pair occupies positions `(even, odd)` — first copy at an even index, second at the odd index right after it. After the singleton, the alignment **flips**: every pair occupies `(odd, even)`.

That flip is a monotonic predicate over the index space: "is `mid` still in the *aligned* region?" `false` once we pass the singleton, `true` before it. Binary search drives toward the boundary.

```
Pre-checks (so mid ± 1 is always safe):
  if size == 1 or nums[0] != nums[1]:                return nums[0]
  if nums[size-1] != nums[size-2]:                   return nums[size-1]

Search on [1, size-2]:
  if nums[mid] != nums[mid-1] and nums[mid] != nums[mid+1]:
      return nums[mid]                               // landed exactly on the singleton

  if mid is odd:                                     // expect pair at (mid-1, mid) before singleton
      if nums[mid-1] == nums[mid]:  low  = mid + 1   // still aligned, singleton is to the right
      else:                         high = mid - 1   // misaligned, singleton is to the left

  else (mid is even):                                // expect pair at (mid, mid+1) before singleton
      if nums[mid+1] == nums[mid]:  low  = mid + 1   // still aligned, singleton is to the right
      else:                         high = mid - 1   // misaligned, singleton is to the left
```

### Why the parity check works
In the prefix before the singleton: `nums[0] == nums[1]`, `nums[2] == nums[3]`, …  → pairs sit at `(even, odd)`.
In the suffix after the singleton: pairs sit at `(odd, even)`.

So at any `mid`:
- If `mid` is **odd**, "still aligned" means its partner is `nums[mid-1]`.
- If `mid` is **even**, "still aligned" means its partner is `nums[mid+1]`.

Aligned ⇒ singleton is to the right; misaligned ⇒ singleton is at `mid` or to the left. Each step halves the window.

### Why the pre-checks
The inner loop dereferences `nums[mid-1]` and `nums[mid+1]`, which would walk off the ends at indices `0` and `size-1`. Handling the singleton-at-an-endpoint cases up front lets the search run on `[1, size-2]` with no boundary guards inside.

---

## Complexity
| | |
|---|---|
| **Time** | `O(log n)` — binary search on the alignment predicate |
| **Space** | `O(1)` |

---

## Trace — `nums = [1, 1, 2, 3, 3, 4, 4, 8, 8]`

Pre-checks: `nums[0] == nums[1]` (1==1 ✓), `nums[8] == nums[7]` (8==8 ✓) — no early return. Search on `[1, 7]`.

| iter | low | high | mid | parity | nums[mid-1, mid, mid+1] | exact match? | aligned? | branch |
|---|---|---|---|---|---|---|---|---|
| 1 | 1 | 7 | 4 | even | `2, 3, 3` | no | yes (`nums[5]==nums[4]`? no — wait, mid=4 even checks nums[5]==nums[4]: 3==3 → yes) | go right |

Re-walking carefully:

| iter | low | high | mid | parity | check | result |
|---|---|---|---|---|---|---|
| 1 | 1 | 7 | 4 | even | `nums[4]=3`, `nums[3]=3`, `nums[5]=4` — partner-by-parity is `nums[5]=4`, ≠ `nums[4]` → misaligned | go left |
| 2 | 1 | 3 | 2 | even | `nums[2]=2`, `nums[1]=1`, `nums[3]=3` — both neighbors differ → singleton hit | **return 2** |

→ Result: `2` ✓

---

## Common Bugs to Avoid
- **No pre-checks before the loop.** Without them, a singleton at index `0` or `size-1` causes `mid ± 1` to read out of bounds, and an array of size 1 dereferences `nums[1]`.
- **Confusing the parity rules.** Remember the convention: at odd `mid` look *left* (`mid-1`); at even `mid` look *right* (`mid+1`). Swapping these inverts the alignment predicate and sends the search the wrong way.
- **Skipping the "exact match" check.** Without `if (nums[mid] != nums[mid-1] && nums[mid] != nums[mid+1]) return nums[mid]`, the loop can step past the singleton and the boundaries cross, returning the sentinel `-1` even though the answer was just inspected.
- **XOR-only solutions in interviews.** `O(n)` XOR works but ignores the sortedness — interviewers asking this expect `O(log n)`. Mention XOR as a fallback, not the primary approach.

> **Cleaner one-liner:** observe that "aligned" is equivalent to `nums[mid] == nums[mid ^ 1]` (XOR with 1 flips the last bit, giving the parity-partner index). The whole branching collapses to:
> ```cpp
> if (nums[mid] == nums[mid ^ 1])  low  = mid + 1;
> else                              high = mid;
> ```
> with `low < high` as the loop condition. Same `O(log n)`, fewer branches.

---

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
