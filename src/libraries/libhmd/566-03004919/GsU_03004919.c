#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

typedef struct
{
  short vx,vy;
  short vz,rx;
  short ry,rz;
  short scale;
} LECTOR;

typedef struct
{
  GsSEQ *base;
  LECTOR *src;
  LECTOR *dst;
  LECTOR *intr;
} GsARGANIM;


int
GsU_03004919(GsARGUNIT_ANIM *sp0)
{
  GsCOORDUNIT *dtop;
  u_long ofs0,ofs1;
  GsSEQ *seq;
  GsARGANIM *sp;
  long  rframe,tframe;
  VECTOR scale;

  sp   = (GsARGANIM *)(&(sp0->header_size)+sp0->header_size);
  seq  = sp->base;
  if(seq->tframe==0)
      return 1;
  ofs0 = ((seq->rewrite_idx)&0xff000000)>>24;
  ofs1 = (seq->rewrite_idx)&0x00ffffff;

  rframe = seq->rframe;
  tframe = seq->tframe;

  dtop = (GsCOORDUNIT *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);
  dtop->matrix.t[0] = (sp->src->vx*rframe+sp->dst->vx*(tframe-rframe))/tframe;
  dtop->matrix.t[1] = (sp->src->vy*rframe+sp->dst->vy*(tframe-rframe))/tframe;
  dtop->matrix.t[2] = (sp->src->vz*rframe+sp->dst->vz*(tframe-rframe))/tframe;
  dtop->rot.vx = (sp->src->rx*rframe+sp->dst->rx*(tframe-rframe))/tframe;
  dtop->rot.vy = (sp->src->ry*rframe+sp->dst->ry*(tframe-rframe))/tframe;
  dtop->rot.vz = (sp->src->rz*rframe+sp->dst->rz*(tframe-rframe))/tframe;
  RotMatrixZXY(&dtop->rot,&dtop->matrix);

  scale.vx = scale.vy = scale.vz =
    (sp->src->scale*rframe+sp->dst->scale*(tframe-rframe))/tframe;
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
