# Per-file cc1 overrides. Evidence comment directly above each entry.
# CC1FLAGS_<source-basename-without-.c> := <extra cc1 flags>

# No overrides. The two allocator overrides that compensated for GCC 2.7.2's
# address folding (-fforce-addr -fno-rerun-cse-after-loop on REALLOC3.OBJ and
# -fno-rerun-cse-after-loop on FREE3.OBJ) were retired on 2026-10-17 when the
# project moved to the identified 1997 trunk compiler, which has that
# behavior natively; see notes/research/compiler-identification-1997-trunk.md.

# TOC.OBJ (libcd_1) was compiled with the FP register class allocatable, i.e.
# without the project-default -msoft-float. Evidence: the target hoists the
# 0x66666667 division constant out of the track loop (word 0x18C..0x190, used by
# the single mult at 0x198). loop.c moves it only when
# threshold*savings*lifetime >= insn_count; with -msoft-float n_non_fixed_regs=28
# so threshold=29 < 30 (measured: "move-insn savings 1 not desirable") and the
# constant stays inside the loop. -mhard-float makes the 32 FP registers
# non-fixed (n_non_fixed_regs=60, threshold=61) and the same source hoists it
# ("moved to ..."), reproducing the target's preheader order and its 8-word
# register save area. No FP value appears in the member, so the only observed
# effect is this loop heuristic.
CC1FLAGS_libcd_1 := -mhard-float

# ISO9660.OBJ (libcd_4): the whole member reads plain char as SIGNED. Every
# plain-char load in CdSearchFile is `lb` (the char* `name` parameter at 0xD8,
# `buf[0]` at 0x1B8, `file_[i].name[0]` at 0x268, the path loop's `*p` at
# 0x110/0x138), while the project default -funsigned-char emits `lbu` there.
# The one `lbu` (0x114/0x13C) is the zero-only test, which GCC may load
# unsigned regardless. This is a whole-TU source-language property.
CC1FLAGS_libcd_4 := -fsigned-char

# libcd_20 (BIOS_1.OBJ): the whole member shows no cross-function inlining.
# Evidence: CD_sync (0x564), CD_ready (0x7e4) and CD_datasync (0x1330) all issue
# a direct `jal CD_flush` to the 21-instruction CD_flush defined earlier in the
# same member; CD_cw (0xaac) likewise calls CD_sync. Under the baseline flags the
# compiler treats CD_flush as inlineable and expands it inside CD_datasync
# (measured: no jal, inlined flush body, extra $21 save).
CC1FLAGS_libcd_20 := -fno-inline-functions

# DSTOC.OBJ (libds_5): the target hoists the 0x66666667 division constant out
# of its track loop (measured: lui/ori into $20 before the loop, single mult
# inside). loop.c moves it only when threshold*savings*lifetime >= insn_count;
# with the project-default -msoft-float n_non_fixed_regs=28 so threshold=29 < 30
# and the constant stays inside the loop. -mhard-float makes the 32 FP registers
# non-fixed (n_non_fixed_regs=60, threshold=61) and the same source hoists it,
# reproducing the target's preheader and its $20 save slot. No FP value appears
# in the member, so the only observed effect is this loop heuristic. Same
# mechanism as the recorded TOC.OBJ (libcd_1) witness.
CC1FLAGS_libds_5 := -mhard-float

# DSFILE.OBJ (libds_9) needs both overrides; they are independent, whole-TU
# properties of the original build.
#
# -fsigned-char: the whole member reads plain char as SIGNED. Every plain-char
# load in DsSearchFile is `lb` (the `name` parameter at 0xE0, the parse loop's
# `*p` at 0x118/0x13C/0x14C, `path[0]` at 0x1C0, and the file table's
# `B_00000BE0[i].name[0]` at 0x268), while the project default -funsigned-char
# emits `lbu` there. The only `lbu`s (0x11C/0x140) are the zero-only test and
# the byte copy, which GCC loads unsigned regardless. Same whole-TU property as
# ISO9660.OBJ (libcd_4).
#
# -mhard-float: the target hoists the two loop invariants of its path parser out
# of the outer loop: `'\\'` into $21 and `-1` into $20 in the preheader, and it
# saves $16-$22 (frame 0x50). Under the project-default -msoft-float those
# constants are rematerialized inside the loop and the frame is 0x48 (6 saved
# registers); -mhard-float raises n_non_fixed_regs and loop.c moves them,
# reproducing the preheader and the 7-register save area. No FP value appears in
# the member, so the only observed effect is this loop heuristic. Same mechanism
# as the recorded DSTOC.OBJ (libds_5) and TOC.OBJ (libcd_1) witnesses.
#
# -fno-builtin: the original member calls the ordinary `memcpy` symbol
# from both func_00000378 (0x490) and func_000006E0 (0x472). Under the baseline
# flags the builtin expansion of a `<memory.h>`-declared call emits `jal bcopy`
# instead (measured: func_00000378 compiled to 175 words with `jal bcopy` and a
# 1-word-smaller frame). The reference memory.h deliberately declares
# `void *memcpy()` without a prototype, so the target call can only come from a
# compiler run in which the builtin was disabled for this TU. This 1997 cc1 has
# only the all-builtins -fno-builtin switch, no -fno-builtin-<name>.
CC1FLAGS_libds_9 := -fsigned-char -mhard-float -fno-builtin


