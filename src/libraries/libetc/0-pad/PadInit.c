#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libetc.h>

void PAD_init(char *buf1, char *buf2);

extern s32 B_000000F0;

void PadInit(int mode) {
    PadIdentifier = mode;
    B_000000F0 = -1;
    ResetCallback();
    PAD_init((char *)0x20000001, (char *)&B_000000F0);
    ChangeClearPAD(0);
}
