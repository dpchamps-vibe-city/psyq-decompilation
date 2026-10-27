#include "common.h"
#include <libapi.h>

extern s32 B_00000740;
extern s32 B_00000744;
extern s32 B_00000748;
extern s32 B_0000074C;

s32 _chk_card_event(void) {
    return B_00000740 + (B_00000744 * 2) + (B_00000748 * 4) + (B_0000074C * 8);
}
