# Completing Claude's Cycles

**Hamiltonian decomposition of Z_m^3 Cayley digraphs for all m > 2.**

This repository contains constructions, proofs, exploration logs, and a verification suite for the Hamiltonian decomposition problem posed by Knuth in ["Claude's Cycles"](https://cs.stanford.edu/~knuth/papers/claude-cycles.pdf) (2026).

## The Problem

Consider the digraph with m^3 vertices ijk for 0 ≤ i, j, k < m, and three arcs from each vertex: to i⁺jk, ij⁺k, and ijk⁺, where i⁺ = (i+1) mod m. Decompose the arcs into three directed Hamiltonian cycles, for all m > 2.

Knuth's Claude solved the odd case in 31 explorations with significant human guidance. The even case was left open.

## Results

| Case | Status | Construction |
|------|--------|-------------|
| m = 2 | Impossible | Exhaustive search (Aubert & Schneider, 1982) |
| Odd m ≥ 3 | **Solved** (symbolic proof) | Diagonal layer schedule: 4 layer types, count-based |
| Even m ≥ 4 | **Solved** (verified to m = 100) | Bulk XYI + staircase + terminal layer |

**Odd case:** 5 explorations, no human intervention. Different construction from Knuth's (layer-level vs. vertex-level). Symbolic proof via skew-map criterion.

**Even case:** Closed-form construction — m−2 bulk layers of constant XYI, one structured staircase layer (parity-sensitive in h = m/2), one terminal row-block layer. Simpler than Stappers's CP-SAT program or Ho Boon Suan's GPT-5.3-codex construction.

## How It Was Found

Two LLM agents operating under a shared structured exploration prompt ("Residue"), with an orchestrator agent (also Claude Opus 4.6 Thinking) routing data and tools between them:

- **Agent O** (GPT-5.4 Thinking, Extra High — top-down symbolic reasoner): Solved odd case in 5 explorations. Discovered the layer-sign parity invariant for even m. Stalled at m = 10.
- **Agent C** (Claude Opus 4.6 Thinking — bottom-up computational solver): Hit the serpentine dead end (5 explorations vs. ~10 for Knuth's Claude), then achieved a 67,000× speedup via MRV + forward checking. Produced solutions for m = 3 through 12.
- **Orchestrator** (Claude Opus 4.6 Thinking, directed by the author): Transferred Agent C's solutions in fiber-coordinate format to Agent O. Transferred the MRV solver, which Agent O adapted into a seeded solver. The combination produced insight neither agent could reach alone.

## Repository Structure

```
residue/
├── README.md
├── constructions/
│   ├── odd_construction.py    # decompose(m) for odd m ≥ 3
│   ├── even_construction.py   # decompose(m) for even m ≥ 4
│   └── verify.py              # full verification suite
├── prompt/
│   └── residue.md             # the structured exploration prompt
├── logs/
│   ├── fast_agent_log.md      # Agent O: 28 explorations (odd + even)
│   ├── slow_agent_log.md      # Agent C: 15 explorations
│   └── meta_log.md            # orchestration decisions
├── lean/                      # formalization (in progress)
└── paper/
    └── completing_claudes_cycles.tex
```

## Quick Start

```bash
cd constructions

# Verify all m from 3 to 101
python verify.py

# Verify a single value
python verify.py --m 42

# Fast mode (round-map composition, no full cycle tracing)
python verify.py --fast

# Generate a decomposition
python -c "
from odd_construction import decompose
cycles = decompose(7)
print(f'{len(cycles)} cycles, each length {len(cycles[0])}')
"
```

## The Residue Prompt

The key methodological contribution. Five design principles:

1. **Structure the record-keeping, not the reasoning.** Prescribes what to record (strategy, outcome, failure constraints, surviving structure, reformulations, concrete artifacts) but never what to try.
2. **Make failures retrievable.** Each failed exploration produces a structured record that prevents re-exploration of dead approaches.
3. **Force periodic synthesis.** Every 5 explorations, scan artifacts for patterns.
4. **Bound unproductive grinding.** If the Strategy Register hasn't changed in 5 explorations, stop and assess.
5. **Preserve session continuity.** Re-read the full log before starting each session.

See [prompt/residue.md](prompt/residue.md) for the full text.

## Key Mathematical Ideas

**Fiber coordinates.** Write vertices as (s, x, y) where s = i+j+k mod m. The three generators become layer transitions X, Y, I between consecutive s-values.

**2D diagonal gadget.** On the diagonal D = {(x,y) : x+y ≡ 0}, define matchings A (X off D, Y on D) and B (Y off D, X on D). Both are Hamiltonian cycles on Z_m^2.

**Skew-map criterion.** A word with a copies of A and b copies of B gives a round map that is an m^2-cycle iff gcd(a+b, m) = 1 and gcd(b-a, m) = 1.

**Layer-sign parity invariant.** For even m, any Hamiltonian decomposition must contain an odd number of sign-negative layers. This explains why the odd construction cannot extend and why Kempe-cycle local search gets trapped.

## References

- D. E. Knuth, "Claude's Cycles," Stanford CS, Feb 28 2026; rev. Mar 4 2026.
- J. Aubert & B. Schneider, "Graphes orientés indécomposables en circuits hamiltoniens," JCTB 32 (1982).
- B. Alspach, "Research Problem 59," Discrete Mathematics 50 (1984).
- S. Curran & D. Witte, "Hamilton paths in Cartesian products of directed cycles," Ann. Disc. Math. 27 (1985).
- I. Darijani, B. Miraftab, & D. W. Morris, "Arc-disjoint Hamiltonian paths in Cartesian products of directed cycles," Ars Math. Contemp. 25(2) (2025). arXiv:2203.11017.

## License

MIT
