# Strategy Register

## Eliminated approach classes

- Single-special-layer constructions in which one layer carries all the nontrivial 2D matching structure and every other layer uses only constant `I/X/Y` matchings. Ruled out at exploration 1: one factor can be made Hamilton this way, but the remaining two factors collapse to short cycles because the residual 2D matchings cannot be translated into Hamilton round maps.
- Common-hierarchy cyclic-shift constructions of the form "outside a set `S0` use directions `(1,2,3)`, on `S0 \\ S1` rotate once, on `S1` rotate again", with the same nested sets for all three cycles. Ruled out at exploration 3: even when `S0` is the natural sum surface `i+j+k = m-1`, no choice of a single shared second-level set `S1` worked for `m = 3`, and the natural affine transversals fail for larger odd `m`.
- Same-diagonal layer ansatz for even `m`, where every layer is factorized by choosing one identity matching and the standard 2D diagonal `X/Y` decomposition on the complementary two colors. Ruled out structurally at exploration 3: every color then advances the common diagonal coordinate by a constant number `n_r` of non-identity layers, so `n_1 + n_2 + n_3 = 2m`; for even `m`, all three `n_r` would need to be odd units mod `m`, which is impossible.
- Same-permutation-transversal layer family for even `m`, where each layer chooses one identity matching and the other two colors use the 2D decomposition attached to a single permutation line `S = {(x, pi(x))}`. Ruled out at exploration 4 for `m = 4`: exhaustive search over all `pi` and all owner/orientation schedules of this form found no decomposition.
- Bounded-state periodic even templates, including raw periodic lifts of the exact `m = 4` solution and local rules depending only on small residue data such as `(s mod r, x mod 2, y mod 2)`. Ruled out at exploration 6: they preserve a coarse block/parity quotient and split into multiple synchronized macro-cycles.

## Active structural constraints

- In fiber coordinates `(s, x, y)` with `s = i + j + k mod m`, the three edge directions become `X : (x,y) -> (x+1,y)`, `Y : (x,y) -> (x,y+1)`, and `I : (x,y) -> (x,y)` between consecutive layers. This turns the 3D problem into choosing, on each layer transition, a 1-factorization of the bipartite graph `I + X + Y`.
- The standard 2D torus decomposition is explicit: on `Z_m^2`, the matchings
  `A : X` off the diagonal `x + y = c`, `Y` on that diagonal, and
  `B : Y` off the diagonal, `X` on the diagonal,
  are both Hamilton cycles. This is the key reusable 2D gadget.
- The single odometer Hamilton cycle in 3D has a clean local rule:
  use `i+` unless `i + j + k = m-1`,
  use `j+` on that surface unless `i = 0`,
  and use `k+` on the line `i = 0`, `j + k = m-1`.
- In the same-diagonal layer family, each color induces a skew map on `Z_m^2` of the form `(u,v) -> (u + n, v + f(u))`, where `u = x + y - c`. Such a map is Hamilton iff `gcd(n,m) = 1` and the one-round vertical drift `sum_u f(u)` is also a unit mod `m`.
- For the same-diagonal layer family with counts `(a_r, b_r)` of `A`-layers and `B`-layers seen by color `r`, the Hamilton criterion simplifies to:
  `n_r = a_r + b_r` is a unit mod `m`, and
  `F_r = b_r - a_r` is a unit mod `m`.
- In the same-diagonal family, the odd case reduces completely to choosing layer-type counts; order does not affect the Hamilton criterion, only the counts `(a_r, b_r)`.
- The exact `m = 4` solution has nontrivial block-wrap vectors `(5,6,5)`, `(6,6,4)`, `(5,4,7)` over one microcycle, but raw periodic repetition still produces several macro-cycles on `m = 4q`; the obstruction is quotient periodicity rather than zero drift.
- For even `m`, if `M_s^(r)` is the layer-`s` matching used by color `r`, then the sign of the full color permutation is `sign(P_r) = prod_s sign(M_s^(r))`, because the layer-shift permutation contributes even sign. Since a Hamilton cycle on `m^3` vertices has sign `-1` when `m` is even, any even solution must satisfy `prod_s tau_s = -1`, where `tau_s = prod_r sign(M_s^(r))`.
- Kempe-cycle swaps inside a single layer preserve `tau_s`. So search methods based only on those swaps stay trapped in one layer-sign component and can miss genuine even solutions entirely.
- Exact searched decompositions are now in hand for the even parameters `m = 4, 6, 8`, while exhaustive search shows `m = 2` has no decomposition.
- Independent repair searches for `m = 10` repeatedly stalled at the same profile `[97,3], [100], [100]`, suggesting a stable local basin rather than mere bad luck.
- The raw `6`-periodic lift to `m = 12` gives four `36`-cycles in each color, and repair from that lift can make one color Hamilton while leaving the other two near-Hamilton. So `m = 12` appears to be a quotient-repair problem rather than a raw existence problem.
- The exact even artifacts and the best larger near-hits are strongly row/strip based: repeated rows, repeated adjacent-row motifs, and large horizontal bands dominate, whereas diagonal structure is weak or absent.
- In the exact `m = 10` near-hit `[97,3], [100], [100]`, the defective color permutation on `Z_10^2` has sign `+1`, while any Hamilton `100`-cycle has sign `-1`. So any successful final repair must perform an odd sign change on that color; parity-neutral repair neighborhoods cannot close the residual `3`-cycle.

## Known reformulations

- Fiber-coordinate reformulation: write vertices as `(s, x, y)` with `s = i + j + k mod m`, `x = i`, `y = j`. Then the problem becomes an `m`-layer skew-product problem over `Z_m^2`.
- Layer-factorization reformulation: between each consecutive pair of sum-layers, the available edges are exactly the three perfect matchings `I`, `X`, and `Y`; a Hamilton decomposition corresponds to choosing an ordered 1-factorization on each layer so that each color's round product on `Z_m^2` is an `m^2`-cycle.
- Surface-switch reformulation: starting from the trivial decomposition `(i+, j+, k+)`, rotating the colors on the surface `i + j + k = m-1` converts each color class into `m` planar Hamilton cycles. Additional switches must then splice those planar cycles together.
- Same-diagonal symbolic reduction: fix one diagonal `D` in every fiber layer, define the 2D Hamilton matchings `A` and `B` there, and analyze each color by the counts of `A`-layers and `B`-layers it sees.
- Macro/micro reformulation for periodic lifts: a repeated small solution induces a wrap vector on the quotient of repeated blocks, and Hamiltonicity of the lift depends on transitivity of the induced quotient action.
- Layer-sign reformulation for even `m`: each layer factorization carries a sign class `tau_s in {+1,-1}` coming from the product of the three matching signs, and an even Hamilton decomposition requires an odd number of `tau_s = -1` layers.
- Strip-template reformulation for even artifacts: the exact `m = 4, 6, 8` solutions and the best `m = 10, 12` near-hits are more naturally described by row templates and short row blocks than by diagonal transversals.
- Basin-parity reformulation for the `m = 10` near-hit: the last obstruction is not just cycle count but permutation parity. The defective color already has the wrong sign for a Hamilton cycle, so the missing move must cross to the opposite sign component.

## Session Start

Resuming from exploration 0. Next step: compute small cases and search for a reusable way to color the three outgoing directions at each vertex so that each color class is a single directed Hamiltonian cycle.

## Exploration 1

### Strategy
Collapse the 3D problem into a single distinguished layer in fiber coordinates, hoping to realize the whole decomposition by one nontrivial 2D matching factorization and constant matchings on every other layer.

### Outcome
FAILED

### Failure Constraint
If only one layer is nontrivial, each color's round map on `Z_m^2` is "translation composed with one residual 2D matching". One can make one factor Hamilton, but the other two factors inherit residual matchings whose translated cycle structures stay highly non-Hamiltonian.

### What This Rules Out
Any construction that tries to put all the combinatorial complexity into one special layer and leaves every other layer completely trivial.

### Surviving Structure
- The fiber-coordinate model is valid and useful.
- The 2D matchings `I`, `X`, and `Y` are the right objects to organize the search.
- A single 3D Hamilton cycle is easy to obtain from a one-layer odometer-style factorization; the difficulty is simultaneous compatibility of all three colors.

