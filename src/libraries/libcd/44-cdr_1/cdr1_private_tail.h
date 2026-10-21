static void T_00000320(void);

static void T_00000320(void) {
    volatile CdReadState *cd;

    cd = (volatile CdReadState *)&D_00000A68;
    cd->unk8 += cd->unk10;
    cd->unk14 -= 1;
    cd->unk20 += 1;
    if (cd->unk14 == 0) {
        CdReadyCallback(cd->unk2C);
        if (CD_read_dma_mode & 1) {
            CdDataCallback(cd->unk30);
        }
        CdSyncCallback((CdlCB)func_00000078);
        CdControlF(9, 0);
        cd->unk24 = 1;
        if (CD_cbread != 0) {
            CD_cbread(2, cd->unk34);
        }
    }
}
