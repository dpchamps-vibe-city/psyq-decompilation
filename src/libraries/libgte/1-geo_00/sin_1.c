#include "common.h"

extern s16 rsin_tbl[];

int sin_1(int a) {
    if (a < 0x801) {
        if (a < 0x401) {
            return rsin_tbl[a];
        }
        return rsin_tbl[0x800 - a];
    }
    if (a < 0xC01) {
        return -rsin_tbl[a - 0x800];
    }
    return -rsin_tbl[0x1000 - a];
}
