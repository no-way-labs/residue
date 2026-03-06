"""Full verification suite for Hamiltonian decompositions of Z_m^3.

Verifies both the odd and even constructions for all m from 3 to a given
upper bound. For each m, checks that:

  1. Each cycle has exactly m^3 vertices
  2. Each cycle visits every vertex exactly once
  3. Every arc is a valid Cayley digraph arc
  4. No arc is shared between cycles
  5. All 3m^3 arcs are covered

Usage:
    python verify.py              # verify m = 3..101
    python verify.py --max-m 50   # verify m = 3..50
    python verify.py --m 42       # verify just m = 42
"""

import argparse
import sys
import time
from itertools import product as iprod

from odd_construction import decompose as odd_decompose
from even_construction import decompose as even_decompose


def verify(m, cycles):
    """Verify a Hamiltonian decomposition of Cay(Z_m^3, {e1, e2, e3}).

    Args:
        m: modulus
        cycles: tuple of 3 lists, each a list of m^3 vertex tuples (i,j,k)

    Returns:
        (True, "OK") or (False, error_message)
    """
    if cycles is None:
        return False, "no decomposition provided"
    if len(cycles) != 3:
        return False, f"expected 3 cycles, got {len(cycles)}"

    n = m ** 3
    all_vertices = set(iprod(range(m), repeat=3))
    used_arcs = set()

    for c, cycle in enumerate(cycles):
        if len(cycle) != n:
            return False, f"cycle {c}: length {len(cycle)}, expected {n}"

        seen = set()
        for idx, v in enumerate(cycle):
            if v in seen:
                return False, f"cycle {c}: vertex {v} visited twice"
            seen.add(v)

            w = cycle[(idx + 1) % n]
            i, j, k = v

            valid_successors = [
                ((i + 1) % m, j, k),
                (i, (j + 1) % m, k),
                (i, j, (k + 1) % m),
            ]
            if w not in valid_successors:
                return False, f"cycle {c}: {v} -> {w} is not a valid arc"

            d = valid_successors.index(w)
            arc = (v, d)
            if arc in used_arcs:
                return False, f"arc {v} dir {d} used by multiple cycles"
            used_arcs.add(arc)

        if seen != all_vertices:
            missing = all_vertices - seen
            return False, f"cycle {c}: missing {len(missing)} vertices"

    if len(used_arcs) != 3 * n:
        return False, f"only {len(used_arcs)} arcs used, expected {3 * n}"

    return True, "OK"


def verify_round_maps(m, layers):
    """Verify via round-map composition (faster for large m).

    Instead of tracing full cycles, compose the m layer permutations
    for each color and check that the result is a single m^2-cycle.

    Args:
        m: modulus
        layers: list of m tables, each m x m of direction strings

    Returns:
        (True, "OK") or (False, error_message)
    """
    n = m * m
    pts = [(x, y) for x in range(m) for y in range(m)]
    idx = {p: i for i, p in enumerate(pts)}
    delta = {"I": (0, 0), "X": (1, 0), "Y": (0, 1)}

    for c in range(3):
        # Compose round map
        perm = list(range(n))
        for s_layer in layers:
            mapping = [None] * n
            for x in range(m):
                for y in range(m):
                    cell = s_layer[x][y]
                    if isinstance(cell, tuple):
                        d = cell[c]
                    else:
                        d = cell[c]
                    dx, dy = delta[d]
                    mapping[idx[(x, y)]] = idx[((x + dx) % m, (y + dy) % m)]
            perm = [mapping[p] for p in perm]

        # Check single cycle
        seen = [False] * n
        num_cycles = 0
        for i in range(n):
            if seen[i]:
                continue
            num_cycles += 1
            cur = i
            while not seen[cur]:
                seen[cur] = True
                cur = perm[cur]

        if num_cycles != 1:
            return False, f"color {c}: round map has {num_cycles} cycles, expected 1"

    return True, "OK"


def main():
    parser = argparse.ArgumentParser(
        description="Verify Hamiltonian decompositions of Z_m^3"
    )
    parser.add_argument(
        "--max-m", type=int, default=201,
        help="verify all m from 3 to this value (default: 201)"
    )
    parser.add_argument("--m", type=int, default=None,
                        help="verify just this single m value")
    parser.add_argument("--fast", action="store_true",
                        help="use round-map verification (faster, less thorough)")
    args = parser.parse_args()

    if args.m is not None:
        ms = [args.m]
    else:
        ms = list(range(3, args.max_m + 1))
        # Skip m = 2 (impossible)
        ms = [m for m in ms if m >= 3]

    total = len(ms)
    passed = 0
    failed = 0
    t_start = time.time()

    for m in ms:
        t0 = time.time()

        # Choose construction
        if m % 2 == 1:
            cycles = odd_decompose(m)
        else:
            cycles = even_decompose(m)

        t_construct = time.time() - t0

        # Verify
        t0 = time.time()
        if args.fast:
            # Use round-map verification
            from odd_construction import odd_fiber_layers
            from even_construction import even_fiber_layers
            if m % 2 == 1:
                layers = odd_fiber_layers(m)
            else:
                layers = even_fiber_layers(m)
            ok, msg = verify_round_maps(m, layers)
        else:
            ok, msg = verify(m, cycles)
        t_verify = time.time() - t0

        status = "PASS" if ok else "FAIL"
        if ok:
            passed += 1
        else:
            failed += 1

        parity = "odd " if m % 2 == 1 else "even"
        print(
            f"  m={m:3d} ({parity})  n={m**3:8d}  {status:4s}  "
            f"construct={t_construct:.3f}s  verify={t_verify:.3f}s"
            f"{'  ' + msg if not ok else ''}"
        )

    elapsed = time.time() - t_start
    print(f"\n{'=' * 60}")
    print(f"  Total: {total}  Passed: {passed}  Failed: {failed}")
    print(f"  Elapsed: {elapsed:.1f}s")
    print(f"{'=' * 60}")

    return 0 if failed == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
