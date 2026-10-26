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
  GsSEQ *base;
  short *src;
  short *dst;
  short *intr;
} GsARGANIM1;

typedef struct
{
  u_short pidx;
  u_char  tframe;
  u_char  tidx;
} ACTR;

extern void setBetaCof(long ,long ,long ,long ,short *);

/* hokan driver */
int GsU_03010341(GsARGUNIT_ANIM *sp0)
{
  short *dtop;
  u_long ofs0,ofs1;
  GsSEQ *seq;
  GsARGANIM1 *sp;
  long  rframe,tframe;
  long t,i;
  short co[4];
  ACTR *ctop;
  short **cpt;
  
  sp   = (GsARGANIM1 *)(&(sp0->header_size)+sp0->header_size);
  seq  = sp->base;
  ofs0 = ((seq->rewrite_idx)&0xff000000)>>24; 
  ofs1 = (seq->rewrite_idx)&0x00ffffff;
  
  rframe = seq->rframe;
  tframe = seq->tframe;
  
  ctop = (ACTR *)sp0->ctop;	/* control top */
  cpt = (short **)(sp0->ptop+(ctop+seq->start)->pidx);
  
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
  if(tframe == 0) {
      return 1;
  }
  
  t = (tframe-rframe)*0xffff/tframe;
  
  setBetaCof(*cpt[0],*cpt[1],*cpt[2],*cpt[3],co);
  
  dtop = (short *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);
  dtop += 2;
  
  *dtop = ((((((((co[0]*t)>>16)+co[1])*t)>>16)+co[2])*t)>>16)+co[3];
  
  if(sp->intr)
    {
      *sp->intr = *dtop;
    }
  return 0;
}
