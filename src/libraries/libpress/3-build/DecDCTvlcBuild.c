#include "common.h"
#include <sys/types.h>
#include <libpress.h>

#include "libpress_internal.h"

void DecDCTvlcBuild(u_short *table) {
    s32 distance = 0;
    u8 *src = &D_00000160;
    u8 *dst = (u8 *)table;
    s32 count;
    u8 token;
    s32 i;

    do {
        token = *src++;
        count = token & 0xFF;
        if ((u32)count < 0xF0) {
            if (distance != 0) {
                while (count >= 0) {
                    count--;
                    *dst = *(dst - distance);
                    dst++;
                }
            } else {
                while (count >= 0) {
                    *dst++ = *src++;
                    count--;
                }
            }
        } else {
            distance = 0;
            if (count != 0xF0) {
                distance = ((count << 8) | *src++) + 0xFFFF0F01;
            }
        }
    } while (distance != 0xF00);
    for (i = 4; i <= 0x87FF; i++) {
        table[i] ^= table[i - 4];
    }
}
