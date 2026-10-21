#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libcd.h>

typedef union {
    int addr;
    CdlLOC i;
} LBA;

extern s32 D_00000BD8;
extern CdlFILE B_00000BE8[];
extern u8 B_000027E8[0x800];
extern char RO_STR_00000B54[];
extern char RO_STR_00000B74[];
extern short RO_STR_00000B90[];
extern short RO_STR_00000B94[];
extern char RO_STR_00000B98[];
extern char RO_STR_00000BB4[];

extern void *memcpy(void *dest, const void *src, u32 n);

static s32 func_00000974(s32, s32, u8 *);

static s32 func_000006D8(s32 arg0);

static s32 func_000006D8(s32 arg0) {
    LBA entryLba;
    u8 *entry;
    s32 i;
    short *namePtr;

    if (arg0 == D_00000BD8) {
        return 1;
    }

    if (func_00000974(1, (B_000011E8 - 1)[arg0].lba, B_000027E8) != 1) {
        if (CD_debug > 0) {
            printf(RO_STR_00000B54);
        }
        return -1;
    }
    if (CD_debug > 1) {
        printf(RO_STR_00000B74);
    }
    entry = B_000027E8;
    i = 0;
    while (entry < B_000027E8 + sizeof(B_000027E8)) {
        if (entry[0] == 0) {
            break;
        }
        entryLba.i = ((LBA *)&entry[2])->i;
        CdIntToPos(entryLba.addr, &B_00000BE8[i].pos);
        ((LBA *)&B_00000BE8[i].size)->i = ((LBA *)&entry[0xA])->i;
        switch (i) {
        case 0:
            namePtr = (short *)B_00000BE8[i].name;
            __builtin_memcpy(namePtr, RO_STR_00000B90, 2);
            break;
        case 1:
            namePtr = (short *)B_00000BE8[i].name;
            __builtin_memcpy(namePtr, RO_STR_00000B94, 3);
            break;
        default:
            ((void *(*)(void *, const void *, u32))memcpy)(B_00000BE8[i].name, &entry[0x21], entry[0x20]);
            B_00000BE8[i].name[entry[0x20]] = '\0';
            break;
        }
        if (CD_debug > 1) {
            printf(RO_STR_00000B98, B_00000BE8[i].pos.minute,
                   B_00000BE8[i].pos.second, B_00000BE8[i].pos.sector, B_00000BE8[i].size,
                   B_00000BE8[i].name);
        }
        entry += entry[0];
        if (++i >= CdlMAXFILE) {
            break;
        }
    }
    D_00000BD8 = arg0;
    if (i < CdlMAXFILE) {
        B_00000BE8[i].name[0] = '\0';
    }
    if (CD_debug > 1) {
        printf(RO_STR_00000BB4, i);
    }
    return 1;
}