### Reformulations
- The 3D problem reduces to finding `m` ordered factorizations of the `I + X + Y` bipartite graph so that the round products are Hamilton on `Z_m^2`.

### Concrete Artifacts
- Natural 2D Hamilton matching on `Z_m^2`: `A`, defined by `X` off a diagonal and `Y` on the diagonal.
- Complementary matching `B`, defined by `Y` off the diagonal and `X` on the same diagonal.
- Testing the residual complements coming from a single special layer showed that the translated round maps for the other two colors have many short cycles rather than one `m^2`-cycle.

### Key Parameters
- Tested diagonal-based 2D matchings for `m = 3, 4, 5, 6`.
- In all of these, one factor became Hamilton and the other two did not.

### Open Questions
- Can the nontrivial structure be spread across several layers while keeping the 2D analysis tractable?

## Exploration 2

### Strategy
Compute exact decompositions for small cases (`m = 3` and `m = 4`) to see what local layer factorizations actually occur in genuine solutions.

### Outcome
SUCCEEDED

### Failure Constraint
N/A

### What This Rules Out
- Not a ruling-out exploration; the main value was artifact generation.

### Surviving Structure
- Exact decompositions exist for `m = 3` and `m = 4`.
- The small-case solutions are not simple translates, not simple coordinate permutations of one odometer cycle, and not pointwise cyclic shifts of a single direction function.

### Reformulations
- Small-case exact search confirms that local layer factorizations are the right granularity: the `m = 3` solution can be seen as a sequence of three explicit layer factorizations; the `m = 4` solution likewise as four explicit factorization choices.

### Concrete Artifacts
- For `m = 3`, an exact sequence of three layer factorizations was found:
  1. `(I, X, Y)`
  2. `(I on rows 0,1 and Y on row 2; Y on rows 0,1 and I on row 2; X everywhere)`
  3. `(X everywhere; I on row 0 and Y on rows 1,2; Y on row 0 and I on rows 1,2)`
  In round-product form, these yield three Hamilton maps on `Z_3^2`.
- For `m = 4`, a random search over the finite layer-factorization space produced an explicit 4-layer decomposition, confirming that even `m` is genuinely feasible but structurally less transparent.

### Key Parameters
- Exhaustive layer-factorization search for `m = 3`.
- Randomized search over the `m = 4` one-layer factorization space.

### Open Questions
- Which features of the `m = 4` decomposition are essential, and which are accidental artifacts of the search?

## Exploration 3

### Strategy
Look for a structured family built from the standard 2D diagonal decomposition on every layer, and analyze it symbolically instead of by case-by-case search.

### Outcome
PARTIAL

### Failure Constraint
- The cleanest cyclic-shift surface-switch model does not suffice: a shared nested-set rule cannot make all three colors Hamilton simultaneously.
- The same-diagonal layer family cannot handle even `m` because each color then advances a common diagonal coordinate by a constant unit count `n_r`, and `n_1 + n_2 + n_3 = 2m` is incompatible with all three `n_r` being odd units.
- The same-diagonal layer family also cannot handle `m = 3`.

### What This Rules Out
- Uniform even-case constructions based on one fixed diagonal coordinate and per-layer choices among `I`, `A`, and `B`.
- Any "one shared surface plus one shared second-level subset" construction where all three colors are just cyclic level-shifts of one another.

### Surviving Structure
- For odd `m >= 5`, the same-diagonal family is viable.
- In that family, order does not matter for Hamiltonicity; only the counts `(a_r, b_r)` matter, where `a_r` is the number of `A`-layers and `b_r` the number of `B`-layers seen by color `r`.
- The Hamilton criterion in that family is exactly:
  `gcd(a_r + b_r, m) = 1` and `gcd(b_r - a_r, m) = 1`.
- Explicit odd-case count patterns were found:
  - If `3` does not divide `m`, the constant-diagonal sequence with owner pattern `0` repeated `m-2` times, then `1`, then `2`, works.
  - If `3` divides `m` and `m >= 9`, one can choose counts
    `(a_0, b_0) = (0, 2)`,
    `(a_1, b_1) = ((m-3)/2, (m+1)/2)`,
    `(a_2, b_2) = ((m+3)/2, (m-5)/2)`,
    which satisfy the symbolic Hamilton criterion.

### Reformulations
- In the same-diagonal family, every color induces a skew map `(u,v) -> (u+n, v+f(u))` on `Z_m^2`, where `u` is the diagonal coordinate and `v` is the transverse coordinate. Hamiltonicity reduces to a 1-dimensional arithmetic condition.

### Concrete Artifacts
- Standard 2D gadget on diagonal `x+y=c`:
  `A(u,v) = (u+1, v+1)` if `u != 0`, else `(u+1, v)`,
  `B(u,v) = (u+1, v)` if `u != 0`, else `(u+1, v+1)`.
- For a word with `a` letters `A` and `b` letters `B`, the resulting skew map has:
  diagonal increment `n = a+b`,
  total transverse drift `F = b-a (mod m)`.

### Key Parameters
- Same-diagonal family searched for `m = 3, 4, 5, 6`; solution found first at `m = 5`.
- Symbolic count conditions checked for odd `m = 5, 7, 9, 11, 13, 15`.

### Open Questions
- Can the odd-case count solution be turned into a clean explicit owner/orientation schedule for every odd `m >= 5`?
- What even-case layer family replaces the impossible same-diagonal construction?

## Exploration 4

### Strategy
Finish the same-diagonal symbolic analysis, turn the count criterion into an explicit odd-case construction, and test whether the obvious generalization from diagonals to arbitrary permutation transversals can rescue the even case.

### Outcome
PARTIAL

### Failure Constraint
- The same-diagonal family now gives a complete odd-case construction, but its structural parity obstruction for even `m` remains absolute.
- Replacing the diagonal by a single permutation transversal `S = {(x, pi(x))}` still did not help for even `m`: exhaustive search for `m = 4` found no decomposition in that broader family.

### What This Rules Out
- Any all-`m` construction that keeps one color equal to `I` on every layer and uses only one fixed transversal-based `X/Y` decomposition for the other two colors.

### Surviving Structure
- The odd case is now explicit for every odd `m >= 5`.
- The special case `m = 3` is handled by an exact 3-layer decomposition found computationally.
- The even case needs a genuinely different layer mechanism, one that is not reducible to a fixed common "drive coordinate" with constant non-identity count.

### Reformulations
- In the odd same-diagonal family, the round map for a color with `a` copies of `A` and `b` copies of `B` is a skew map
  `(u,v) -> (u+a+b, v+f(u))`,
  and `P^m(u,v) = (u, v + (b-a))`.
  So Hamiltonicity is equivalent to `a+b` and `b-a` both being units mod `m`.

### Concrete Artifacts
- Verified odd construction:
  use one `P0 = (I, B, A)` layer,
  one `P1 = (B, I, A)` layer,
  `t` copies of `P2 = (A, B, I)`,
  `m-2-t` copies of `Q2 = (B, A, I)`,
  where `t = (s-1)/2` and `s` is any odd residue with `gcd(s,m) = gcd(s+2,m) = 1`.
- For this schedule, the color count pairs are:
  `C1 : (a,b) = (t, m-1-t)`,
  `C2 : (a,b) = (m-2-t, t+1)`,
  `C3 : (a,b) = (2,0)`.
- The resulting unit checks are:
  `C1 : a+b = m-1`, `b-a = -s`;
  `C2 : a+b = m-1`, `b-a = s+2`;
  `C3 : a+b = 2`, `b-a = -2`.
- Verified by direct computation for `m = 5, 7, 9, 11, 13, 15`.
- Exhaustive search result for the broader same-transversal family at `m = 4`: no solution.

### Key Parameters
- Verified odd construction for `m = 5, 7, 9, 11, 13, 15`.
- Exhaustive failure of the same-transversal family for `m = 4`.

### Open Questions
- What is the right even-case analogue of the odd same-diagonal construction?
- Can the exact `m = 4` decomposition be simplified enough to reveal a reusable even-layer gadget?

## Exploration 5

### Strategy
Stress-test the explicit odd construction computationally on every odd parameter up to `m = 101`, to confirm that the symbolic proof matches the actual cycle structure over a wide range.

### Outcome
SUCCEEDED

### Failure Constraint
N/A

