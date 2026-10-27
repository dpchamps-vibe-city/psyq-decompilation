#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

#include <inline_c.h>
#include <gtemac.h>
#include <asm.h>

typedef struct {
	u_char		r, g, b, pad;
	long		vpx,vpy,vpz;
	long		vrx,vry,vrz;
} HMD_P_LIGHT;

/*
 * Light primitive (AMBIENT)
 */
u_long *GsU_07000200(GsARGUNIT *sp)
{
	GsARGUNIT_LIGHT		*ap = (GsARGUNIT_LIGHT *)sp;
	HMD_P_LIGHT		*cp = (HMD_P_LIGHT *)
					(ap->lparam + (*(ap->primp+1) >> 16));

	gte_SetBackColor((long)cp->r, (long)cp->g, (long)cp->b);
	return(ap->primp+2);
}
