/* $PSLibId: Run-time Library Release 4.4$ */

/*
 *	Copyright(C) 1998 Sony Computer Entertainment Inc.
 *  	All rights reserved.
 */
#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

typedef struct
{
    u_char vx0,vy0,vz0;
    u_char vx1,vy1,vz1;
    u_char vx2,vy2,vz2;
} MYVECTOR;

typedef struct
{
  GsSEQ *base;
  MYVECTOR *src;
  MYVECTOR *dst;
  u_char *intr;
} GsARGANIM1;

extern void setBezierCof(long ,long ,long ,long ,short *);

/* hokan driver */
int GsU_03010272(GsARGUNIT_ANIM *sp0)
{
  u_char *dtop;
  u_long ofs0,ofs1;
  GsSEQ *seq;
  GsARGANIM1 *sp;
  long  rframe,tframe;
  long t;
  short co[3][4];

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

  dtop = (u_char *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);

  dtop[0] = ((((((((co[0][0]*t)>>16)+co[0][1])*t)>>16)+co[0][2]) *t)>>16)+co[0][3];
  dtop[1] = ((((((((co[1][0]*t)>>16)+co[1][1])*t)>>16)+co[1][2]) *t)>>16)+co[1][3];
  dtop[2] = ((((((((co[2][0]*t)>>16)+co[2][1])*t)>>16)+co[2][2]) *t)>>16)+co[2][3];

  if(sp->intr)
    {
      sp->intr[0] = dtop[0];
      sp->intr[1] = dtop[1];
      sp->intr[2] = dtop[2];
    }

  return 0;
}
