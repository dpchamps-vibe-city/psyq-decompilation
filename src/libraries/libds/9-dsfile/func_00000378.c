#include "common.h"
#include <memory.h>
#include <stdio.h>
#include <strings.h>

extern u8 B_000027D8[];
extern u32 D_00000BC8;

typedef struct {
    u32 number;
    u32 parent;
    u32 lba;
    char name[32];
} DirEntry;

typedef struct {
    u8 b[4];
} Word4;

extern DirEntry B_000011D8[];

extern s32 func_0000097C(s32, s32, u8 *);

extern char RO_STR_00000A64[];
extern char RO_STR_00000A90[];
extern char RO_STR_00000A98[];
extern char RO_STR_00000AC8[];
extern char RO_STR_00000AEC[];
extern char RO_STR_00000B0C[];
extern char RO_STR_00000B20[];

static s32 func_00000378(void) {
    u8 *p;
    u8 *pvd;
    u32 pt;
    u32 n;
    u32 m;
    s32 stat;
    s32 i;

    pvd = B_000027D8;
    stat = func_0000097C(1, 0x10, pvd);
    if (stat != 1) {
        if (CD_debug > 0) {
            puts(RO_STR_00000A64);
        }
        return 0;
    }
    if (strncmp((s8 *)&pvd[1], (s8 *)RO_STR_00000A90, 5) != 0) {
        if (CD_debug > 0) {
            puts(RO_STR_00000A98);
        }
        return 0;
    }
    *(Word4 *)&pt = *(Word4 *)(pvd + 0x8C);
    if (func_0000097C(1, pt, pvd) != stat) {
        if (CD_debug > 0) {
            printf(RO_STR_00000AC8, pt);
        }
        return 0;
    }
    if (CD_debug >= 2) {
        puts(RO_STR_00000AEC);
    }
    p = pvd;
    i = 0;
    if (p < pvd + 0x800) {
        do {
            if (p[0] != 0) {
                *(Word4 *)&B_000011D8[i].lba = *(Word4 *)(p + 2);
                B_000011D8[i].parent = p[6];
                B_000011D8[i].number = i + 1;
                memcpy(B_000011D8[i].name, p + 8, p[0]);
                B_000011D8[i].name[p[0]] = 0;
                n = p[0];
                m = n & 1;
                m += 8;
                p += n + m;
                if (CD_debug >= 2) {
                    printf(RO_STR_00000B0C, B_000011D8[i].lba, B_000011D8[i].number,
                           B_000011D8[i].parent, B_000011D8[i].name);
                }
                i++;
            } else {
                break;
            }
        } while (i < 128 && p < pvd + 0x800);
    }
    if (i < 128) {
        B_000011D8[i].parent = 0;
    }
    D_00000BC8 = 0;
    if (CD_debug >= 2) {
        printf(RO_STR_00000B20, i);
    }
    return 1;
}
