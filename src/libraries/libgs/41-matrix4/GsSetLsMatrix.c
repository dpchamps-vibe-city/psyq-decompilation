#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsSetLsMatrix(MATRIX *mp) {
    SetRotMatrix(mp);
    SetTransMatrix(mp);
}
