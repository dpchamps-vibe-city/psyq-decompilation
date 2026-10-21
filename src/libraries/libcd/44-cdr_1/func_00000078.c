#include "common.h"

static void func_00000078(void) {
    CdlCB self;

    /* Address-taken before the end of its own body, so -O3 emits it here
       instead of deferring it: its callers only take its address later. */
    self = (CdlCB)func_00000078;
    (void)self;
    CdSyncCallback(D_00000A68.unk28);
    ((volatile CdReadState *)((u8 *)&D_00000A68.unk28 - 0x28))->unk24 = 0;
}
