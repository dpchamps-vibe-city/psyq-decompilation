#include "common.h"

typedef struct {
    u32 number;
    u32 parent;
    u32 lba;
    char name[32];
} DirEntry;

extern DirEntry $LB_000011E8[];
extern int strcmp();

static s32 func_00000634(s32 arg0, s8 *arg1) __asm__("$Lfunc_00000634");

static s32 func_00000634(s32 arg0, s8 *arg1) {
    s32 i;

    if (0) {
        func_00000634(arg0, arg1);
    }

    for (i = 0; i < 0x80; i++) {
        if ($LB_000011E8[i].parent == 0) {
            break;
        }
        if ($LB_000011E8[i].parent == arg0) {
            if (strcmp(arg1, $LB_000011E8[i].name) == 0) {
                return i + 1;
            }
        }
    }
    return -1;
}
