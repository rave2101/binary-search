# Find Out How Many Times an Array Has Been Rotated

## Problem
Given a sorted array `nums` of **distinct** integers that has been right-rotated `k` times (so element originally at index `i` is now at index `(i + k) mod n`), return `k`.

`k` equals the index of the minimum element in the rotated array — once you know where the original `nums[0]` ended up, that index *is* the rotation count.

Required time complexity: `O(log n)`.

**Examples**
```
nums = [4, 5, 6, 7, 0, 1, 2]   ->  4   (original [0,1,2,4,5,6,7] rotated 4 times)
nums = [3, 4, 5, 1, 2]         ->  3
nums = [11, 13, 15, 17]        ->  0   (no rotation)
nums = [2, 1]                  ->  1
nums = [1]                     ->  0
```

---

## Approach — `findMin` That Returns the *Index*

This problem is problem 10 with one twist: we need the **index** of the minimum, not its value. The structure is identical — identify the sorted half, capture its left endpoint as a min candidate, throw the sorted half away — but every time we update `ans` we also remember which index produced it:

```
On every step:
  if nums[low] <= nums[mid]:                          // LEFT half is sorted
      candidate = min(nums[low], nums[mid])
      if candidate < ans:
          ans = candidate
          result = (candidate == nums[low]) ? low : mid
      low = mid + 1
  else:                                                // RIGHT half is sorted
      candidate = min(nums[mid], nums[high])
      if candidate < ans:
          ans = candidate
          result = (candidate == nums[mid]) ? mid : high
      high = mid - 1
```

`findKRotation` is then a one-liner that just returns `result` from `findMin`.

### Why `index of min == rotation count`
After `k` right rotations, `nums[k]` holds the original `nums[0]`, which is the smallest element of the (originally sorted ascending) array. So the position of the minimum after rotation = `k`.

> Edge case: when the array is **not** rotated at all, the minimum sits at index `0` and `k = 0`. The algorithm handles this naturally — the very first iteration sees `nums[low] <= nums[mid]` (whole array is sorted), captures `nums[0]` with `result = 0`, and any later iterations only consider larger values, leaving `result` untouched.

---

## Complexity
| | |
|---|---|
| **Time** | `O(log n)` — one halving per iteration |
| **Space** | `O(1)` — iterative, no recursion |

---

## Trace — `nums = [4, 5, 6, 7, 0, 1, 2]`

| iter | low | high | mid | nums[low,mid,high] | sorted half | candidate | ans | result |
|---|---|---|---|---|---|---|---|---|
| start | 0 | 6 | — | — | — | — | INT_MAX | 6 |
| 1 | 0 | 6 | 3 | `4, 7, 2` | left `[4..7]` | min(4,7)=4 | 4 | 0 |
| 2 | 4 | 6 | 5 | `0, 1, 2` | left `[0..2]` | min(0,1)=0 | **0** | **4** |
| 3 | 6 | 6 | 6 | `2, 2, 2` | left `[2..2]` | min(2,2)=2 (no update) | 0 | 4 |
| 4 | 7 | 6 | — | — | — | — | exit | **4** |

→ Result: `4` ✓ (the `0` lives at index 4)

---

## Common Bugs to Avoid
- **Returning `ans` (the value) instead of `result` (the index).** This is the whole point of the problem; mixing them up gives the minimum element, not the rotation count.
- **Initializing `result = 0`.** Looks innocent but is wrong on inputs where the first iteration's branch never updates `result` (rare, but the safe initializer is `SIZE - 1` or any sentinel — the "no update" guard `if (candidate < ans)` then ensures only a real winner overwrites it).
- **Using `<=` in the `if (ans > mini)` guard.** It must be strict `>` (equivalently, `mini < ans`) — on `==` you'd overwrite `result` with a tied later index, breaking correctness when the true minimum was found earlier.
- **Picking `result = mid` always inside a branch.** The sorted-half minimum is at the *left endpoint* of that half, which is `low` (left branch) or `mid` (right branch) — not always `mid`. The ternary preserves that.
- **Treating `index of min == k` as obvious without the rotation-count argument.** If you accidentally apply this to a left-rotated input, the equivalence flips (`k = n - index_of_min`). Make sure the convention matches the problem statement.

---

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
