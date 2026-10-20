extern volatile CdReadState cd __asm__("$LD_00000A68");
extern s32 CD_read_dma_mode;
extern int func_000003F0(s32 arg0) __asm__("$Lfunc_000003F0");

int CdRead(int sectors, u_long *buf, int mode) {
    s32 i;

    if (cd.unk24 != 0) {
        i = VSync(-1);
        while (cd.unk24 != 0) {
            if ((u32)(VSync(-1) - i) >= 0x79) {
                CdSyncCallback(cd.unk28);
                cd.unk24 = 0;
                break;
            }
        }
    }
    cd.unkC = mode;
    switch (cd.unkC & 0x30) {
    case 0x00:
        cd.unk10 = 0x200;
        break;
    case 0x20:
        cd.unk10 = 0x249;
        break;
    default:
        cd.unk10 = 0x246;
        break;
    }
    cd.unkC |= 0x20;
    cd.unk4 = (u32)buf;
    cd.unk0 = sectors;
    cd.unk28 = CdSyncCallback(0);
    cd.unk2C = CdReadyCallback(0);
    if (CD_read_dma_mode & 1) {
        cd.unk30 = CdDataCallback(0);
    }
    cd.unk1C = VSync(-1);
    if (CdStatus() & 0xE0) {
        CdControlB(9, 0, 0);
    }
    return func_000003F0(0) > 0;
}
