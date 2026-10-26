/* $PSLibId: Run-time Library Release 4.4$ */

/* 
 *	Copyright(C) 1998 Sony Computer Entertainment Inc.
 *  	All rights reserved. 
 */


#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <inline_c.h>
#include <gtemac.h>
#include <asm.h>
#include <libgs.h>
#include <libhmd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libhmd_animation_sequence.h"


u_long *
GsU_03000000(GsARGUNIT_ANIM *sp)	/* update driver */
{
	int	size, wnum, i;
	int	(*func)(GsARGUNIT_ANIM *);
	DWORD	*htop = sp->htop;	/* hokan top */
	DWORD	*ctop = sp->ctop;	/* control top */
	DWORD	*ptop = sp->ptop;	/* parameter top */
	DWORD	*base;

	wnum = (*(sp->primp)) >> 16;
	for (base = &sp->primp[1], i = 0;
			i < wnum; i++, base += base[1] & 0xffff) {
		GsSEQ	*seq = (GsSEQ *)base;
		GsARGANIM_OPAQ	*parm;
		int	dir;
      
		if (seq->aframe == 0) {
			continue;
		} else if(seq->aframe != 0xffff) {
			seq->aframe--;
		}
      
		dir = seq->speed < 0 ? -1 : 1;
      
		/* to treat overshoot in the last interpolation */
		if (seq->rframe == 0x7000) {
			dir = 1;
			seq->rframe = 0;
		} else if (seq->rframe == 0x6000) {
			dir = -1;
			seq->rframe = 0;
		}
      
START:
		if (seq->rframe == 0 || seq->tframe ==0) {
			/* key frame switching */
			seq->traveling = 0;
			if (dir == 1) {
				if (IS_NOT_NORM(ctop[seq->ti])
				&& (seq->ti = get_tctr(
						seq->ti + dir,
						ctop, seq)) == 0xffff) {
					seq->aframe = 0;
					continue;
				}
				seq->ci = seq->ti;
				if ((seq->ti = get_tctr(
						seq->ci + dir,
						ctop, seq)) == 0xffff) {
					seq->aframe = 0;
					continue;
				}
			} else {
				if (IS_NOT_NORM(ctop[seq->ci])
				&& (seq->ci = get_tctr(
						seq->ci + dir,
						ctop, seq))==0xffff) {
					seq->aframe = 0;
					continue;
				}
				seq->ti = seq->ci;
				if ((seq->ci = get_tctr(
						seq->ti + dir,
						ctop, seq))==0xffff) {
					seq->aframe = 0;
					continue;
				}
			}
			if (dir == 1) {
				seq->tframe = TFRAME(ctop[seq->ti]) << 4;
				seq->rframe = seq->tframe - seq->rframe;
			} else {
				seq->tframe = TFRAME(ctop[seq->ti]) << 4;
			}
		}
      
		(u_long)func = htop[TYPE_IDX(ctop[seq->ti]) + 1];
		parm = (GsARGANIM_OPAQ *)
			(&(sp->header_size) + sp->header_size);
		parm->base = base;
		parm->src  = &ptop[PARAM_IDX(ctop[seq->ci])];
		parm->dst  = &ptop[PARAM_IDX(ctop[seq->ti])];
		if (seq->ii != 0xffff) {
			parm->intr = &ptop[PARAM_IDX(ctop[seq->ii])];
		} else {
			parm->intr = 0;
		}
      
		if (seq->ci != seq->ti) {
			if (func(sp) == 1) {
				seq->rframe = 0;
				goto START;
			}
	  
			if (TFRAME(ctop[seq->ti]) == 0) { /* 0 tframe */
				goto START;
			}
      
			seq->rframe -= seq->speed;
      
			if (dir == 1 && seq->rframe < 0) {
				seq->rframe = 0x7000;
			} else if (dir == -1 && (seq->rframe >= seq->tframe)) {
				seq->rframe = 0x6000;
			}
		}
	}
	size = (*(sp->primp)) & 0xffff;

	return sp->primp + size;
}
