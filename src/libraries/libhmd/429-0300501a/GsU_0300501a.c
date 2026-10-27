#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

typedef struct
{
  short vx0,vy0,vz0;
  short vx1,vy1,vz1;
  short vx2,vy2,vz2;
  short rx, ry, rz;
} LECTOR;

typedef struct
{
  GsSEQ *base;
  LECTOR *src;
  LECTOR *dst;
  LECTOR *intr;
} GsARGANIM1;

extern void setBezierCof(int ,int ,int ,int ,short *);

int
GsU_0300501a(GsARGUNIT_ANIM *sp0)
{
  GsCOORDUNIT *dtop;
  u_long ofs0,ofs1;
  GsSEQ *seq;
  GsARGANIM1 *sp;
  long  rframe,tframe;
  long t;
  short co[3][4];
  int i;

  sp   = (GsARGANIM1 *)(&(sp0->header_size)+sp0->header_size);
  seq  = sp->base;
  if(seq->tframe==0)
      return 1;
  ofs0 = ((seq->rewrite_idx)&0xff000000)>>24;
  ofs1 = (seq->rewrite_idx)&0x00ffffff;

  rframe = seq->rframe;
  tframe = seq->tframe;

  t = (tframe-rframe)*0xffff/tframe;

  setBezierCof((long)sp->src->vx0,(long)sp->src->vx1,(long)sp->src->vx2,
	       (long)sp->dst->vx0,co[0]);
  setBezierCof((long)sp->src->vy0,(long)sp->src->vy1,(long)sp->src->vy2,
	       (long)sp->dst->vy0,co[1]);
  setBezierCof((long)sp->src->vz0,(long)sp->src->vz1,(long)sp->src->vz2,
	       (long)sp->dst->vz0,co[2]);

  dtop = (GsCOORDUNIT *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);

    for(i=0;i<3;i++)
      dtop->matrix.t[i] = ((((((((co[i][0]*t)>>16)+co[i][1])*t)>>16)+co[i][2])
	  *t)>>16)+co[i][3];

  dtop->rot.vx = (((long)sp->src->rx)*rframe+((long)sp->dst->rx)*(tframe-rframe))/tframe;
  dtop->rot.vy = (((long)sp->src->ry)*rframe+((long)sp->dst->ry)*(tframe-rframe))/tframe;
  dtop->rot.vz = (((long)sp->src->rz)*rframe+((long)sp->dst->rz)*(tframe-rframe))/tframe;
  RotMatrixZYX(&dtop->rot,&dtop->matrix);

  dtop->flg = 0;

  if(sp->intr)
    {
      sp->intr->vx0 = dtop->matrix.t[0];
      sp->intr->vy0 = dtop->matrix.t[1];
      sp->intr->vz0 = dtop->matrix.t[2];
      sp->intr->rx = dtop->rot.vx;
      sp->intr->ry = dtop->rot.vy;
      sp->intr->rz = dtop->rot.vz;
    }

  return 0;
}
