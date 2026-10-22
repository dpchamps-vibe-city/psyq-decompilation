#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <stdio.h>

static s32 func_000000EC(u_long *addr, TIM_IMAGE *timimg) {
    s32 len;
    u_long tail;
    s32 size;

    if (*addr++ != 0x10) {
        return -1;
    }
    timimg->mode = *addr++;
    if (GetGraphDebug() == 2) {
        printf("id  =%08x\n", 0x10);
    }
    if (GetGraphDebug() == 2) {
        printf("mode=%08x\n", timimg->mode);
    }
    if (GetGraphDebug() == 2) {
        printf("timaddr=%08x\n", addr);
    }
    if (timimg->mode & 8) {
        len = *addr >> 2;
        timimg->crect = (RECT *)(addr + 1);
        timimg->caddr = addr + 3;
        addr += len;
    } else {
        len = 0;
        timimg->crect = 0;
        timimg->caddr = 0;
    }
    tail = *addr;
    timimg->prect = (RECT *)(addr + 1);
    timimg->paddr = addr + 3;
    size = (tail >> 2) + 2;
    return len + size;
}
