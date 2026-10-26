#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

typedef struct {
	u_short	nSize, nNum;
	u_long	idxMIMeDiff[0];
} JntMIMePrim;

typedef struct {
	short	dvx, dvy, dvz;
	u_short	dtp;
	long	dtx, dty, dtz;
} JntMIMeDiffData;

typedef struct {
	u_short	nCoordId, nDiffsNum;
	u_long	nDflags;
	JntMIMeDiffData	jntMIMeDiffData[0];
} JntMIMeDiff;

typedef struct {
	short	dvx, dvy, dvz;
	u_short	changed;
	long	dtx, dty, dtz;
} RstRPYMIMeDiffData;

/*
	RstJntRPYMIMe primitive driver.
*/

u_long *
GsU_04010019(GsARGUNIT *sp)
{
	GsARGUNIT_RstJntMIMe	*ap = (GsARGUNIT_RstJntMIMe *)sp;
	u_long		*pCoordSect	= ap->coord_sect;
	GsCOORDUNIT	*pCoord0	= (GsCOORDUNIT *)(pCoordSect + 1);
	u_long		*pMIMeDiffSect	= ap->mime_diff_sect;
	JntMIMePrim	*pPrim		= (JntMIMePrim *)ap->primp;
	int		num = pPrim->nNum;
	u_long		*idxMIMeDiff = pPrim->idxMIMeDiff;
	int		i;

	for (i = 0; i < num; i++) {
		/*
			For each JntMIMeDiff ptrs...
		*/
		JntMIMeDiff	*pMIMeDiff
			= (JntMIMeDiff *)&pMIMeDiffSect[idxMIMeDiff[i]];
		u_short	nCoordId = pMIMeDiff->nCoordId;
		u_short	nDiffsNum = pMIMeDiff->nDiffsNum;
		JntMIMeDiffData	*jntMIMeDiffData = pMIMeDiff->jntMIMeDiffData;
		RstRPYMIMeDiffData	*pRst
			= (RstRPYMIMeDiffData *)&jntMIMeDiffData[nDiffsNum];

		if (pRst->changed) {
			GsCOORDUNIT	*pCoord = &pCoord0[nCoordId];

			pCoord->rot.vx = pRst->dvx;
			pCoord->rot.vy = pRst->dvy;
			pCoord->rot.vz = pRst->dvz;
			pCoord->matrix.t[0] = pRst->dtx;
			pCoord->matrix.t[1] = pRst->dty;
			pCoord->matrix.t[2] = pRst->dtz;
			pRst->changed = 0;

			pCoord->flg = 0;
		}
	}

	/*
		Return the next primitive.
	*/
	return &((u_long *)pPrim)[pPrim->nSize];
}
