"""Odd-case Hamiltonian decomposition of the Cayley digraph of Z_m^3.

Constructs three arc-disjoint directed Hamiltonian cycles for any odd m >= 3.

The construction works in fiber coordinates (s, x, y) where s = i+j+k mod m,
x = i, y = j. At each layer transition s -> s+1, the three available moves
are X: (x,y)->(x+1,y), Y: (x,y)->(x,y+1), I: (x,y)->(x,y).

The key 2D gadget uses the diagonal D = {(x,y) : x+y = 0 mod m}:
  A: use X off D, Y on D
  B: use Y off D, X on D

Both A and B are Hamiltonian cycles on Z_m^2. A word with a copies of A
and b copies of B gives a round map that is an m^2-cycle iff gcd(a+b, m) = 1
and gcd(b-a, m) = 1.

Layer types:
  P0 = (I, B, A)    -- color 1 gets I, color 2 gets B, color 3 gets A
  P1 = (B, I, A)
  P2 = (A, B, I)
  Q2 = (B, A, I)

For odd m >= 5, choose odd s with gcd(s,m) = gcd(s+2,m) = 1,
set t = (s-1)/2, and use: 1xP0, 1xP1, txP2, (m-2-t)xQ2.

For m = 3: explicit exceptional table.
"""

from math import gcd
from itertools import product as iprod


def _choose_s(m):
    """Find odd s with gcd(s,m) = gcd(s+2,m) = 1."""
    for s in range(1, m, 2):
        if gcd(s, m) == 1 and gcd(s + 2, m) == 1:
            return s
    raise ValueError(f"no valid s found for m={m}")


def _make_layer_table(m, layer_type):
    """Return an m x m table of direction triples for one layer.

    Each cell (x, y) gets a triple (d1, d2, d3) where d_c in {I, X, Y}
    is the matching for color c.

    layer_type is one of 'P0', 'P1', 'P2', 'Q2'.
    """
    table = [[None] * m for _ in range(m)]
    for x in range(m):
        for y in range(m):
            on_diag = (x + y) % m == 0
            # A: X off diagonal, Y on diagonal
            # B: Y off diagonal, X on diagonal
            A = "Y" if on_diag else "X"
            B = "X" if on_diag else "Y"
            if layer_type == "P0":
                table[x][y] = ("I", B, A)
            elif layer_type == "P1":
                table[x][y] = (B, "I", A)
            elif layer_type == "P2":
                table[x][y] = (A, B, "I")
            elif layer_type == "Q2":
                table[x][y] = (B, A, "I")
            else:
                raise ValueError(f"unknown layer type: {layer_type}")
    return table


def _m3_layers():
    """Explicit construction for m = 3."""
    m = 3
    layers = [[[None] * m for _ in range(m)] for _ in range(m)]

    # Layer 0: (I, X, Y) everywhere
    for x in range(m):
        for y in range(m):
            layers[0][x][y] = ("I", "X", "Y")

    # Layer 1
    for x in range(m):
        for y in range(m):
            if x in (0, 1):
                layers[1][x][y] = ("I", "Y", "X")
            else:  # x == 2
                layers[1][x][y] = ("Y", "I", "X")

    # Layer 2
    for x in range(m):
        for y in range(m):
            if x == 0:
                layers[2][x][y] = ("X", "I", "Y")
            else:  # x in (1, 2)
                layers[2][x][y] = ("X", "Y", "I")

    return layers


def odd_fiber_layers(m):
    """Return fiber-coordinate layer tables for odd m >= 3.

    Returns a list of m tables, each m x m, where table[s][x][y] is a
    triple (d1, d2, d3) with d_c in {'I', 'X', 'Y'}.
    """
    if m < 3 or m % 2 == 0:
        raise ValueError(f"m must be odd and >= 3, got {m}")

    if m == 3:
        return _m3_layers()

    s = _choose_s(m)
    t = (s - 1) // 2

    # Build layer schedule: 1xP0, 1xP1, txP2, (m-2-t)xQ2
    schedule = ["P0", "P1"] + ["P2"] * t + ["Q2"] * (m - 2 - t)
    assert len(schedule) == m

    return [_make_layer_table(m, lt) for lt in schedule]


def layers_to_cycles(m, layers):
    """Convert fiber-coordinate layers to three Hamiltonian cycles.

    Each cycle is a list of m^3 tuples (i, j, k) in traversal order.
    """
    # Build direction map: at vertex (i,j,k), which direction does each color use?
    direction = {}
    for i, j, k in iprod(range(m), repeat=3):
        s = (i + j + k) % m
        x, y = i, j
        triple = layers[s][x][y]
        direction[(i, j, k)] = triple

    delta = {"I": (0, 0, 1), "X": (1, 0, 0), "Y": (0, 1, 0)}

    cycles = []
    for c in range(3):
        cycle = []
        start = (0, 0, 0)
        v = start
        for _ in range(m ** 3):
            cycle.append(v)
            d = direction[v][c]
            di, dj, dk = delta[d]
            i, j, k = v
            v = ((i + di) % m, (j + dj) % m, (k + dk) % m)
        assert v == start, f"cycle {c} did not close"
        cycles.append(cycle)

    return tuple(cycles)


def decompose(m):
    """Return a Hamiltonian decomposition for odd m >= 3.

    Returns (cycle0, cycle1, cycle2) where each cycle is a list of m^3
    tuples (i,j,k) in traversal order.
    """
    layers = odd_fiber_layers(m)
    return layers_to_cycles(m, layers)


if __name__ == "__main__":
    import sys
    import time

    ms = [int(x) for x in sys.argv[1:]] if len(sys.argv) > 1 else list(range(3, 22, 2))
    for m in ms:
        t0 = time.time()
        cycles = decompose(m)
        elapsed = time.time() - t0
        # Quick verify: check cycle lengths
        ok = all(len(c) == m ** 3 for c in cycles)
        print(f"m={m:3d}  n={m**3:7d}  ok={ok}  ({elapsed:.3f}s)")
