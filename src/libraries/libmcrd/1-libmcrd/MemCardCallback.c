#include "common.h"
#include <libmcrd.h>

extern s32 B_00001B78;

MemCB MemCardCallback(MemCB func) {
    MemCB *slot = (MemCB *)((u8 *)&B_00001B78 + 0x44);
    MemCB prev = *slot;

    *slot = func;
    return prev;
}
