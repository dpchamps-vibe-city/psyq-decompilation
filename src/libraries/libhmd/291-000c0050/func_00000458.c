/* Retained DAF4_CM.C with extracted private symbol names. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000848();
static int func_00000928();
static void func_00000AE4();

static void func_00000458(u_long *scratch, GsADIV_F4 *ifo, int level)
{
  register GsADIV_P_F4 *in,*out;
  register POLY_F4 *si;

  in = (GsADIV_P_F4 *)scratch;
  scratch += sizeof(GsADIV_P_F4)/4;
  out = (GsADIV_P_F4 *)scratch;

  gte_ldv3(&in->vt[0].vx,&in->vt[1].vx,&in->vt[2].vx);
  gte_rtpt();
  si = &ifo->si;
  gte_stflg(&ifo->flg);
  gte_stsxy3_f4((long *)si);
  gte_ldv0(&in->vt[3].vx);
  gte_rtps();
  gte_stflg(&ifo->flg0);
  gte_stsxy((long *)&si->x3);
  gte_avsz4();
  ifo->flg |= ifo->flg0;
  gte_stszotz(&ifo->otz);

  if(func_00000928(si,ifo))
    return;

  if(ifo->limit == level){
    if(ifo->flg & 0x7f85e000)
      return;
    else
      goto aaa;
  }

  if(ifo->flg>=0 && ifo->maxx-ifo->minx<ifo->adivw &&
     ifo->maxy-ifo->miny<ifo->adivh)
    {
    aaa:
      *ifo->pk = *(u_long *)si;
      *(ifo->pk+1) = *(u_long *)((u_long *)si+1);
      *(ifo->pk+2) = *(u_long *)((u_long *)si+2);
      *(ifo->pk+3) = *(u_long *)((u_long *)si+3);
      *(ifo->pk+4) = *(u_long *)((u_long *)si+4);
      *(ifo->pk+5) = *(u_long *)((u_long *)si+5);
      ifo->tag = ifo->org+(ifo->otz>>ifo->shift);
      *(u_long *)ifo->pk = (*ifo->tag&0x00ffffff)|0x05000000;
      *ifo->tag = (u_long)ifo->pk&0x00ffffff;
      ifo->pk += sizeof(POLY_F4)/4;
      return;
    }

  level++;
  out->vt[0] = in->vt[0];
  func_00000AE4(&out->vt[1],&in->vt[0],&in->vt[1]);
  func_00000AE4(&out->vt[2],&in->vt[0],&in->vt[2]);
  func_00000AE4(&out->vt[3],&in->vt[0],&in->vt[3]);
  func_00000848(&in->vt[0],&in->vt[1],&out->vt[1],ifo);
  func_00000458(scratch,ifo,level);

  out->vt[0] = in->vt[1];
  func_00000AE4(&out->vt[2],&in->vt[1],&in->vt[3]);
  func_00000848(&in->vt[1],&in->vt[3],&out->vt[2],ifo);
  func_00000458(scratch,ifo,level);

  out->vt[0] = in->vt[3];
  func_00000AE4(&out->vt[1],&in->vt[3],&in->vt[2]);
  func_00000848(&in->vt[3],&in->vt[2],&out->vt[1],ifo);
  func_00000458(scratch,ifo,level);

  out->vt[0] = in->vt[2];
  func_00000AE4(&out->vt[2],&in->vt[0],&in->vt[2]);
  func_00000848(&in->vt[2],&in->vt[0],&out->vt[2],ifo);
  func_00000458(scratch,ifo,level);
}
