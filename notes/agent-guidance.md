# Future matching-agent sessions: tricky C spellings

Read this when equivalent-looking rewrites repeatedly fail to move a residual.
The concrete solved example is [STRTOK's assignment tests and loop shape](research/strtok-assignment-tests-and-loop-shape.md).
These are experiment prompts, not universal code-generation rules.

1. **Restore source operations before imitating emitted instructions.** A
   decompiler's load/increment/cast/test sequence may have come from one
   assignment expression. In STRTOK, `s8 c; if ((c = *s++) == 0)` produced the
   target's `lbu`, `lb`, and delay-slot increment. Explicitly loading through
   `s - 1` reproduced the bytes read, but introduced the wrong machine operand.
   Check the assignment's destination type, narrowing and expression value—not
   just the pointer type. Plain `char` here is unsigned under production flags.
2. **Keep syntactic loops in the hypothesis space.** A backward goto and a
   `while` can compute the same thing but present different loop notes and
   optimization opportunities. STRTOK's second phase matched when its label
   loop became `while ((c = *s++) != 0)`, keeping the shared termination label.
   Read native loop evidence rather than assuming all CFG-equivalent C is the
   same compiler experiment.
3. **Verify delay-slot semantics independently of m2c.** Identify which pointer
   value supplies a branch's loaded operand and which update executes in its
   delay slot. Fix compilation errors separately from semantic transcription
   errors. Do not make the optimizer's increment placement a source requirement
   before testing the ordinary fetch-and-postincrement expression.
4. **Read the ledger and classify a compiling residual.** Use
   `psx_reverse_pipeline` with the actual scratch source, then the mechanism
   sheet or native trace for the owning pass. Honor provisional ownership and
   missing replay checks. Different instruction populations are not a license
   to begin register-allocation tuning.
5. **Check block correspondence before trusting block scores.** A degraded CFG
   comparison can make five reported population differences look like a tiny
   local fix while comparing different regions. Even equal block counts do not
   prove correspondence. Check actual operations and edges; byte/whole-TU
   identity remains the acceptance oracle.
6. **Stop respelling identical compiler output.** `ALREADY MEASURED` means the
   same experiment, not another vote against clean C. After several distinct
   failures, change the evidence class: declarations/SDK boundaries, matched
   source idioms, native pass dumps, compiler-source rules, or a bounded
   mechanism-specific experiment. Do not keep permuting local declarations.
7. **Scope every negative result.** An engine refusing symbolic relocations, a
   sweep lacking the required source input, or an unsupported compiler flag
   closes no clean-C source domain. Record the actual capability limit and its
   premises. A flag change needs independent evidence, not fatigue.
8. **Finish with the real gate.** A scratch EXACT must be integrated and pass
   `psx_finalize_function` (owning-TU bytes/relocations, full build, scope and
   source policy). Preserve neighbors and original data. Document measured
   constructions and their conditions; do not claim historical source recovery
   or add speculative TU groupings. Do not commit unless explicitly asked.
