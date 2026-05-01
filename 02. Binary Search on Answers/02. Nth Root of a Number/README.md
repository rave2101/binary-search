# Nth Root of a Number

## Problem

Given two integers `N` and `M`, return the integer `x` such that `x^N == M`. If no such integer exists, return `-1`.

```
N = 2,  M = 9     →  3      (3^2 = 9)
N = 3,  M = 27    →  3      (3^3 = 27)
N = 4,  M = 69    →  -1     (2^4 = 16, 3^4 = 81 — no integer root)
N = 5,  M = 243   →  3
```

---

## The Core Insight

`f(x) = x^N` is **strictly increasing** for `x ≥ 1` and `N ≥ 1`. So as `mid` walks `1 → M`, `mid^N` is monotonic — a sorted sequence. We binary search for the exact value `M`; if we never land on it, no integer root exists.

```
mid:       1   2   3   4   5
mid^3:     1   8  27  64 125
vs M=27:   <   <   =   >   >
                   ^
                   exact hit → return 3
```

---

## Approach — Binary Search + Fast Exponentiation with Early Exit

1. Search `mid ∈ [1, M]`. For each `mid`, compute `mid^N` and compare against `M`.
2. Three branches: `==M` returns `mid`; `>M` shrinks `high`; `<M` grows `low`.
3. Computing `mid^N` naively can overflow even `long long` for large `mid` and `N`. Two tricks together:
   - **Binary exponentiation** (`O(log N)` multiplications instead of `O(N)`).
   - **Early exit**: the moment a partial product exceeds `M`, return immediately — the caller only needs to know "too big", not the exact value.

### Why the early exit is safe

Once any intermediate product exceeds `M`, the final result will too (all factors are `≥ 1`). Returning that intermediate value preserves the `current > M` comparison in the caller. This is what keeps `mid^N` from overflowing for large inputs like `M = 2^31 − 1`.

---

## Complexity
| | |
|---|---|
| **Time** | `O(log M · log N)` — binary search over `[1, M]`, each step does fast exponentiation in `O(log N)` |
| **Space** | `O(1)` — iterative, no recursion stack |

---

## Trace — `N = 3, M = 27`

| iter | low | high | mid | mid^3 | branch |
|---|---|---|---|---|---|
| 1 | 1 | 27 | 14 | 2744 | `> 27` → high = 13 |
| 2 | 1 | 13 | 7  | 343  | `> 27` → high = 6  |
| 3 | 1 | 6  | 3  | 27   | `== 27` → **return 3** |

### Trace inside `powUtil(3, 3, 27)`

| step | pow | a | result | action |
|---|---|---|---|---|
| start | 3 | 3 | 1 | pow odd → `result = 3`, pow = 2 |
| | 2 | 3 | 3 | pow even → `a = 9`, pow = 1 |
| | 1 | 9 | 3 | pow odd → `result = 27`, pow = 0 |
| end | 0 | 9 | 27 | return 27 |

---

## Common Bugs to Avoid

### 1. Computing `mid^N` without overflow guard

```cpp
// WRONG — even long long overflows for mid=46341, N=2 if M is near INT_MAX,
// and certainly for larger N
long long p = 1;
for (int i = 0; i < N; i++) p *= mid;
```

The early-exit `if (result > M) return result;` after every multiplication is what makes this safe. Without it, `powUtil(100000, 10, ...)` produces nonsense.

### 2. Starting `high = M` is correct, but `high = M/2` is **not**

Tempting analogy with sqrt, but for `N = 1` you need `high ≥ M`. The `if (N == 1) return M;` early return sidesteps this — keep it.

### 3. `(low + high) / 2` overflowing

`M` can be up to `INT_MAX`, so `low + high` overflows `int`. Use `low + (high - low) / 2`.

### 4. Returning `low` or `high` at the end

In this problem there is no "floor of the Nth root" — the spec wants exact match or `-1`. Initialize `result = -1` and only return it after the loop, never `low - 1`.

---

## Compile & Run

```bash
g++ -std=c++17 -o solution solution.cpp && ./solution
```
