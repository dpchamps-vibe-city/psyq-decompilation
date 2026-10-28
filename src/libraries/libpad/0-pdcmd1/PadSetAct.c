#include "common.h"
#include <libpad.h>
#include "libpad-internal.h"

void PadSetAct(int port, unsigned char *table, int size) {
    PadInfo2 *info = _padFuncPort2Info(port);
    info->actTable = table;
    info->actSize = size;
}
