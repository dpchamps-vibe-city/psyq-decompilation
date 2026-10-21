extern volatile CdReadState D_00000A68;
extern s32 CD_read_dma_mode;
static int func_000003F0(s32 arg0);

int CdRead(int sectors, u_long *buf, int mode) {
    s32 i;

    if (D_00000A68.unk24 != 0) {
        i = VSync(-1);
        while (D_00000A68.unk24 != 0) {
            if ((u32)(VSync(-1) - i) >= 0x79) {
                CdSyncCallback(D_00000A68.unk28);
                D_00000A68.unk24 = 0;
                break;
            }
        }
    }
    D_00000A68.unkC = mode;
    switch (D_00000A68.unkC & 0x30) {
    case 0x00:
        D_00000A68.unk10 = 0x200;
        break;
    case 0x20:
        D_00000A68.unk10 = 0x249;
        break;
    default:
        D_00000A68.unk10 = 0x246;
        break;
    }
    D_00000A68.unkC |= 0x20;
    D_00000A68.unk4 = (u32)buf;
    D_00000A68.unk0 = sectors;
    D_00000A68.unk28 = CdSyncCallback(0);
    D_00000A68.unk2C = CdReadyCallback(0);
    if (CD_read_dma_mode & 1) {
        D_00000A68.unk30 = CdDataCallback(0);
    }
    D_00000A68.unk1C = VSync(-1);
    if (CdStatus() & 0xE0) {
        CdControlB(9, 0, 0);
    }
    return func_000003F0(0) > 0;
}
