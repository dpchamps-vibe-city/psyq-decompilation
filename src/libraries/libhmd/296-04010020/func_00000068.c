#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

/* Layouts and call contract: Sony HMD MIME.H and 04010020.C. */
typedef struct {
    u_short nSize, nNum;
    u_long idxMIMeDiff[0];
} VNMIMePrim;
typedef struct {
    u_short nOnum, nDiffsNum;
    u_long nDflags;
    u_long idxMIMeDiffData[0];
} VNMIMeDiff;
typedef struct {
    u_long idxVstart;
    u_short res, nVnum;
    SVECTOR svDiff[0];
} VNMIMeDiffData;
extern void GsVNMIMeFunc(SVECTOR *vec, SVECTOR *dvec, long np, long weight);

static u_long *func_00000068(GsARGUNIT_VNMIMe *ap, SVECTOR *pVNSect)
{
    long *pMIMePr = ap->mimepr;
    u_long nMIMeNum = ap->mimenum;
    u_long *pMIMeDiffSect = ap->mime_diff_sect;
    SVECTOR *pOrgsVNSect = ap->orgs_vn_sect;
    VNMIMePrim *pPrim = (VNMIMePrim *)ap->primp;
    int num = pPrim->nNum;
    u_long *idxMIMeDiff = pPrim->idxMIMeDiff;
    int i;

    for (i = 0; i < num; i++) {
        VNMIMeDiff *pMIMeDiff = (VNMIMeDiff *)&pMIMeDiffSect[idxMIMeDiff[i]];
        u_short nOnum = pMIMeDiff->nOnum;
        u_short nDiffsNum = pMIMeDiff->nDiffsNum;
        u_long nDflags = pMIMeDiff->nDflags;
        u_long *idxMIMeDiffData = pMIMeDiff->idxMIMeDiffData;
        u_short j, key;
        u_short changed = 0;

        j = 0;
        key = 0;
        if (nDiffsNum != 0) {
            u_long nDiffs = nDiffsNum;
            do {
                long pr;
                if (key >= nMIMeNum) {
                    break;
                }
                if (nDflags & (1 << key)) {
                    pr = pMIMePr[key];
                    if (pr != 0) {
                        VNMIMeDiffData *pMIMeDiffData = (VNMIMeDiffData *)
                            &((u_long *)pMIMeDiff)[idxMIMeDiffData[j]];
                        SVECTOR *pVstart = &pVNSect[pMIMeDiffData->idxVstart];
                        GsVNMIMeFunc(pVstart, pMIMeDiffData->svDiff,
                            pMIMeDiffData->nVnum, pr);
                        changed = 1;
                    }
                    j++;
                }
                key++;
            } while (j < nDiffs);
        }
        if (changed) {
            u_long *idxVNMIMeChanged = (u_long *)&((u_long *)pMIMeDiff)[2 + nDiffsNum];
            int j;
            for (j = 0; j < nOnum; j++) {
                u_short *p = (u_short *)&pMIMeDiffSect[idxVNMIMeChanged[j]];
                *p = 1;
            }
        }
    }
    return &((u_long *)pPrim)[pPrim->nSize];
}
