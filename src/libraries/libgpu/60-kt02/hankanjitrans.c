#include "common.h"
#include <stdio.h>

extern u16 D_000001D8[];
extern u16 D_000001E4[];
extern char RO_STR_000001B8[];

int hankanjitrans(u8 c) {
    int code = 0;
    u8 tbl;
    int idx;
    int base;

    if ((u8)(c - 0x20) < 0x10) {
        code = 1;
    } else if ((u8)(c - 0x30) < 0x0A) {
        tbl = 0;
    } else if ((u8)(c - 0x3A) < 7) {
        code = 0xB;
    } else if ((u8)(c - 0x41) < 0x1A) {
        tbl = 1;
    } else if ((u8)(c - 0x5B) < 6) {
        code = 0x25;
    } else if ((u8)(c - 0x61) < 0x1A) {
        tbl = 2;
    } else if ((u8)(c - 0x7B) < 4) {
        code = 0x3F;
    } else {
        printf(RO_STR_000001B8, c);
        return 0;
    }
    if ((code & 0xFF) == 0) {
        return D_000001D8[tbl * 2] + (c & 0xFF) - D_000001D8[tbl * 2 + 1];
    }
    idx = c & 0xFF;
    base = (code & 0xFF) + 0x1F;
    return D_000001E4[idx - base];
}
