#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

u_long *GsU_02000001(GsARGUNIT *sp)
{
	GsARGUNIT_IMAGE	*ap = (GsARGUNIT_IMAGE *)sp;
	u_long		*p;
	int		i, n;

	p = ap->primp;
	n = *(u_short *)((char *)p + 2);
	ap->primp = p + 1;
	for (i = 0; i < n; i++) {
		LoadImage((RECT *)ap->primp,
			  ap->imagetop + *(u_long *)((char *)ap->primp + 8));
		ap->primp += 3;
		LoadImage((RECT *)ap->primp,
			  ap->cluttop + *(u_long *)((char *)ap->primp + 8));
		ap->primp += 3;
	}
	return (ap->primp);
}
