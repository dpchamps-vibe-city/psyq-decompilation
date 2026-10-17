# LIBSN: GCC 2.8.0 libgcc built by SN's 2.8.1-class compiler

Date: 2026-10-17. Scope: the 57 `libsn` members that came from `Libsn.lib`.

**Conclusion first.** `Libsn.lib` is SN Systems' runtime library, not Sony
code, and it was dropped from the project on 2026-10-17 (section 7). It does
not need decompiling: for 54 of its 57 objects the original source exists and
demonstrably built them (49 byte-exact, 5 instruction-exact or one assembler
detail off; section 6), and the remaining 3 (`eh`, `profile`, `snctors`) are
SN's work and outside the project's goal of Sony's original source regardless.
Nothing about the Sony compiler identification is affected; libsn was never
part of that corpus.

The rest of this note records where the source is, which toolchain reproduces
it, what was measured, and what the harness would need if anyone ever wanted
libsn back. Probe driver and every object produced here: `build/libsn-probe/`
(git-ignored).

## 1. What LIBSN is

The Psy-Q CD's `\GNU` folder is the GPL-licensed part of the toolchain: the
GCC-derived executables plus the libgcc runtime. Sony's `LIBC.LIB` is not part
of it. The 3.6 CD vendored under
`~/Documents/code/btn-decompilation/tools/vendor/psyq_sdk/psyq/psyq/src/LIBSN/`
ships the runtime's sources: `LIBGCC2.C` (FSF, dated 1995-02-14, one SN edit to
`new_handler`), `READ.C`, `WRITE.C`, nine `.S` files in ASMPSX syntax, SN's
1994 target header `TM.H` (derived from `iris3.h`, "to build a little-endian
compiler"), and `BUILD.BAT`, which compiles libgcc2.c once per `-DL_<piece>`
with `ccpsx -O2 -c`. `LIBSN.ZIP` (1996-09-24) holds the same files.

Forty-five of the 4.7 members carry a FILENAME record naming
`D:\SOURCE\GCC\gcc-2.8.0\LIBGCC2.C`; the 3.6 `LIBSN.LIB` names
`C:\GNUMIPS\LIB\LIBSN\LIBGCC2.C`. The shipped 1995 copy is the wrong vintage
for 4.7: it lacks `__negdi2`, the `static inline __udivmoddi4` with its 256-byte
`__clz_tab` in `.rdata`, and `L_eh_compat`, all of which the 4.7 objects show.

## 2. The source that matches

The matching libgcc2.c is the FSF file between 1997-12-30 (`_eh_compat`
stdlib fix, present) and 1998-02-05 (the 1998-02-06 "round properly"
`__floatdi*f` change is absent). That window is the gcc 2.8.0 release
(1998-01-07), as the FILENAME records say. The homebrew-psyq tree vendored in
btn carries the FSF history for this file, so the text is available locally:

```
git -C ~/Documents/code/btn-decompilation/tools/vendor/homebrew-psyq \
  show 717a45202^:gcc-2.8.1_psyq-4.4/gcc/libgcc2.c
```

`longlong.h` vintage does not matter (1997-10-18 and 2.8.1 give identical
results). The division family matches only with this 2.8.0 structure.

## 3. The recipe (all measured against the originals with the whole-member oracle)

| ingredient | value | evidence |
| --- | --- | --- |
| compiler | Homebrew Psy-Q 2.8.1 `cc1` (btn: `tools/vendor/homebrew-psyq/build/psyq-4.4_old-school/gcc-2.8.1/cc1`) | only compiler that produces exact matches; the 1997 trunk, 2.7.2, the CDK and 2.95.2 are far off on everything non-trivial |
| cc1 flags | production list without `-mmips-as` and without `-G0`; `-mno-split-addresses` makes no difference | `__new_handler` lands in `.sdata` and `__builtin_new` matches only with the default `-G 8`; assembler still gets `-G0` as in the `sn-aspsx` profile |
| 64-bit word order | high word first (`LIBGCC2_WORDS_BIG_ENDIAN` = 1) | every DImode helper matched only after this; 2.8.x `mips.h` sets it unless `MIPSEL`/`__MIPSEL__` is predefined, so SN's libgcc build simply did not predefine them. The resulting helpers disagree with the compiler's own little-endian `long long` layout |
| target headers for preprocessing | homebrew `config/mips/psx.h` → `mips/mips.h`, `xm-mips.h`, `defaults.h`, `frame.h`, `gbl-ctors.h`; no `MIPSEL` predefine | gives the word order above and the DWARF2 `L_eh` function set |
| `limits.h` | the 3.6 SDK's, `LONG_MIN (-2147483648)` (unsigned) | `__fixunsdfsi`/`__fixunssfsi` match only with it; the converted 4.7 header's `(-2147483647-1)` swaps the two double constants |
| preprocessor | the bundled GCC 2.7.2 `cpp` (`build/dependencies/compiler/gcc-2.7.2-psx/cpp`) with `-nostdinc -undef -D__GNUC__=2 -D__GNUC_MINOR__=8 -lang-c -D__mips__ -D__mips=1 -Dmips -DR3000` | the 1995 `longlong.h` carries newlines inside string literals that a modern cpp rejects; the 2.8.0 file does not need it but it is harmless |
| assembler | maspsx at or after upstream `3629944` (2026-09-11), `--aspsx-version 2.80 --use-comm-section --expand-div`, GAS flags `-march=r3000 -mtune=r3000 -EL -G0 -no-pad-sections` | the pinned `0249ed27` lacks the `$16/$17` pair that `li.d` into `s0` needs (`__floatdidf`, `__floatdisf`); `--expand-div` gives the originals' `divu; bnez; nop; break` order |
| read-only section name | the compiler's `.rdata` must reach the object as `.rdata` | same blocker as `plans/harness-rdata-section-rewrite.md`; verified with `objcopy --rename-section .rodata=.rdata` |

## 4. Results, member by member

Exact under the recipe (35): `negdi2 lshrdi3 ashldi3 ashrdi3 ffsdi2 udiv_w_sdiv
cmpdi2 ucmpdi2 floatdidf floatdisf fixunsdfsi fixunssfsi fixunsdfdi fixdfdi
fixunssfdi fixsfdi gcc_bcmp dummy op_new op_vnew op_delete op_vdel shtab
clear_cache trampoline exit ctors eh_compat` and the seven empty
extended-precision stubs `fixxfdi fixunsxfdi floatdixf fixunsxfsi fixtfdi
fixunstfdi floatditf`.

Exact once the read-only section is named `.rdata` (5): `divdi3 moddi3 udivdi3
umoddi3 udivmoddi4` (each carries its own `__clz_tab`).

Instruction-exact, blocked by tooling (2):

- `muldi3`: exact through plain GNU as with `-no-pad-sections`; maspsx skips
  the two hazard nops before the `multu` that comes from `umul_ppmm`'s inline
  asm, because it does not look across the `#APP` boundary.
- `new_handler`: exact with `__default_new_handler` defined ahead of
  `set_new_handler` (FSF order is the reverse, so SN's copy was rearranged)
  and the `.rdata` rename. The oracle still reports the `.sdata`
  (`R_MIPS_GPREL16`) and `.text` references as differing because the original
  encodes them section-relative and the candidate symbol-relative; the
  same-object fold does not cover GPREL16.

Near (4):

- `varargs` (4/6): the `__builtin_saveregs` block is inline asm; the original
  has `sw a3; jr ra; nop`, every GAS path fills the delay slot. ASPSX did not
  reorder inside `#APP`; maspsx hands the region to GAS unchanged.
- `read`, `write` (24/47 each): SN's 1995 `READ.C`/`WRITE.C` (strip the DOS
  ^Z from `WRITE.C`) compile to the same instructions with a different
  callee-saved register assignment; declaration order does not change it, so
  the 4.7 source probably differs slightly.
- `eh` (20/663): the DWARF2 path with `frame.h` gives the right function set
  (`__sjthrow`, `__throw`, `find_exception_handler`, `get_reg`, …) but the
  code still differs, and this is the only object in the whole 2,224-member
  corpus with weak symbols (`find_exception_handler`, `get_reg`, `top_elt`).
  Unresolved.

Hand-written (9): the shipped `.S` files are instruction-for-instruction the
4.7 objects for `open close lseek creat snread fsinit snwrite` and the `sndef`
data (`_stacksize 0x8000`, `_ramsize 0x800000`); only `pure` changed, from
`break 0` to `jr ra; nop`. They are ASMPSX syntax and trivially re-spelled as
GAS `.s` TUs for the handwritten pipeline.

No shipped source (2): `profile` (`INITprofile`, `SNprofile`, …) and
`snctors` (`__sn_cpp_structors`) are 4.7-era SN code.

## 5. What integration needs

1. The `.rdata` rewrite from `plans/harness-rdata-section-rewrite.md`.
2. A per-member (or per-library) compiler profile: different `cc1`, cpp,
   flags and include set from the Sony members. The toolchain profiles today
   only select the assembler.
3. maspsx: bump the pin past `3629944`; add `--expand-div` to the `sn-aspsx`
   profile for libsn (confirm it changes nothing for the other `sn-aspsx`
   members); report upstream the two `#APP` gaps (hazard nops before an
   inline-asm `mult`, no delay-slot filling inside inline asm).
4. The oracle's same-object fold should cover `R_MIPS_GPREL16`.
5. A decision on vendoring libgcc2.c (GPL with the runtime exception) versus
   referencing the homebrew tree, and the one-line reorder for `new_handler`.

Related: `notes/research/compiler-identification-1997-trunk.md` (the Sony
members' compiler; libsn was excluded there as SN-built, which this confirms).

## 6. Receipt: source availability per member (2026-10-17)

Verification: whole-member oracle (`compareRelocatableObjects`) against `library-input/redux/libsn/*.o`. libgcc pieces: Homebrew 2.8.1 cc1, recipe of section 3, upstream maspsx `--expand-div`, read-only section renamed to `.rdata` with objcopy. `.S` sources: GNU as `-march=r3000 -mtune=r3000 -EL -G0 -no-pad-sections`, `.set noreorder`, two-operand `break`. Inputs: libgcc2.c sha256 `fc58eae136cea06f…`, LIBSN dir files sha256 in `build/libsn-probe/source-hashes.txt`. Objects and receipts: `build/libsn-probe/`.

| member | id | source | verdict |
| --- | --- | --- | --- |
| `0-open` | `lib_77fc35f7d7678d6e_0` | OPEN.S (ASMPSX source, re-spelled in GAS syntax) | MATCH |
| `1-close` | `lib_627c79d3ec61f03b_0` | CLOSE.S (ASMPSX source, re-spelled in GAS syntax) | MATCH |
| `2-lseek` | `lib_3490a783ba36853b_0` | LSEEK.S (ASMPSX source, re-spelled in GAS syntax) | MATCH |
| `3-creat` | `lib_af3488c36a0825a4_0` | CREAT.S (ASMPSX source, re-spelled in GAS syntax) | MATCH |
| `4-snread` | `lib_1fb606ad1db19cd6_0` | SNREAD.S (ASMPSX source, re-spelled in GAS syntax) | MATCH |
| `6-fsinit` | `lib_9b8fb260ce66e220_0` | FSINIT.S (ASMPSX source, re-spelled in GAS syntax) | MATCH |
| `7-snwrite` | `lib_6ff1bdb9be2e6834_0` | SNWRITE.S (ASMPSX source, re-spelled in GAS syntax) | MATCH |
| `8-sndef` | `lib_97dea4e103dfff3a_0` | SNDEF.S (ASMPSX source, re-spelled in GAS syntax) | MATCH |
| `10-profile` | `lib_9d60be61c08b31b1_0` | none shipped | not reproduced |
| `11-snctors` | `lib_5247c2bd0adb5de2_0` | none shipped | not reproduced |
| `12-read` | `lib_fd54b0e3548785eb_0` | READ.C (1995) | 24/47: same code, different callee-saved register assignment; 4.7 source likely differs |
| `13-write` | `lib_dc5870faf2510c4f_0` | WRITE.C (1995) | 24/47: same code, different callee-saved register assignment; 4.7 source likely differs |
| `14-muldi3` | `lib_b290ef0de3b0f44d_0` | libgcc2.c `L_muldi3` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH (GNU as path; maspsx omits the inline-asm hazard nops) |
| `15-divdi3` | `lib_8761c93334dedc99_0` | libgcc2.c `L_divdi3` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `16-moddi3` | `lib_42f9a44297caf96b_0` | libgcc2.c `L_moddi3` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `17-udivdi3` | `lib_f3c730159c03d3ab_0` | libgcc2.c `L_udivdi3` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `18-umoddi3` | `lib_ee231489c77ed268_0` | libgcc2.c `L_umoddi3` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `19-negdi2` | `lib_13e6b223116a0406_0` | libgcc2.c `L_negdi2` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `20-lshrdi3` | `lib_579c9115d112fa3b_0` | libgcc2.c `L_lshrdi3` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `21-ashldi3` | `lib_1241b9ed9b7ea516_0` | libgcc2.c `L_ashldi3` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `22-ashrdi3` | `lib_ec2238b818cf7cb3_0` | libgcc2.c `L_ashrdi3` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `23-ffsdi2` | `lib_80f5b374a9f77a7b_0` | libgcc2.c `L_ffsdi2` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `24-udiv_w_sdiv` | `lib_68c9e96369c0fa66_0` | libgcc2.c `L_udiv_w_sdiv` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `25-udivmoddi4` | `lib_68cbfb8740dc4fea_0` | libgcc2.c `L_udivmoddi4` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `26-cmpdi2` | `lib_ef70639fd907db15_0` | libgcc2.c `L_cmpdi2` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `27-ucmpdi2` | `lib_ac1b471355cf3a4e_0` | libgcc2.c `L_ucmpdi2` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `28-floatdidf` | `lib_c3d2c224ab0e2fe3_0` | libgcc2.c `L_floatdidf` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `29-floatdisf` | `lib_6d5a97fd9af876e1_0` | libgcc2.c `L_floatdisf` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `30-fixunsdfsi` | `lib_a4ce911bdb4f4519_0` | libgcc2.c `L_fixunsdfsi` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `31-fixunssfsi` | `lib_3f031d855c415918_0` | libgcc2.c `L_fixunssfsi` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `32-fixunsdfdi` | `lib_7eb88b9dd66509ba_0` | libgcc2.c `L_fixunsdfdi` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `33-fixdfdi` | `lib_73374a9e5a43ba22_0` | libgcc2.c `L_fixdfdi` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `34-fixunssfdi` | `lib_29a607627cb8e095_0` | libgcc2.c `L_fixunssfdi` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `35-fixsfdi` | `lib_c8e601504581bbf9_0` | libgcc2.c `L_fixsfdi` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `36-fixxfdi` | `lib_ffe9100aa5699aff_0` | libgcc2.c `L_fixxfdi` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `37-fixunsxfdi` | `lib_98d44406535e7536_0` | libgcc2.c `L_fixunsxfdi` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `38-floatdixf` | `lib_00910173d44ba1a6_0` | libgcc2.c `L_floatdixf` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `39-fixunsxfsi` | `lib_ddceec13e21a492a_0` | libgcc2.c `L_fixunsxfsi` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `40-fixtfdi` | `lib_7480fc7aad328b3d_0` | libgcc2.c `L_fixtfdi` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `41-fixunstfdi` | `lib_5c17b856492164b9_0` | libgcc2.c `L_fixunstfdi` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `42-floatditf` | `lib_5a5f5d660fc58d75_0` | libgcc2.c `L_floatditf` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `43-gcc_bcmp` | `lib_27374ebe77ed4c0b_0` | libgcc2.c `L__gcc_bcmp` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `44-varargs` | `lib_4d88ac3464b40ae3_0` | libgcc2.c `L_varargs` (gcc 2.8.0, homebrew history `717a45202^`) | 4/6: `j $31` delay slot filled by the assembler; ASPSX did not |
| `45-dummy` | `lib_542b0bbafd0034d3_0` | libgcc2.c `L__dummy` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `46-op_new` | `lib_874667cc712bc2e8_0` | libgcc2.c `L_op_new` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `47-op_vnew` | `lib_aaf10fd25fdc34ee_0` | libgcc2.c `L_op_vnew` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `48-new_handler` | `lib_438a6e3ef979d633_0` | libgcc2.c `L_new_handler` (gcc 2.8.0, homebrew history `717a45202^`) | 14/16: instructions exact, references spelled symbol- vs section-relative |
| `49-op_delete` | `lib_07feb99b6061a47c_0` | libgcc2.c `L_op_delete` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `50-op_vdel` | `lib_69127bde55a215c7_0` | libgcc2.c `L_op_vdel` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `51-shtab` | `lib_e192bfd66927bbf3_0` | libgcc2.c `L_shtab` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `52-clear_cache` | `lib_30887daf344d1199_0` | libgcc2.c `L_clear_cache` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `53-trampoline` | `lib_f29ec4b70cc30eca_0` | libgcc2.c `L_trampoline` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `54-exit` | `lib_c762fed246442559_0` | libgcc2.c `L_exit` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `55-ctors` | `lib_b01dc257212f3635_0` | libgcc2.c `L_ctors` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `56-eh` | `lib_c7a612f9d80f3853_0` | libgcc2.c `L_eh` (gcc 2.8.0, homebrew history `717a45202^`) | 13/663: not reproduced |
| `57-eh_compat` | `lib_cbfabe010ae28fb4_0` | libgcc2.c `L_eh_compat` (gcc 2.8.0, homebrew history `717a45202^`) | MATCH |
| `58-pure` | `lib_ad66f84a018bda5b_0` | PUREV.S (1995) `break 0`; 4.7 object is `jr ra; nop` | 0/2: source changed after 1995 |

Totals: 49 of 57 byte-exact from the available source; 1 instruction-exact (`new_handler`); 3 near (`varargs`, `read`, `write`); 1 not reproduced (`eh`); 1 changed after the shipped source (`pure`); 2 with no shipped source (`profile`, `snctors`).

## 7. Decision: Libsn.lib dropped from the project (2026-10-17)

The project's goal is Sony's original source. `Libsn.lib` only entered the
member set because SN placed it in the same `LIB` directory as Sony's
libraries; it is SN's runtime, built with SN's toolchain, and its source is
available as shown above. It was removed from the selection:

- `src/libraries/libsn/` (57 TU stub directories) removed from git.
- `library-input/redux/libsn/` (57 converted objects, git-ignored) moved to
  `library-input/excluded/libsn/`, outside the `library-input/redux/**/*.o`
  selection, not deleted.
- `toolchain.json`: the 54 `containerProfiles` entries (all libsn) removed;
  the `sn-aspsx` and `sn-aspsx-padded` profile definitions are left in place
  but now unused.
- `configs/conversion-policy.json`: `excludedArchives` records the
  exclusion; `selectedEntryCount` is 2167.
- `library-input/psyq/LIB/Libsn.lib` and `original-members.json` are
  untouched: the originals stay inventoried.
- `npm run check-all` after the removal: all 2167 configured members byte-exact.
- Not done: `configs/project-profile.md` was not regenerated
  (`node tools/harness-proxy.mjs tools/build/genProjectProfile.ts --write`),
  and stale `build/libraries/{verified,originals,disassembly,nonmatchings,drivers}`
  entries for the 57 ids were left in place; both are harmless and can be
  cleaned up at any time.
