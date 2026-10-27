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
    short rx,ry,rz;
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


extern void setBezierCof(long ,long ,long ,long ,short *);
extern void setBetaCof(long ,long ,long ,long ,short *);

int
GsU_0300103a(GsARGUNIT_ANIM *sp0)
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

  setBezierCof((long)sp->src->vx0,(long)sp->src->vx1,(long)sp->src->vx2,
	       (long)sp->dst->vx0,co[0][0]);
  setBezierCof((long)sp->src->vy0,(long)sp->src->vy1,(long)sp->src->vy2,
	       (long)sp->dst->vy0,co[0][1]);
  setBezierCof((long)sp->src->vz0,(long)sp->src->vz1,(long)sp->src->vz2,
	       (long)sp->dst->vz0,co[0][2]);
  setBetaCof(cpt[0]->rx,cpt[1]->rx,cpt[2]->rx,cpt[3]->rx,co[1][0]);
  setBetaCof(cpt[0]->ry,cpt[1]->ry,cpt[2]->ry,cpt[3]->ry,co[1][1]);
  setBetaCof(cpt[0]->rz,cpt[1]->rz,cpt[2]->rz,cpt[3]->rz,co[1][2]);

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
      sp->intr->rx = dtop->rot.vx;
      sp->intr->ry = dtop->rot.vy;
      sp->intr->rz = dtop->rot.vz;
    }

  return 0;
}
