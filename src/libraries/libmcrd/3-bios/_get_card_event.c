#include "common.h"
#include <libapi.h>

extern s32 B_00000730;
extern s32 B_00000734;
extern s32 B_00000738;
extern s32 B_0000073C;
extern s32 B_00000740;
extern s32 B_00000744;
extern s32 B_00000748;
extern s32 B_0000074C;

s32 _get_card_event(void) {
    s32 temp_s0;

    do {
        temp_s0 = B_00000740 + (B_00000744 * 2) + (B_00000748 * 4) + (B_0000074C * 8);
    } while (temp_s0 == 0);
    TestEvent(B_00000730);
    TestEvent(B_00000734);
    TestEvent(B_00000738);
    TestEvent(B_0000073C);
    B_0000074C = 0;
    B_00000748 = B_0000074C;
    B_00000744 = B_00000748;
    B_00000740 = B_00000744;
    return temp_s0 >> 1;
}
