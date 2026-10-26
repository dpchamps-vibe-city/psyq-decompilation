#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

typedef struct {
	u_short	nSize, n;
	u_long	idxDiff[0];
} RstVNMIMePrim;

extern void GsRestoreOrgsVNMIMe(RstVNMIMePrim *, u_long *, SVECTOR *, SVECTOR *);

u_long *
GsU_04010028(GsARGUNIT *sp)
{
	GsARGUNIT_RstVNMIMe	*ap = (GsARGUNIT_RstVNMIMe *)sp;
	u_long		*pMIMeDiffSect	= ap->mime_diff_sect;
	SVECTOR		*pOrgsVNSect	= ap->orgs_vn_sect;
	SVECTOR		*pVNSect	= ap->vert_sect;
	RstVNMIMePrim	*pPrim		= (RstVNMIMePrim *)ap->primp;

	GsRestoreOrgsVNMIMe(pPrim,
		pMIMeDiffSect,
		pOrgsVNSect,
		pVNSect);

	return &((u_long *)pPrim)[pPrim->nSize];
}
