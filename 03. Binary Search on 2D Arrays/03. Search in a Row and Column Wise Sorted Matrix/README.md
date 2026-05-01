# Search in a Row and Column Wise Sorted Matrix

## Problem

Given an `R × C` matrix where:
- Each row is sorted left-to-right.
- Each column is sorted top-to-bottom.

Return `true` if `target` exists. **No** relationship between the end of one row and the start of the next — so we can't flatten and binary search like in *Search in 2D Matrix I*.

```
[[ 1, 4, 7,11,15],
 [ 2, 5, 8,12,19],
 [ 3, 6, 9,16,22],
 [10,13,14,17,24],
 [18,21,23,26,30]]   target = 5  → true
                     target = 20 → false
```

## The Core Insight — Staircase Search

Start at a corner where moving in one direction increases values and the other decreases. The **top-right** corner works:

- Below `matrix[i][j]` → only larger values (column sorted descending… upward, ascending downward).
- Left of `matrix[i][j]` → only smaller values.

So at each step, comparing `matrix[i][j]` to `target` rules out an entire row or column:

| comparison | what's eliminated | move |
|---|---|---|
| `matrix[i][j] == target` | found | return `true` |
| `matrix[i][j] < target`  | the entire row `i` to the left is too small | `i++` (drop this row) |
| `matrix[i][j] > target`  | the entire column `j` below is too large | `j--` (drop this column) |

Each step eliminates one full row or column, so we walk at most `R + C` cells. Bottom-left corner works symmetrically; top-left and bottom-right do not (both directions go the same way).

## Approach

1. `i = 0, j = C - 1` (top-right corner).
2. While `i < R && j >= 0`:
   - Equal → return `true`.
   - Cell `< target` → `i++`.
   - Cell `> target` → `j--`.
3. Loop exits when we walk off the grid → return `false`.

## Complexity
- **Time:** `O(R + C)` — each step strictly increases `i` or decreases `j`, bounded by `R + C` total moves.
- **Space:** `O(1)`.

A per-row binary search is `O(R · log C)`, which is worse for square matrices (`R · log R` vs `2R`) and the same order only when one dimension is tiny. Staircase wins.

## Why not top-left or bottom-right

At top-left, both `i++` and `j++` go to *larger* values — neither move can prune toward a smaller `target`. Same problem in reverse at bottom-right. The corner must straddle the gradient.

## Trace — searching for `5` in the example matrix

| step | (i, j) | matrix[i][j] | branch |
|---|---|---|---|
| 1 | (0, 4) | 15 | `> 5` → j = 3 |
| 2 | (0, 3) | 11 | `> 5` → j = 2 |
| 3 | (0, 2) | 7  | `> 5` → j = 1 |
| 4 | (0, 1) | 4  | `< 5` → i = 1 |
| 5 | (1, 1) | 5  | **found** → `true` |

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
