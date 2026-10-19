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
