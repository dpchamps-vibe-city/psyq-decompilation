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
}  MYVECTOR;

typedef struct
{
  u_short pidx;
  u_char  tframe;
  u_char  tidx;
} ACTR;

typedef struct
{
  GsSEQ *base;
  MYVECTOR *src;
  MYVECTOR *dst;
  MYVECTOR *intr;
} GsARGANIM2;


extern void setBetaCof(long ,long ,long ,long ,short *);

int
GsU_0300103b(GsARGUNIT_ANIM *sp0)
{
  GsCOORDUNIT *dtop;
  u_long ofs0,ofs1;
  GsSEQ *seq;
  GsARGANIM2 *sp;
  long  rframe,tframe;
  long t;
  short co[2][3][4];
  int i;
  ACTR *ctop;
  MYVECTOR **cpt;

  sp   = (GsARGANIM2 *)(&(sp0->header_size)+sp0->header_size);
  seq  = sp->base;

  ofs0 = ((seq->rewrite_idx)&0xff000000)>>24;
  ofs1 = (seq->rewrite_idx)&0x00ffffff;

  rframe = seq->rframe;
  tframe = seq->tframe;

  ctop = (ACTR *)sp0->ctop;	/* control top */
  cpt = (MYVECTOR **)(sp0->ptop+(ctop+seq->start)->pidx);

  if(seq->speed>=0) {
      if(sp->src == cpt[1]) {
	  cpt[2] = cpt[1];
	  cpt[1] = 0;
	  return 1;
      }
      if(tframe == 0 || rframe == tframe) {
	  cpt[0] = cpt[1];
	  cpt[1] = cpt[2];
	  cpt[2] = sp->src;
	  cpt[3] = sp->dst;
	  for(i=0;i<4;i++)
	      if(cpt[i] == 0)
		  return 1;
      }
  }
  if(seq->speed<0) {
      if(sp->src == cpt[1]) {
	  cpt[1] = cpt[2];
	  cpt[2] = 0;
	  return 1;
      }
      if(tframe == 0 || rframe == 0) {
	  cpt[3] = cpt[2];
	  cpt[2] = cpt[1];
	  cpt[0] = sp->src;
	  cpt[1] = sp->dst;
	  for(i=0;i<4;i++)
	      if(cpt[i] == 0)
		  return 1;
      }
  }
  if(seq->tframe==0)
      return 1;

  t = (tframe-rframe)*0xffff/tframe;

  setBetaCof(cpt[0]->vx0,cpt[1]->vx0,cpt[2]->vx0,cpt[3]->vx0,co[0][0]);
  setBetaCof(cpt[0]->vy0,cpt[1]->vy0,cpt[2]->vy0,cpt[3]->vy0,co[0][1]);
  setBetaCof(cpt[0]->vz0,cpt[1]->vz0,cpt[2]->vz0,cpt[3]->vz0,co[0][2]);
  setBetaCof(cpt[0]->vx1,cpt[1]->vx1,cpt[2]->vx1,cpt[3]->vx1,co[1][0]);
  setBetaCof(cpt[0]->vy1,cpt[1]->vy1,cpt[2]->vy1,cpt[3]->vy1,co[1][1]);
  setBetaCof(cpt[0]->vz1,cpt[1]->vz1,cpt[2]->vz1,cpt[3]->vz1,co[1][2]);

  dtop = (GsCOORDUNIT *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);
  for(i=0;i<3;i++)
      dtop->matrix.t[i] = ((((((((co[0][i][0]*t)>>16)+co[0][i][1])*t)>>16)+co[0][i][2])*t)>>16)+co[0][i][3];
  dtop->rot.vx = ((((((((co[1][0][0]*t)>>16)+co[1][0][1])*t)>>16)+co[1][0][2])
		   *t)>>16)+co[1][0][3];
  dtop->rot.vy = ((((((((co[1][1][0]*t)>>16)+co[1][1][1])*t)>>16)+co[1][1][2])
		   *t)>>16)+co[1][1][3];
  dtop->rot.vz = ((((((((co[1][2][0]*t)>>16)+co[1][2][1])*t)>>16)+co[1][2][2])
		   *t)>>16)+co[1][2][3];

  RotMatrixXZY(&dtop->rot,&dtop->matrix);
  dtop->flg = 0;

  if(sp->intr) {
      sp->intr->vx0 = dtop->matrix.t[0];
      sp->intr->vy0 = dtop->matrix.t[1];
      sp->intr->vz0 = dtop->matrix.t[2];
      sp->intr->vx1 = dtop->rot.vx;
      sp->intr->vy1 = dtop->rot.vy;
      sp->intr->vz1 = dtop->rot.vz;
    }

  return 0;
}
