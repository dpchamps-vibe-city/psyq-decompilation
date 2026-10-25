#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <stdio.h>

/* TMD primitive header: h at offset 0, attribute at offset 2.
 * The dispatch code is the high byte of attribute (prim[3]). */
typedef struct {
	u_short h;
	u_short attribute;
} GsTMDPrim;

/* libgs.h only documents GsFCALL4 inside #if 0 hook samples; the
 * original TU declared it itself (the 94 sibling uses the same idiom). */
extern _GsFCALL GsFCALL4;

/* The printf message is the blob's rodata string (RO_STR_00000908), not a
 * separate literal: the original .rdata is string@0 then switch table@32,
 * so a duplicate literal would shift the table and misplace the reference. */
extern char RO_STR_00000908[];

void GsSortObject4J(GsDOBJ2 *objp, GsOT *ot, int shift, u_long *scratch)
{
	struct TMD_STRUCT *tmd;
	GsTMDPrim *prim;
	u_long primn;
	u_long *vp;
	u_long *np;
	u_long div;
	u_long col;
	u_long code;

	if ((long)objp->attribute < 0) {
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
		scratch[1] = HWD0;
		scratch[2] = VWD0;
		scratch[0] = GsNDIV;
	} else {
		div = 0;
	}

	if (GsLIOFF == 1) {
		col = 2;
	} else {
		if ((GsLIGNR == 0 && (GsLIGHT_MODE & 1)) ||
		    (GsLIGNR == 1 && (GsLMODE & 1))) {
			col = 1;
		} else {
			col = 0;
		}
	}

	tmd = (struct TMD_STRUCT *)objp->tmd;
	prim = (GsTMDPrim *)tmd->primtop;
	primn = tmd->primn;
	vp = tmd->vertop;
	np = tmd->nortop;

	if (primn == 0) {
		return;
	}

	do {
		code = ((u_char *)prim)[3] & 0xFD;
		switch (code) {
		case GPU_COM_F3:
			if (prim->attribute & GsTMDFlagGRD) {
				GsOUT_PACKET_P = (*GsFCALL4.f3g[col])(prim, vp, np, GsOUT_PACKET_P,
								prim->h, shift, ot, scratch);
				primn -= ((u_short *)prim)[0];
				prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_F3G));
			} else {
				GsOUT_PACKET_P = (*GsFCALL4.f3[div][col])(prim, vp, np, GsOUT_PACKET_P,
								prim->h, shift, ot, scratch);
				primn -= ((u_short *)prim)[0];
				prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_F3));
			}
			break;
		case GPU_COM_TF3:
			GsOUT_PACKET_P = (*GsFCALL4.tf3[div][col])(prim, vp, np, GsOUT_PACKET_P,
							prim->h, shift, ot, scratch);
			primn -= ((u_short *)prim)[0];
			prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_TF3));
			break;
		case GPU_COM_G3:
			if (prim->attribute & GsTMDFlagGRD) {
				GsOUT_PACKET_P = (*GsFCALL4.g3g[col])(prim, vp, np, GsOUT_PACKET_P,
								prim->h, shift, ot, scratch);
				primn -= ((u_short *)prim)[0];
				prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_G3G));
			} else {
				GsOUT_PACKET_P = (*GsFCALL4.g3[div][col])(prim, vp, np, GsOUT_PACKET_P,
								prim->h, shift, ot, scratch);
				primn -= ((u_short *)prim)[0];
				prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_G3));
			}
			break;
		case GPU_COM_TG3:
			GsOUT_PACKET_P = (*GsFCALL4.tg3[div][col])(prim, vp, np, GsOUT_PACKET_P,
							prim->h, shift, ot, scratch);
			primn -= ((u_short *)prim)[0];
			prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_TG3));
			break;
		case GPU_COM_F4:
			if (prim->attribute & GsTMDFlagGRD) {
				GsOUT_PACKET_P = (*GsFCALL4.f4g[col])(prim, vp, np, GsOUT_PACKET_P,
								prim->h, shift, ot, scratch);
				primn -= ((u_short *)prim)[0];
				prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_F4G));
			} else {
				GsOUT_PACKET_P = (*GsFCALL4.f4[div][col])(prim, vp, np, GsOUT_PACKET_P,
								prim->h, shift, ot, scratch);
				primn -= ((u_short *)prim)[0];
				prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_F4));
			}
			break;
		case GPU_COM_TF4:
			GsOUT_PACKET_P = (*GsFCALL4.tf4[div][col])(prim, vp, np, GsOUT_PACKET_P,
							prim->h, shift, ot, scratch);
			primn -= ((u_short *)prim)[0];
			prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_TF4));
			break;
		case GPU_COM_G4:
			if (prim->attribute & GsTMDFlagGRD) {
				GsOUT_PACKET_P = (*GsFCALL4.g4g[col])(prim, vp, np, GsOUT_PACKET_P,
								prim->h, shift, ot, scratch);
				primn -= ((u_short *)prim)[0];
				prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_G4G));
			} else {
				GsOUT_PACKET_P = (*GsFCALL4.g4[div][col])(prim, vp, np, GsOUT_PACKET_P,
								prim->h, shift, ot, scratch);
				primn -= ((u_short *)prim)[0];
				prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_G4));
			}
			break;
		case GPU_COM_TG4:
			GsOUT_PACKET_P = (*GsFCALL4.tg4[div][col])(prim, vp, np, GsOUT_PACKET_P,
							prim->h, shift, ot, scratch);
			primn -= ((u_short *)prim)[0];
			prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_TG4));
			break;
		case GPU_COM_NF3:
			GsOUT_PACKET_P = (*GsFCALL4.nf3[div])(prim, vp, GsOUT_PACKET_P,
							prim->h, shift, ot, scratch);
			primn -= ((u_short *)prim)[0];
			prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_NF3));
			break;
		case GPU_COM_NF4:
			GsOUT_PACKET_P = (*GsFCALL4.nf4[div])(prim, vp, GsOUT_PACKET_P,
							prim->h, shift, ot, scratch);
			primn -= ((u_short *)prim)[0];
			prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_NF4));
			break;
		case GPU_COM_NG3:
			GsOUT_PACKET_P = (*GsFCALL4.ng3[div])(prim, vp, GsOUT_PACKET_P,
							prim->h, shift, ot, scratch);
			primn -= ((u_short *)prim)[0];
			prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_NG3));
			break;
		case GPU_COM_NTF3:
			GsOUT_PACKET_P = (*GsFCALL4.ntf3[div])(prim, vp, GsOUT_PACKET_P,
							prim->h, shift, ot, scratch);
			primn -= ((u_short *)prim)[0];
			prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_TNF3));
			break;
		case GPU_COM_NTG3:
			GsOUT_PACKET_P = (*GsFCALL4.ntg3[div])(prim, vp, GsOUT_PACKET_P,
							prim->h, shift, ot, scratch);
			primn -= ((u_short *)prim)[0];
			prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_TNG3));
			break;
		case GPU_COM_NG4:
			GsOUT_PACKET_P = (*GsFCALL4.ng4[div])(prim, vp, GsOUT_PACKET_P,
							prim->h, shift, ot, scratch);
			primn -= ((u_short *)prim)[0];
			prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_NG4));
			break;
		case GPU_COM_NTF4:
			GsOUT_PACKET_P = (*GsFCALL4.ntf4[div])(prim, vp, GsOUT_PACKET_P,
							prim->h, shift, ot, scratch);
			primn -= ((u_short *)prim)[0];
			prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_TNF4));
			break;
		case GPU_COM_NTG4:
			GsOUT_PACKET_P = (*GsFCALL4.ntg4[div])(prim, vp, GsOUT_PACKET_P,
							prim->h, shift, ot, scratch);
			primn -= ((u_short *)prim)[0];
			prim = (GsTMDPrim *)((u_char *)prim + ((u_short *)prim)[0] * sizeof(TMD_P_TNG4));
			break;
		default:
			printf(RO_STR_00000908, code, prim);
			break;
		}
	} while (primn != 0);
}
