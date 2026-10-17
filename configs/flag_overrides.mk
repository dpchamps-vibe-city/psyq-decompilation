# Per-file cc1 overrides. Evidence comment directly above each entry.
# CC1FLAGS_<source-basename-without-.c> := <extra cc1 flags>

# FREE3.OBJ: original _r_bp/_r_p base+offset reuse; native cse2 folds these under baseline. Natural C + this delta matches the whole member; see notes/research/free3-source-scoped-flag-probe.md.
CC1FLAGS_lib_5a59d0efe7ad3e69_0 := -fno-rerun-cse-after-loop