### What This Rules Out
- Not a ruling-out exploration. The point was verification, not elimination.

### Surviving Structure
- The odd construction behaves exactly as predicted on every tested odd value up to `101`.
- No hidden small-parameter pathology appeared beyond the already-isolated special case `m = 3`.

### Reformulations
- The CRT choice of `s` is computationally mild in practice: for all tested odd `m <= 101`, the smallest working `s` was one of `1`, `5`, or `11`.

### Concrete Artifacts
- Directly verified odd parameters:
  `m = 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 67, 69, 71, 73, 75, 77, 79, 81, 83, 85, 87, 89, 91, 93, 95, 97, 99, 101`.
- For `m = 3`, the exact searched construction gives three round maps of length `9`, hence three directed `27`-cycles in the original graph.
- For every odd `m = 5, 7, ..., 101`, the explicit odd construction gave three round maps, each a single cycle of length `m^2`.
- Parameter choices observed:
  - `s = 1`, `t = 0` for
    `m = 5, 7, 11, 13, 17, 19, 23, 25, 29, 31, 35, 37, 41, 43, 47, 49, 53, 55, 59, 61, 65, 67, 71, 73, 77, 79, 83, 85, 89, 91, 95, 97, 101`.
  - `s = 5`, `t = 2` for
    `m = 9, 27, 33, 39, 51, 57, 69, 81, 87, 93, 99`.
  - `s = 11`, `t = 5` for
    `m = 15, 21, 45, 63, 75`.

### Key Parameters
- Exhaustive verification of every odd `m <= 101`.

### Open Questions
- Can the even case be forced into a similarly small-parameter family, or is its mechanism fundamentally different?

## Synthesis after exploration 5

Across the successful work so far, the recurring pattern is that odd `m` becomes tractable exactly when the 3D problem is reduced to a 1-dimensional skew map over a fixed diagonal coordinate. Once that reduction is available, the Hamilton condition collapses to unit conditions in `Z_m`, and the construction scales cleanly.

By contrast, every failed family for the even case has shared the same defect: all colors inherit one common drive coordinate and therefore one common parity obstruction. The `m = 4` existence result shows the even case is not impossible, but it strongly suggests that the correct even construction must break this single-coordinate regime, probably by using more than one transversal/diagonal type or by changing the 2D gadget from layer to layer in a genuinely non-equivalent way.

## Exploration 6

### Strategy
Test whether the even case can be forced into a bounded-complexity template by lifting the exact `m = 4` solution periodically and by searching small-state local-rule families that only remember parity-scale information.

### Outcome
FAILED

### Failure Constraint
Every family tested retained a hidden macro-periodicity. The raw `4`-periodic lift of the exact `m = 4` decomposition to `m = 4q` decomposed into several synchronized macro-cycles instead of one Hamilton cycle, and the broader small-state families depending only on `(s mod r, x mod 2, y mod 2)` likewise failed to produce Hamilton round maps for `m = 6` or `m = 12`. The obstruction is not just parity of the fixed-diagonal count; it is that these templates preserve a coarse quotient dynamics on blocks/parity classes.

### What This Rules Out
- Direct periodic lifts of the exact `m = 4` solution to larger multiples of `4`.
- Even-case constructions whose layer rule depends only on a bounded residue pattern in the layer index and the parity classes of `(x,y)`.
- The specific "owner `I` plus one line gadget" families built only from rows, columns, and the two standard diagonal directions.

### Surviving Structure
- The exact `m = 4` solution is still a real artifact, but it does not scale by naive periodic replication.
- The `m = 4` microcycle has nontrivial wrap vectors, so the failure of the periodic lift is not because the microcycle is degenerate; it is because the lift preserves a block quotient.
- Even-case solutions must break coarse periodicity more aggressively than the tested bounded-state families do.

### Reformulations
- The periodic-lift experiments show that an exact small solution can be viewed as a "microcycle" carrying a wrap vector on the block quotient. A successful lift would need those macro wrap vectors to act transitively on the quotient, not just within each repeated block.
- The failed parity-state searches suggest that the right even-case construction, if it exists in layer form, probably needs a moving geometric object rather than one frozen parity partition.

### Concrete Artifacts
- Raw `4`-periodic lift of the exact `m = 4` solution:
  - `m = 8`: cycle structures
    `C1`: `4` cycles of length `128`,
    `C2`: `8` cycles of length `64`,
    `C3`: `4` cycles of length `128`.
  - `m = 12`: each color had `9` cycles of length `192`.
  - `m = 16`: `C1` and `C3` had `16` cycles of length `256`, while `C2` had `32` cycles of length `128`.
  - `m = 20`: each color had `25` cycles of length `320`.
- Over one `64`-step microcycle of the exact `m = 4` solution, the block-wrap vectors were:
  `C1`: `(5,6,5)`,
  `C2`: `(6,6,4)`,
  `C3`: `(5,4,7)`.
  Their determinant is `-32`.
- Exhaustive search over rules periodic in `(s mod 3, x mod 2, y mod 2)`:
  `13824` valid local rules satisfy the one-layer incoming/outgoing constraints, and none produced Hamilton decompositions for `m = 6` or `m = 12`.
- Exhaustive search over alternating pairs of `3 x 3` layer factorizations (a `2`-periodic family intended for `m = 6`) found no pair giving Hamilton round maps.
- Random search in owner-`I` line-gadget families built from rows `x = c`, columns `y = c`, and diagonals `x + y = c`, `x - y = c` found no solution for `m = 6` in hundreds of thousands of trials.

### Key Parameters
- Periodic lifts tested at `m = 8, 12, 16, 20`.
- Small-state parity rule search tested at `m = 6` and `m = 12`.
- Alternating `2`-periodic layer search tested at `m = 6`.
- Random line-gadget searches tested primarily at `m = 6`.

### Open Questions
- Can the fixed-diagonal odd construction be generalized by letting the diagonal offset move from layer to layer?
- Is there a way to use the exact `m = 4` solution as a local gadget without preserving a block quotient?

## Exploration 7

### Strategy
Revisit the even-case search space with parity-changing layer moves: analyze permutation signs of layer factorizations, test whether the earlier Kempe-cycle search was confined to the wrong connected component, and then search for explicit `m = 6` decompositions using whole-layer randomized factorization sampling.

### Outcome
SUCCEEDED

### Failure Constraint
N/A

### What This Rules Out
- Pure Kempe-cycle local search as a reliable existence detector for even `m`. It can stay inside one fixed layer-sign component and therefore fail even when solutions exist.

### Surviving Structure
- Exact even decompositions exist at least for `m = 4` and `m = 6`.
- The sign of a full color permutation on `m^3` vertices factors cleanly through the signs of its layer matchings when `m` is even.
- Even solutions require an odd number of sign-negative layers, so the layer-sign parity is a genuine structural datum, not just a search artifact.

### Reformulations
- View each layer factorization through its sign class
  `tau_s = prod_r sign(M_s^(r))`.
  For even `m`, a Hamilton decomposition must satisfy
  `prod_s tau_s = -1`.
  This is a new coarse invariant on any candidate construction.

### Concrete Artifacts
- Exact search for `m = 2` found no decomposition.
- Randomized direct sampling of one-layer factorizations for `m = 4` produced both sign classes `tau = +1` and `tau = -1`, confirming that the earlier Kempe-cycle move set was only seeing one component.
- Exact `m = 6` layer sequence found by whole-layer randomized search. Each entry below is the triple of directions `(C1,C2,C3)` used at the corresponding `(x,y)` in that layer:

Layer `0`
`YIX XIY IYX IXY XIY IXY`
`IYX XYI IXY IXY XIY IYX`
`IXY XIY IXY IYX XYI IYX`
`IXY XIY IYX IYX XYI IXY`
`XYI YXI YIX XIY YIX YXI`
`XIY IYX IXY YIX XIY IXY`

Layer `1`
`YXI XYI IYX XYI IYX IYX`
`IYX XYI IYX XYI IYX IXY`
`IYX XYI IYX XYI IXY IYX`
`IYX XYI IXY YIX XYI IYX`
`XIY XIY IYX IXY YIX YIX`
`XYI YXI YIX XYI IYX IYX`

