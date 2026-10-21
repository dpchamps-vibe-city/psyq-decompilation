#include "common.h"
#include <libapi.h>
#include <libcomb.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern long AddDrv(void *);
extern u8 D_STR_00001210[];

void AddCOMB(void) {
    s32 temp_s0;

    temp_s0 = EnterCriticalSection();
    AddDrv(D_STR_00001210);
    if (temp_s0 == 1) {
        ExitCriticalSection();
    }
}
