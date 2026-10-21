#include "common.h"
#include <libapi.h>
#include <memory.h>

static s32 func_00000070(s32 chan, s32 block, u8 *buf);

static s32 func_00000070(s32 chan, s32 block, u8 *buf) {
    u8 temp[0x80];
    u8 *p;
    u8 *q;
    u8 *r;
    u8 sum;
    s32 i;
    s32 j;
    s32 k;

    i = 0;
    p = buf;
    sum = 0;
    for (j = 0x7E; j >= 0; j--) {
        sum ^= *p++;
    }
    *p = sum;

    for (;;) {
        if (i >= 8) {
            return 0;
        }
        _new_card();
        if (_card_write(chan, block, buf) != 1) {
            return 0;
        }
        while ((_card_status(chan >> 4) & 1) == 0) {
        }
        q = temp;
        bzero(q, 0x80);
        _new_card();
        if (_card_read(chan, block, q) == 1) {
            while ((_card_status(chan >> 4) & 1) == 0) {
            }
        }
        r = temp;
        sum = 0;
        for (k = 0x7E; k >= 0; k--) {
            sum ^= *r++;
        }
        if (buf[0x7F] == sum) {
            return 1;
        }
        i++;
    }
    if (0) {
        return func_00000070(chan, block, buf);
    }
}
