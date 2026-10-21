#include "common.h"
#include <sys/types.h>
#include <libds.h>

void DS_stop(void);

void DS_CQ_flush(void);

void DS_restart(void);


void DsFlush(void) {
    DS_stop();
    DS_CQ_flush();
    DsEndReadySystem();
    DS_restart();
}
