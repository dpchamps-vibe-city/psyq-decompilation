# Deferred PSY-Q 4.7 object conversion work

These six originals remain part of the goal of reconstructing the complete SDK.
They are deliberately deferred, **not deleted, replaced with empty stubs, or
removed from the completeness denominator**. Machine-readable identities,
archive/member ordinals, SHA-256 hashes and observed failures are in
`configs/deferred-sdk-objects.json`.

Selected converter: pinned PCSX-Redux `psyq-obj-parser`, preserving ELF COMMON
with `-c`. Configuration and executable identity: `configs/conversion-policy.json`.

Excluded, not deferred: `Libsn.lib` (57 objects) was removed from the project
on 2026-10-17 because it is SN Systems' runtime, not Sony code, and its source
is available and reproduces it (54 of 57 confirmed). It is recorded under
`excludedArchives` in `configs/conversion-policy.json` with the evidence in
`notes/research/libsn-libgcc-provenance.md`; the original archive stays in
`library-input/psyq/LIB`. The completeness denominator for Sony's SDK is now
2167 selected members plus the six deferred originals below.

| Original | Current blocker | Required work |
|---|---|---|
| `2MBYTE.OBJ` | Section-end expression (opcode 22) | Translate section start/end/size expressions and define an explicit linker-boundary symbol contract. Validate startup addresses against original-tool evidence. |
| `8MBYTE.OBJ` | Section-end expression (opcode 22) | Same boundary-expression/linker-contract work; validate this distinct memory-size startup variant independently. |
| `NOHEAP.OBJ` | Section-end expression (opcode 22) | Same boundary-expression work, preserving the no-heap startup behavior. |
| `NONE3.OBJ` | Section-end expression (opcode 22) | Same boundary-expression work; do not substitute another startup variant. |
| `Libsn.lib[5] SNMAIN.OBJ` | Four initialized zero bytes in `.sbss` | Permit only proven all-zero BSS payloads while retaining exact extent, alignment and symbols. Then retry and audit section-boundary/startup/constructor expressions; clearing this first error is not proof of full support. |
| `Libsn.lib[9] CACHE.OBJ` | Unknown expression opcode 54 | Establish the operator's arithmetic from independent format/original-tool evidence. Preserve its `0xA0000000` operand and validate HI16/LO16 effects. Jype's emitted object drops the enclosing operation and is not an acceptable substitute. |

Regression requirements: retain original hashes and ordinals; compare sections,
BSS/COMMON, symbol bindings, encoded addends and ordered HI16/LO16 relocations.
For boundary expressions, validate the explicit link contract as well as the
relocatable object. Use synthetic/minimized public reproducers for upstream
reports rather than publishing proprietary original objects.

Do not let these items block work on supported members. Conversely, do not claim
full original-SDK completion until each deferred entry has an evidence-supported
resolution. Old converted inputs also require a separately reviewed migration to
restore 30 distinct LIBGTE variants and 50 missing LIBSN entries; selecting a new
converter alone does not repair that historical target-set coverage gap.
