#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsClearVcount(void) {
    ResetRCnt(0xF2000001U);
}
