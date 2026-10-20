#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsSetLightMatrix2(MATRIX *mp) {
    SetLightMatrix(MulMatrix2(&GsLIGHTWSMATRIX, mp));
}