Layer `2`
`XYI IXY YIX XIY IYX IYX`
`XIY IYX IXY YIX YIX XIY`
`YIX YIX YXI YIX XIY XIY`
`IYX IXY IYX IYX XYI XYI`
`YIX XYI IYX IXY XIY YIX`
`XIY YIX XIY IYX YXI YIX`

Layer `3`
`XYI IXY YIX XIY XIY IYX`
`XIY IYX IYX XYI XYI IXY`
`YXI YIX XIY XIY YIX XYI`
`XYI IYX XYI YXI XIY YIX`
`XYI IXY XIY IYX XYI IYX`
`XIY IYX XYI IYX XYI IXY`

Layer `4`
`YXI XYI IXY IXY YIX XYI`
`XYI YXI YXI XYI IXY YIX`
`XIY IXY IXY YIX YXI XIY`
`XIY IXY IYX IXY IXY XIY`
`YIX YXI XIY IXY IXY XIY`
`XIY IXY YIX YXI XYI YXI`

Layer `5`
`IXY YIX XIY YIX XIY IYX`
`IYX IYX XYI IYX YXI XIY`
`YIX XIY YIX YIX XYI YXI`
`IYX XYI IYX IXY XIY IYX`
`XIY YIX XIY IYX YXI YIX`
`YIX XIY YIX XIY IYX IXY`

- For this `m = 6` decomposition, each color's round map on `Z_6^2` is a single `36`-cycle.
- A Kempe-cycle search restricted to one sign component repeatedly stalled at a near-solution with cycle profile `[36], [36], [35,1]`, which is now explained by the sign obstruction in the move set.

### Key Parameters
- Exact `m = 2` search.
- Direct whole-layer factorization sampling for `m = 4` and `m = 6`.
- Sign sampling of random one-layer factorizations at `m = 3` and `m = 4`.

### Open Questions
- Can the layer-sign parity invariant be combined with a structured family to produce all even `m >= 4`?
- Does the `m = 6` solution reveal a reusable motif, or is it still too irregular and search-generated?

## Exploration 8

### Strategy
Push the parity-aware whole-layer sampling method to the next even parameter `m = 8` to test whether the `m = 6` success reflects a real even-family phenomenon rather than an isolated small case.

### Outcome
SUCCEEDED

### Failure Constraint
N/A

### What This Rules Out
- The suspicion that `m = 6` might be an isolated exceptional even case.

### Surviving Structure
- The same search mechanism that found `m = 6` also finds `m = 8`.
- The structural bottleneck in the even search is not the size jump from `6` to `8`; it is the lack of a symbolic family explaining the sampled solutions.

### Reformulations
- None beyond exploration 7; the main value of this exploration is artifact extension rather than a new representation.

### Concrete Artifacts
- Exact `m = 8` layer sequence found by whole-layer randomized search. Each entry below is the triple of directions `(C1,C2,C3)` used at the corresponding `(x,y)` in that layer:

Layer `0`
`YIX XYI XYI YXI XIY IXY XIY IXY`
`IYX XYI YXI XYI YXI XYI YXI XYI`
`XIY YIX XYI YXI XYI YXI XYI YXI`
`XYI IXY YIX XYI YXI XYI YXI XYI`
`YXI XYI IXY XIY IYX YXI XYI XYI`
`IXY YIX XYI XYI IXY IXY XIY XIY`
`XYI IXY XIY XIY IXY IYX XYI YXI`
`XIY IXY XIY XIY IYX IXY XIY IXY`

Layer `1`
`IXY YIX XIY XIY IYX IXY XIY IYX`
`XYI IXY XIY YIX XIY IYX YXI YIX`
`XIY IYX YXI XIY YIX XIY IYX IXY`
`YIX XIY IYX XYI IXY YIX XIY IXY`
`IXY YIX XIY XIY IYX IXY XIY IYX`
`IYX IYX XYI YXI YIX XYI XYI IXY`
`IYX IYX YXI XYI IYX XYI YXI XYI`
`YIX XIY IYX XYI IXY YIX XYI YXI`

Layer `2`
`XYI YXI YXI XIY YIX XIY YIX XYI`
`YXI YXI XYI XYI IYX XYI IYX XYI`
`IXY IYX XYI YXI XIY YIX XIY XIY`
`XYI IXY XIY IYX YXI XIY XIY YIX`
`XIY IXY YIX YIX XYI XYI YXI XIY`
`YIX XYI IYX IXY XIY XIY IXY XIY`
`IYX XYI IXY IXY XIY YIX XYI XYI`
`XIY XIY IXY IYX XYI IYX XYI YXI`

Layer `3`
`XIY IXY XIY XIY IYX IYX XYI YXI`
`YXI XYI XYI XYI IYX IXY XIY IYX`
`IYX XYI XYI YXI YIX XYI YXI XIY`
`XIY XIY YIX YXI XIY XIY IXY YIX`
`XIY YIX YIX XYI XYI YXI YXI XIY`
`XYI IYX IYX XYI YXI YXI XYI XYI`
`YIX YIX XIY XIY IXY IXY XIY XIY`
`IYX IXY XIY XIY IXY IYX XYI XYI`

Layer `4`
`YXI XIY IXY IXY XIY IXY XIY YIX`
`IXY XIY IXY IYX YXI XYI YXI XIY`
`XYI YXI XYI IXY IXY YIX XYI YXI`
`YIX XYI YXI YXI YXI XIY XIY IXY`
`IYX YXI YXI YXI XYI XYI YXI XYI`
`IXY IXY IXY IYX XYI YXI XYI XYI`
`IXY IXY IYX IXY XIY IXY XIY XIY`
`IXY IYX IXY IXY XIY IXY XIY XIY`

Layer `5`
`IYX IXY XIY IYX IYX XYI IXY IYX`
`IXY IXY YIX YIX XIY YIX XYI IYX`
`IXY IYX IYX IYX XYI IYX YXI XIY`
`IYX IYX IYX IYX XYI IXY IXY XIY`
`IYX IYX IYX IYX YXI YXI XYI XYI`
`IYX IYX IYX IXY IXY IYX XYI XYI`
`YIX YIX YIX YXI XYI IYX XYI YXI`
`YIX YIX XIY IXY YIX XIY YIX YXI`

Layer `6`
`XYI IYX IXY IYX XYI XYI XYI IYX`
`YIX XIY IYX IYX XYI XYI YXI XIY`
`IYX XYI IYX IXY XIY YIX XYI XYI`
`XIY YIX YIX XYI YXI XIY XIY YIX`
`YIX YIX XIY YIX XYI XYI YXI XIY`
`IYX IXY YIX XIY XIY YIX XYI XYI`
`XIY IYX IYX XYI YXI XIY XIY YIX`
`XYI IYX IYX YXI XYI XYI XYI IYX`

Layer `7`
`XIY XIY IXY XIY IXY IYX IXY IXY`
`XIY XIY IXY YIX YXI XIY IXY IXY`
`XYI YXI YXI YIX XYI YXI YXI XYI`
`YXI YXI YXI XIY XIY IXY IYX XYI`
`YXI YXI XYI XYI YXI XYI IXY YIX`
`IXY IYX XYI YXI XYI YXI YXI XIY`
`YXI XIY YIX XYI YXI YXI XYI YXI`
`XYI XYI IXY XIY IXY IXY YIX YXI`

- For this `m = 8` decomposition, each color's round map on `Z_8^2` is a single `64`-cycle.

### Key Parameters
- Whole-layer randomized factorization sampling at `m = 8`.

### Open Questions
- Can the `m = 6` and `m = 8` artifacts be compressed into a finite motif that survives for all even `m >= 4`?
- Is `m = 10` equally accessible by the same search, or does a new obstruction appear there?

## Exploration 9

### Strategy
Probe the next even case `m = 10` with the same whole-layer randomized factorization sampler that succeeded for `m = 6` and `m = 8`.

### Outcome
ABANDONED

### Failure Constraint
No structural obstruction was found. The limitation was computational: within the allotted search budget, the sampler improved the cycle profile substantially but did not reach three Hamilton round maps.

### What This Rules Out
- Nothing structural yet. This exploration does not suggest nonexistence for `m = 10`; it only shows that the current unguided sampler scales more slowly at this size.

