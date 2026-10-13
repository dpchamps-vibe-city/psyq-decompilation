# Plan: configurable assembler backend (MASPSX or direct GNU as)

Status: implemented in the harness and adopted here on 2026-10-13, following
explicit user authorization. See the implementation record below for validation
and the broader harness-suite limitation.

## Implementation record

- Config/schema, closed rewrites, shared sync/async assembler builder, GAS input
  and listing capture, effective identities/caches, and all invocation sites are
  implemented. Legacy omitted-backend argv and v1 compilation/toolchain identity
  shapes are preserved; explicit selections carry assembler kind and rewrites.
  Raw/reference assembly also uses the builder, without compiler rewrites.
- Diagnostics cover indexed triples, expected absolute-load expansions, GAS
  attribution caveats, GP-rule guarding, profile summaries and original-word/native
  packaging evidence. Documentation is assembler-neutral; MASPSX is unchanged.
- Five new focused tests, grouped in two files, cover the configuration/builder,
  synthetic backend words/listings, and diagnostic rules/packaging. The affected
  suite run passed **103 tests**, with five optional skips; the final packaging
  boundary adjustment passed its two diagnostic tests separately.
- The broad `npm test` run was not green: 1,292 passed, 22 failed, 122 skipped.
  Feature-related identity/schedule/census integration failures were corrected
  and covered by the affected-suite run. Other failures included unchanged
  prompt-contract, CLI-registration, preparation-freshness, ELF-header,
  modification-time and overlay-routing checks. No claim is made that the
  entire harness suite now passes; it was not repeatedly rerun or repaired
  outside this feature's scope. Strict TypeScript also retains inherited errors.
- This project's base is GAS + `move-addu`, with no lowered `-O`. The 38 old
  unpadded libsn selections are renamed `sn-aspsx`. Native packaging witnesses
  authorize 16 additional members under `sn-aspsx-padded`, retaining their
  default padding rather than copying the unpadded flag.
- All **123** previously verified members remain whole-member MATCHes.
  StopRCnt (**92/92**) and SetInitPadFlag (**164/164**) were integrated separately
  and passed official member/build/scope/source-policy/context-publication gates.
  Both already had accepted neighbors, so the accepted-member count remains 123.
- GAS expansion receipts have byte-identical production/listing objects. There
  were no warnings in 125 production receipts. StopRCnt reversal has complete
  value correspondence and no unpaired address webs; missing .mach replay
  evidence remains provisional rather than being fabricated.
- The active Pi finalizer had stale in-process project-schema modules. The same
  official `finalizeWorkspace` implementation passed in a fresh runtime; reload
  Pi to refresh its loaded modules. No gate or configuration validation was
  bypassed. See `notes/stoprcnt-investigation.md` §19 and
  `configs/toolchain-identification.md` for project evidence and remaining
  ambiguous libsn packaging. No commits were made.

## Where the work happens

| Repo | Location | Work |
|---|---|---|
| **Harness** | `../psx-decompilation-harness/` (sibling checkout) | Phases 0–4: the feature, its tests and docs. |
| **This project** | `psyq-decomp` (this repo) | Phase 5: adopt the feature. The evidence also lives here. |

Path convention: paths are written from the root of the repo they belong to.
Sections marked **(harness)** use harness-relative paths; for example,
`tools/lib/toolchain.ts` means `../psx-decompilation-harness/tools/lib/toolchain.ts`.
This project's files are always marked "this repo". `../btn-decompilation/…`
is a sibling checkout and resolves the same way from either repo. MASPSX itself
is not modified anywhere.

## Purpose

Make the assembler stage a configured, per-profile choice instead of a
hard-coded `cc1 → MASPSX → GAS` protocol:

- `maspsx`: today's behavior. ASPSX emulation, which is right for code built
  with SN's `ccpsx`/`ASPSX` (games such as BTN, and SN's own `libsn`).
- `gas`: GNU `as` assembles cc1's output directly, after a small, named
  period-compatibility rewrite. This is right for code built with a GNU
  toolchain, which includes Sony's PSY-Q SDK libraries.

