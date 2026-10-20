#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsSetWorkBase(PACKET *outpacketp) {
    GsOUT_PACKET_P = outpacketp;
}
