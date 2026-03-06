# Meta-Observation Log: Orchestrating Two Agents on the Knuth Hamiltonian Decomposition Problem

## Background

**Problem:** Decompose the arcs of the Cayley digraph on Z_m^3 (with generators i+, j+, k+) into three directed Hamiltonian cycles, for all m > 2. Posed by Knuth for a future volume of TAOCP. Solved for odd m by Claude Opus 4.6 in a session guided by Filip Stappers (31 explorations, ~1 hour, significant human intervention). Published as "Claude's Cycles" (Knuth, Feb 28 2026, revised Mar 2 2026). Even case left open.

**Experiment:** Test a structured exploration prompt ("Residue") against the same problem, using two different LLM providers. Same prompt, same problem statement, no hints about odd/even split. Benchmark: does the prompt improve on the 31-exploration trajectory from the Knuth case?

**Agents:**
- **Fast agent** (Provider A): Top-down symbolic reasoner
- **Slow agent** (Provider B): Bottom-up computational solver

---

## Phase 1: Independent Runs on the Full Problem

### Fast Agent

| Exploration | Action | Result |
|---|---|---|
| 1 | Fiber-coordinate reformulation | Recast 3D problem as m-layer skew product over Z_m^2. Key structural move. |
| 2 | Compute exact m=3, m=4 | Solutions found. Confirmed layer factorization is right granularity. |
| 3 | Symbolic diagonal family analysis | Found Hamilton criterion: gcd conditions on (a_r, b_r) counts. Works for odd m ≥ 5. Parity obstruction blocks even m. |
| 4 | Explicit odd construction + even transversal search | Odd case closed for m ≥ 5. Even case: exhaustive search at m=4 rules out single-transversal families. |
| 5 | Verification sweep, odd m=3 to 101 | All pass. Odd case solved. |

**Observation:** 5 explorations, no human intervention. Same milestone as Knuth's 31-exploration session. Different construction (layer factorization vs. vertex-level direction function). More mathematically mature — top-down symbolic reduction rather than bottom-up pattern matching.

### Slow Agent

| Exploration | Action | Result |
|---|---|---|
| 1-2 | Computational search for m=3 | Found solutions. Identified cyclic symmetry. |
| 3 | d0-table approach for m=4 | Failed. Exhaustive search of 3^12 tables. |
| 4 | Block structure analysis | Partial. m=3 pattern doesn't scale. |
| 5-9 | Serpentine constructions | Extended dead end. Arc distribution fundamentally incompatible. |
| 10-12 | Brute force search, various orderings | Failed. Exponential blowup without constraint propagation. |
| 13 | Quotient approach | Works for m=3 only. Lift fails for m>3. |
| 14 | MRV + forward checking | **Breakthrough.** 67,000× speedup. Solutions for m=3 through m=12. |
| 15 | Literature search | Found Knuth's paper. Stopped. |

**Observation:** 15 explorations. Never found the fiber-coordinate framework. Reached the same serpentine attractor as Knuth's Claude and spent 5 explorations escaping it (vs. ~10 for Knuth's Claude). The breakthrough was algorithmic (better search), not mathematical (better theory). Produced solutions for m=10 and m=12 that the fast agent could not reach.

### Comparison

| Dimension | Fast Agent | Slow Agent | Knuth's Claude |
|---|---|---|---|
| Explorations to odd solution | 5 | Never (found individual cases) | 31 |
| Mathematical framework | Fiber coords + layer factorization | Permutation assignment + brute force | Fiber decomposition (expl. 15) + SA |
| Even case results | m=4, 6, 8 | m=4, 6, 8, 10, 12 | m=4, 6, 8 (claimed) |
| Nature of contribution | Proof | Computed examples | Construction (program) |
| Human intervention needed | None | None | Significant (restarts, reminders) |
| Degradation | Clean stall at m=10 | None (found literature) | Yes (lost ability to write programs) |

**Key insight:** Same prompt, radically different strategies. The prompt structured the record-keeping identically; the models diverged in reasoning style. The fast agent skipped the serpentine attractor entirely. The slow agent followed almost the same trajectory as Knuth's Claude but compressed by the structured logging.

---

## Phase 2: Fast Agent Pushes Even Case

Instructed to work on even m with 15-exploration budget.

| Exploration | Action | Result |
|---|---|---|
| 6 | Periodic lift of m=4 solution | Failed. Block quotient not transitive. Bounded-state rules also fail. |
| 7 | Sign parity analysis + whole-layer search | **Found m=6.** Discovered layer-sign parity invariant (new structural result). |
| 8 | Push to m=8 | Found m=8 by same whole-layer search. |
| 9 | Push to m=10 | **Abandoned.** Best profile [97,3], [100], [100]. Rigid basin, not a compute issue. |

**Observation:** Agent discovered the layer-sign parity invariant — for even m, valid decompositions require an odd number of sign-negative layers. This explains why Kempe-cycle local search gets trapped. Not in Knuth's paper. Genuine structural contribution. But stalled at m=10 with a 3-cycle defect it couldn't close.

---

## Phase 3: Cross-Agent Data Transfer

### Decision Point
The slow agent had m=10 and m=12 solutions. The fast agent had the structural framework but couldn't reach m=10. I decided to bridge them.

