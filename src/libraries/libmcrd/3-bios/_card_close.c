#include "common.h"
#include <libapi.h>

s32 _card_close(void) {
    return StopCARD();
}
