# Find the Row with Maximum Number of 1's

## Problem

Given a 2D binary matrix where **each row is sorted** (zeros followed by ones), return the **index of the row** containing the maximum number of `1`s. If multiple rows tie, return the smallest index. If no row contains a `1`, return `-1`.

```
[[0,1,1,1],
 [0,0,1,1],
 [1,1,1,1],
 [0,0,0,0]]   → 2

[[0,0],
 [0,0]]       → -1
```

## Approach — Lower Bound Per Row

Because each row is sorted (`0`s then `1`s), the count of `1`s in a row equals `n - lowerBound(row, 1)` — the index of the first `1` tells us how many follow.

1. For each row, binary search for the leftmost index `firstOne` where `row[mid] >= 1`.
2. Count of ones in that row = `n - firstOne` (or `0` if no `1` exists).
3. Track the row with the strictly greater count — strict `>` preserves the first-occurrence tie-break.
4. Initialize `result = -1` so the "no ones anywhere" case returns `-1` naturally.

### Why lower bound works

The predicate `row[mid] >= 1` is monotonic across a sorted binary row: false on the `0` prefix, true on the `1` suffix. Standard leftmost-true binary search.

## Complexity
- **Time:** `O(R · log C)` — one binary search per row.
- **Space:** `O(1)`.

A linear scan per row would be `O(R · C)`. For wide matrices (large `C`), the `log C` factor is the win.

## Trace — `mat = [[0,1,1,1],[0,0,1,1],[1,1,1,1],[0,0,0,0]]`

| row | lowerBound(·, 1) | count = 4 − firstOne | maxi after | result after |
|---|---|---|---|---|
| 0: `[0,1,1,1]` | 1 | 3 | 3 | 0 |
| 1: `[0,0,1,1]` | 2 | 2 | 3 | 0 |
| 2: `[1,1,1,1]` | 0 | 4 | 4 | 2 |
| 3: `[0,0,0,0]` | −1 | 0 | 4 | 2 |

Return `2`.

## Compile & Run
```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
