# Find Peak Element (2D Matrix)

## Problem

Given an `R × C` matrix where no two adjacent cells are equal, return the position `[i, j]` of **any** peak — a cell strictly greater than its 4 orthogonal neighbors (top, bottom, left, right). Out-of-grid neighbors are treated as `-1`.

```
[[10,20,15],
 [21,30,14],
 [ 7,16,32]]   one valid answer → (1,1) value 30
                another valid answer → (2,2) value 32
```

## The Core Insight — Binary Search on Columns

Pick a column `mid`. Find the row `idx` where `mat[idx][mid]` is the **maximum in that column**. Then:

- `mat[idx][mid]` is automatically `>` its top and bottom neighbors (it's the column max).
- Compare it only against its **horizontal** neighbors `mat[idx][mid-1]` and `mat[idx][mid+1]`:
  - Greater than both → it's a peak. Return.
  - Smaller than the **left** neighbor → there must be a peak somewhere in columns `[low, mid-1]` (climb the gradient). Set `high = mid-1`.
  - Smaller than the **right** neighbor → peak in `[mid+1, high]`. Set `low = mid+1`.

Why a peak must exist on the side we move toward: the matrix is finite. Climbing the value gradient from any starting cell, you can't go up forever — you'll hit a local max. Restricting that climb to the chosen half-grid still works because the boundary acts as `-1`.

## Approach

```
1. low = 0, high = C - 1.
2. mid = (low + high) / 2.
3. idx = argmax over rows of mat[i][mid].
4. Compare mat[idx][mid] to its left/right neighbors.
   - both smaller → return {idx, mid}
   - left bigger  → high = mid - 1
   - else         → low = mid + 1
5. If loop ends, return {-1, -1} (won't happen on valid input).
```

## Complexity
- **Time:** `O(R · log C)` — `log C` binary search steps, each does an `O(R)` column scan.
- **Space:** `O(1)`.

Symmetric variant: binary search on rows, scan column-of-mid for the max → `O(C · log R)`. Pick the dimension with the smaller log.

---

## Why not flatten to 1D and reuse the 1D peak algorithm?

Tempting — *Search in a 2D Matrix I* used `i = mid/C, j = mid%C` to treat the matrix as a flat sorted array. Why doesn't that work here?

The 1D peak algorithm relies on this invariant: at each step, comparing `arr[mid]` to `arr[mid+1]` tells you which half **must** contain a peak. If `arr[mid] < arr[mid+1]`, climbing rightward leads to a peak (you can't ascend forever in a finite array — a local max must exist on the right).

Two things break when you flatten a 2D matrix row-major:

1. **`mid` and `mid+1` may not be spatial neighbors.** When `mid % C == C - 1`, the next flat index is the start of the next row — not adjacent in the grid. The "going up means peak ahead" argument depends on actual adjacency.

2. **A 1D peak in the flat array isn't a 2D peak.** Even if you find a flat-index `k` where `flat[k-1] < flat[k] > flat[k+1]`, the cell `(k/C, k%C)` could still be smaller than its **vertical** neighbors `(k/C ± 1, k%C)`. The 1D algorithm has no information about those.

Striver's column binary search dodges both issues: by picking the **column max** at `mid`, the vertical comparisons are pre-resolved, and the only thing left to check is left/right — exactly the situation the 1D peak argument handles.

So the column-max-then-compare-horizontally trick is what gives a clean monotone-climb argument in 2D. Plain flattening doesn't preserve enough structure.

## Trace — `mat = [[10,20,15],[21,30,14],[7,16,32]]`

`R = 3, C = 3`, so binary search columns `[0, 2]`.

| iter | low | high | mid | column [mid] | idx (row of col-max) | mat[idx][mid] | left | right | branch |
|---|---|---|---|---|---|---|---|---|---|
| 1 | 0 | 2 | 1 | `[20,30,16]` | 1 | 30 | 21 | 14 | both smaller → **return (1, 1)** |

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