### Surviving Structure
- The same sampler still moved far from random toward near-Hamilton profiles at `m = 10`.
- The even artifacts at `m = 6` and `m = 8` remain credible evidence that the search is probing the right space, even if `m = 10` needs stronger guidance.

### Reformulations
- None beyond explorations 7 and 8.

### Concrete Artifacts
- Best `m = 10` cycle profile reached in this run:
  `[100]`, `[74, 26]`, `[93, 4, 3]`.
- Earlier near-best profiles in the same run included:
  `[100]`, `[82, 18]`, `[84, 12, 4]`
  and
  `[78, 13, 9]`, `[53, 27, 20]`, `[77, 23]`.

### Key Parameters
- Whole-layer randomized factorization sampling at `m = 10` for one search budget of roughly `90` seconds.

### Open Questions
- Can the `m = 10` search be improved by local repair moves layered on top of whole-layer resampling?
- Is there a sign-aware structured family lurking inside the searched `m = 6` and `m = 8` solutions?

## Exploration 10

### Strategy
Recover an explicit `m = 4` layer table for later comparison, then push `m = 10` with multiple parity-aware search modes: pure whole-layer sampling, greedy small-radius layer repair, and annealed small-radius layer repair.

### Outcome
PARTIAL

### Failure Constraint
All successful search modes for `m = 10` converged to the same basin: two colors became Hamilton and the remaining color split as `[97,3]`. Neither greedy nor annealed resampling of `1`, `2`, or `3` whole layers escaped that basin within the allotted budget.

### What This Rules Out
- The hope that `m = 10` would fall to the same unguided whole-layer search that solved `m = 6` and `m = 8`.
- Purely local whole-layer repair around the current best `m = 10` candidate.

### Surviving Structure
- An explicit `m = 4` decomposition is now recovered in table form.
- `m = 10` is very likely not far from solvable computationally: multiple independent runs reached the identical near-hit profile with two exact Hamilton colors.
- The recurring `m = 10` defect is tiny and structured, not diffuse.

### Reformulations
- The `m = 10` behavior suggests a basin picture: the even search space contains a robust near-solution component where the global scaffolding is correct and only one small residual cycle remains.

### Concrete Artifacts
- Exact `m = 4` layer sequence recovered by the parity-aware search:

Layer `0`
`IYX IYX IYX IYX`
`YIX YIX YIX YIX`
`IYX IYX IYX IYX`
`YIX YIX YIX YIX`

Layer `1`
`YIX XIY IXY XIY`
`XIY XIY IYX YXI`
`XIY YIX XIY IXY`
`XYI IYX YXI XYI`

Layer `2`
`YXI XYI IYX YXI`
`IXY YIX XIY IXY`
`XYI IXY YIX YXI`
`YXI YXI YIX XYI`

Layer `3`
`XYI IYX YXI XYI`
`XYI IXY IYX XYI`
`YIX YXI XIY XIY`
`XIY IYX XYI YXI`

- Best `m = 10` profile reached:
  `[97,3]`, `[100]`, `[100]`.
- Other strong `m = 10` near-hits included:
  `[93,7]`, `[100]`, `[100]`
  and
  `[100]`, `[100]`, `[94,6]`.

### Key Parameters
- `m = 4` explicit recovery.
- `m = 10` whole-layer search with multiple seeds.
- `m = 10` greedy and annealed repair using replacements of up to `3` whole layers.

### Open Questions
- What invariant separates the `m = 10` near-hit basin from a true solution?
- Is the residual `3`-cycle at `m = 10` a genuine quotient obstruction tied to the factorization `10 = 2 * 5`?

## Synthesis after exploration 10

Across `m = 4, 6, 8`, the even artifacts are much less diagonal than the odd construction. The stable visual feature is strip structure: repeated rows, adjacent-row repetition, and broad horizontal bands of the same local permutation types. This is already visible at `m = 4`, becomes clearer at `m = 6`, and is very strong at `m = 8`.

The local alphabet is still the full set of six permutations `IXY`, `IYX`, `XIY`, `XYI`, `YIX`, `YXI`, but the exact even solutions do not use them in a diagonal-gadget way. Instead, they are arranged in short row words that repeat with low-complexity vertical modulation. That points toward a symbolic family built from row templates plus occasional repair layers, rather than from one fixed transversal or diagonal.

The failed `m = 10` search sharpens this picture: the scaffolding can evidently be made correct enough to produce two Hamilton colors and only one tiny residual `3`-cycle. So the missing insight for even `m` does not look like “how to globalize at all”; it looks more like “how to break a small quotient defect without destroying the strip-based scaffold.”

## Exploration 11

### Strategy
Attack `m = 12` from a structured starting point: lift the exact `m = 6` solution `6`-periodically to `m = 12`, then repair that lift by resampling a small number of whole layers.

### Outcome
PARTIAL

### Failure Constraint
The raw `6`-lift was much better than random, but the repair process still stalled before Hamiltonicity. The main obstruction moved from a clean `2 x 2` quotient defect to a near-Hamilton regime with one exact Hamilton color and two larger residual defects, and further small-radius whole-layer repair did not finish the job.

### What This Rules Out
- The raw `6`-periodic lift by itself as a full `m = 12` construction.
- Very small local repair around that lift as a complete solution mechanism.

### Surviving Structure
- The `m = 6` solution is genuinely relevant to `m = 12`: its raw lift is far closer than a random start.
- `m = 12` also appears to be governed by block/quotient structure rather than by a lack of global organization.

### Reformulations
- The `m = 12` problem can be viewed as a quotient-repair problem over the `6`-periodic lift: first build the right microstructure from `m = 6`, then splice the four quotient cycles.

### Concrete Artifacts
- Raw `6`-periodic lift to `m = 12`:
  each color decomposes into `4` cycles of length `36`.
- Best repaired `m = 12` profile reached:
  `[144]`, `[125,11,4,4]`, `[74,70]`.
- Earlier repaired `m = 12` near-hits included:
  `[132,9,3]`, `[141,3]`, `[119,9,7,6,3]`
  and
  `[110,25,6,3]`, `[108,36]`, `[135,9]`.

### Key Parameters
- Structured `m = 12` search initialized from the `6`-lift.
- Follow-up local repair with replacements of up to `3` whole layers.

### Open Questions
- Can the quotient defect of the `6`-lift be repaired symbolically, perhaps by a small fixed collection of non-periodic layers?
- Is there a hybrid `4 x 3` viewpoint for `m = 12` that is more natural than the `6 x 2` lift?

## Exploration 12

### Strategy
Use the exact even artifacts at `m = 4, 6, 8`, the stubborn `m = 10` near-hit, and the structured `m = 12` near-hit to look for a common symbolic mechanism.

### Outcome
PARTIAL

### Failure Constraint
No finished symbolic family emerged yet. The comparison sharpened the candidate mechanism, but not enough to write down a proof-quality construction.

### What This Rules Out
- The idea that the even family is just a noisy variant of the odd same-diagonal construction.
- The idea that larger even cases should look visually random if they are search-generated.

### Surviving Structure
- The even side is consistent with a strip-template family.
- Larger even cases seem to require two ingredients:
  1. a periodic microstructure inherited from a smaller even solution, and
  2. a sparse set of repair layers that kill a small quotient defect.
- `m = 10` behaves differently from `m = 12`: `10 = 2 * 5` seems to create a tiny but very rigid defect, while `12` responds well to the `6`-lift scaffold.

### Reformulations
- Candidate symbolic picture for even `m`:
  start from a low-complexity strip template, likely periodic in rows;
  then apply a bounded number of exceptional repair layers to merge a small residual quotient of cycles.

### Concrete Artifacts
- Exact cases available for comparison:
  `m = 4, 6, 8`.
- Best larger artifacts available for comparison:
  `m = 10` with profile `[97,3], [100], [100]`,
  `m = 12` with profile `[144], [125,11,4,4], [74,70]`.
- Shared visual pattern across all of these:
  strong row repetition, weak diagonal organization, and many adjacent rows that are identical or differ by only a small local rewrite.

### Key Parameters
- Comparison set: `m = 4, 6, 8, 10, 12`.

### Open Questions
- Can the strip-template idea be formalized as a finite row automaton producing the layer sequences?
- Is the right induction step from `m` to `m + 2`, from `m` to `2m`, or from `m` to `m + 4`?
- Does `m = 10` need a genuinely different microstructure from the `4/6/8/12` line, or is its residual `3`-cycle still compatible with the same family?

