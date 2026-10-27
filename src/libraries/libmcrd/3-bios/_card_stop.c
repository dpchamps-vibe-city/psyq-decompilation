#include "common.h"
#include <libapi.h>

extern s32 B_00000720;
extern s32 B_00000724;
extern s32 B_00000728;
extern s32 B_0000072C;
extern s32 B_00000730;
extern s32 B_00000734;
extern s32 B_00000738;
extern s32 B_0000073C;

void _card_stop(void) {
    s32 temp_s0;

    temp_s0 = EnterCriticalSection();
    CloseEvent(B_00000720);
    CloseEvent(B_00000724);
    CloseEvent(B_00000728);
    CloseEvent(B_0000072C);
    CloseEvent(B_00000730);
    CloseEvent(B_00000734);
    CloseEvent(B_00000738);
    CloseEvent(B_0000073C);
    if (temp_s0 == 1) {
        ExitCriticalSection();
    }
}
