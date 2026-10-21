#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <stdio.h>
#include <strings.h>

static s32 func_0000063C(s32 parent, char *name) {
    s32 i;

    for (i = 0; i < 128; i++) {
        if (B_000011D8[i].parent == 0) {
            break;
        }
        if (B_000011D8[i].parent == parent && strcmp(name, B_000011D8[i].name) == 0) {
            return i + 1;
        }
    }
    return -1;
}
