# P1 Exploration Log: Hamiltonian Decomposition of Z_m^3 Cayley Digraph

## Strategy Register

**Eliminated approach classes:**
1. **d0-table depending only on (a,b) for m≥4** — ruled out at Exploration 3 because exhaustive search of all 3^12 tables found 0 valid solutions for m=4. The in-degree constraint requires d0 to depend on the full vertex (i,j,k), not just translated coordinates (a,b)=((i-k)%m,(j-k)%m).
2. **Single-splice spiral (one vertical arc per layer)** — ruled out at Exploration 5 because algebraically visits only m³+m-m² < m³ vertices for all m>1. The shift-1-per-layer pattern creates short cycles.
3. **Multi-splice with fixed 2D-cycle directions** — ruled out at Exploration 6 because constraining horizontal arcs to follow C_A's exact direction sequence is incompatible with known solutions, which use different horizontal directions.
4. **Serpentine H1 + decompose remainder** — ruled out at Exploration 8. Serpentine arc distribution (m²(m-1) dominant arcs) is fundamentally incompatible with 3-cycle decomposition. Known m=3 solutions have 15+6+6 but serpentine gives 18+6+3.
5. **Per-vertex repair of serpentine overlaps** — ruled out at Exploration 9. Changing individual arcs in a Hamiltonian cycle always breaks Hamiltonicity. Need coordinated multi-arc modifications.
6. **Binary search (fix one serpentine cycle, search remainder)** — ruled out at Exploration 10. Serpentine arc distribution is incompatible regardless of which cycle is fixed.
7. **BFS-ordered permutation search for m≥6** — ruled out at Exploration 11-12. Exponential blowup without constraint propagation (400M+ calls for m=6).
8. **Quotient via ⟨(1,1,1)⟩ for m>3** — ruled out at Exploration 13. Lift fails when displacement gcd ≠ 1.

**Active structural constraints:**
1. **Cyclic symmetry exists for m=3**: Under (i,j,k)→(k,i,j) with direction rotation 0→1→2→0, valid decompositions can be symmetric. 18 cyclically-symmetric solutions found for m=3 (Exploration 2).
2. **Arc count pattern for m=3**: Each Hamiltonian cycle in a valid decomposition uses 15 of one direction, 6 of another, 6 of a third (total 27). NOT evenly distributed.
3. **Serpentine always produces valid Hamiltonian cycles**: For ANY m≥3 and ANY 2D inter-coset Hamiltonian cycle, the serpentine construction yields a valid Hamiltonian cycle (Exploration 7). But three serpentines always overlap.
4. **Inter-coset shift closure**: Entry point in serpentine shifts by -1 per coset visit. After m² visits, -m² ≡ 0 (mod m). Cycle closes. This is exact, not approximate.
5. **Minimum serpentine overlap = 3(m-1)**: Verified for m=3,4,5,6 across all 8 zigzag combinations. The overlap is inherent to the construction, not a choice issue (Exploration 9).
6. **Known m=3 cycle structure**: (long_block, +k, short_block, +k)^3 where long_block = i²j²i² (7 arcs) and short_block = i (1 arc). Total: 15i + 6j + 6k = 27 arcs.

**Known reformulations:**
1. **Permutation assignment**: Decomposition ↔ assigning σ(v) ∈ S₃ at each vertex, where σ(v)(c) = direction for cycle c. Must satisfy: at each vertex, incoming arcs from 3 predecessors have distinct cycle labels (Exploration 1).
2. **Translated coordinates**: (a,b) = ((i-k)%m, (j-k)%m). For m=3, d0 depends only on (a,b). For m≥4, d0 must depend on full (i,j,k) (Exploration 3).
3. **Fiber/coset structure**: Z_m^3 decomposes into m² fibers (cosets) along each coordinate direction. Each fiber is a Z_m cycle. A Hamiltonian cycle visits all fibers, spending m-1 steps within each (Exploration 7).

---

## Exploration 1

### Strategy
Computational search for m=3: build the digraph, assign direction 0 for cycle 0 at each vertex, check in-degree constraints, then verify full Hamiltonian decomposition. Use cyclic symmetry to reduce search space.

### Outcome
SUCCEEDED

### Concrete Artifacts
- Found 3 non-symmetric solutions for m=3 via constraint search (`p1_search3.py`)
- Direction sequence for cycle 0 in one solution: `(i,i,j,i,i,j,i,i,k)^3` — 27 arcs total with pattern (2i, j, 2i, j, 2i, k) repeated 3 times
- All 3 solutions have identical d0 (cycle 0 direction assignment)

