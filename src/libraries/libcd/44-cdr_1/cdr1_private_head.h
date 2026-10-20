static void func_00000078(void) __asm__("$Lfunc_00000078");

/* Takes the callback's address before its definition, which is what makes the
 * compiler emit the out-of-line copy for a static function at -O3. The
 * function itself is never called and is not emitted. */
static void func_00000078_keepalive(void) {
    CdlCB cb;

    cb = (CdlCB)func_00000078;
}

static void func_00000078(void) {
    CdSyncCallback(D_00000A68.unk28);
    ((volatile CdReadState *)((u8 *)&D_00000A68.unk28 - 0x28))->unk24 = 0;
}