## Exploration 13

### Strategy
Analyze the exact `m = 10` near-hit at the permutation level, rather than only through cycle counts, to see whether the stubborn residual `3`-cycle sits behind a preserved invariant of the repair neighborhood.

### Outcome
PARTIAL

### Failure Constraint
The defective color in the canonical `m = 10` near-hit has the wrong permutation sign for Hamiltonicity: its round map on `Z_10^2` has sign `+1`, whereas a single `100`-cycle has sign `-1`. Any repair neighborhood that acts on that color only by even permutations is therefore trapped: it can move the `3`-cycle around, but it cannot merge `[97,3]` into `[100]`.

### What This Rules Out
- Any parity-neutral local repair scheme for the defective color, including neighborhoods built only from even layer trades.
- The idea that the remaining obstruction at `m = 10` is purely geometric. It already has a hard permutation-parity component.

### Surviving Structure
- The `m = 10` basin is genuinely close to a solution: the obstruction is now reduced to crossing a parity wall in the defective color.
- This points to a new kind of move: a repair that flips the sign of one chosen color while keeping a valid layer factorization.

### Reformulations
- Closing `[97,3]` can be restated as: find a local edit whose induced change on the defective round map is an odd permutation.
- Equivalently, one must introduce a sign-flipping trade in at least one layer (or in a short stack of layers) for the defective color.

### Concrete Artifacts
- In the exact trapped `m = 10` near-hit, the defective color has cycle profile `[97,3]` and sign `+1`.
- The residual `3`-cycle support is
  `(3,9) -> (6,3) -> (9,5) -> (3,9)`.
- Since a `100`-cycle has sign `-1`, any successful final repair must change the defective color sign.

### Key Parameters
- Parameter analyzed: `m = 10`.
- Object analyzed: the defective color round permutation in the canonical `[97,3], [100], [100]` near-hit.

### Open Questions
- What is the smallest support of a valid sign-flipping trade in one layer of the `I/X/Y` factorization model?
- Can that odd trade be embedded into the strip-template scaffold without destroying the other two Hamilton colors?

## Exploration 14

### Strategy
Search directly for a genuinely local parity-breaking layer trade: take a valid even layer, freeze the outside, and ask whether a small patch can be refactorized so that exactly one color flips sign. In parallel, sample many random valid layers to see which layer sign triples actually occur.

### Outcome
PARTIAL

### Failure Constraint
On the simple exact `m = 4` layer
with rows alternating `IYX` and `YIX`, there is no support-`k` patch with `k <= 10` whose replacement flips exactly one color sign while preserving a valid layer factorization. So the desired parity-breaking move is not a naive small rectangle or a tiny arbitrary Latin trade on that scaffold.

### What This Rules Out
- A `2 x 2`-style sign-breaking patch as the missing final move.
- The hope that the required odd trade is visible as a very small local rewrite on the simplest strip layer.

### Surviving Structure
- The right parity-breaking move probably has to be more global in one of two senses:
  1. larger support inside one layer, or
  2. a coupled trade across a short stack of consecutive layers.
- Random valid layers consistently realize the sign triples
  `(+,+,+)`, `(-,-,+)`, `(-,+,-)`, `(+,-,-)`, `(-,-,-)`.
  In particular, the single-negative sign triples did not appear in sampling for `m = 4, 6, 8, 10`.

### Reformulations
- A one-layer sign-flip for one chosen color should be sought as a transition between two valid layers whose sign triples differ by exactly one minus sign.
- Since sampled layer sign triples occupy only a restricted subset of `{+1,-1}^3`, the parity-breaking move is constrained already at the layer level, before any global cycle criterion is imposed.

### Concrete Artifacts
- Exhaustive patch search on the simple `m = 4` strip layer found no one-color sign-flip trade with support `<= 10`.
- Random layer-sign triples seen for `m = 4, 6, 8, 10`:
  `(+,+,+)`, `(-,-,+)`, `(-,+,-)`, `(+,-,-)`, `(-,-,-)`.

### Key Parameters
- Patch sizes tested in one layer: every support size `1` through `10` on the simple exact `m = 4` strip layer.
- Random layer sampling: `200` valid layers each for `m = 4, 6, 8, 10`.

### Open Questions
- Is the absence of the single-negative layer sign triples a theorem of the `I/X/Y` layer model?
- What is the smallest support of a one-color sign-flip trade on a generic even layer, if one exists at all?

## Exploration 15

### Strategy
Try to recover an `m = 10` near-hit quickly from scratch, to get a live repair target for the sign-aware operator rather than reasoning only from the earlier logged basin.

### Outcome
PARTIAL

### Failure Constraint
The quick recovery search reproduced the characteristic `97 + 3` defect immediately, but not the stronger basin with two Hamilton colors. So the residual `3`-cycle is robust, while the full `[97,3], [100], [100]` scaffold is rarer and needs either more time or a more directed initializer.

### What This Rules Out
- The hope that a very short random run would reliably regenerate the full canonical basin on demand.

### Surviving Structure
- The `97 + 3` phenomenon is not a one-off artifact. It appears quickly in fresh `m = 10` searches.
- The parity-focused repair idea still looks relevant, but the initializer should be stronger than a blind short run.

### Reformulations
- For implementation work, it is enough to target any near-hit whose leading defect is a `3`-cycle in one color; reproducing the exact canonical basin is not strictly necessary.

### Concrete Artifacts
- In a `20`-second fresh `m = 10` search with seed `0`, the best profile reached was
  `[97,3]`, `[84,16]`, `[51,26,20,3]`.

### Key Parameters
- Search run: `m = 10`, seed `0`, `20` seconds.

### Open Questions
- Which initializer recovers the stronger `[97,3], [100], [100]` basin most reliably?
- Does the same sign barrier appear already in the weaker fresh near-hits with one `97 + 3` color?

## Exploration 16

### Strategy
Inspect the newly provided fiber-coordinate tables and verify directly whether they encode genuine even decompositions, especially at the previously unresolved case `m = 10`.

### Outcome
SUCCEEDED

### Failure Constraint
N/A

### What This Rules Out
- The assumption that `m = 10` was still computationally unresolved.
- The assumption that the even family needed to be inferred only from noisy searched artifacts.

### Surviving Structure
- The fiber tables expose a clean even template:
  `m - 2` bulk layers of constant `XYI`,
  one exceptional staircase repair layer,
  and one terminal row-block layer of `YIX/IYX` type.
- This template is not just suggestive; it exactly realizes the known cases `m = 4, 6, 8, 10`.

### Reformulations
- The even family should now be viewed as a low-complexity strip/staircase construction rather than a random searched strip scaffold.

### Concrete Artifacts
- Direct verification from `p1_fiber_tables.md`:
  - `m = 4`: each color is a single `16`-cycle.
  - `m = 6`: each color is a single `36`-cycle.
  - `m = 8`: each color is a single `64`-cycle.
  - `m = 10`: each color is a single `100`-cycle.
- In each of these even cases, all three round-map signs are `-1`, as required.

### Key Parameters
- Verified table parameters: `m = 4, 6, 8, 10`.

### Open Questions
- Does the same fiber-table template also solve `m = 12` and beyond?
- Can the staircase layer and terminal row-block layer be written in a compact symbolic formula for all even `m >= 4`?

## Exploration 17

### Strategy
Push the verified fiber-table template one step further by checking the `m = 12` table directly.

### Outcome
SUCCEEDED

### Failure Constraint
N/A

### What This Rules Out
- The remaining belief that `m = 12` was only a near-hit or lift-repair phenomenon.

### Surviving Structure
- The same explicit fiber-table pattern that solves `m = 4, 6, 8, 10` also solves `m = 12`.
- The even side now looks like a genuine symbolic family, not a collection of isolated computational artifacts.

### Reformulations
- The main open problem for even `m` has shifted from existence to compression:
  write the bulk `XYI` layers, the staircase repair layer, and the terminal row-block layer as one clean formula.

### Concrete Artifacts
- Direct verification from `p1_fiber_tables.md`:
  for `m = 12`, each color round map is a single `144`-cycle.

### Key Parameters
- Verified table parameter: `m = 12`.

