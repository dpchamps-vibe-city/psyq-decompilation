#include "common.h"
#include <libapi.h>

void _card_open(s32 arg0) {
    InitCARD(arg0);
    StartCARD();
    _bu_init();
}
