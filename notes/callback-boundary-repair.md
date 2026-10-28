# Callback boundary / worker-promotion recovery

The escalation loop stopped after promoting a compound worker draft into
`src/libraries/libmcx/23-mcxcmd24/func_000000EC.c`. The manifest allowed one
function, but the draft defined both Tx and Rx callbacks. Call-graph regeneration
correctly rejected the two definitions. The compound attempt is preserved at
`build/recovery/mcx-callback-boundary/compound-attempt.c`; the live file is back
to its canonical original-assembly placeholder. No decompilation match is claimed.

## Original-code boundary repair

Private-entry discovery previously refused address-taken callbacks with switch
dispatches, even when a readonly relocation-backed table proved every case edge.
Discovery now uses the existing bounded dispatch resolver. Unknown/missing table
relocations, mutable tables, cross-boundary targets and delay-slot entry targets
remain blockers. There is no guessed target, changed original input or relaxed
byte oracle.

Regeneration found these additional independent entries:

| Member | Local listing symbol | ELF view `.text` offset |
| --- | --- | --- |
| `libmcrd_1` | `func_00000580` | `0x4F8` |
| `libmcx_14` | `func_00000128` | `0xA8` |
| `libmcx_23` | `func_00000110` | `0x98` |
| `libmcx_25` | `func_00000124` | `0xAC` |

The numeric symbol spellings are original listing coordinates, NOT runtime
addresses or section offsets. In `libmcx_23`, Tx starts at section offset `0x74`
and ends at `0x98`; Rx starts there. The caller separately publishes both
addresses. Each callback now owns its own manifest part and extraction.

Existing `MemCardGetDirentry` C and the disabled `MemCardOpen` attempt referenced
`T_00000580`, the former interior listing label. Their declaration and callback
use now reference the canonical `func_00000580` entry. No logic or ABI changed;
whole-original-object identity passed after this rename.

## Promotion protection

Harness worker promotion now checks C parsing, the owning part's definition
contract, canonical backlog ownership and the assignment's original partition
identity before source/header mutation. Declaration patches are limited to owned
headers. Failed explicit finalization and unexpected loop exceptions roll back
unsettled promotions, including newly created headers. Compare-and-swap rollback
refuses to overwrite concurrent edits and stops an unsafe loop for review.
Workers' build drafts remain available. A rejected compound draft is not evidence
of a C-matching impossibility.

## Validation and resumption

- Harness full suite: 1,747 tests, 1,624 passed, 123 skipped, zero failures.
- Project `npm run split` and `npm run graph`: passed.
- Project `npm run check-all`: all 2,164 configured library members byte-exact
  against their complete native original `.OBJ` hashes.
- Regenerated graph: 4,042 functions, all 2,164 member verifications fresh.
- Final focused regressions after the last controller changes: 33 passed.
- Source policy for the renamed `MemCardGetDirentry` reference: passed.
- Harness strict TypeScript checking remains nonzero on existing repository-wide
  errors; none of its diagnostics names the changed controller/discovery/addend
  modules. This is not a clean repository-wide typecheck claim.

Existing parked attempts and historical reports are preserved. Reports made with
the old compound boundaries or missing Rx import are historical, not current
measurements. In particular, revisit `libmcx_23::McxAllInfo` with fresh measurements
before reusing its old residual. This repair does not claim that caller matches.

Reload Pi before restarting the loop so the updated controller is loaded. No
loop was restarted, no policy exceptions/flags were changed, and no commit was
made by this repair.
