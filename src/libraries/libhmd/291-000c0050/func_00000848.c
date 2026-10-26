/* Retained DAF4_CM.C sukima with extracted private symbol name. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000848(VERT *v0, VERT *v1, VERT *v2, GsADIV_F4 *ifo)
{
  POLY_F3 *si;

  gte_ldv3(&v0->vx,&v1->vx,&v2->vx);
  gte_rtpt();
  si = (POLY_F3 *)ifo->pk;
  *(u_long *)&si->r0 = *(u_long *)&ifo->si.r0;
  setPolyF3(si);

  gte_stflg(&ifo->flg);

  if(ifo->flg&0x80000000)
    return;
  gte_avsz3();
  gte_stsxy3_f3((long *)si);
  gte_stotz(&ifo->otz);
  ifo->tag = ifo->org+(ifo->otz>>ifo->shift);
  *(u_long *)si = (*ifo->tag&0x00ffffff)|0x04000000;
  *ifo->tag = (u_long)si&0x00ffffff;
  ifo->pk += sizeof(POLY_F3)/4;
}