The configured assembler remains the one acceptance path. Assembling through an
unconfigured path is still only a diagnostic.

## Why: measured evidence in this repo (2026-10-13)

StopRCnt's only residual was three words: the original computes the mask-table
address in `$v0`, the candidate in `$at` (this repo:
`notes/stoprcnt-investigation.md` §4).

| Measurement | Result |
|---|---|
| COUNTER.OBJ itself | StartRCnt's `lw $4,D($4)` (dest = base) expands with `$at`; StopRCnt's `lw $2,D($4)` (dest ≠ base) expands with `$v0`. That is GNU `as`'s macro rule. ASPSX always uses `$at`. |
| Real ASPSX 2.86 (`../btn-decompilation/tools/vendor/psyq_sdk/psyq/bin/ASPSX.EXE`, wine) on the same cc1 output | `lui at / addu at,at,a0 / lw v0,8(at)`, identical to MASPSX. MASPSX models ASPSX correctly. |
| SDK `CC1PSX.EXE` (GCC 2.95.2 SN build 4.0.0030, `-msplit-addresses` default) | Emits a 4-instruction `lui/addiu/addu/lw 0` form. That does not explain the original either. |
| Census of all 2,224 converted members | 455 indexed loads with dest ≠ base use the destination as temp (GAS rule), in 133 members across 19 libraries. **0** use `$at` (ASPSX rule). 160 with dest = base use `$at` (both rules agree). |
| Native LNK packaging, all LIBs | 2,167 Sony objects have converter-style section ids `0xF001…`, no file records, and immediates prefilled with `.data` placed after `.text`: a COFF-style GNU object converted to LNK. Only `Libsn.lib` (48 objects) has ASPSX-native packaging (ids `1…`, `.ctors/.dtors`, file records). |
| Plain GNU as on the production cc1 output, scored with the harness's `compareRelocatableObjects` | StopRCnt's minimal C: **92/92 whole-member MATCH** (MASPSX path: 89/92). All **123/123** currently verified members still match, with GAS default and with `-O1`. No assembler warnings. |
| Remaining GAS difference | binutils 2.42 encodes `move` as `or` (`0x00001025`); the originals and MASPSX's `expand_move` use `addu` (`0x00001021`). That is the only rewrite needed so far. |
| Delay-slot swap census, all members | 590 sites where the second half of a 2-word macro sits in a branch delay slot (`lui rT` / branch / `s*`,`addiu`,`ori` using rT). 210 of them use `$at`, which only the assembler allocates. Only GAS's reorder-mode swap at its default `-O2` produces this; GCC 2.7.2's delay-slot pass cannot split a macro. Only 2 counter-examples (macro + branch + `nop`): one in libgte `PushMatrix`, one in libsn (SN-built). |
| `SetInitPadFlag` (still a stub), C `D_00000300 = flag;` | Whole-member **MATCH 164/164** with GAS default (`lui at / jr ra / sw a0,0(at)`). GAS `-O1` and production MASPSX both mismatch (`lui / sw / jr / nop`). The current pipeline cannot match this class of function. |

