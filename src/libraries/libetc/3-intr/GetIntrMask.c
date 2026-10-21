#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libetc.h>
#include <setjmp.h>
#include <stdio.h>

extern u16 *D_00001898;

u16 GetIntrMask(void) {
    return *D_00001898;
}