### Open Questions
- What is the exact general formula for the staircase repair layer?
- What is the exact general formula for the terminal `YIX/IYX` row-block layer?

## Exploration 18

### Strategy
Compress the verified `m = 12` fiber table into an explicit parametric family and extrapolate it to `m = 14` and `m = 16`.

### Outcome
PARTIAL

### Failure Constraint
The first extrapolated family correctly reproduces the full verified `m = 12` table and gives valid layer factorizations for `m = 14` and `m = 16`, but the resulting round maps are not yet Hamilton.

### What This Rules Out
- The naive idea that the visible `m = 12` pattern can be extended by a completely rigid row-template family with no further adjustments.

### Surviving Structure
- The even pattern really does compress: one can write a finite row-template family that exactly recovers `m = 12`.
- That same family remains valid as a layer-factorization family at `m = 14` and `m = 16`; the remaining issue is global cycle splicing, not local validity.

### Reformulations
- The extrapolation problem has split into two stages:
  1. generate a valid bulk/staircase/terminal layer system, and
  2. tune the staircase/terminal interaction so that the three round maps become transitive.

### Concrete Artifacts
- First extrapolated predictions:
  - `m = 14`: cycle profile
    `[72,62,62]`, `[179,10,7]`, `[92,53,51]`.
  - `m = 16`: cycle profile
    `[256]`, `[240,8,8]`, `[110,102,44]`.
- In both cases the predicted layers were valid one-layer factorizations, but not yet Hamilton decompositions.

### Key Parameters
- Tested extrapolation targets: `m = 14`, `m = 16`.

### Open Questions
- Which small adjustment to the staircase or terminal layer turns the valid extrapolated family into a Hamilton one?
- Is the right correction a shift of the two exceptional terminal rows, a modification of the bottom row templates, or both?

## Exploration 19

### Strategy
Assume the bulk pattern is correct and test the stronger hypothesis that only the last two layers matter: fix the first `m - 2` layers to `XYI` and try direct random search over the final two layers.

### Outcome
FAILED

### Failure Constraint
In this raw form the search was too slow to be useful at `m = 14, 16`. Sampling even a single pair of unrestricted final layers already took too long, so the method did not return informative cycle data on the available budget.

### What This Rules Out
- Unrestricted direct random search over the last two layers as a practical next step.

### Surviving Structure
- The reduction to “bulk `XYI` plus two special layers” still looks right conceptually.
- But the final two layers need to be searched inside a much smaller structured family, not by unrestricted layer sampling.

### Reformulations
- Future search should stay inside the row-template family suggested by the fiber tables, rather than over all valid one-layer factorizations.

### Concrete Artifacts
- No informative candidate was produced before the run became too slow to justify continuing it.

### Key Parameters
- Targets attempted: `m = 14`, `m = 16`.
- Bulk fixed: first `m - 2` layers set to `XYI`.

### Open Questions
- What is the smallest structured family for the final two layers that is still expressive enough to solve `m = 14` and `m = 16`?

## Exploration 20

### Strategy
Use the exact MRV solver directly on `m = 14` and `m = 16` to obtain ground-truth decompositions for comparison with the predicted staircase layers.

### Outcome
PARTIAL

### Failure Constraint
The unseeded exact solver did not return promptly on either `m = 14` or `m = 16` within the observed window, so in raw form it is too slow to serve as an interactive source of exact tables for these larger cases.

### What This Rules Out
- Blind use of the exact solver with no structural guidance as a practical workflow for the next even cases.

### Surviving Structure
- The MRV solver remains the right exact verifier.
- But to make it useful at `m = 14, 16, 18`, it should be seeded or domain-restricted by the near-correct staircase template.

### Reformulations
- The task is now: use the staircase prediction as a partial assignment, then let the exact solver repair only the gap.

### Concrete Artifacts
- Unseeded exact runs for `m = 14` and `m = 16` were launched and observed, but neither returned within the interactive budget.

### Key Parameters
- Exact solver targets attempted: `m = 14`, `m = 16`.

### Open Questions
- What is the smallest seed that makes the exact solver practical on `m = 14` and `m = 16`?
- Is it enough to fix the bulk `XYI` layers and leave only the final staircase region free?

## Exploration 21

### Strategy
Patch the exact solver to accept per-vertex domain restrictions, then seed it with the predicted even template: fix the bulk `XYI` layers, the top half of the staircase layer, and the full terminal row-block layer; leave the bottom staircase rows free and solve exactly.

### Outcome
PARTIAL

### Failure Constraint
No failure on the first target. The seeded exact solve for `m = 14` returned quickly and exposed the actual staircase defect precisely.

### What This Rules Out
- The hypothesis that the last layer was still part of the unknown pattern at `m = 14`.

### Surviving Structure
- The terminal row-block layer prediction is exact at `m = 14`.
- The bulk `XYI` region and the top half of the staircase are also correct.
- The only remaining error sits in a small block of the bottom staircase rows of layer `m - 2`.

### Reformulations
- The even extrapolation problem is now sharply localized:
  keep the bulk and last layer fixed, and determine the bottom staircase rows of layer `m - 2`.

### Concrete Artifacts
- Exact seeded solve for `m = 14` succeeded.
- The last layer had zero differences from the prediction.
- Penultimate-layer differences were confined to rows `8` through `12`.
- Exact `m = 14` penultimate rows from the solver:
  - row `8`: `XIY XIY XIY XIY XIY YIX XYI XYI XYI XYI XYI XYI XYI IXY`
  - row `9`: `XIY XIY XIY XIY YIX XIY XIY XIY XIY XIY XIY XIY XIY IXY`
  - row `10`: `XIY XIY XIY YIX XIY XIY XIY XIY XIY XIY XIY XIY XIY IXY`
  - row `11`: `XYI XYI YXI XIY XIY XIY XIY XIY XIY XIY XIY XIY YIX XYI`
  - row `12`: `XYI YXI XYI XYI XYI XYI XYI XYI XYI XYI XYI XYI IYX XYI`

### Key Parameters
- Exact seeded target solved: `m = 14`.

### Open Questions
- Does the same localization hold at `m = 16`?
- What compact row rule generates the exact `m = 14` staircase rows `8` through `12`?

## Exploration 22

### Strategy
Run the seeded exact comparison at `m = 16`, then refit the penultimate-layer staircase rule using the combined exact data from `m = 10, 12, 14, 16`.

### Outcome
SUCCEEDED

### Failure Constraint
N/A

### What This Rules Out
- The idea that the staircase defect was ad hoc or unstable across `m = 14` and `m = 16`.

### Surviving Structure
- The last layer formula is exact for `m = 10, 12, 14, 16`.
- The top half of the penultimate staircase layer is exact for `m = 10, 12, 14, 16`.
- The bottom staircase rows follow a parity-sensitive rule in `h = m/2`:
  even `h` and odd `h` have different tail behavior, but each regime is internally consistent across the solved cases.

### Reformulations
- The even family now has a concrete candidate symbolic form:
  bulk `XYI` layers,
  the known top staircase rows,
  and a parity-sensitive bottom staircase rule.

### Concrete Artifacts
- Exact seeded solve for `m = 16` succeeded, with zero differences from the corrected last-layer formula and zero differences from the corrected penultimate-layer formula.
- After refitting, the corrected predictor matches the exact data at:
  `m = 10, 12, 14, 16`.

### Key Parameters
- Exact seeded targets solved: `m = 14`, `m = 16`.
- Validation set for the corrected predictor: `m = 10, 12, 14, 16`.

### Open Questions
- Does the corrected parity-sensitive staircase rule already solve `m = 18`?
- If it does, is the next useful test `m = 20` or a symbolic proof of the cycle structure?

## Exploration 23

### Strategy
Apply the corrected parity-sensitive staircase rule unchanged at `m = 18`, verify the predicted fiber table directly, and then compare it against a seeded exact solve.

### Outcome
SUCCEEDED

### Failure Constraint
N/A

### What This Rules Out
- The idea that the corrected staircase rule only interpolates the solved cases up to `m = 16`.

### Surviving Structure
- The corrected staircase rule already gives a genuine Hamilton decomposition at `m = 18`.
- The last layer remains exactly right.
- By `m = 18`, the exact solution is not unique: the seeded exact solver found a different penultimate staircase, while the predicted staircase is itself already exact.

