INCLUDE_ASM("build/libraries/nonmatchings/libgs_94", GsSortObject4);


/* PARKED by /auto_decompilation_loop on 2026-10-25T07:50:51.555Z.
 * Reason: asm-needs-human-approval.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgs_94::GsSortObject4.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <stdio.h>

extern _GsFCALL D_000009B8;

/* Primitive header: h at 0, attribute at 2 (code is the high byte). */
typedef struct {
    u_short h;
    u_short attribute;
} GsTMDPrim;

void GsSortObject4(GsDOBJ2 *objp, GsOT *ot, int shift, u_long *scratch) {
    struct TMD_STRUCT *tmd;
    GsTMDPrim *prim;
    u_long primn;
    u_long *vp;
    u_long *np;
    u_long div;
    u_long col;
    u_long code;

    if ((long) objp->attribute < 0) {
        return;
    }

    GsMATE_C = objp->attribute & 7;
    GsLMODE = (objp->attribute >> 3) & 3;
    GsLIGNR = (objp->attribute >> 5) & 1;
    GsLIOFF = (objp->attribute >> 6) & 1;
    GsNDIV = (objp->attribute >> 9) & 7;
    GsTON = (objp->attribute >> 30) & 1;

    div = 1;
    if (GsNDIV != 0) {
        scratch[0] = GsNDIV;
        scratch[1] = HWD0;
        scratch[2] = VWD0;
    } else {
        div = 0;
    }

    if (GsLIOFF == 1) {
        col = 2;
    } else {
        col = 0;
        if (GsLIGNR == 0) {
            if (GsLIGHT_MODE & 1) {
                col = 1;
            }
        } else if (GsLIGNR == 1) {
            if (GsLMODE & 1) {
                col = 1;
            }
        }
    }

    tmd = (struct TMD_STRUCT *) objp->tmd;
    prim = (GsTMDPrim *) tmd->primtop;
    primn = tmd->primn;
    vp = tmd->vertop;
    np = tmd->nortop;

    while (primn != 0) {
        code = ((u_char *) prim)[3] & 0xFD;
        switch (code) {
        case GPU_COM_F3:
            if (prim->attribute & GsTMDFlagGRD) {
                GsOUT_PACKET_P = (*D_000009B8.f3g[col])(prim, vp, np, GsOUT_PACKET_P,
                                                        prim->h, shift, ot, scratch);
                primn -= prim->h;
                prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_F3G));
            } else {
                GsOUT_PACKET_P = (*D_000009B8.f3[div][col])(prim, vp, np, GsOUT_PACKET_P,
                                                            prim->h, shift, ot, scratch);
                primn -= prim->h;
                prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_F3));
            }
            break;
        case GPU_COM_TF3:
            GsOUT_PACKET_P = (*D_000009B8.tf3[div][col])(prim, vp, np, GsOUT_PACKET_P,
                                                         prim->h, shift, ot, scratch);
            primn -= prim->h;
            prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_TF3));
            break;
        case GPU_COM_G3:
            if (prim->attribute & GsTMDFlagGRD) {
                GsOUT_PACKET_P = (*D_000009B8.g3g[col])(prim, vp, np, GsOUT_PACKET_P,
                                                        prim->h, shift, ot, scratch);
                primn -= prim->h;
                prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_G3G));
            } else {
                GsOUT_PACKET_P = (*D_000009B8.g3[div][col])(prim, vp, np, GsOUT_PACKET_P,
                                                            prim->h, shift, ot, scratch);
                primn -= prim->h;
                prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_G3));
            }
            break;
        case GPU_COM_TG3:
            GsOUT_PACKET_P = (*D_000009B8.tg3[div][col])(prim, vp, np, GsOUT_PACKET_P,
                                                         prim->h, shift, ot, scratch);
            primn -= prim->h;
            prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_TG3));
            break;
        case GPU_COM_F4:
            if (prim->attribute & GsTMDFlagGRD) {
                GsOUT_PACKET_P = (*D_000009B8.f4g[col])(prim, vp, np, GsOUT_PACKET_P,
                                                        prim->h, shift, ot, scratch);
                primn -= prim->h;
                prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_F4G));
            } else {
                GsOUT_PACKET_P = (*D_000009B8.f4[div][col])(prim, vp, np, GsOUT_PACKET_P,
                                                            prim->h, shift, ot, scratch);
                primn -= prim->h;
                prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_F4));
            }
            break;
        case GPU_COM_TF4:
            GsOUT_PACKET_P = (*D_000009B8.tf4[div][col])(prim, vp, np, GsOUT_PACKET_P,
                                                         prim->h, shift, ot, scratch);
            primn -= prim->h;
            prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_TF4));
            break;
        case GPU_COM_G4:
            if (prim->attribute & GsTMDFlagGRD) {
                GsOUT_PACKET_P = (*D_000009B8.g4g[col])(prim, vp, np, GsOUT_PACKET_P,
                                                        prim->h, shift, ot, scratch);
                primn -= prim->h;
                prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_G4G));
            } else {
                GsOUT_PACKET_P = (*D_000009B8.g4[div][col])(prim, vp, np, GsOUT_PACKET_P,
                                                            prim->h, shift, ot, scratch);
                primn -= prim->h;
                prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_G4));
            }
            break;
        case GPU_COM_TG4:
            GsOUT_PACKET_P = (*D_000009B8.tg4[div][col])(prim, vp, np, GsOUT_PACKET_P,
                                                         prim->h, shift, ot, scratch);
            primn -= prim->h;
            prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_TG4));
            break;
        case GPU_COM_NF3:
            GsOUT_PACKET_P = (*D_000009B8.nf3[div])(prim, vp, GsOUT_PACKET_P,
                                                    prim->h, shift, ot, scratch);
            primn -= prim->h;
            prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_NF3));
            break;
        case GPU_COM_NF4:
            GsOUT_PACKET_P = (*D_000009B8.nf4[div])(prim, vp, GsOUT_PACKET_P,
                                                    prim->h, shift, ot, scratch);
            primn -= prim->h;
            prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_NF4));
            break;
        case GPU_COM_NG3:
            GsOUT_PACKET_P = (*D_000009B8.ng3[div])(prim, vp, GsOUT_PACKET_P,
                                                    prim->h, shift, ot, scratch);
            primn -= prim->h;
            prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_NG3));
            break;
        case GPU_COM_NTF3:
            GsOUT_PACKET_P = (*D_000009B8.ntf3[div])(prim, vp, GsOUT_PACKET_P,
                                                     prim->h, shift, ot, scratch);
            primn -= prim->h;
            prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_TNF3));
            break;
        case GPU_COM_NTG3:
            GsOUT_PACKET_P = (*D_000009B8.ntg3[div])(prim, vp, GsOUT_PACKET_P,
                                                     prim->h, shift, ot, scratch);
            primn -= prim->h;
            prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_TNG3));
            break;
        case GPU_COM_NG4:
            GsOUT_PACKET_P = (*D_000009B8.ng4[div])(prim, vp, GsOUT_PACKET_P,
                                                    prim->h, shift, ot, scratch);
            primn -= prim->h;
            prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_NG4));
            break;
        case GPU_COM_NTF4:
            GsOUT_PACKET_P = (*D_000009B8.ntf4[div])(prim, vp, GsOUT_PACKET_P,
                                                     prim->h, shift, ot, scratch);
            primn -= prim->h;
            prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_TNF4));
            break;
        case GPU_COM_NTG4:
            GsOUT_PACKET_P = (*D_000009B8.ntg4[div])(prim, vp, GsOUT_PACKET_P,
                                                     prim->h, shift, ot, scratch);
            primn -= prim->h;
            prim = (GsTMDPrim *) ((u_char *) prim + prim->h * sizeof(TMD_P_TNG4));
            break;
        default:
            printf("non supported code %x %x\n", code, prim);
            break;
        }
    }
}
#endif
