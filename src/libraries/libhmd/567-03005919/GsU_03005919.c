#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

typedef struct
{
  short vx,vy,vz;
  short rx,ry,rz;
  short scale;
} LECTOR;

typedef struct
{
  GsSEQ *base;
  LECTOR *src;
  LECTOR *dst;
  LECTOR *intr;
} GsARGANIM4;

int
GsU_03005919(GsARGUNIT_ANIM *sp0)
{
  GsCOORDUNIT *dtop;
  u_long ofs0,ofs1;
  GsSEQ *seq;
  GsARGANIM4 *sp;
  long  rframe,tframe;
  VECTOR scale;

  sp   = (GsARGANIM4 *)(&(sp0->header_size)+sp0->header_size);
  seq  = sp->base;
  if(seq->tframe==0)
      return 1;
  ofs0 = ((seq->rewrite_idx)&0xff000000)>>24;
  ofs1 = (seq->rewrite_idx)&0x00ffffff;

  rframe = seq->rframe;
  tframe = seq->tframe;

  dtop = (GsCOORDUNIT *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);
  dtop->matrix.t[0] = (((long)sp->src->vx)*rframe+((long)sp->dst->vx)*(tframe-rframe))/tframe;
  dtop->matrix.t[1] = (((long)sp->src->vy)*rframe+((long)sp->dst->vy)*(tframe-rframe))/tframe;
  dtop->matrix.t[2] = (((long)sp->src->vz)*rframe+((long)sp->dst->vz)*(tframe-rframe))/tframe;
  dtop->rot.vx = (((long)sp->src->rx)*rframe+((long)sp->dst->rx)*(tframe-rframe))/tframe;
  dtop->rot.vy = (((long)sp->src->ry)*rframe+((long)sp->dst->ry)*(tframe-rframe))/tframe;
  dtop->rot.vz = (((long)sp->src->rz)*rframe+((long)sp->dst->rz)*(tframe-rframe))/tframe;
  RotMatrixZYX(&dtop->rot,&dtop->matrix);
  scale.vx = scale.vy = scale.vz =
    (((long)sp->src->scale)*rframe+((long)sp->dst->scale)*(tframe-rframe))/tframe;
  ScaleMatrix(&dtop->matrix,&scale);

  dtop->flg = 0;

  if(sp->intr)
    {
      sp->intr->vx = dtop->matrix.t[0];
      sp->intr->vy = dtop->matrix.t[1];
      sp->intr->vz = dtop->matrix.t[2];
      sp->intr->rx = dtop->rot.vx;
      sp->intr->ry = dtop->rot.vy;
      sp->intr->rz = dtop->rot.vz;
      sp->intr->scale = scale.vx;
    }
  return 0;
}