### Reformulations
- The staircase rule should now be viewed as one valid symbolic family rather than necessarily the unique exact family.

### Concrete Artifacts
- Direct verification of the predicted `m = 18` fiber table gave cycle profile
  `[324]`, `[324]`, `[324]`.
- A seeded exact solve at `m = 18` also succeeded.
- Comparing that exact solve to the predicted table gave:
  `0` differences in the last layer and `26` differences in the penultimate layer.

### Key Parameters
- Verified predicted target: `m = 18`.
- Exact seeded comparison target: `m = 18`.

### Open Questions
- Does the same symbolic family continue to work at `m = 20` and beyond?
- Can the cycle structure of the parity-sensitive staircase family now be proved symbolically?

## Exploration 25

### Strategy
Promote the corrected staircase family to a single explicit construction:
exact small cases `m = 4, 6, 8`, and the closed-form staircase rule for every even `m >= 10`. Then verify it on every even parameter up to `100`.

### Outcome
SUCCEEDED

### Failure Constraint
N/A

### What This Rules Out
- The possibility that the corrected staircase rule only works sporadically beyond the first few solved cases.

### Surviving Structure
- The explicit even family is now computationally stable across the full test range.
- The small cases `4, 6, 8` are genuine exceptions to the compact staircase rule, but from `m = 10` onward the family is uniform.

### Reformulations
- Even case, current best form:
  use exact exceptional tables for `m = 4, 6, 8`;
  for every even `m = 2h >= 10`, use
  `m - 2` bulk `XYI` layers,
  one parity-sensitive staircase layer,
  and one row-block terminal layer.

### Concrete Artifacts
- Direct verification passed for every even
  `m = 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100`.
- In every checked case, all three round maps were single cycles of length `m^2`.

### Key Parameters
- Verification range: all even `m` from `4` through `100`.

### Open Questions
- Can the parity-sensitive staircase family now be proved correct for all even `m >= 10`?
- Is there a cleaner reformulation of the staircase layer that removes the visible parity split in `h = m/2`?

## Exploration 24

### Strategy
Reduce the corrected even family to its three round maps on `Z_m^2` and inspect their row-by-row displacement patterns, to see whether the construction is really just a small perturbation of simple translations.

### Outcome
PARTIAL

### Failure Constraint
No proof yet, but the maps did not simplify all the way to a single one-line arithmetic formula.

### What This Rules Out
- The idea that the staircase family is still visually chaotic after composing the layers. It is not.

### Surviving Structure
- For `m = 12, 14, 16, 18`, each color round map is a near-translation with only a few exceptional columns in each row.
- The exceptional structure is strongly localized:
  long runs in a row share the same displacement vector, and only a small number of breakpoints occur.
- This makes a direct symbolic proof of Hamiltonicity look plausible: the family is much more rigid dynamically than the raw fiber tables suggest.

### Reformulations
- The proof problem may be attacked at the round-map level:
  describe each color as a piecewise translation of `Z_m^2` with a bounded number of row breakpoints, then analyze the induced row-to-row odometer behavior.

### Concrete Artifacts
- Computed explicit row-by-row displacement summaries for the predicted family at
  `m = 12, 14, 16, 18`.
- In every case, each row of each color had only a small number of displacement runs.

### Key Parameters
- Round-map inspection targets: `m = 12, 14, 16, 18`.

### Open Questions
- Can the row-run structure be written as an explicit piecewise formula for each color round map?
- Is there a natural conjugation that turns one or more of the three maps into an odometer plus a bounded carry rule?

## Exploration 26

### Strategy
Do a final consistency pass on the even-family write-up: rerun the direct verification for every even `m` from `4` through `100`, then clean the presentation of the fiber-table document so the closed-form rule is stated before the generated examples.

### Outcome
SUCCEEDED

### Failure Constraint
N/A

### What This Rules Out
- The possibility that the reported even family only passed an earlier ad hoc test harness but fails under the current direct round-map check.
- The possibility that the closed-form rule still needed case-by-case patching somewhere in the range `14 <= m <= 100`.

### Surviving Structure
- The even family remains:
  exact exceptional tables for `m = 4, 6, 8`,
  and a uniform parity-sensitive staircase rule for every even `m = 2h >= 10`.
- The verification result is fully stable: every tested even parameter through `100` gives three single `m^2`-cycles.

### Reformulations
- Presentation choice for the table file:
  state the closed-form rule first,
  then list compressed generated examples (`m = 14, 16, 18`),
  then retain the full explicit tables for `m = 4, 6, 8, 10, 12`.

### Concrete Artifacts
- Re-ran the direct verifier on every even `m = 4, 6, 8, ..., 100`; no failures.
- Prepared the final even-case write-up in `p1.md`.
- Cleaned `p1_fiber_tables.md` so the rule is the first mathematical object a reader sees.

### Key Parameters
- Verification range: all even `m` from `4` through `100`.

### Open Questions
- Can the parity-sensitive staircase rule now be proved correct for all even `m >= 10`?
- Is there a cleaner derivation that explains why the same terminal layer works uniformly while only the staircase layer carries parity dependence?

## Exploration 27

### Strategy
Bootstrap a local Lean 4 project inside `/Users/keston/at2` and check whether the odd-case formalization can be developed directly against `Mathlib`, with the first target being the load-bearing skew-map cycle criterion.

### Outcome
PARTIAL

### Failure Constraint
No theorem yet; this was an environment and scaffolding pass.

### What This Rules Out
- The concern that the repository lacked enough Lean infrastructure to start formalization immediately.
- The need to search for an external project skeleton before doing theorem work.

### Surviving Structure
- Lean `4.27.0`, `lake`, and `Mathlib` are all usable from inside the project directory.
- A minimal local package layout is now present and can host the proof files for `p1`.

### Reformulations
- Build iteration should use direct theorem-file checks first, then `lake build` once the main lemma stabilizes.

### Concrete Artifacts
- Added a local `lakefile.lean`, `lean-toolchain`, and `P1` library skeleton.
- Confirmed `mathlib4` resolves locally inside `.lake/packages`.

### Key Parameters
- Lean toolchain: `v4.27.0`.
- First formal target: lemma 1, the skew-map criterion on `ZMod m × ZMod m`.

### Open Questions
- What is the cleanest formal route to the cycle criterion:
  explicit orbit computation on `ZMod m × ZMod m`,
  or a conjugation to an additive translation?
- Which existing `Mathlib` lemmas about `ZMod`, units, and finite orders will minimize custom number-theory glue?

## Exploration 28

### Strategy
Attempt a first formal implementation of the core skew-map file, including explicit definitions for the skew permutation and the finite odometer that should serve as the normal form after conjugation.

### Outcome
FAILED

### Failure Constraint
The hand-written `Fin`-based odometer inverse was too brittle: coercions between `Fin m`, `Nat`, and the wrap-around cases generated avoidable proof noise and blocked progress before the main theorem was even stated cleanly.

### What This Rules Out
- The plan of proving the whole criterion around a manually specified `Fin` inverse with low-level case splits.
- Spending more proof budget on raw `Fin` arithmetic before the conjugation architecture is stabilized.

### Surviving Structure
- The `skewPerm` definition on `ZMod m × ZMod m` is straightforward and compiles modulo cleanup.
- The right normal form is still an odometer/rotation model, but it should be built from existing equivalences (`ZMod.finEquiv`, `finProdFinEquiv`, `finRotate`) instead of a bespoke inverse proof.

### Reformulations
- Sufficiency direction:
  conjugate to step `1`,
  straighten the cocycle,
  scale the second coordinate,
  and land on `finRotate`.
- Necessity direction:
  stay on the original skew map and extract the coprimality conditions from reachability of the targets `(1,0)` and `(0,1)`.

### Concrete Artifacts
- Added the first draft of `P1/SkewCycle.lean`.
- Identified the exact blocking zone: manual inverse proofs for the `Fin` odometer.

### Key Parameters
- Formal target remains lemma 1 only.

### Open Questions
- What is the minimal explicit odometer interface needed before the conjugation proof to `finRotate` becomes easy?
- Is it cleaner to formalize the core criterion with `Equiv.Perm.IsCycle`, or with a custom whole-orbit predicate first and connect to `IsCycle` later?
