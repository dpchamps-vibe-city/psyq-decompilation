/* $PSLibId: Run-time Library Release 4.4$ */

/*
 *	Copyright(C) 1998 Sony Computer Entertainment Inc.
 *  	All rights reserved.
 */

#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

typedef struct
{
  GsSEQ *base;
  short *src;
  short *dst;
  short *intr;
} GsARGANIM2;

/* general hokan driver (16bit) */
int GsU_03010121(GsARGUNIT_ANIM *sp0)
{
  short  *dtop;
  u_long ofs0,ofs1;
  GsSEQ  *seq;
  GsARGANIM2 *sp;
  long  rframe,tframe;

  sp   = (GsARGANIM2 *)(&(sp0->header_size)+sp0->header_size);
  seq  = sp->base;
  if(seq->tframe==0)
      return 1;
  ofs0 = ((seq->rewrite_idx)&0xff000000)>>24;
  ofs1 = (seq->rewrite_idx)&0x00ffffff;

  rframe = seq->rframe;
  tframe = seq->tframe;

  dtop = (short *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);
  dtop[1] = (*(sp->src)*rframe+*(sp->dst)*(tframe-rframe))/tframe;

  if(sp->intr)
      {
	  *sp->intr = dtop[1];
      }

  return 0;
}
