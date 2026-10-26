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
  short vx0;
  short vx1;
  short vx2;
} MYVECTOR;

typedef struct
{
  GsSEQ *base;
  MYVECTOR *src;
  MYVECTOR *dst;
  short *intr;
} GsARGANIM1;

extern void setBezierCof(long ,long ,long ,long ,short *);

/* hokan driver */
int GsU_03010221(GsARGUNIT_ANIM *sp0)
{
  short *dtop;
  u_long ofs0,ofs1;
  GsSEQ *seq;
  GsARGANIM1 *sp;
  long  rframe,tframe;
  long t;
  short co[4];

  sp   = (GsARGANIM1 *)(&(sp0->header_size)+sp0->header_size);
  seq  = sp->base;
  if(seq->tframe==0)
      return 1;
  ofs0 = ((seq->rewrite_idx)&0xff000000)>>24;
  ofs1 = (seq->rewrite_idx)&0x00ffffff;

  rframe = seq->rframe;
  tframe = seq->tframe;

  t = (tframe-rframe)*0xffff/tframe;

  setBezierCof(sp->src->vx0,sp->src->vx1,sp->src->vx2,sp->dst->vx0,co);

  dtop = (short *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);
  dtop += 1;
  *dtop = ((((((((co[0]*t)>>16)+co[1])*t)>>16)+co[2]) *t)>>16)+co[3];

  if(sp->intr)
    {
      *sp->intr = *dtop;
    }

  return 0;
}
