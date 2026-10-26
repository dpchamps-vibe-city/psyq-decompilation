#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000810();
static int func_00000940();
static void func_00000A8C();

static void func_00000430(u_long *scratch, GsADIV_GT3 *ifo, int level)
{
  register GsADIV_P_GT3 *in,*out;
  register POLY_GT3 *si;
  VECTOR   tmp;

  in  = (GsADIV_P_GT3 *)scratch;
  scratch += (sizeof(GsADIV_P_GT3)/4);
  out = (GsADIV_P_GT3 *)scratch;

  gte_ldv3(&in->vt[0].vx,&in->vt[1].vx,&in->vt[2].vx);
  gte_rtpt();

  si = &ifo->si;
  *(u_short *)&si->u0 = *(u_short *)&in->vt[0].tu;
  *(u_short *)&si->u1 = *(u_short *)&in->vt[1].tu;
  *(u_short *)&si->u2 = *(u_short *)&in->vt[2].tu;
  gte_stflg(&ifo->flg);

  gte_stsxy3_gt3((long *)si);
  gte_avsz3();
  gte_stszotz(&ifo->otz);

  if(func_00000940(si,ifo))
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
      *(ifo->pk+1) = *(u_long *)&in->vt[0].col.r;
      *(ifo->pk+2) = *(u_long *)((u_long *)si+2);
      *(ifo->pk+3) = *(u_long *)((u_long *)si+3);
      *(ifo->pk+4) = *(u_long *)&in->vt[1].col.r;
      *(ifo->pk+5) = *(u_long *)((u_long *)si+5);
      *(ifo->pk+6) = *(u_long *)((u_long *)si+6);
      *(ifo->pk+7) = *(u_long *)&in->vt[2].col.r;
      *(ifo->pk+8) = *(u_long *)((u_long *)si+8);
      *(ifo->pk+9) = *(u_long *)((u_long *)si+9);
      ifo->tag = ifo->org+(ifo->otz>>ifo->shift);
      *(u_long *)ifo->pk  = (*ifo->tag&0x00ffffff)|0x09000000;
      *ifo->tag = (u_long)ifo->pk&0x00ffffff;
      ifo->pk += sizeof(POLY_GT3)/4;
      return;
    }

  level++;

  /********************** 1 st ***************************/
  out->vt[0] = in->vt[0];
  func_00000A8C(&out->vt[1],&in->vt[0],&in->vt[1]);
  func_00000A8C(&out->vt[2],&in->vt[0],&in->vt[2]);
  func_00000810(&in->vt[0],&in->vt[1],&out->vt[1],ifo);
  func_00000430(scratch,ifo,level);

  /********************** 2 nd ***************************/
  func_00000A8C(&out->vt[0],&in->vt[1],&in->vt[2]);
  func_00000430(scratch,ifo,level);

  /********************** 3 rd ***************************/
  out->vt[2]=in->vt[1];
  func_00000810(&in->vt[1],&in->vt[2],&out->vt[0],ifo);
  func_00000430(scratch,ifo,level);

  /********************** 4 th ***************************/
  out->vt[1] =in->vt[2];
  func_00000A8C(&out->vt[2],&in->vt[0],&in->vt[2]);
  func_00000810(&in->vt[2],&in->vt[0],&out->vt[2],ifo);
  func_00000430(scratch,ifo,level);
}
