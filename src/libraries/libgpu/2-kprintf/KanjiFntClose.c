#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>
#include <strings.h>

extern s32 D_00001060;
extern s32 D_00001064;
extern s32 D_00001068;

void KanjiFntClose(void) {
    D_00001068 = 0;
    D_00001064 = 0;
    D_00001060 = 0;
}