Interpretation: no MASPSX defect. ASPSX is the wrong assembler model for the
Sony-built libraries. The harness's current policy text in
`../psx-decompilation-harness/docs/toolchain.md` ("assembling cc1's `.s`
directly with GAS … is not an acceptance oracle") is what prevented earlier
sessions from acting on a correct GAS observation (investigation §10). That
policy needs to become assembler-neutral.

## Decisions and scope

1. **Additive, default-preserving.** If `assembler` is absent, the kind is
   `maspsx` and every argv stays byte-identical to today. BTN and every
   existing project are unaffected. `schemaVersion` stays 1.
2. **MASPSX is untouched.** It stays at the same pin and is still used for
   `maspsx` profiles.
3. **One command builder.** No harness tool constructs an assembler command
   anywhere else. The parity tests enforce this.
4. **GAS input rewrites are named, closed and evidence-backed.** Each rewrite
   needs original-word evidence and a regression test. Rewrites apply only to
   compiler output, never to `.include`d stubs or handwritten assembly. Line
   count is preserved.
5. **The assembler choice is evidence-based per container/member.** The
   harness's identification report gains assembler-family evidence. Nothing
   switches automatically.
6. **GAS runs at its default optimization level** (branch swapping on). The
   swap census and `SetInitPadFlag` require it. `-O` stays an ordinary
   `flags.as` argument, but this project must not lower it, and a harness
   fixture guards the behavior.
7. **The harness stays game- and SDK-agnostic.** Harness tests use synthetic
   fixtures through `tools/testing/projectFixture.ts` / `harnessFixture.ts`
   (see `test-fixtures/harness/README.md`). They contain no PSY-Q names or
   bytes, consistent with `docs/game-agnosticity.md`. Harness docs describe
   the mechanism and how to gather evidence. The PSY-Q conclusion is recorded
   in this repo, and the real-member checks run here in Phase 5.
8. **Out of scope:** compiler-version identification, the real-ASPSX
   differential tool (`../btn-decompilation/plans/aspsx-same-input-differential.md`),
   and MASPSX changes.
9. **Harness constraints:** the harness's `AGENTS.md` stays off-limits. Its
   working tree currently holds uncommitted repairs in 17 files (flag-probe,
   triage, idiom corpus/scratch census, residual objective, docs). Build on
   them and do not revert them. Commit them first if the user agrees.

## Design (harness)

### Configuration

The schema is a harness change. The values below are what this project adopts
in Phase 5:

```json
{
  "assembler": { "kind": "gas", "inputRewrites": ["move-addu"] },
  "profiles": {
    "sn-aspsx": {
      "assembler": { "kind": "maspsx" },
      "as": ["-march=r3000", "-mtune=r3000", "-EL", "-G0", "-no-pad-sections"]
    }
  }
}
```

- `assembler.kind`: `"maspsx" | "gas"`. The base default is `{ "kind": "maspsx" }`.
- `assembler.inputRewrites`: required for `gas` (may be empty) and rejected for
  `maspsx`. Each entry must be a known rewrite id. Initial set: `move-addu`.
- A profile's `assembler` replaces the base value, consistent with "supplied
  arrays replace". Resolution follows the existing owner order:
  `container.profile` → `containerProfiles[id]` → `containerProfiles[kind]`.
  For libraries, the project's `project.json` `memberProfiles[id]` →
  `toolchainProfile` (`tools/lib/project.ts` `libraryContext`).
- `tools.maspsx` and `flags.maspsx` stay required in v1. They are ignored for
  contexts whose effective kind is `gas`.
- Reject `gas` combined with a nonzero `-G` in `flags.as` until GAS's
  small-data rule is modeled (see the rules table).

Files: `tools/lib/toolchain.ts` (`ToolchainConfig`, `loadToolchain` key
validation, a new `configuredAssembler(context, root)`),
`tools/lib/toolchain.schema.json`. `templates/project/toolchain.json` keeps
the default; scaffolding does not pick `gas`.

### Command builder: new `tools/lib/assembler.ts`

```ts
type AssemblerKind = "maspsx" | "gas";
interface AssemblerSelection { kind: AssemblerKind; inputRewrites: string[] }
configuredAssembler(context?: FlagContext, root?): AssemblerSelection
assemblerInvocation(context, input, object, root): { command; args; cwd; assemblerInput }
assemble(...) / assembleAsync(...)        // runs it, returns a receipt
captureAssemblerExpansion(...)            // kind-aware, see below
assemblerRules(kind): AssemblerRules      // the rules table, for diagnostics
```

- **maspsx:** `python <tools.maspsx> <flags.maspsx> --gnu-as-path <tools.as> -o <obj> <flags.as> <input.s>`,
  cwd = the project root. A test asserts this is byte-identical to today's argv.
- **gas:** write `<obj>.as-input.s`, which is cc1's `.s` with the rewrites
  applied line by line. Then run `<tools.as> <flags.as> <obj>.as-input.s -o <obj>`
  with cwd = the project root, so project-relative `.include`s (for example
  this repo's `include/macro.inc` and `build/libraries/nonmatchings/...`)
  resolve as they do today. There is no implicit `-G0`; MASPSX injects one
  unless `--dont-force-G0` is given, so document that difference.
- **`move-addu`:** an instruction line that is exactly `move rd,rs` (two
  register operands, optional trailing `#` comment) becomes `addu rd,rs,$0`.
  Labels, directives, comments, `.include` targets and every other mnemonic
  are left alone. spimdisasm stubs already spell these as explicit
  `addu …,$zero`, so they never needed it.

Migrate all five invocation sites to the builder:

| Site | Today |
|---|---|
| `tools/build/pipeline.ts` `compileObject` | literal MASPSX argv |
| `tools/agent/decompToolchain.ts` `assembleCompilerOutput` | literal MASPSX argv |
| `tools/agent/decompToolchain.ts` `compileSourceAsync` | literal MASPSX argv |
| `tools/agent/prepareFunction.ts` `measurePreparation` | literal MASPSX argv |
| `tools/agent/decompToolchain.ts` `captureAssemblerExpansion` | MASPSX without `--run-assembler` |

### Expansion receipts

- **maspsx:** unchanged. The MASPSX text output is the expansion.
- **gas:** keep `<obj>.as-input.s` plus a GAS listing (`-alm=<obj>.listing.txt`).
  Verified on binutils 2.42 (this repo's
  `build/assembler-backend-evidence/gas-listing-counter.lst`): the listing maps
  each source line to all of its words. For example, `lw $2,D_000001E8($4)`
  lists `0000023C 21104400 0800428C`, i.e. `lui v0 / addu v0,v0,a0 / lw v0,8(v0)`.
  Producing the listing needs a second assembly with the listing flag, so the
  production object is not built with extra flags. Assert that both objects
  are byte-identical.
- The receipt records `kind`, rewrites, input/listing/object hashes and both
  argvs. Wording in `tools/agent/residualObjective.ts` and
  `tools/agent/pipeline-reversal/render-text.ts` becomes assembler-neutral
  ("configured assembler expansion").

### Identity, caching and receipts

Each of these must carry the effective selection (`kind` + rewrites + MASPSX
hash when used):

- `tools/lib/cacheIdentity.ts` `compilationIdentity`: add
  `assembler: configuredAssembler(flags)`. Include `maspsx` flags/hash only
  when the kind is `maspsx`.
- `tools/agent/decompToolchain.ts` `configuredToolchainIdentity`: replace
  `assemblerShim` with `assembler: { kind, inputRewrites, maspsx? }`.
- `tools/build/buildInputs.ts` `buildToolInputs`: keep the `maspsx/` package
  directory, plus `tools/lib/assembler.ts` itself.
- Reports that list stage flags: `tools/agent/idiom-corpus/fingerprint.ts`
  (`contextFlags`), `tools/diagnostics/macroIdentity.ts`,
  `tools/diagnostics/macroEncodings.ts`, `tools/agent/pipeline-reversal/reverse.ts`.
- `tools/agent/type-propagation/seeds.ts`: it hard-codes stale
  `tools/vendor/maspsx/...` paths. Switch it to `buildToolInputs`.

Changing a member's assembler changes its verification identity, so its
receipt becomes stale and must be re-verified. That is intended.

### Assembler rules, and the diagnostics that must use them

| Behavior | `maspsx` (ASPSX ≥ 2.30) | `gas` |
|---|---|---|
| `l* rD,sym(rB)` temp | `$at` | `rD`, or `$at` when `rD == rB` |
| `l* rD,sym` (no index) | `rD` (left to GAS) | `rD` |
| `s* rV,sym(rB)` / `s* rV,sym` | `$at` | `$at` |
| `move` | `addu` (MASPSX `expand_move`) | `addu` via `move-addu` |
| load-delay / HI-LO hazard nops | inserted into the text by MASPSX (`# DEBUG:`), with `.set noreorder` forced per `.ent` | inserted internally by GAS in reorder mode; visible only in the listing/object |
| reorder-mode branch delay slots | never filled (noreorder forced) | GAS swaps the preceding instruction in, including a macro's last word; never a MIPS1 load. Default `-O2`, required by the evidence. |
| small data, `-G > 0` | ASPSX: GP-relative only for symbols the file declares | GAS: undeclared externs assumed small. Unsupported until modeled. |
| `-G` passed to GAS | `-G0` forced unless `--dont-force-G0` | exactly `flags.as` |

Consumers to update:

1. **`tools/agent/pipeline-reversal/inverse-assembler.ts`.** It folds only the
   2-instruction `lui/l*` pair. Add folding for the indexed triple
   `lui T,%hi(s) / addu T,T,B / l* D,%lo(s)(T)` → `l* D,s(B)`. Accept
   `T = $at`, and also `T = D ≠ B` when the rule is `gas`. Record which rule
   folded it. Expected effect, checked in Phase 5: StopRCnt-shaped targets no
   longer leave the address webs unpaired (investigation §9.1, target values
   5/6). Verify this rather than assume it.
2. **`tools/agent/flagProbe.ts` `fingerprintSelfClobberLoads` and
   `tools/agent/triage.ts` `symbolicSelfClobberPairs` /
   `detectFlagFingerprint`.** `lui rD / l* rD,%lo(s)(rD)` is the normal
   expansion of `l* rD,s` under both kinds. Under `gas` this extends to the
   indexed triple. Classify it as an expected assembler expansion, not a
   `-mno-split-addresses` fingerprint. Example from this repo: COUNTER words
   2–3 are the plain `lw $5,D_000001E0`.
3. **`tools/agent/compiler-trace/emission-attribution.ts`.** Under `gas`,
   `assemblerInserted` is empty by construction. Add a caveat pointing to the
   listing. Keep MASPSX `# DEBUG:` handling.
4. **`tools/build/deriveTuOwnedGlobals.ts`.** Its GP rule is ASPSX's. Guard it
   by kind, and fail clearly for `gas` with nonzero `-G`.
5. **`tools/build/genProjectProfile.ts`.** The "Assembler semantics" sentence
   and the console summary report the kind per profile, plus the ASPSX version
   only for `maspsx`.
6. **`tools/diagnostics/identifyToolchain.ts`.** Add assembler-family
   evidence: a per-member census of dest≠base indexed loads (`gas-rule` /
   `aspsx-rule` / `ambiguous`). When the project's `sdk.originalDir` holds
   native LNK libraries, also add the packaging signature (first section id
   `0xF001` vs `1`, `.ctors/.dtors`, file records). This is report-only and
   never writes configuration. Use this repo's `census_indexed_loads.py` as
   the reference behavior.
7. **`tools/agent/idiom-corpus/scratch-census.ts` / docs.** Name
   "load-destination" scratch as the GAS rule and `$at` as either.

### Documentation (harness)

- `docs/toolchain.md`:
  - The protocol is cpp → cc1 → configured assembler (MASPSX→GAS, or direct
    GAS with named rewrites).
  - Replace the paragraph that calls direct GAS "not an acceptance oracle"
    with: the configured assembler is the only acceptance path; any other
    assembly path is diagnostic; changing a container's assembler requires
    assembler-family evidence and re-verification.
  - Document `assembler` and `inputRewrites`.
  - Keep "ASPSX 2.80 is a starting candidate" scoped to `maspsx`.
- `docs/library-targets.md`: same protocol sentence. Explain how to choose a
  kind per member from the identification evidence; a target's own
  ASPSX-built and GNU-built members may differ. No SDK-specific conclusions
  (decision 7).
- Check the wording in `docs/migration.md`, `docs/bootstrap.md` and
  `docs/game-agnosticity.md`.

## Phases

### Phases 0–4 (harness)

**Phase 0: baseline and fixtures.**
- Record today's argv for all five sites from a synthetic fixture project.
- Add synthetic fixtures (decision 7), assembled through the builder, with
  expected `.text` words per kind:
  - `lw $2,sym($4)` (dest ≠ base): `$at` under `maspsx`, `$v0` under `gas`.
  - `lw $4,sym($4)` (dest = base): `$at` under both.
  - Delay slot: `sw $4,sym` then `j $31` in reorder mode. Under `gas` at the
    default `-O`, expect `lui at / jr ra / sw a0,%lo(sym)(at)`; under `gas -O1`
    and `maspsx`, `lui / sw / jr / nop`.
  - `move $2,$0`: `0x00001021` under both.
- Exit: the fixture tests fail for `gas` only because `gas` does not exist yet.

**Phase 1: config and builder; default behavior only.**
- Schema/loader validation, `configuredAssembler`, `tools/lib/assembler.ts`,
  and all five call sites migrated.
- Exit: argv byte-identical under the default; all existing tests pass; the
  parity tests forbid assembler commands outside the builder.

**Phase 2: the `gas` backend.**
- Rewrites, `.as-input.s`, listing capture, identity/caching fields, and the
  nonzero-`-G` guard.
- Exit: the synthetic fixtures pass for both kinds. As a pre-merge check, a
  scratch copy of this repo with the Phase 5 config reproduces the measured
  results against the harness branch.

**Phase 3: assembler-aware diagnostics.**
- Items 1–7 under "Consumers to update".
- Exit: unit tests (synthetic) for both triple forms in the inverse assembler,
  for self-clobber classification, and for the identification census.

**Phase 4: documentation.**

### Phase 5: adopt it in this repo (psyq-decomp)

All paths in this phase are in this repo.

1. In `toolchain.json`, set the base to
   `"assembler": { "kind": "gas", "inputRewrites": ["move-addu"] }`. Rename
   `unpadded-original-sections` to `sn-aspsx` and add
   `"assembler": { "kind": "maspsx" }`. All 38 members using it today are
   libsn, and no libsn member is verified yet, so this cannot regress.
   Assign the remaining libsn members only after Phase 3's packaging evidence
   (48 ASPSX-packaged objects vs 57 libsn members).
2. Re-verify every member. Expected: the 123 remain matched (already measured).
3. Integrate StopRCnt's minimal C, and then SetInitPadFlag's, through the
   normal gate as separate changes.
4. Check consumer item 1's expected effect on the StopRCnt reversal report.
5. Record the resolution in `notes/stoprcnt-investigation.md`, and the
   assembler-family evidence (PSY-Q conclusion included) in
   `configs/toolchain-identification.md`.

## Tests (harness)

- Loader: unknown kind, missing or extra `inputRewrites`, unknown rewrite id,
  profile override and inheritance, `gas` with nonzero `-G` rejected.
- Builder: default argv identical to legacy; `gas` argv and cwd; the rewrite
  preserves line count; the rewrite does not touch comments, labels, operands
  named `move`, or `.include` lines.
- Integration (synthetic fixtures): words per kind, as in Phase 0. Listing
  receipt present and the listed object identical to the production object.
- Parity (`tools/agent/toolchain-parity.test.ts`): extend "no tool spells out a
  maspsx flag" to "no tool invokes `configuredTool("maspsx")` or the
  assembler outside `tools/lib/assembler.ts`". Drop the `-G8` assumption only
  if a fixture requires it.
- Identity: switching kind changes `compilationIdentity` and invalidates
  receipts. The default leaves existing identities unchanged.
- Diagnostics: inverse-assembler triple folding in both forms, self-clobber
  classification, census classification.

## Acceptance criteria

1. (harness) With no `assembler` key, every assembler invocation and every
   existing receipt identity is unchanged, and `npm test` passes.
2. (harness) GAS-mode receipts include the rewritten input and the listing.
3. (harness) No assembler command is built outside `tools/lib/assembler.ts`.
4. (harness) Docs no longer state that direct GAS cannot be an acceptance path.
   They state the evidence requirement instead.
5. (this repo) With the Phase 5 config, all 123 previously verified members
   verify. StopRCnt's and SetInitPadFlag's minimal C are whole-member MATCHes.
   No assembler warnings.

## Risks

- **Other period-vs-modern GAS differences** (swap rules, nop placement at
  labels, `.lcomm` alignment, `-G` behavior). Mitigation: re-verification, the
  named-rewrite mechanism, and the nonzero-`-G` guard. A new rewrite needs a
  failing member and original-word evidence.
- **A lowered GAS `-O` would silently break swap sites.** The delay-slot
  fixture guards against it.
- **Receipt churn.** Expected, and bounded to members whose kind changes.
- **Uncommitted harness changes.** Implement on top of them.

## Open questions

1. *Resolved:* the GAS optimization level is the default (swapping on); see
   the evidence table. The 123 verified members could not discriminate it
   because none has a macro before an unfilled branch. SetInitPadFlag and the
   590-site census do.
2. Compiler version per member. This is out of scope here, but measured in
   this repo with the GAS backend (`compiler-sweep.*`). Across the 123 verified
   members plus the two new candidates:
   - 100 match under every available PSX build (2.7.2, 2.8.0, 2.8.1, egcs
     2.91.66, 2.95.1, 2.95.2), so they discriminate nothing.
   - 10 members plus both candidates match **only** 2.7.2.
   - 14 match 2.7.2 and 2.8.x but not egcs/2.95.
   - None matches another compiler without also matching 2.7.2.

   The discriminating members span libapi, libc2, libcd, libds, libetc, libgpu,
   libgs, libhmd, libmcx, libsnd and libspu. Still untested: near neighbours
   (2.6.x, 2.7.0/2.7.1, 2.7.2.x; recipes exist in this repo's
   `build/dependencies/old-gcc/<pin>/`, builds do not), and members outside the
   matched set.
3. Libsn classification: 57 members, 48 ASPSX-packaged objects, 38 with
   unpadded sections. Which members are SN-built, and is any of them C?
4. Should `tools.maspsx`/`flags.maspsx` become optional when no profile selects
   `maspsx`? That would be a schema change; not needed now.

## Evidence and reproduction (this repo)

Preserved under this repo's git-ignored `build/assembler-backend-evidence/`
(`../psyq-decomp/build/assembler-backend-evidence/` from the harness). It may
be cleaned; this document keeps the substance.

- `census_indexed_loads.py`, `census.json`: indexed-load temp census over
  `library-input/redux`.
- `assemblerSideBySide.mts`: compiles each member once with the production
  cc1, assembles it via MASPSX and via plain GAS (+`move-addu`, default and
  `-O1`), and scores both with the harness's `compareRelocatableObjects`. Run
  it from this repo's root:
  `node --import ../psx-decompilation-harness/node_modules/tsx/dist/loader.mjs build/assembler-backend-evidence/assemblerSideBySide.mts <outdir> [memberId[=candidate.c]]`.
- `side-by-side-123-members.{json,log}`, `side-by-side-counter-stoprcnt.json`,
  `side-by-side-setinitpadflag.json` (with `candidates/SetInitPadFlag.c`):
  results.
- `census_delay_swap.py`, `delay-swap-census.txt`: split-macro delay-slot
  census. `gas-swap-probe.s` shows GAS `-O2` vs `-O1` swapping on r3000.
- `compilerSweep.mts`, `compiler-sweep.{json,log}`: the same preprocessed TU
  under six PSX GCC builds, assembled with GAS and scored by the harness
  comparator.
- `gas-listing-counter.lst`: GAS `-alm` listing of the COUNTER TU.
- `real-aspsx/`: ASPSX 2.86 input (`COUNTER.S`, CRLF), LNK output and its
  converted ELF.

Running real ASPSX (the BTN procedure,
`../btn-decompilation/plans/aspsx-same-input-differential.md`):

1. Use a fresh 32-bit prefix: `WINEPREFIX=<dir> WINEARCH=win32 wineboot -i`.
   The default `~/.wine` fails with `could not load kernel32.dll`.
2. ASPSX mangles long paths, so map a short drive:
   `ln -s <workdir> $WINEPREFIX/dosdevices/x:`.
3. Assemble: `wine cmd /c "x: && ASPSX.EXE -o OUT.OBJ IN.S"`. Feed it CRLF
   input with short `.file` names.
4. Convert with this repo's `tools/psyq2elf-redux OUT.OBJ out.o`.
