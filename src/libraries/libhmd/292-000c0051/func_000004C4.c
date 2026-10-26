/* Retained DAFT4_CM.C Adiv_ft4 with extracted private symbol name. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000924();
static int func_00000A3C();
static void func_00000BF8();

static void func_000004C4(u_long *scratch, GsADIV_FT4 *ifo, int level)
{
  register GsADIV_P_FT4 *in,*out;
  register POLY_FT4 *si;
  VECTOR   tmp;

  in = (GsADIV_P_FT4 *)scratch;
  scratch += sizeof(GsADIV_P_FT4)/4;
  out = (GsADIV_P_FT4 *)scratch;

  gte_ldv3(&in->vt[0].vx,&in->vt[1].vx,&in->vt[2].vx);
  gte_rtpt();

  si = &ifo->si;
  *(u_short *)&si->u0 = *(u_short *)&in->vt[0].tu;
  *(u_short *)&si->u1 = *(u_short *)&in->vt[1].tu;
  *(u_short *)&si->u2 = *(u_short *)&in->vt[2].tu;
  gte_stflg(&ifo->flg);

  gte_stsxy3_ft3((long *)si);

  gte_ldv0(&in->vt[3].vx);
  gte_rtps();
  *(u_short *)&si->u3 = *(u_short *)&in->vt[3].tu;

  gte_stflg(&ifo->flg0);
  ifo->flg |= ifo->flg0;

  gte_stsxy((long *)&si->x3);
  gte_avsz4();
  gte_stszotz(&ifo->otz);

  if(func_00000A3C(si,ifo))
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
      *(ifo->pk+6) = *(u_long *)((u_long *)si+6);
      *(ifo->pk+7) = *(u_long *)((u_long *)si+7);
      *(ifo->pk+8) = *(u_long *)((u_long *)si+8);
      *(ifo->pk+9) = *(u_long *)((u_long *)si+9);
      ifo->tag = ifo->org+(ifo->otz>>ifo->shift);
      *(u_long *)ifo->pk  = (*ifo->tag&0x00ffffff)|0x09000000;
      *ifo->tag = (u_long)ifo->pk&0x00ffffff;
      ifo->pk += sizeof(POLY_FT4)/4;
      return;
    }

  level++;
  /********************** 1 st ***************************/
  out->vt[0] = in->vt[0];
  func_00000BF8(&out->vt[1],&in->vt[0],&in->vt[1]);
  func_00000BF8(&out->vt[2],&in->vt[0],&in->vt[2]);
  func_00000BF8(&out->vt[3],&in->vt[0],&in->vt[3]);
  func_00000924(&in->vt[0],&in->vt[1],&out->vt[1],ifo);
  func_000004C4(scratch,ifo,level);

  /********************** 2 nd ***************************/
  out->vt[0]=in->vt[1];
  func_00000BF8(&out->vt[2],&in->vt[1],&in->vt[3]);
  func_00000924(&in->vt[1],&in->vt[3],&out->vt[2],ifo);
  func_000004C4(scratch,ifo,level);

  /********************** 3 rd ***************************/
  out->vt[0]=in->vt[3];
  func_00000BF8(&out->vt[1],&in->vt[3],&in->vt[2]);
  func_00000924(&in->vt[3],&in->vt[2],&out->vt[1],ifo);
  func_000004C4(scratch,ifo,level);

  /********************** 4 th ***************************/
  out->vt[0] =in->vt[2];
  func_00000BF8(&out->vt[2],&in->vt[0],&in->vt[2]);
  func_00000924(&in->vt[2],&in->vt[0],&out->vt[2],ifo);
  func_000004C4(scratch,ifo,level);
}
