#include "common.h"
#include <libapi.h>

extern volatile s32 B_00000720;
extern volatile s32 B_00000724;
extern volatile s32 B_00000728;
extern volatile s32 B_0000072C;
extern volatile s32 B_00000730;
extern volatile s32 B_00000734;
extern volatile s32 B_00000738;
extern volatile s32 B_0000073C;
extern volatile s32 B_00000740;
extern volatile s32 B_00000744;
extern volatile s32 B_00000748;
extern volatile s32 B_0000074C;
extern volatile s32 B_00000750;
extern volatile s32 B_00000754;
extern volatile s32 B_00000758;
extern volatile s32 B_0000075C;

void _clr_card_event(void) {
    TestEvent(B_00000720);
    TestEvent(B_00000724);
    TestEvent(B_00000728);
    TestEvent(B_0000072C);
    TestEvent(B_00000730);
    TestEvent(B_00000734);
    TestEvent(B_00000738);
    TestEvent(B_0000073C);
    B_0000074C = 0;
    B_00000748 = B_0000074C;
    B_00000744 = B_00000748;
    B_00000740 = B_00000744;
    B_0000075C = 0;
    B_00000758 = B_0000075C;
    B_00000754 = B_00000758;
    B_00000750 = B_00000754;
}