# libetc_3 (INTR.OBJ): the member contains an unreferenced static function at
# 0x69C (func_0000071C) that the original object still emits as a standalone
# leaf. Under the project-default -O3, -finline-functions makes cc1 treat every
# small static definition as inlineable, defer it, and then discard it because
# nothing references it: the rebuilt .text ends at 0x6A0 and defines no such
# function (measured). -fno-inline-functions makes cc1 compile it immediately,
# reproducing the original unreferenced 9-word body without any caller or
# frame; a per-file flag is required because this is a whole-TU build property.
CC1FLAGS_libetc_3 := -fno-inline-functions

# libgpu_0 (FNT.OBJ): no override. A -fno-strength-reduce override was tried
# (and retired here) to explain the member's raw-biv sprite addressing, but it
# was a wrong reading of the same fingerprint: under the project's baseline -O3
# FntFlush with the walking-pointer sprite source is byte-exact (199/199 words,
# zero population/schedule/allocation residual), and the retired override made
# it 198/199. The original bytes' `addiu $18,$18,0x10` plus base-relative
# offsets 0x4..0xD is the ordinary strength-reduced giv of a `SPRT_8 *sp`
# walking pointer, and FntOpen/FntLoad/SetDumpFnt match under the same baseline.


# libgpu_2 (KPRINTF.OBJ) needs -mhard-float. Evidence: loop.c decides a
# move-insn with `threshold * savings * lifetime >= insn_count`, and the target
# hoists the 0x824F decimal-digit constant that this source materializes inside
# the loop body (measured: `li $8,33359` in the loop, frame/regs 7/0, 368-byte
# .text difference chain). The same source compiled with -mhard-float raises
# n_non_fixed_regs from 28 to 60, so threshold goes from 29 to 61,
# 61*1*23 >= insn_count makes the movable desirable, and the rebuilt function is
# byte-exact (282/282 words, zero population/schedule/allocation residual,
# frame 568, regs 8/0=$16-$22, preheader `li $22,0xcccccccd; li $21,0x824f`).
# No FP value appears in the member (0 COP2 words), so the only observed effect
# is this loop heuristic. Same mechanism as the recorded TOC.OBJ (libcd_1),
# DSTOC.OBJ (libds_5) and DSFILE.OBJ (libds_9) witnesses.
CC1FLAGS_libgpu_2 := -mhard-float

# OTAG.OBJ (libgpu_3) needs -mhard-float for the same loop.c threshold mechanism.
# Evidence: DumpOTag's loop hoists the loop-invariant address of the primitive
# type-name table D_STR_000004F0 out of the walk (preheader `lui $20,%hi` /
# `addiu $20,$20,%lo` = la, in-loop `addu $v0,$v0,$20; lw $a1,0($v0)`) and its
# frame saves six registers ($16-$20 + $ra, 0x28). Under the project-default
# -msoft-float n_non_fixed_regs=28 so threshold=29 and the address stays inside
# the loop (measured: `lw $a1,D_STR_000004F0($v0)` macro in-loop, frame 0x28 with
# five saves, no $20). -mhard-float raises n_non_fixed_regs to 60, threshold to
# 61, the movable becomes desirable and the preheader/$20 save area reproduce.
# No FP value appears in the member (0 COP2 words); the only observed effect is
# this loop heuristic. Same mechanism as libgpu_2 (KPRINTF.OBJ), libcd_1
# (TOC.OBJ), libds_5 (DSTOC.OBJ) and libds_9 (DSFILE.OBJ).
CC1FLAGS_libgpu_3 := -mhard-float
