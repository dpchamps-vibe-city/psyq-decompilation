INCLUDE_ASM("build/libraries/nonmatchings/libgs_87", GsSortObject5);

/* Unverified draft from 794aaa2b, preserved for future reconstruction.
 * Parking must retain the original assembly, not compile this incomplete C.
 * See notes/human-needed-approvals/libgs_87::GsSortObject5.md.
 */
#if 0
#include <psyq.h>

void GsSortObject5(GsDOBJ5 *objp, GsOT *ot, int shift, u_long *scratch)
{
    u_long d = objp->attribute;
    if ((int)d < 0)
	return;

    GsLMODE = (d >> 3) & 3;
    GsLIGNR = (d >> 5) & 1;
    GsLIOFF = (d >> 6) & 1;
    GsNDIV  = (d >> 9) & 7;
    GsTON   = (d >> 30) & 1;

    u_long *tmd = objp->tmd;
    u_long *p = objp->packet;
    u_long *s;
    u_long t0, t2;
    int flag = 0;

    s = tmd + 4;
    t0 = tmd[0];
    t2 = tmd[2];

    if (GsNDIV) {
	scratch[0] = GsNDIV;
	scratch[1] = HWD0;
	scratch[2] = VWD0;
	flag = 1;
    }

    int mode;
    if (GsLIOFF == 1)
	mode = 2;
    else if (GsLIGNR)
	mode = (GsLMODE == GsLIGNR);
    else
	mode = (GsLIGHT_MODE == 1);

    if (flag) {
	for (;;) {
	    u_long c = *(s + 3);
	    int idx = ((int)(c & 0xFD)) - 0x20;
	    if ((unsigned int)idx >= 0x1E) {
		printf(RO_STR_000012A0, p);
		goto loopA_check;
	    }
	    switch (idx) {
		u_long r;
	    case 0:
		if (*(s + 2) & 4) {
		    printf(RO_STR_00001288, s);
		    p[1] <<= 1;
		    p[1] += p[1];
		    p[1] <<= 3;
		    s += p[1];
		} else {
		    r = GsFCALL5.f3[1][mode](s, t0, t2, GsOUT_PACKET_P);
		    GsOUT_PACKET_P = r;
		    s += (p[1] << 4);
		}
		break;
	    case 1:
		r = GsFCALL5.tf3[1][mode](s, t0, t2, GsOUT_PACKET_P);
		GsOUT_PACKET_P = r;
		p[1] <<= 1;
		p[1] += p[1];
		p[1] <<= 3;
		s += p[1];
		break;
	    case 2:
		if (*(s + 2) & 4) {
		    printf(RO_STR_00001288, s);
		    p[1] <<= 3;
		    p[1] -= (p[1] >> 3);
		    p[1] <<= 2;
		    s += p[1];
		} else {
		    r = GsFCALL5.g3[1][mode](s, t0, t2, GsOUT_PACKET_P);
		    GsOUT_PACKET_P = r;
		    s += (p[1] << 2);
		    s += (p[1] << 2);
		}
		break;
	    case 3:
		r = GsFCALL5.g3[1][mode](s, t0, t2, GsOUT_PACKET_P);
		GsOUT_PACKET_P = r;
		s += (p[1] << 2);
		s += (p[1] << 2);
		break;
	    case 4:
		r = GsFCALL5.tg3[1][mode](s, t0, t2, GsOUT_PACKET_P);
		GsOUT_PACKET_P = r;
		p[1] <<= 3;
		p[1] -= (p[1] >> 3);
		p[1] <<= 2;
		s += p[1];
		break;
	    case 5:
		r = GsFCALL5.f4[1][mode](s, t0, t2, GsOUT_PACKET_P);
		GsOUT_PACKET_P = r;
		s += (p[1] << 2);
		s += (p[1] << 2);
		break;
	    case 6:
		r = GsFCALL5.tf4[1][mode](s, t0, t2, GsOUT_PACKET_P);
		GsOUT_PACKET_P = r;
		s += (p[1] << 5);
		break;
	    case 7:
		r = GsFCALL5.g4[1][mode](s, t0, t2, GsOUT_PACKET_P);
		GsOUT_PACKET_P = r;
		p[1] <<= 1;
		p[1] += p[1];
		p[1] <<= 3;
		s += p[1];
		break;
	    case 8:
		r = GsFCALL5.tg4[1][mode](s, t0, t2, GsOUT_PACKET_P);
		GsOUT_PACKET_P = r;
		p[1] <<= 3;
		p[1] += p[1];
		p[1] <<= 2;
		s += p[1];
		break;
	    case 9:
		r = GsFCALL5.nf3[1](s, t0, GsOUT_PACKET_P, p[1]);
		GsOUT_PACKET_P = r;
		s += (p[1] << 4);
		break;
	    case 10:
		r = GsFCALL5.nf4[1](s, t0, GsOUT_PACKET_P, p[1]);
		GsOUT_PACKET_P = r;
		s += (p[1] << 4);
		break;
	    case 11:
		r = GsFCALL5.ng3[1](s, t0, GsOUT_PACKET_P, p[1]);
		GsOUT_PACKET_P = r;
		p[1] <<= 1;
		p[1] += p[1];
		p[1] <<= 3;
		s += p[1];
		break;
	    case 12:
		r = GsFCALL5.ntf3[1](s, t0, GsOUT_PACKET_P, p[1]);
		GsOUT_PACKET_P = r;
		s += (((p[1] << 3) - p[1]) << 2);
		break;
	    case 13:
		r = GsFCALL5.ntg3[1](s, t0, GsOUT_PACKET_P, p[1]);
		GsOUT_PACKET_P = r;
		s += ((p[1] << 3) << 2);
		break;
	    case 14:
		r = GsFCALL5.ng4[1](s, t0, GsOUT_PACKET_P, p[1]);
		GsOUT_PACKET_P = r;
		s += (((p[1] << 3) - p[1]) << 2);
		break;
	    case 15:
		r = GsFCALL5.ntf4[1](s, t0, GsOUT_PACKET_P, p + 8);
		GsOUT_PACKET_P = r;
		s += (p[1] << 5);
		break;
	    }
loopA_check:
	    {
		u_long n = p[0] & 0xFFFFFF;
		if (n == 0)
		    return;
		p = (u_long *)n;
	    }
	}
    } else {
	if (PSDIDX == 1)
	    goto loopC_setup;
	goto loopB_setup;
    }

loopC_setup:
    /* PSDIDX == 1 path */
    {
	u_long *lA, *lB, *lC, *lD;
	lA = (u_long *)(((u_long)&GsFCALL5.f3g[0]) + (mode << 2));
	lB = (u_long *)(((u_long)&GsFCALL5.f4[0][0]) + (mode << 2) + (flag << 0));
	lC = (u_long *)(((u_long)&GsFCALL5.tf3[0][0]) + (mode << 2));
	lD = (u_long *)(((u_long)&GsFCALL5.f3g[2]) + (mode << 2));
	/* dummy compute for asm match */
	(void)lD;
	scratch = (u_long *)(flag << 2);
	goto loopC_dispatch;
    }

loopB_setup:
    /* PSDIDX != 1 path */
    {
	u_long *lA, *lB, *lC, *lD;
	lA = (u_long *)(((u_long)&GsFCALL5.f3g[0]) + (mode << 2));
	lB = (u_long *)(((u_long)&GsFCALL5.f4[0][0]) + (mode << 2));
	lC = (u_long *)(((u_long)&GsFCALL5.tf3[0][0]) + (mode << 2));
	lD = (u_long *)(((u_long)&GsFCALL5.f3g[2]) + (mode << 2));
	/* dummy compute for asm match */
	(void)lD;
	scratch = (u_long *)0;
	goto loopB_dispatch;
    }

loopB_dispatch:
    for (;;) {
	u_long c = *(s + 3);
	int idx = ((int)(c & 0xFD)) - 0x20;
	if ((unsigned int)idx >= 0x1E) {
	    printf(RO_STR_000012BC, p);
	    goto loopB_check;
	}
	switch (idx) {
	    u_long r;
	case 0:
	    if (*(s + 2) & 4) {
		printf(RO_STR_00001288, s);
		r = 0;
		goto loopB_stride_72;
	    } else {
		r = GsFCALL5.f3g[0](s, t0, t2, p + 8);
		GsOUT_PACKET_P = r;
		goto loopB_stride_32;
	    }
	    break;
	case 1:
	    r = GsFCALL5.f4[0][mode](s, t0, t2, p + 8);
	    GsOUT_PACKET_P = r;
	    goto loopB_stride_16;
	case 2:
	    if (*(s + 2) & 4) {
		printf(RO_STR_00001288, s);
		r = 0;
		goto loopB_stride_224;
	    } else {
		r = GsFCALL5.tf3[0][mode](s, t0, t2, p + 8);
		GsOUT_PACKET_P = r;
		goto loopB_stride_44;
	    }
	    break;
	case 3:
	    r = GsFCALL5.tf3[0][mode](s, t0, t2, p + 8);
	    GsOUT_PACKET_P = r;
	    goto loopB_stride_44;
	case 4:
	    r = GsFCALL5.g4[0][mode](s, t0, t2, p + 8);
	    GsOUT_PACKET_P = r;
	    goto loopB_stride_64;
	case 5:
	    r = GsFCALL5.ng4[1](s, t0, GsOUT_PACKET_P, p + 8);
	    GsOUT_PACKET_P = r;
	    goto loopB_stride_140;
	case 6:
	    r = GsFCALL5.tg4[0][mode](s, t0, t2, p + 8);
	    GsOUT_PACKET_P = r;
	    goto loopB_stride_32;
	case 7:
	    r = GsFCALL5.ntg3[1](s, t0, GsOUT_PACKET_P, p + 8);
	    GsOUT_PACKET_P = r;
	    goto loopB_stride_56;
	case 8:
	    r = GsFCALL5.ntf3[1](s, t0, GsOUT_PACKET_P, p + 8);
	    GsOUT_PACKET_P = r;
	    goto loopB_stride_72;
	case 9:
	    r = GsFCALL5.nf3[0](s, t0, GsOUT_PACKET_P, p + 8);
	    GsOUT_PACKET_P = r;
	    goto loopB_stride_16;
	case 10:
	    r = GsFCALL5.nf4[1](s, t0, GsOUT_PACKET_P, p + 8);
	    GsOUT_PACKET_P = r;
	    goto loopB_stride_16;
	case 11:
	    r = GsFCALL5.ng3[1](s, t0, GsOUT_PACKET_P, p + 8);
	    GsOUT_PACKET_P = r;
	    goto loopB_stride_72;
	case 12:
	    r = GsFCALL5.ntf3[1](s, t0, GsOUT_PACKET_P, p + 8);
	    GsOUT_PACKET_P = r;
	    goto loopB_stride_56;
	case 13:
	    r = GsFCALL5.ntg3[1](s, t0, GsOUT_PACKET_P, p + 8);
	    GsOUT_PACKET_P = r;
	    goto loopB_stride_72;
	case 14:
	    r = GsFCALL5.ng4[1](s, t0, GsOUT_PACKET_P, p + 8);
	    GsOUT_PACKET_P = r;
	    goto loopB_stride_56;
	case 15:
	    r = GsFCALL5.ntf4[1](s, t0, GsOUT_PACKET_P, p + 8);
	    GsOUT_PACKET_P = r;
	    goto loopB_stride_196;
	}
loopB_check:
	{
	    u_long n = p[0] & 0xFFFFFF;
	    if (n == 0)
		return;
	    p = (u_long *)n;
	}
    }

loopC_dispatch:
    for (;;) {
	u_long c = *(s + 3);
	int idx = ((int)(c & 0xFD)) - 0x20;
	if ((unsigned int)idx >= 0x1E) {
	    printf(RO_STR_000012BC, p);
	    goto loopC_check;
	}
	switch (idx) {
	    u_long r;
	case 0:
	    if (*(s + 2) & 4) {
		printf(RO_STR_00001288, s);
		r = 0;
		goto loopC_stride_72;
	    } else {
		r = GsFCALL5.f3g[0](s, t0, t2, p + 0x24);
		GsOUT_PACKET_P = r;
		goto loopC_stride_32;
	    }
	    break;
	case 1:
	    r = GsFCALL5.f4[0][mode](s, t0, t2, p + 0x1C);
	    GsOUT_PACKET_P = r;
	    goto loopC_stride_16;
	case 2:
	    if (*(s + 2) & 4) {
		printf(RO_STR_00001288, s);
		r = 0;
		goto loopC_stride_224;
	    } else {
		r = GsFCALL5.tf3[0][mode](s, t0, t2, p + 0x28);
		GsOUT_PACKET_P = r;
		goto loopC_stride_44;
	    }
	    break;
	case 3:
	    r = GsFCALL5.tf3[0][mode](s, t0, t2, p + 0x30);
	    GsOUT_PACKET_P = r;
	    goto loopC_stride_44;
	case 4:
	    r = GsFCALL5.g4[0][mode](s, t0, t2, p + 0x2C);
	    GsOUT_PACKET_P = r;
	    goto loopC_stride_64;
	case 5:
	    r = GsFCALL5.ng4[1](s, t0, GsOUT_PACKET_P, p + 0x3C);
	    GsOUT_PACKET_P = r;
	    goto loopC_stride_140;
	case 6:
	    r = GsFCALL5.tg4[0][mode](s, t0, t2, p + 0x30);
	    GsOUT_PACKET_P = r;
	    goto loopC_stride_32;
	case 7:
	    r = GsFCALL5.ntg3[1](s, t0, GsOUT_PACKET_P, p + 0x20);
	    GsOUT_PACKET_P = r;
	    goto loopC_stride_56;
	case 8:
	    r = GsFCALL5.ntf3[1](s, t0, GsOUT_PACKET_P, p + 0x24);
	    GsOUT_PACKET_P = r;
	    goto loopC_stride_72;
	case 9:
	    r = GsFCALL5.nf3[0](s, t0, GsOUT_PACKET_P, p + 0x1C);
	    GsOUT_PACKET_P = r;
	    goto loopC_stride_16;
	case 10:
	    r = GsFCALL5.nf4[1](s, t0, GsOUT_PACKET_P, p + 0x20);
	    GsOUT_PACKET_P = r;
	    goto loopC_stride_16;
	case 11:
	    r = GsFCALL5.ng3[1](s, t0, GsOUT_PACKET_P, p + 0x28);
	    GsOUT_PACKET_P = r;
	    goto loopC_stride_72;
	case 12:
	    r = GsFCALL5.ntf3[1](s, t0, GsOUT_PACKET_P, p + 0x30);
	    GsOUT_PACKET_P = r;
	    goto loopC_stride_56;
	case 13:
	    r = GsFCALL5.ng4[1](s, t0, GsOUT_PACKET_P, p + 0x2C);
	    GsOUT_PACKET_P = r;
	    goto loopC_stride_56;
	case 14:
	    r = GsFCALL5.ng4[1](s, t0, GsOUT_PACKET_P, p + 0x3C);
	    GsOUT_PACKET_P = r;
	    goto loopC_stride_196;
	case 15:
	    r = GsFCALL5.ng4[1](s, t0, GsOUT_PACKET_P, p + 0x3C);
	    GsOUT_PACKET_P = r;
	    goto loopC_stride_196;
	}
loopC_check:
	{
	    u_long n = p[0] & 0xFFFFFF;
	    if (n == 0)
		return;
	    p = (u_long *)n;
	}
    }

loopB_stride_224:
    p[1] <<= 3;
    p[1] >>= 3;
    s += p[1];
    goto loopB_check;

loopB_stride_140:
    p[1] <<= 3;
    p[1] += p[1];
    p[1] -= (p[1] >> 3);
    p[1] <<= 2;
    s += p[1];
    goto loopB_check;

loopB_stride_72:
    p[1] <<= 3;
    p[1] += p[1];
    p[1] <<= 3;
    s += p[1];
    goto loopB_check;

loopB_stride_64:
    p[1] <<= 5;
    s += p[1];
    goto loopB_check;

loopB_stride_56:
    p[1] <<= 3;
    p[1] -= (p[1] >> 3);
    p[1] <<= 2;
    s += p[1];
    goto loopB_check;

loopB_stride_44:
    p[1] <<= 2;
    p[1] += p[1];
    p[1] += (p[1] >> 3);
    p[1] <<= 3;
    s += p[1];
    goto loopB_check;

loopB_stride_32:
    p[1] <<= 5;
    s += p[1];
    goto loopB_check;

loopB_stride_196:
    p[1] <<= 1;
    p[1] += p[1];
    p[1] <<= 2;
    p[1] -= (p[1] >> 2);
    p[1] <<= 2;
    s += p[1];
    goto loopB_check;

loopB_stride_16:
    p[1] <<= 4;
    s += p[1];
    goto loopB_check;

loopC_stride_224:
    p[1] <<= 3;
    p[1] >>= 3;
    s += p[1];
    goto loopC_check;

loopC_stride_140:
    p[1] <<= 3;
    p[1] += p[1];
    p[1] -= (p[1] >> 3);
    p[1] <<= 2;
    s += p[1];
    goto loopC_check;

loopC_stride_72:
    p[1] <<= 3;
    p[1] += p[1];
    p[1] <<= 3;
    s += p[1];
    goto loopC_check;

loopC_stride_64:
    p[1] <<= 5;
    s += p[1];
    goto loopC_check;

loopC_stride_56:
    p[1] <<= 3;
    p[1] -= (p[1] >> 3);
    p[1] <<= 2;
    s += p[1];
    goto loopC_check;

loopC_stride_44:
    p[1] <<= 2;
    p[1] += p[1];
    p[1] += (p[1] >> 3);
    p[1] <<= 3;
    s += p[1];
    goto loopC_check;

loopC_stride_32:
    p[1] <<= 5;
    s += p[1];
    goto loopC_check;

loopC_stride_196:
    p[1] <<= 1;
    p[1] += p[1];
    p[1] <<= 2;
    p[1] -= (p[1] >> 2);
    p[1] <<= 2;
    s += p[1];
    goto loopC_check;

loopC_stride_16:
    p[1] <<= 4;
    s += p[1];
    goto loopC_check;
}
#endif
