void func_0000034C(u_char com, u_char *result) {
    DslCB func;

    D_00000580.buf += D_00000580.size;
    D_00000580.sectors--;
    if (VSync(-1) > D_00000580.vsync + 0x4B0) {
        D_00000580.sectors = -1;
    }
    if (D_00000580.sectors == 0 || VSync(-1) > D_00000580.vsync + 0x4B0) {
        func_000004C4(1);
        func = D_000005A4;
        if (func == 0) {
            return;
        }
        com = 2;
        if (D_00000580.sectors < 0) {
            com = 5;
        }
        func(com, (u_char *)D_00000580.pad0);
    }
}
