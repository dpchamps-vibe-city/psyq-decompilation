#include "common.h"
#include <libapi.h>

extern s32 B_00000750;
extern s32 B_00000754;
extern s32 B_00000758;
extern s32 B_0000075C;

s32 _chk_card_event_x(void) {
    return B_00000750 + (B_00000754 * 2) + (B_00000758 * 4) + (B_0000075C * 8);
}