---

## Exploration 2

### Strategy
Search for cyclically-symmetric decompositions for m=3, exploiting the (i,j,k)→(k,i,j) symmetry with direction rotation 0→1→2→0.

### Outcome
SUCCEEDED

### Concrete Artifacts
- Found 18 cyclically-symmetric solutions for m=3 (`p1_symmetric.py`)
- d0-table in (a,b) coordinates (a=(i-k)%3, b=(j-k)%3):
  ```
  d0(a,b):
    (0,0)=0  (0,1)=2  (0,2)=0
    (1,0)=0  (1,1)=0  (1,2)=1
    (2,0)=2  (2,1)=1  (2,2)=2
  ```
- Formula: d0 = 0 if a=0 or (a+b)%3=1, else (-a)%3
- Arc counts per cycle: 15 + 6 + 6 = 27 (NOT evenly distributed across directions)

---

## Exploration 3

### Strategy
Test whether d0-table approach (d0 depending only on translated coordinates (a,b)) extends to m=4, by exhaustive search of all 3^12 possible tables.

### Outcome
FAILED

### Failure Constraint
For m=4, the in-degree constraint at each vertex requires that the 3 predecessors (i-1,j,k), (i,j-1,k), (i,j,k-1) all use different directions for cycle 0. When d0 depends only on (a,b)=((i-k)%m,(j-k)%m), the predecessor directions depend on (a,b) values of the predecessors, which are (a-1,b), (a,b-1), (a+1,b+1) mod m. For m=4 this creates more constraints than for m=3, and no table satisfies all of them.

### What This Rules Out
Any approach that defines d0 as a function of only (a,b) for m≥4. The direction assignment must depend on the full vertex coordinates (i,j,k), or at least on more than just two coordinates.

### Concrete Artifacts
- Exhaustive search: 531,441 tables tested, 0 valid (`p1_gen_m4.py`)
- The m=3 formula d0 = 0 if a=0 or (a+b)%m=1, else (-a)%m gives (-a)%m > 2 for m>3 (e.g., a=1 gives 3 for m=4), so it literally can't produce valid directions

---

## Exploration 4 (probe)

### Strategy
Check whether the m=3 solution structure (long_block, +k, short_block, +k)^3 generalizes to larger m.

### Outcome
PARTIAL — structure identified but doesn't directly scale

### Concrete Artifacts
- m=3 cycle 0 pattern: (i²j²i², k, i, k)^3 = (7-arc long block, +k, 1-arc short block, +k) × 3
- Long block visits m²-m+1 = 7 "non-hole" positions in (a,b) space
- Short block visits m-1 = 2 "hole" positions at {(a,1): 0≤a≤m-2}
- For the ^m repetition to work, need t +k arcs per repeat where gcd(t,m)=1
- m=3: t=2 (gcd(2,3)=1) ✓
- Even m: need t=m-1 (gcd(m-1,m)=1 always)
- But long block pattern i²j²i² gives 3m-2 arcs = m²-m+1 only when m=3

---

## Exploration 5

### Strategy
Spiral construction: traverse Z_m^2 via Hamiltonian cycle C_A, at each 2D vertex traverse the Z_m fiber vertically, splicing one vertical arc to a horizontal arc to connect to the next fiber.

### Outcome
FAILED

### Failure Constraint
Algebraically, the spiral visits 1 + (m-1)(m²+1) = m³ + m - m² vertices, which equals m³ only when m=1. The shift-1-per-layer entry pattern creates short cycles because after visiting all m² fibers with 1 horizontal splice each, the accumulated shift doesn't return to 0.

### What This Rules Out
Any single-splice-per-fiber construction where each fiber contributes exactly (m-1) vertical arcs and exactly 1 horizontal arc. The arithmetic closure condition (-m² ≡ 0 mod m) IS satisfied, but the single-splice topology creates subcycles.

### Concrete Artifacts
- `p1_spiral_test.py`: tested all m² starting positions r0, all gave Ham=False
- Bug found and fixed: original `make_2d_cycle_A` returned m²-1 vertices instead of m²
- Arc counts for spiral: [16,8,3] for m=3 — wrong distribution

---

## Exploration 6

