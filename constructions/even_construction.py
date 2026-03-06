"""Even-case Hamiltonian decomposition of the Cayley digraph of Z_m^3.

Constructs three arc-disjoint directed Hamiltonian cycles for any even m >= 4.

The construction works in fiber coordinates (s, x, y) where s = i+j+k mod m,
x = i, y = j. The structure is:

  - Bulk layers (s = 0, ..., m-3): constant XYI at every position
  - Staircase layer (s = m-2): parity-sensitive structured layer
  - Terminal layer (s = m-1): row-block of YIX/IYX

Small cases m = 4, 6, 8 use explicit exceptional tables.
For m >= 10 (even), a uniform closed-form rule applies.

The staircase layer has a top half (rows 0..h) and a bottom half (rows h+1..m-1),
where h = m/2. The bottom half depends on the parity of h.
"""

from itertools import product as iprod


# Exceptional tables for m = 4, 6, 8
_SMALL_EVEN = {
    4: [
        [["XYI"] * 4 for _ in range(4)],
        [["XYI"] * 4 for _ in range(4)],
        [
            ["XYI", "XYI", "YXI", "YIX"],
            ["XIY", "XIY", "IYX", "IXY"],
            ["XIY", "YIX", "XIY", "IXY"],
            ["YXI", "XIY", "XIY", "IYX"],
        ],
        [
            ["IXY", "IXY", "IXY", "IXY"],
            ["YXI", "YXI", "YXI", "YXI"],
            ["YXI", "YXI", "YXI", "YXI"],
            ["IXY", "IXY", "IXY", "IXY"],
        ],
    ],
    6: [
        [["XYI"] * 6 for _ in range(6)],
        [["XYI"] * 6 for _ in range(6)],
        [["XYI"] * 6 for _ in range(6)],
        [["XYI"] * 6 for _ in range(6)],
        [
            ["XYI", "XYI", "XYI", "XYI", "IYX", "YXI"],
            ["XYI", "XYI", "XYI", "XYI", "IXY", "IYX"],
            ["XIY", "XIY", "XIY", "YIX", "YXI", "XIY"],
            ["XIY", "XIY", "YIX", "XIY", "IXY", "XIY"],
            ["XYI", "YXI", "XIY", "XIY", "IYX", "XYI"],
            ["YXI", "XYI", "XYI", "XYI", "IYX", "XYI"],
        ],
        [
            ["YIX"] * 6,
            ["YIX"] * 6,
            ["IYX"] * 6,
            ["IYX"] * 6,
            ["YIX"] * 6,
            ["YIX"] * 6,
        ],
    ],
    8: [
        [["XYI"] * 8 for _ in range(8)],
        [["XYI"] * 8 for _ in range(8)],
        [["XYI"] * 8 for _ in range(8)],
        [["XYI"] * 8 for _ in range(8)],
        [["XYI"] * 8 for _ in range(8)],
        [["XYI"] * 8 for _ in range(8)],
        [
            ["XYI", "XYI", "XYI", "XYI", "XYI", "XYI", "IYX", "YXI"],
            ["XYI", "XYI", "XYI", "XYI", "XYI", "XYI", "IXY", "IYX"],
            ["XIY", "XIY", "XIY", "XIY", "XIY", "YIX", "XYI", "IXY"],
            ["XIY", "XIY", "XIY", "XIY", "YIX", "XIY", "XIY", "IXY"],
            ["XIY", "XIY", "XIY", "YIX", "XIY", "XIY", "XIY", "IXY"],
            ["XYI", "XYI", "YXI", "XIY", "XIY", "XIY", "YIX", "XYI"],
            ["XYI", "YXI", "XYI", "XYI", "XYI", "XYI", "IYX", "XYI"],
            ["YXI", "XYI", "XYI", "XYI", "XYI", "XYI", "IYX", "XYI"],
        ],
        [
            ["YIX"] * 8,
            ["YIX"] * 8,
            ["YIX"] * 8,
            ["IYX"] * 8,
            ["IYX"] * 8,
            ["YIX"] * 8,
            ["YIX"] * 8,
            ["YIX"] * 8,
        ],
    ],
}


