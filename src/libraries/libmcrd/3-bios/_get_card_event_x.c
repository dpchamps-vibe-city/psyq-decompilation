#include "common.h"
#include <libapi.h>

extern s32 B_00000720;
extern s32 B_00000724;
extern s32 B_00000728;
extern s32 B_0000072C;
extern s32 B_00000750;
extern s32 B_00000754;
extern s32 B_00000758;
extern s32 B_0000075C;

s32 _get_card_event_x(void) {
    s32 temp_s0;

    do {
        temp_s0 = B_00000750 + (B_00000754 * 2) + (B_00000758 * 4) + (B_0000075C * 8);
    } while (temp_s0 == 0);
    TestEvent(B_00000720);
    TestEvent(B_00000724);
    TestEvent(B_00000728);
    TestEvent(B_0000072C);
    B_0000075C = 0;
    B_00000758 = B_0000075C;
    B_00000754 = B_00000758;
    B_00000750 = B_00000754;
    return temp_s0 >> 1;
}
