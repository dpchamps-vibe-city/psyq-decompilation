#include "common.h"
#include <sys/types.h>
#include <libcd.h>

void *DMACallback();                     /* extern */

void *CdDataCallback(void (*func)()) {
    return DMACallback(3, func);
}
