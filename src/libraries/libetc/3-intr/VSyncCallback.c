#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libetc.h>
#include <setjmp.h>
#include <stdio.h>

int VSyncCallback(void (*f)(void)) {
    return ((int (*)(int, void (*)(void)))D_00001890->unk14)(4, f);
}
