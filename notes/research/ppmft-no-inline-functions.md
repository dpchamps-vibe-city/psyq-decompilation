# PPMFT.OBJ: out-of-line helper fingerprint

Scope: LIBGTE.LIB[224], libgte_224. Native original member SHA-256:
`c63999e6dadb33f695e1687514a828a7a579dbc983e72578fd7b817ac77ff342`.

## Independent target evidence

The original `func_000013FC.ASM` has a direct `jal` at member coordinate
0x1688 to the earlier 18-word helper at 0x6BC, with argument 9 in its delay
slot. The helper computes the maximum absolute value of an int array. The
original member does not export this helper. The original retains calls to
the other private helpers too; no contrary cross-function-inlining witness
was found in this TU. Coordinates are section/member offsets, not RAM.

## Measured columns

The static max-abs candidate and existing C caller compile under baseline
-O3, but the compiler inlines the loop into the caller and drops its separate
entry. `pers_map` moves from 0x684 to 0x63c. With the other prepared member
fragments present, the native rebuilt SHA-256 is
`95890428f385cd13d9a942b746dfb0244cdc6d18e05c8d8c4eca54050772b6dd`,
and the oracle reports 430/1792 words, 1784 candidate words.

A build-only compile of the same complete preprocessed TU with only
`-fno-inline-functions` appended, followed by the configured assembler,
DMPSX and LNK stages, produces the exact original native member SHA-256
above. This settles the complete object, including relocations and padding,
not merely the helper's 18 words. The standard flag_probe cannot build its
matrix when the baseline private entry is absent, so this is an explicit
baseline/no-inline attribution experiment rather than a claimed successful
flag_probe report.

Artifacts:
`build/subagents/125fcbff-630b-4e9a-ada2-c454acad12c4/3dc416f0-ab92-4bc3-90c0-e5cc7ee15986/`
contains candidate.c, evidence.md, tu_noinline.s, assemble_noinline.mjs and
`tu_noinline.final.o`. Supervisor independently measured its SHA-256.
The assembler script invokes the installed production assembler adapter;
it does not patch words or edit the target.

## Production reconstruction

`CC1FLAGS_libgte_224 := -fno-inline-functions` records the witnessed per-TU
behavior, with its matching `flag-override` policy entry. This follows the
same evidence class as libcd_20, libetc_3 and libgpu_4. It does not establish
a unique historical command line or prove every possible C spelling
impossible. Final acceptance still requires the ordinary production
function/member, accepted-member, scope and clean-source gates.
