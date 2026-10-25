#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsSortObject3(GsDOBJ3 *objp, GsOT *ot, int shift)
{
	unsigned long *base;
	unsigned long n;
	int i;

	if ((s32)objp->attribute >= 0) {
		base = objp->base;
		i = 0;
		n = *base;
		base += 1;
		if (n != 0) {
			do {
				unsigned long *p;
				unsigned short type;
				unsigned int t;
				int c;

				p = (unsigned long *)((u8 *)objp->pmd + (*base >> 2 << 2));
				type = *(unsigned short *)((u8 *)p + 2);
				t = type & 0xF;
				c = 0;
				if ((type & 0x20) || ((objp->attribute >> 8) & 1))
					c = 1;
				switch (t) {
				case 0:
					RotPMD_FT3((long *)p, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 1:
					RotPMD_FT4((long *)p, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 2:
					RotPMD_GT3((long *)p, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 3:
					RotPMD_GT4((long *)p, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 4:
					RotPMD_F3((long *)p, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 5:
					RotPMD_F4((long *)p, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 6:
					RotPMD_G3((long *)p, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 7:
					RotPMD_G4((long *)p, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 8:
					RotPMD_SV_FT3((long *)p, (long *)objp->sv, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 9:
					RotPMD_SV_FT4((long *)p, (long *)objp->sv, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 10:
					RotPMD_SV_GT3((long *)p, (long *)objp->sv, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 11:
					RotPMD_SV_GT4((long *)p, (long *)objp->sv, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 12:
					RotPMD_SV_F3((long *)p, (long *)objp->sv, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 13:
					RotPMD_SV_F4((long *)p, (long *)objp->sv, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 14:
					RotPMD_SV_G3((long *)p, (long *)objp->sv, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				case 15:
					RotPMD_SV_G4((long *)p, (long *)objp->sv, (u_long *)ot->org, 0xE - shift, PSDIDX, c);
					break;
				}
				base += 1;
				i += 1;
			} while (i < n);
		}
	}
}
