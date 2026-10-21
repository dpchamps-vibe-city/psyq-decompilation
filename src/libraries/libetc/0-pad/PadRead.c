#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libetc.h>

void PAD_dr(void);

extern s32 B_000000F0;

u_long PadRead(int id) {
    PAD_dr();
    return ~B_000000F0;
}
