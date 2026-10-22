#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <stdio.h>

extern u_long *B_00000238;

int OpenTIM(u_long *addr) {
    B_00000238 = addr;
    return 0;
}