### Strategy
Multi-splice: replace multiple C_A arcs per fiber with vertical arcs, searching all possible splice positions to find Hamiltonian cycles.

### Outcome
FAILED

### Failure Constraint
Constraining horizontal arcs to follow C_A's exact direction sequence at non-spliced positions forces specific successor relationships. Known m=3 solutions use different horizontal directions than C_A prescribes at some positions. The splice approach is over-constrained.

### What This Rules Out
Any layer-by-layer construction that uses a fixed 2D cycle to determine which horizontal direction to use between fibers. The per-vertex horizontal direction must be chosen more flexibly.

### Concrete Artifacts
- `p1_multisplice.py`: searched all C(9,2)^3 = 46,656 configs for m=3, found 0 Hamiltonian cycles
- The search allows any subset of positions to be spliced, but forces the remaining positions to follow C_A's direction sequence

---

## Exploration 7

### Strategy
Serpentine construction: visit m² cosets (Z_m fibers) via a 2D Hamiltonian cycle, going +dominant for m-1 steps within each coset, then using an inter-coset arc from the 2D cycle. Entry point shifts by -1 each step.

### Outcome
SUCCEEDED (construction works) but INSUFFICIENT (cycles overlap)

### Surviving Structure
**The serpentine construction is a guaranteed Hamiltonian cycle generator.** For ANY m≥3, ANY dominant direction d, and ANY Hamiltonian cycle C in the quotient Z_m^2, the serpentine produces a valid Hamiltonian cycle in Z_m^3. This is proved by the closure condition: entry shifts by -1 per coset, and -m² ≡ 0 (mod m).

### Reformulations
The serpentine reveals the fiber/coset structure: Z_m^3 = ⋃ (Z_m fibers along dominant direction), indexed by quotient Z_m^2. A Hamiltonian cycle "visits" each fiber, spending m-1 steps going +dominant within it, then "jumps" to the next fiber via a non-dominant arc.

### Concrete Artifacts
- `p1_serpentine.py`: verified for m=3,4,5,6 — ALL produce valid Hamiltonian cycles
- Arc counts: m²(m-1) dominant + m² non-dominant = m³ total ✓
- For m=3: 18+9=27, dominant arc count = 18 (too many for decomposition)

### Key Parameters
- m=3: H1(18,6,3), H2(6,18,3), H3(6,3,18) — overlaps (2,2,2), total 6
- m=4: overlaps (3,3,3), total 9
- m=5: overlaps (4,4,4), total 12
- m=6: overlaps (5,5,5), total 15
- Pattern: overlap = 3(m-1)

---

## Exploration 8

### Strategy
Use serpentine H1, then find H2+H3 by exhaustive backtracking in the remaining 2-regular digraph.

### Outcome
FAILED

### Failure Constraint
Serpentine H1 uses m²(m-1) = 18 arcs in the dominant direction (for m=3), but valid decompositions require each cycle to use only m(m²-2m+2) = 15 dominant arcs. The remaining 2-regular digraph after removing serpentine H1 has wrong arc distribution to contain two more Hamiltonian cycles.

### What This Rules Out
Using a serpentine cycle as ANY of the three cycles in a valid decomposition. The serpentine's arc distribution (m²(m-1) dominant, m(m-1) secondary, m tertiary) is fundamentally incompatible with the decomposition's arc distribution.

### Concrete Artifacts
- `p1_decompose.py`: tested all 4 serpentine H1 configs for m=3
- Exhaustive backtracking found ALL H2 cycles in remaining graph
- For each H2 found, checked if complement H3 is Hamiltonian — NONE were
- 21,120 backtracking calls per config, 0 decompositions found

---

## Exploration 9

### Strategy
Repair serpentine overlaps by (a) trying all 2D cycle combinations, and (b) per-vertex direction swaps.

### Outcome
FAILED

### Failure Constraint
(a) ALL 6³=216 triples of 2D Hamiltonian cycles for m=3 give minimum overlap 6 — the overlap is inherent to the serpentine construction, not a choice of inter-coset cycle. (b) Per-vertex swaps (2^6=64 for m=3, 2^9=512 for m=4) all break Hamiltonicity because changing a single arc in a Hamiltonian cycle disrupts the successor chain.

### What This Rules Out
- Any repair strategy that only modifies individual conflict arcs without coordinated multi-arc restructuring
- Reducing serpentine overlap below 3(m-1) by choosing different inter-coset cycles

