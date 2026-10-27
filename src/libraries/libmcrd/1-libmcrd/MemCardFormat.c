#include "common.h"
#include <libmcrd.h>
#include <stdio.h>

extern char RO_STR_00001AFC[];
/* LOW.OBJ _card_format2 preserves its incoming channel from a0 in s4. */
extern s32 _card_format2(long chan);
static s32 func_000017FC(s32);

long MemCardFormat(long chan)
{
    McrdState *mcrd = (McrdState *)&B_00001B78;
    s32 result;

    if (mcrd->unk00 != 0) {
        printf(RO_STR_00001AFC);
        return -1;
    }
    result = _card_format2(chan);
    if (result != 0) {
        if (result == 4)
            return 2;
        return func_000017FC(result);
    }
    return 0;
}
