#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void SetDQA(s16);
void SetDQB(s32);

void GsSetFogParam(GsFOGPARAM *fogparm) {
    SetDQA(fogparm->dqa);
    SetDQB(fogparm->dqb);
    SetFarColor(fogparm->rfc, fogparm->gfc, fogparm->bfc);
}
