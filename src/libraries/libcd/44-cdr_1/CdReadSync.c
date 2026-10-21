extern volatile CdReadState cd __asm__("D_00000A68");
static int func_000003F0(s32 arg0);

int CdReadSync(int mode, u_char *result) {
    volatile s32 *p;
    volatile u32 *q;
    s32 ret;

    /* p anchors the read state at unk1C; p[-7] is unk0, p[-2] is unk14 and
     * p[-1] is unk18. q is unk24. */
    p = &cd.unk1C;
    q = &cd.unk24;
    do {
        ret = -1;
        if (VSync(-1) <= p[0] + 0x4B0) {
            if (p[-2] < 0 || VSync(-1) > p[-1] + 0x3C) {
                func_000003F0(1);
                ret = p[-7];
            } else {
                ret = p[-2];
            }
        }
    } while (mode == 0 && ((*q != 0 && ret == 0) || ret > 0));
    CdReady(1, result);
    if (*q != 0 && ret == 0) {
        ret = 1;
    }
    return ret;
}
