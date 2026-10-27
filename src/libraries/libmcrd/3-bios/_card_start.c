#include "common.h"
#include <libapi.h>

void _clr_card_event();                             /* static */
extern s32 B_00000720;
extern s32 B_00000724;
extern s32 B_00000728;
extern s32 B_0000072C;
extern s32 B_00000730;
extern s32 B_00000734;
extern s32 B_00000738;
extern s32 B_0000073C;

extern s32 funcEvSpIOE(void);
extern s32 funcEvSpError(void);
extern s32 funcEvSpTimeout(void);
extern s32 funcEvSpNewcard(void);
extern s32 funcEvSpIOEx(void);
extern s32 funcEvSpErrorx(void);
extern s32 funcEvSpTimeoutx(void);
extern s32 funcEvSpNewcardx(void);

void _card_start(void) {
    s32 temp_s0;

    temp_s0 = EnterCriticalSection();
    B_00000720 = OpenEvent(0xF4000001U, 4, 0x1000, (long (*)())funcEvSpIOE);
    B_00000724 = OpenEvent(0xF4000001U, 0x8000, 0x1000, (long (*)())funcEvSpError);
    B_00000728 = OpenEvent(0xF4000001U, 0x100, 0x1000, (long (*)())funcEvSpTimeout);
    B_0000072C = OpenEvent(0xF4000001U, 0x2000, 0x1000, (long (*)())funcEvSpNewcard);
    B_00000730 = OpenEvent(0xF0000011U, 4, 0x1000, (long (*)())funcEvSpIOEx);
    B_00000734 = OpenEvent(0xF0000011U, 0x8000, 0x1000, (long (*)())funcEvSpErrorx);
    B_00000738 = OpenEvent(0xF0000011U, 0x100, 0x1000, (long (*)())funcEvSpTimeoutx);
    B_0000073C = OpenEvent(0xF0000011U, 0x2000, 0x1000, (long (*)())funcEvSpNewcardx);
    EnableEvent(B_00000720);
    EnableEvent(B_00000724);
    EnableEvent(B_00000728);
    EnableEvent(B_0000072C);
    EnableEvent(B_00000730);
    EnableEvent(B_00000734);
    EnableEvent(B_00000738);
    EnableEvent(B_0000073C);
    _clr_card_event();
    if (temp_s0 == 1) {
        ExitCriticalSection();
    }
}
