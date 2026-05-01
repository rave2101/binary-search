# Kth Missing Positive Number

## Problem

Given a strictly increasing array `arr` of positive integers and an integer `k`, return the **k-th positive integer missing** from `arr`.

```
arr = [2,3,4,7,11], k = 5   → 9
arr = [1,2,3,4],    k = 2   → 6
arr = [3,5,7,10],   k = 6   → 9
```

For `[3,5,7,10]`, the missing positives in order are `1, 2, 4, 6, 8, 9, …` — so the 6th missing is `9`.

## The key identity

At index `i`, how many positive integers are missing from `arr[0..i]`?

- Without any gaps the value at index `i` would be `i + 1`.
- The actual value is `arr[i]`.
- So the count of missing numbers up to (and including) `arr[i]` is `arr[i] - (i + 1) = arr[i] - i - 1`.

This count is **monotonically non-decreasing** in `i` — gaps only accumulate. So we can binary search for the boundary index where `missing(i) ≥ k`.

For `arr = [3, 5, 7, 10]`:

| i | arr[i] | missing = arr[i] − i − 1 |
|---|---|---|
| 0 | 3  | 2 |
| 1 | 5  | 3 |
| 2 | 7  | 4 |
| 3 | 10 | 6 |

## Approach — Binary Search on the Index

1. `low = 0, high = n - 1`. Predicate: `arr[mid] - mid - 1 < k` means we haven't reached enough missing numbers yet.
2. If true → `low = mid + 1`. Else → `high = mid - 1`.
3. After the loop, `high` is the largest index whose missing-count is still `< k` (i.e. `arr[high]` is the last array element before the k-th missing falls). The answer lies past it.

### Deriving the answer formula

Let `m = arr[high] - high - 1` be the missing count at index `high` (with `m < k`). The k-th missing is `(k - m)` positions past `arr[high]` on the integer line:

```
answer = arr[high] + (k - m)
       = arr[high] + k - (arr[high] - high - 1)
       = k + high + 1
```

The `arr[high]` term cancels out — the answer collapses to `k + high + 1`.

Boundary cases:
- If every index has `missing < k` (the k-th missing is past `arr[n-1]`): loop ends with `high = n - 1` → answer `k + n`. Correct.
- If `arr[0]` already has `missing ≥ k` (the k-th missing comes before any array element): loop ends with `high = -1` → answer `k`. Correct.

## Complexity
- **Time:** `O(log n)`
- **Space:** `O(1)`

## Trace — `arr = [3, 5, 7, 10], k = 6`

| iter | low | high | mid | arr[mid] − mid − 1 | branch |
|---|---|---|---|---|---|
| 1 | 0 | 3 | 1 | 3 | `< 6` → low = 2 |
| 2 | 2 | 3 | 2 | 4 | `< 6` → low = 3 |
| 3 | 3 | 3 | 3 | 6 | `≥ 6` → high = 2 |

Loop ends with `high = 2`. Return `k + high + 1 = 6 + 2 + 1 = 9`. ✓

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