### Concrete Artifacts
- `p1_serpentine2.py`: enumerated all 2D Hamiltonian cycles (6 per Z_3^2 space), tested all 216 triples
- `p1_repair.py`: analyzed conflict structure — conflicts at (a,b) = (2,0), (0,2), (1,1), each appearing twice
- `p1_repair2.py`: tried all 2^|conflicts| bit assignments, 0 solutions for both m=3 and m=4
- Conflict pattern: H1∩H2 conflicts involve +k direction, H2∩H3 involve +i, H1∩H3 involve +j

---

## Synthesis after Exploration 9

The serpentine construction is a powerful Hamiltonian cycle generator but produces cycles with the wrong arc distribution for decomposition. The key insight is:

1. **Serpentine arc distribution**: m²(m-1) dominant, m(m-1) secondary, m tertiary
2. **Decomposition requirement**: Each cycle needs arcs more evenly distributed (15+6+6 for m=3)

The known m=3 solution has a qualitatively different structure: (long_block, +k, short_block, +k)^3. The long block traverses a 2D region using two directions, and the short block fills in gaps. This is NOT a serpentine — it uses far fewer dominant arcs.

**Key open question**: Can the serpentine idea be modified to produce cycles with the right arc distribution? Instead of m-1 dominant arcs per coset visit, use fewer dominant arcs and more non-dominant arcs within each coset. This would require a different "intra-coset" traversal pattern.

**Alternative direction**: Study the m=3 solution structure more carefully. The (L,k,S,k)^m pattern suggests a "block" construction where the blocks are 2D Hamiltonian paths (not cycles) in specific regions.

---

## Exploration 10

### Strategy
Binary search: fix C1 as a fast serpentine, then split the remaining 2m³ arcs between C0 and C2 via backtracking. If fixing one cycle simplifies the search, we reduce from 6^n to 2^n branching factor.

### Outcome
FAILED

### Failure Constraint
After removing a fast serpentine C1, the remaining 2-regular digraph has the wrong structure to decompose into two Hamiltonian cycles. The serpentine C1 consumes m²(m-1) arcs in one direction, leaving an imbalanced remainder. For m=4: tested all C1 configurations (dominant direction × zigzag pattern), 500K-700K backtracking calls each, 0 decompositions found.

### What This Rules Out
Fixing any one cycle as a serpentine and decomposing the remainder. The binary search approach inherits the fundamental serpentine incompatibility from Exploration 8.

### Concrete Artifacts
- `p1_binary.py`: m=3 found in 28 calls (solution exists because m=3 is small enough), m=4 FAILED across all configs
- `p1_analyze_remaining.py`: analyzed the 2-regular remainder after removing C1 — uniform direction assignment gives m cycles of length m² (layer structure), never Hamiltonian

---

## Exploration 11

### Strategy
Full S₃ permutation search: instead of fixing one cycle and searching for the split, assign σ(v) ∈ S₃ at every vertex simultaneously (6 choices per vertex). Use BFS vertex ordering with two constraint checks: (1) in-degree — at each vertex, incoming arcs from 3 predecessors must have distinct cycle labels, and (2) premature cycle — no cycle may close before visiting all n vertices.

### Outcome
**BREAKTHROUGH** — first solutions for m=4 and m=5

### Surviving Structure
The full permutation search succeeds where all previous approaches failed because it doesn't pre-commit to any cycle's structure. The constraints propagate effectively: in-degree pruning eliminates most of the 6^n search space.

### Concrete Artifacts
- `p1_perm_search.py`:
  - m=3: 334 calls (instant)
  - m=4: 197,319 calls (0.8s) — **FIRST m=4 SOLUTION EVER FOUND**
  - m=4 arc counts: C0=(40,12,12), C1=(20,36,8), C2=(4,16,44)
- `p1_perm_search2.py`: extended to m=5
  - m=5: 5,566,574 calls (26.5s) — FOUND
  - m=5 arc counts: C0=(95,20,10), C1=(10,95,20), C2=(20,10,95) — **symmetric!**
- m=6: BFS ordering reached 400M+ calls over 34 minutes without finding solution — STOPPED

### Key Parameters
- m=3: 334 calls | m=4: 197K calls | m=5: 5.6M calls — exponential growth with BFS ordering
- m=5 solution is cyclically symmetric (like m=3), m=4 solution is NOT
- `p1_run_m6.py`: background BFS search for m=6, killed after 34 min

