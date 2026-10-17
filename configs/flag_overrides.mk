# Per-file cc1 overrides. Evidence comment directly above each entry.
# CC1FLAGS_<source-basename-without-.c> := <extra cc1 flags>

# FREE3.OBJ: original _r_bp/_r_p base+offset reuse; native cse2 folds these under baseline. Natural C + this delta matches the whole member; see notes/research/free3-source-scoped-flag-probe.md.
CC1FLAGS_lib_5a59d0efe7ad3e69_0 := -fno-rerun-cse-after-loop

# REALLOC3.OBJ: _unfree3 (func_0000014C) restores the two snapshot blocks from
# _r_p/_r_bp. The original materializes one lui/addiu base per global and reads
# the fields at offsets 0/8/4 through it (one HI16/LO16 pair per symbol in the
# original relocations). Natural C with a local BlockReg* expands to exactly that
# register+offset RTL, but cse2 refolds the nonzero offsets to absolute symbol
# operands; -fno-rerun-cse-after-loop keeps the shared base and -fforce-addr
# materializes it for the offset-0 access. Together they reproduce the whole
# member. See notes/research/.
CC1FLAGS_lib_dacb6c202432cdbd_0 := -fforce-addr -fno-rerun-cse-after-loop
