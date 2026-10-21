#include "common.h"

extern DslCB D_000005A4;

int DsGetSector(void *madr, int size);
int DsGetSector2(void *madr, int size);
static void func_000004C4(int arg0);

static void func_000001D4(u_char com, u_char *result, u_long *pad) {
    DslCB func;

    D_00000580.pad1 = VSync(-1);
    if (D_00000580.mode & 1) {
        if (D_00000580.sectors > 0) {
            DsGetSector2(D_00000580.buf, D_00000580.size);
            D_00000580.pad0 = (int) result;
            return;
        }
        func_000004C4(1);
        func = D_000005A4;
        if (func == 0) {
            return;
        }
        if (D_00000580.sectors < 0) {
            com = 5;
        }
        func(com, result);
    } else {
        if (D_00000580.sectors > 0) {
            DsGetSector(D_00000580.buf, D_00000580.size);
            D_00000580.buf += D_00000580.size;
            D_00000580.sectors--;
        }
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
            func(com, result);
        } else {
            return;
        }
    }
}
