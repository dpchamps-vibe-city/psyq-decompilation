#include "common.h"

extern volatile s32 B_00001B48[];
extern void VSyncCallbacks(s32, void (*)(u8, u8 *, s32 *, s32 *));
extern void _card_stop(void);

void MemCardStop(void)
{
    while (B_00001B48[12] != 0) {
    }
    VSyncCallbacks(7, 0);
    _card_stop();
}
