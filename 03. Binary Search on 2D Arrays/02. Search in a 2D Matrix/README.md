# Search in a 2D Matrix

## Problem

Given an `R × C` matrix where:
- Each row is sorted left-to-right.
- The first element of each row is greater than the last element of the previous row.

Return `true` if `target` exists in the matrix.

```
[[ 1, 3, 5, 7],
 [10,11,16,20],
 [23,30,34,60]]   target = 3   → true
                  target = 13  → false
```

## The Core Insight

The two ordering constraints together mean that flattening the matrix row-by-row produces a **single sorted 1D array** of length `R · C`. So the problem reduces to plain binary search — no row-then-column two-pass needed.

The trick is mapping a flat index `mid ∈ [0, R·C − 1]` back to `(i, j)`:

```
i = mid / C
j = mid % C
```

`C` (column count) is the row stride.

## Approach — Binary Search on the Flat Index

1. `low = 0, high = R*C - 1`.
2. `mid = low + (high - low) / 2`. Convert to `(i, j) = (mid / C, mid % C)`.
3. Compare `mat[i][j]` to `target`: equal → return `true`; greater → `high = mid - 1`; smaller → `low = mid + 1`.
4. Loop ends without a hit → return `false`.

## Complexity
- **Time:** `O(log(R · C))` — single binary search over the virtual flat array.
- **Space:** `O(1)`.

The naive two-stage approach (binary search the first column for the right row, then binary search that row) is `O(log R + log C) = O(log(R·C))` — same asymptotic cost, but more code and an extra edge case when the row boundary is fuzzy. The flat-index version is tighter.

## Watch out for: `R * C` overflow

`R, C ≤ ~10^4` per typical constraints, so `R * C` can hit `~10^8` — fits in `int` but not by much. For larger constraints, promote to `long long`:

```cpp
long long low = 0, high = (long long)R * C - 1;
long long mid = low + (high - low) / 2;
int i = mid / C, j = mid % C;
```

## Trace — `mat = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13`

`R = 3, C = 4`, so flat range is `[0, 11]`.

| iter | low | high | mid | (i, j) | mat[i][j] | branch |
|---|---|---|---|---|---|---|
| 1 | 0 | 11 | 5 | (1, 1) | 11 | `< 13` → low = 6 |
| 2 | 6 | 11 | 8 | (2, 0) | 23 | `> 13` → high = 7 |
| 3 | 6 | 7  | 6 | (1, 2) | 16 | `> 13` → high = 5 |
| 4 | 6 | 5  | — | — | — | loop ends → return `false` |

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
