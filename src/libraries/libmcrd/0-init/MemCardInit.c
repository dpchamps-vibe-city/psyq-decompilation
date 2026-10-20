#include "common.h"
#include <libapi.h>
#include <libmcrd.h>

void MemCardInit(long val) {
    InitCARD(val);
    StartCARD();
    _bu_init();
}
