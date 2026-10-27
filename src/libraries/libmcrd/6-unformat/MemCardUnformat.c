#include "common.h"
#include <libapi.h>
#include <libmcrd.h>
#include <stdio.h>
#include "libmcrd_internal.h"
#include "libmcrd_unformat.h"

long MemCardUnformat(long chan)
{
    signed char buffer[128];
    long i;

    if (*McrdGetGlobalStructure() != 0) {
        printf(RO_STR_00000120);
        return -1;
    }
    for (i = 0; i < 128; i++) {
        buffer[i] = -1;
    }
    for (i = 0; i < 15; i++) {
        _clr_card_event();
        _new_card();
        _card_write(chan, i, (unsigned char *)buffer);
        if (_get_card_event_x() != 0) {
            return 0;
        }
    }
    return 1;
}