def _predicted_layers(m):
    """Uniform even construction for m = 2h >= 10."""
    h = m // 2
    layers = [[["XYI"] * m for _ in range(m)] for _ in range(m)]

    # Bulk layers: already XYI everywhere (layers 0 .. m-3)

    # Penultimate staircase layer (s = m-2)
    pen = [["XYI"] * m for _ in range(m)]

    # Top half
    pen[0] = ["XYI"] * (m - 2) + ["IYX", "YXI"]
    pen[1] = ["XYI"] * (m - 2) + ["IXY", "IYX"]
    for x in range(2, h + 1):
        row = ["XYI"] * m
        row[m - 1 - x] = "YXI"
        row[m - 1] = "IYX"
        pen[x] = row

    # Bottom half
    for x in range(h + 1, m):
        d = m - 1 - x  # 0 <= d <= h-2
        if h % 2 == 0:
            if d == h - 2:
                row = ["XIY"] * d + ["YIX"] + ["XYI"] * (m - d - 3) + ["YXI", "XIY"]
            elif d in (h - 3, h - 4):
                row = ["XIY"] * d + ["YIX"] + ["XIY"] * (m - d - 3) + ["IXY", "XIY"]
            elif d == h - 5:
                row = ["XYI"] * d + ["YXI"] + ["XIY"] * (m - d - 3) + ["IYX", "XYI"]
            else:
                row = ["XYI"] * d + ["YXI"] + ["XYI"] * (m - d - 3) + ["IYX", "XYI"]
        else:
            if d == h - 2:
                row = ["XIY"] * d + ["YIX"] + ["XYI"] * (m - d - 2) + ["IXY"]
            elif d in (h - 3, h - 4):
                row = ["XIY"] * d + ["YIX"] + ["XIY"] * (m - d - 2) + ["IXY"]
            elif d == h - 5:
                row = ["XYI"] * d + ["YXI"] + ["XIY"] * (m - d - 3) + ["YIX", "XYI"]
            else:
                row = ["XYI"] * d + ["YXI"] + ["XYI"] * (m - d - 3) + ["IYX", "XYI"]
        pen[x] = row

    layers[m - 2] = pen

    # Terminal layer (s = m-1)
    last = [["YIX"] * m for _ in range(m)]
    for x in [h + 2, h + 3]:
        if x < m:
            last[x] = ["IYX"] * m
    layers[m - 1] = last

    return layers


def even_fiber_layers(m):
    """Return fiber-coordinate layer tables for even m >= 4.

    Returns a list of m tables, each m x m, where table[s][x][y] is a
    string like 'XYI' (3 chars: direction for color 1, 2, 3).
    """
    if m < 4 or m % 2 != 0:
        raise ValueError(f"m must be even and >= 4, got {m}")

    if m in _SMALL_EVEN:
        return _SMALL_EVEN[m]

    return _predicted_layers(m)


def layers_to_cycles(m, layers):
    """Convert fiber-coordinate layers to three Hamiltonian cycles.

    Each cycle is a list of m^3 tuples (i, j, k) in traversal order.
    """
    delta = {"I": (0, 0, 1), "X": (1, 0, 0), "Y": (0, 1, 0)}

    # Build direction map
    direction = {}
    for i, j, k in iprod(range(m), repeat=3):
        s = (i + j + k) % m
        x, y = i, j
        cell = layers[s][x][y]
        direction[(i, j, k)] = (cell[0], cell[1], cell[2])

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
    """Return a Hamiltonian decomposition for even m >= 4.

    Returns (cycle0, cycle1, cycle2) where each cycle is a list of m^3
    tuples (i,j,k) in traversal order.
    """
    layers = even_fiber_layers(m)
    return layers_to_cycles(m, layers)


if __name__ == "__main__":
    import sys
    import time

    ms = [int(x) for x in sys.argv[1:]] if len(sys.argv) > 1 else list(range(4, 22, 2))
    for m in ms:
        t0 = time.time()
        cycles = decompose(m)
        elapsed = time.time() - t0
        ok = all(len(c) == m ** 3 for c in cycles)
        print(f"m={m:3d}  n={m**3:7d}  ok={ok}  ({elapsed:.3f}s)")
