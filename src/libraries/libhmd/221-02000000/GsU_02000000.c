#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

u_long *GsU_02000000(GsARGUNIT *sp)
{
	GsARGUNIT_IMAGE	*ap = (GsARGUNIT_IMAGE *)sp;
	u_long		*p;
	int		i;
	int		num;

	num = ((u_short *)ap->primp)[1];
	ap->primp++;

	for (i = 0; i < num; i++) {
		p = ap->primp;
		LoadImage((RECT *)p, ap->imagetop + p[2]);
		ap->primp += 3;
	}
	return(ap->primp);
}
