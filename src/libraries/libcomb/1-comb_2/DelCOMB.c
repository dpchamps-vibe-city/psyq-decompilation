#include "common.h"
#include <libapi.h>
#include <libcomb.h>

extern long DelDrv(void *);
extern char D_000000C0[] __asm__("$LRO_STR_000000C0");

void DelCOMB(void) {
    s32 temp_s0;

    temp_s0 = EnterCriticalSection();
    DelDrv(D_000000C0);
    FlushCache();
    if (temp_s0 == 1) {
        ExitCriticalSection();
    }
}
