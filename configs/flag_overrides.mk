# Per-file cc1 overrides. Evidence comment directly above each entry.
# CC1FLAGS_<source-basename-without-.c> := <extra cc1 flags>

# FREE3.OBJ: original _r_bp/_r_p base+offset reuse; native cse2 folds these under baseline. Natural C + this delta matches the whole member; see notes/research/free3-source-scoped-flag-probe.md.
CC1FLAGS_lib_5a59d0efe7ad3e69_0 := -fno-rerun-cse-after-loop

# REALLOC3.OBJ: original block-header base+offset reuse; native cse folds the
# bp+4 load/store back to ptr-4 under baseline. See notes/research/.
CC1FLAGS_lib_dacb6c202432cdbd_0 := -fno-cse-follow-jumps -fno-cse-skip-blocks