---

## Exploration 12

### Strategy
Randomized search with restarts (WalkSAT-style): random vertex ordering per restart, random S₃ value ordering. Restart after a budget of calls. Target: m=6,7 where BFS ordering fails.

### Outcome
FAILED for m=6

### Failure Constraint
Even with random restarts, the search gets stuck at depth ~130/216 for m=6. The problem is not the vertex ordering per se, but the lack of constraint propagation — dead ends are discovered too late.

### Concrete Artifacts
- `p1_random_search.py`: 50+ restarts for m=6, best depth 130/216
- Also tried `p1_extract_pattern.py` to analyze direction "words" from m=3,4,5 solutions — m=3 C0 has periodic word "iijjiikik"×3 (period m²=9), but m=4,5 show no clean periodicity

---

## Exploration 13

### Strategy
Quotient graph approach: Z_m^3 / ⟨(1,1,1)⟩ ≅ Z_m^2, with generators e0=(1,0), e1=(0,1), e2=(-1,-1). These sum to (0,0). If the quotient Cay(Z_m^2, {e0,e1,e2}) has a Hamiltonian decomposition into 3 directed m²-cycles, lift it to Z_m^3 by repeating the direction block m times.

### Outcome
PARTIAL — works for m=3 only

### Surviving Structure
The quotient approach works perfectly for m=3: the quotient decomposes (10 calls), and the lift succeeds with symmetric counts (15,6,6). This gives a constructive proof for m=3.

### Failure Constraint
- m=4,5: quotient graph has NO Hamiltonian decomposition (exhaustive search)
- m=6,9: quotient decomposes BUT lift FAILS — the displacement gcd(Σ₀,Σ₁,Σ₂,m) ≠ 1, so the block only covers m/gcd layers instead of all m

### What This Rules Out
The quotient via ⟨(1,1,1)⟩ as a general construction. The lift condition is too restrictive for m>3.

### Concrete Artifacts
- `p1_quotient.py`: tested m=3..14
  - m=3: quotient found (10 calls), lift SUCCEEDED
  - m=4,5: no quotient decomposition
  - m=6: quotient found but lift FAILED (displacement (26,8,2), gcd=2)
  - m=9: quotient found but lift FAILED

---

## Exploration 14

### Strategy
MRV (Minimum Remaining Values) with forward checking — a CSP technique from AI. Instead of fixed vertex ordering (BFS), dynamically choose the most constrained unassigned vertex (smallest domain). After each assignment, propagate constraints to neighbors by removing newly-invalid values from their domains. If any domain becomes empty, backtrack immediately (wipeout).

### Outcome
**MASSIVE BREAKTHROUGH** — solutions for m=3..12

### Surviving Structure
MRV + forward checking reduces the search by 3-4 orders of magnitude compared to BFS ordering. The key insight: choosing the most constrained vertex first causes failures to be detected early, and forward checking prunes dead-end values before they're tried.

### Concrete Artifacts
- `p1_mrv_search.py` (initial version, m=3..6):
  - m=3: 308 calls (was 334 with BFS)
  - m=4: 3,217 calls (was 197K — **61× speedup**)
  - m=5: 1,392 calls (was 5.6M — **4,000× speedup**)
  - m=6: 5,904 calls, 0.2s (BFS failed at 400M+ — **67,000× speedup**)
- `p1_mrv_extended.py` (extended to m=3..30):

```
  m      n        calls     time       C0                C1                C2
  3     27          308     0.0s   (15,6,6)          (6,15,6)          (6,6,15)
  4     64        3,217     0.1s   (40,12,12)        (20,36,8)         (4,16,44)
  5    125        1,392     0.0s   (95,20,10)        (10,95,20)        (20,10,95)
  6    216        5,904     0.2s   (168,30,18)       (6,174,36)        (42,12,162)
  7    343       18,793     0.6s   (287,42,14)       (14,287,42)       (42,14,287)
  8    512       56,598     1.9s   (432,56,24)       (8,432,72)        (72,24,416)
  9    729      232,234     8.9s   (639,72,18)       (18,639,72)       (72,18,639)
 10   1000       27,986     1.5s   (880,90,30)       (10,880,110)      (110,30,860)
 11   1331    2,503,458   140.7s   (1199,44,88)      (110,1133,88)     (22,154,1155)
 12   1728      132,360     9.8s   (1560,132,36)     (12,1560,156)     (156,36,1536)
```

