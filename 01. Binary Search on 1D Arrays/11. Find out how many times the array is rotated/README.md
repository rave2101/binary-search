# Find out how many times the array is rotated

## Problem

Given a sorted array `nums` of **distinct** integers that has been right-rotated `k` times (so element originally at index `i` is now at index `(i + k) mod n`), return `k`. Required time complexity: `O(log n)`.

```
nums = [4, 5, 6, 7, 0, 1, 2]   →  4    (original [0,1,2,4,5,6,7] rotated 4 times)
nums = [3, 4, 5, 1, 2]         →  3
nums = [11, 13, 15, 17]        →  0    (no rotation)
nums = [2, 1]                  →  1
nums = [1]                     →  0
```

---

## The Core Insight

After `k` right rotations, `nums[k]` holds the original `nums[0]` — which was the smallest element of the originally ascending array. So:

```
index of minimum  ==  rotation count k
```

This problem is problem 10 with one twist: track the **index** of the minimum, not just its value. The whole structure is the same (identify sorted half, capture endpoint, discard half) — every time we update the running min, we also record which index produced it.

> If the input were left-rotated instead, the equivalence flips to `k = n − index_of_min`. The convention here is right rotation.

---

## Approach — `findMin` That Returns the Index

```cpp
int findMin(vector<int>& nums) {
    int ans = INT_MAX, result = nums.size() - 1;
    int low = 0, high = nums.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[low] <= nums[mid]) {                          // LEFT half sorted
            int cand = min(nums[low], nums[mid]);
            if (cand < ans) {
                ans = cand;
                result = (cand == nums[low]) ? low : mid;
            }
            low = mid + 1;
        }
        else {                                                 // RIGHT half sorted
            int cand = min(nums[mid], nums[high]);
            if (cand < ans) {
                ans = cand;
                result = (cand == nums[mid]) ? mid : high;
            }
            high = mid - 1;
        }
    }
    return result;
}

int findKRotation(vector<int>& nums) {
    return findMin(nums);
}
```

**Time: O(log n) | Space: O(1)**

### No-rotation case

When the array is already sorted, the first iteration's left branch captures `nums[0]` with `result = 0`. Every later iteration only sees larger candidates, so the strict `<` guard prevents `result` from being overwritten. Returns `0`.

### Trace for `nums = [4, 5, 6, 7, 0, 1, 2]`

```
start                                          ans = INT_MAX   result = 6
low=0  high=6  mid=3  nums[0,3,6]=[4,7,2]      left sorted [4..7]   cand=4   ans=4  result=0
low=4  high=6  mid=5  nums[4,5,6]=[0,1,2]      left sorted [0..2]   cand=0   ans=0  result=4
low=6  high=6  mid=6  nums[6,6,6]=[2,2,2]      left sorted [2..2]   cand=2  (no update)
exit                                           return 4
```

→ The `0` lives at index `4`, so the array was rotated `4` times.

---

## Common Bugs

### 1. Returning `ans` (the value) instead of `result` (the index)

This is the whole point of the problem. Mixing them up returns the minimum element, not the rotation count.

### 2. Picking `result = mid` always inside a branch

```cpp
// WRONG — the sorted left half's minimum is at low, not mid
ans = min(nums[low], nums[mid]);
result = mid;

// CORRECT — pick the index of whichever endpoint is smaller
result = (cand == nums[low]) ? low : mid;
```

### 3. Using `<=` in the `cand < ans` guard

```cpp
// WRONG — on a tie, overwrites result with a later index
if (cand <= ans) { ans = cand; result = ...; }

// CORRECT — strict <, preserves the earliest winning index on ties
if (cand < ans)  { ans = cand; result = ...; }
```

(With distinct elements ties shouldn't occur, but the strict guard is the right defensive default.)

### 4. Initializing `result = 0`

Looks innocent but if the first iteration's guard doesn't fire, you return `0` regardless of where the minimum actually lives. Use a clear sentinel like `nums.size() - 1` and let the guarded update do its job.

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Iterative | O(log n) | O(1) |