### Action: Fiber Coordinate Tables
Asked slow agent to export m=4, 6, 8, 10, 12 solutions in fiber-coordinate layer format (the fast agent's native representation). Passed the resulting p1_fiber_tables.md to the fast agent.

### Fast Agent Response
Immediate recognition: "p1_fiber_tables.md unblocked the even side in a real way." All five solutions verified. Pattern identified: **m-2 bulk XYI layers, one staircase repair layer, one terminal row-block layer.** Simpler description than any other known approach to the even case.

**Observation:** The combination produced insight that neither agent could reach alone. Fast agent had the framework but not the data. Slow agent had the data but not the framework. The human orchestrator was the bridge — same role as Filip, but routing information between agents rather than managing one agent's session.

---

## Phase 4: Tool Transfer

### Decision Point
Fast agent needed to verify predictions at m=14, 16 but couldn't compute exact solutions. Slow agent had the MRV solver.

### Action
Extracted MRV solver from slow agent as standalone Python function. Placed in fast agent's working directory.

### Fast Agent Response
Dismissed the unseeded solver as too slow for m ≥ 14. Adapted it into a seeded solver, using its own structural predictions to constrain the domain. This is the ideal synthesis: theory-guided search.

**Observation:** The fast agent didn't use the tool as given — it improved it by combining the slow agent's search infrastructure with its own structural knowledge. The seeded solver is faster than either the raw MRV or the fast agent's analytical approach alone.

---

## Phase 5: Closing the Even Case

### Fast Agent Trajectory (with seeded solver)

- Seeded exact solve at m=14 and m=16: both returned quickly.
- Last layer prediction was correct. Error localized to bottom staircase rows of penultimate layer.
- Refitting produced a **parity-sensitive staircase rule in h = m/2**.
- Corrected rule matches exact data for m=10, 12, 14, 16.
- **m=18: predicted table verifies directly.** Three round maps are [324], [324], [324].

### Context Update
Informed the fast agent that other researchers (Stappers with Claude, Ho Boon Suan with GPT-5.3-codex) had found working even-case constructions but described them as "chaotic" and "far more complex" than the odd case. No clean closed-form family known.

### Current Status
Fast agent is running verification of the closed-form even construction for all even m from 4 to 100. If it passes, this is the cleanest even-case result known — simpler than any other published construction.

---

## Meta-Observations

### What the Prompt Did

1. **Prevented serpentine trap compression.** The slow agent spent 5 explorations on serpentines (vs. ~10 for Knuth's Claude). The structured failure logging forced clear articulation of why serpentines fail, preventing minor-variation grinding.

2. **Made reformulations persistent.** Both agents discovered fiber coordinates. The fast agent made it central because the Reformulations field elevated it to a first-class artifact. The slow agent noted it but didn't build on it — suggesting the field helps but can't force a model to recognize which insight is load-bearing.

3. **Enabled clean escalation.** The fast agent's stall at m=10 was well-documented: specific basin ([97,3]), specific diagnosis (repair moves preserve an invariant), specific handoff ("here's what kind of insight I'm missing"). This made the cross-agent transfer actionable.

4. **Produced different strategies from different models.** Same scaffolding, different reasoning styles. The prompt structures process, not thought.

### What the Prompt Didn't Do

1. **Didn't expand conception space.** The slow agent never found the layer-factorization framework. No prompt can make a model see structure it can't see.

2. **Didn't prevent dead ends.** Both agents explored unproductive directions. The prompt made the dead ends well-documented and bounded, not non-existent.

3. **Didn't replace the human orchestrator.** The key decisions — when to transfer data between agents, when to transfer tools, what context to provide — were all human. The prompt made each agent more effective individually, but the combination required external coordination.

### What Surprised Us

1. **The slow agent's MRV breakthrough was the most consequential single move.** Not mathematical insight but engineering — and it produced more even-case data than the fast agent's elegant theory.

2. **The cross-agent combination was strictly more powerful than either agent alone.** This wasn't planned — it emerged from the fast agent's stall at m=10 and the slow agent's brute-force solutions.

3. **The fast agent improved the slow agent's tool.** The seeded solver is better than either the raw MRV or the fast agent's analytical predictions. Tools transfer and evolve across agents.

4. **The even case may be genuinely messier than the odd case.** Every approach — Stappers, Ho Boon Suan, both agents — found the even case harder and less elegant. The fast agent's "m-2 bulk layers plus two repair layers" is the simplest description so far, but still more complex than the odd case's pure arithmetic criterion. This may reflect the problem's structure, not any agent's limitation.

---

## Timeline

| Step | Action | Outcome |
|---|---|---|
| 0 | Designed prompt based on analysis of Knuth's paper and Claude's Cycles | Residue prompt v2 |
| 1 | Launched fast agent on full problem | Odd case solved in 5 explorations |
| 2 | Launched slow agent on same problem (different provider) | Reached serpentine dead end, then MRV breakthrough at expl. 14, solutions through m=12 |
| 3 | Directed fast agent to even case (15-expl budget) | Found m=6, m=8. Layer-sign parity invariant. Stalled at m=10. |
| 4 | Extracted slow agent's even solutions in fiber coordinates | p1_fiber_tables.md: m=4,6,8,10,12 |
| 5 | Passed fiber tables to fast agent | Immediate pattern recognition: bulk XYI + staircase + row-block |
| 6 | Transferred MRV solver to fast agent | Fast agent adapted it into seeded solver |
| 7 | Fast agent predicted and verified m=14, 16, 18 | Parity-sensitive staircase rule. m=18 verifies independently. |
| 8 | Informed fast agent of external results (Stappers, Ho Boon Suan) | Context: no clean closed-form known elsewhere |
| 9 | Fast agent running full verification m=4 to 100 | **Pending** |
