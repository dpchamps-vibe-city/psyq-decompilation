# libgs_87::GsSortObject5 — unfinished reconstruction

## Verification regression and repair

Commit `794aaa2bb9c644a932b4ad36ece1979ce690de10` was labelled as a park,
but replaced the canonical `INCLUDE_ASM` placeholder with an active, unverified
C draft. Full project verification failed for exactly this member (1/2164),
with `GsSortObject5.c:1: psyq.h: No such file or directory`.

The repair restores the original placeholder and preserves that entire draft,
unchanged, inside `#if 0`. This is backlog, not a matched C implementation.
No headers, compiler flags, original inputs, verification rules, or campaign
settings were changed to make the draft appear valid.

The preceding commit `1c4e3197d49839738518332ffa21166c4b3bd415`
already used this safe arrangement for `libgs_86::GsPresetObject`; its whole
member verified before the repair (596/596 words, original/rebuilt object match).

## Repair validation

- `npm run check-all`: all 2164 configured members byte-exact.
- `npm run build` and `npm run verify`: passed; verification again covered all
  2164 configured members.
- `npm run graph`: regenerated successfully.
- Repository-wide source policy: passed (592 functions scanned, undecompiled
  placeholders correctly skipped).
- `npm run library -- code-classes`: gate passed.
- Fresh progress: all 2164 members verified; both `GsPresetObject` and
  `GsSortObject5` remain incomplete, not counted as reconstructed C.

## Resuming work

The disabled draft is in `src/libraries/libgs/87-preset2/GsSortObject5.c`.
It is archival material only: it did not compile in the production TU, and
fixing its missing include alone does not establish correctness or a match.

The original commit identifies three dispatch loops, switch-case mapping,
stride arithmetic, function-table declarations, and shared post-call fragments
as unfinished areas. Those are hypotheses to recheck against the original
object, not verified properties of the draft.

Keep experiments under `build/` and use the real owning TU and headers. Do not
replace the live placeholder until the complete member passes the byte oracle.
To verify this library project, use `npm run verify` and `npm run check-all`;
the executable-only `psx_verify_build` command is not applicable here.
