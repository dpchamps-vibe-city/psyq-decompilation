#include "common.h"
#include <sys/types.h>
#include <libds.h>

void *DMACallback();                     /* extern */

void *DsDataCallback(void (*func)()) {
    return DMACallback(3, func);
}