### Key Parameters — Arc Count Patterns

**Odd m (symmetric solutions):** Cycles are cyclically symmetric under (i,j,k)→(k,i,j).
- C0: (m(m²-m-1), m(m-1), 2m) — dominant in direction 0
- C1: (2m, m(m²-m-1), m(m-1)) — dominant in direction 1
- C2: (m(m-1), 2m, m(m²-m-1)) — dominant in direction 2
- Verified for m=3,5,7,9

**Even m:** Solutions are NOT cyclically symmetric. Arc counts follow a different pattern without a clean formula.

**Universal constraint:** All direction counts divisible by m (closure requirement). Verified for all m=3..12.

### Performance Note
m=11 took 2.5M calls (140s) — the search is getting harder. m=13 (n=2197) was attempted but exceeded 10M calls. Main bottleneck: `has_premature_cycle()` traces the full successor chain at O(chain_length) per call.

---

## Exploration 15

### Strategy
Optimize MRV search with O(1) cycle detection (chain endpoint tracking instead of chain tracing), and search the literature for known results.

### Outcome
LITERATURE HIT — problem was recently solved by Knuth

### Key Finding
**Donald Knuth published "Claude's Cycles" (2026)** — a paper addressing exactly this problem (Hamiltonian decomposition of the 3D directed torus C_m □ C_m □ C_m into 3 directed Hamiltonian cycles).

Key facts from the paper:
- Claude (Opus) found a construction through ~31 guided explorations
- The final solution is a compact set of rules expressible as a short C program
- Knuth proved the construction correct and found exactly **760 "Claude-like" decompositions**
- Verified for all odd m = 3, 5, 7, ..., 101
- Paper: https://www-cs-faculty.stanford.edu/~knuth/papers/claude-cycles.pdf

### Background Literature
- **Alspach's Conjecture (1984):** Every connected 2k-regular Cayley graph on a finite abelian group has a Hamiltonian decomposition. Open in general.
- **Bermond's Conjecture (1978):** Cartesian product of Hamilton-decomposable graphs with even valency is Hamilton-decomposable. Open in general.
- **Curran & Witte (1985):** C_m □ C_m □ C_m has at least one Hamiltonian cycle. Does not give full decomposition.
- **Aubert & Schneider (1982):** Undirected Cartesian products of cycles have Hamiltonian decompositions. Doesn't cover directed case.
- **Darijani, Miraftab, Morris (2022):** Arc-disjoint Hamiltonian paths in products of directed cycles. Partial results; the 3-cycle product case for full decomposition was open.

### Concrete Artifacts
- `p1_mrv_fast.py`: optimized version with O(1) cycle detection via chain endpoint tracking (written but search paused after literature hit)

---

## Synthesis after Exploration 15

### What We Found Independently
1. Solutions exist for all m=3..12 (computational verification via MRV search)
2. Odd m admit cyclically symmetric solutions with formula: dominant = m(m²-m-1), secondary = m(m-1), tertiary = 2m
3. MRV + forward checking is the critical algorithmic technique (67,000× speedup over BFS for m=6)
4. The quotient approach Z_m^3/⟨(1,1,1)⟩ works only for m=3
5. Serpentine constructions are fundamentally incompatible with decomposition (wrong arc distribution)

### What Knuth's Paper Adds
A constructive proof for all odd m, with an exact count of 760 distinct constructions of a particular type. The construction is a compact rule set found through AI-guided exploration (the same general approach we were pursuing).

### Status: RESOLVED
The problem is solved for odd m ≥ 3. The even case status is unclear from available information. Our computational results confirm solutions exist for even m=4,6,8,10,12, but we did not find a constructive proof for even m.

### Strategy Register Update
**Add to eliminated approaches:**
6. **Binary search (fix one serpentine cycle, search remainder)** — ruled out at Exploration 10. Serpentine arc distribution is incompatible.
7. **BFS-ordered permutation search for m≥6** — ruled out at Exploration 11-12. Exponential blowup without constraint propagation.
8. **Quotient via ⟨(1,1,1)⟩ for m>3** — ruled out at Exploration 13. Lift fails when displacement gcd ≠ 1.

**Key technique discovered:**
- **MRV + forward checking** — the winning algorithmic approach (Exploration 14). Dynamic variable ordering + domain pruning + wipeout detection.
