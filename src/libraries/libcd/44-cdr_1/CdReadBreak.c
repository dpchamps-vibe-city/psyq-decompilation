extern volatile CdReadState D_00000A68;

void CdReadBreak(void) {
    s32 i;
    s32 j;
    s32 ret;

    if (CD_read_dma_mode & 1) {
        CdDataSync(0);
    }
    D_00000A68.unk14 = 0;
    if (D_00000A68.unk24 == 0) {
        ret = 1;
    } else {
        i = VSync(-1);
        while (D_00000A68.unk24 != 0) {
            if ((u32)(VSync(-1) - i) >= 0x79) {
                CdSyncCallback(D_00000A68.unk28);
                D_00000A68.unk24 = 0;
                ret = -1;
                goto out;
            }
        }
        ret = 0;
    }
out:
    ;
    if (ret != 0) {
        CdReadyCallback(D_00000A68.unk2C);
        if (CD_read_dma_mode & 1) {
            CdDataCallback(D_00000A68.unk30);
        }
        CdSyncCallback((CdlCB)func_00000078);
        CdControlF(9, 0);
        D_00000A68.unk24 = 1;
        if (D_00000A68.unk24 != 0) {
            j = VSync(-1);
            while (D_00000A68.unk24 != 0) {
                if ((u32)(VSync(-1) - j) >= 0x79) {
                    CdSyncCallback(D_00000A68.unk28);
                    D_00000A68.unk24 = 0;
                    break;
                }
            }
        }
    }
}
