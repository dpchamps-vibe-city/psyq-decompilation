#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

long func_0000043C(HMD_P_CAMERA *in)
{
    long ret;

    ret = (in->vpx > 0 ? in->vpx : -in->vpx);
    ret = (ret > (in->vpy > 0 ? in->vpy : -in->vpy) ? ret :
                (in->vpy > 0 ? in->vpy : -in->vpy));
    ret = (ret > (in->vpz > 0 ? in->vpz : -in->vpz) ? ret :
                (in->vpz > 0 ? in->vpz : -in->vpz));
    ret = (ret > (in->vrx > 0 ? in->vrx : -in->vrx) ? ret :
                (in->vrx > 0 ? in->vrx : -in->vrx));
    ret = (ret > (in->vry > 0 ? in->vry : -in->vry) ? ret :
                (in->vry > 0 ? in->vry : -in->vry));
    ret = (ret > (in->vrz > 0 ? in->vrz : -in->vrz) ? ret :
                (in->vrz > 0 ? in->vrz : -in->vrz));
    return ret;
}
