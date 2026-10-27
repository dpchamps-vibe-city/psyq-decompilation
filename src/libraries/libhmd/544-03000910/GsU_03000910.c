#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

typedef struct
{
  short	vx, vy;
  short	vz, scale;
} SSVECTOR;

typedef struct 
{
  GsSEQ *base;
  SSVECTOR *src;
  SSVECTOR *dst;
  SSVECTOR *intr;
} GsARGANIM2;

int
GsU_03000910(GsARGUNIT_ANIM *sp0)
{
  GsCOORDUNIT *dtop;
  u_long ofs0,ofs1;
  GsSEQ *seq;
  GsARGANIM2 *sp;
  long  rframe,tframe;
  VECTOR scale;
  
  sp   = (GsARGANIM2 *)(&(sp0->header_size)+sp0->header_size);
  seq  = sp->base;
  if(seq->tframe==0)
      return 1;
  ofs0 = ((seq->rewrite_idx)&0xff000000)>>24;
  ofs1 = (seq->rewrite_idx)&0x00ffffff;

  rframe = seq->rframe;
  tframe = seq->tframe;
  
  dtop = (GsCOORDUNIT *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);
  dtop->rot.vx = (((long)sp->src->vx)*rframe+((long)sp->dst->vx)*(tframe-rframe))/tframe;
  dtop->rot.vy = (((long)sp->src->vy)*rframe+((long)sp->dst->vy)*(tframe-rframe))/tframe;
  dtop->rot.vz = (((long)sp->src->vz)*rframe+((long)sp->dst->vz)*(tframe-rframe))/tframe;
  RotMatrix(&dtop->rot,&dtop->matrix);
  scale.vx = scale.vy = scale.vz =
    (sp->src->scale*rframe+sp->dst->scale*(tframe-rframe))/tframe;
  ScaleMatrix(&dtop->matrix,&scale);
  
  dtop->flg = 0;
  
  if(sp->intr)
    {
      sp->intr->vx = dtop->rot.vx;
      sp->intr->vy = dtop->rot.vy;
      sp->intr->vz = dtop->rot.vz;
      sp->intr->scale = scale.vx;
    }
  return 0;
}
