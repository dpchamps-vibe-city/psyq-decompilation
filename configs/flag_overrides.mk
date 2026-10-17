# Per-file cc1 overrides. Evidence comment directly above each entry.
# CC1FLAGS_<source-basename-without-.c> := <extra cc1 flags>

# No overrides. The two allocator overrides that compensated for GCC 2.7.2's
# address folding (-fforce-addr -fno-rerun-cse-after-loop on REALLOC3.OBJ and
# -fno-rerun-cse-after-loop on FREE3.OBJ) were retired on 2026-10-17 when the
# project moved to the identified 1997 trunk compiler, which has that
# behavior natively; see notes/research/compiler-identification-1997-trunk.md.
