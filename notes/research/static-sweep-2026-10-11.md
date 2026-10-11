# Automatic exact-match sweep — 2026-10-11

The sweep processed all 2,671 identifiable functions in the configured converted
library inputs, without solver-model or documentation-model calls.

| Outcome | Functions |
| --- | ---: |
| Newly integrated and finalized | 115 |
| Already complete | 10 |
| Compiling but nonmatching | 212 |
| Preparation blocked | 2,334 |

All 115 exact drafts passed the normal finalization route. Their sources contain
72 approved BIOS tail-transfer bindings, 3 approved syscall helpers, and 40 C
bodies, including getters, forwarding wrappers and original return-only no-ops.
A BIOS binding reconstructs the library-side entry operation, not ROM code.

## Evidence and limits

- Run summary and per-function packet paths: `build/static-sweep/report.json`
  (`status: complete`, `accepted: 115`, `newlyDecompiled: 115`).
- Each accepted packet records `finalization.status: passed`; its sibling
  `sweep-gate.json` retains the owning-member/accepted-set verification,
  source-policy/scope result and context publication.
- Sources were substituted into the same ordered production TU used by normal
  builds. Acceptance was not an isolated-function match followed by stitching.
- Nonmatches and blocked drafts were not promoted. Original neighboring function
  and data backlog remains in place and is not counted as decompiled C.
- This result does not establish that every configured member or data-only object
  has passed full-library verification. It establishes the accepted functions'
  owning-TU gates under the measured source, target, header and toolchain inputs.
- Eight earlier Qwen BIOS-binding replacements were already complete when the
  sweep began but still uncommitted. They are separate from the 115 new matches.
  The other two already-complete functions were InitHeap and
  SpuGetTransferStartAddr.

## Grouping wins

`notes/file-groupings.md` now records eight recovered multi-function groups:
PAD, RAND (LIBC2), DSREADY, VMODE, SCANUNIT, VM_VIB, SSCLOSE and S_IT. Membership
comes from the original archive-member mapping and ordered TU manifests, not
function-name similarity. Seven remain partially reconstructed; all four
VM_VIB functions are recovered no-ops, as independently shown by their original
return-only instructions.

LIBC2's RAND member owns a real stateful generator and its `srand` neighbor.
LIBC's same-named `rand` and `srand` are separate BIOS-binding members. This is
an important distinction for selecting future donors and declaration context.
Original C filenames and unread parameter contracts are not recovered merely
by a byte match.
