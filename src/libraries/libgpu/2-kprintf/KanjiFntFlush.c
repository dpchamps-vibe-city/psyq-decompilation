#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>
#include <strings.h>

typedef struct {
	int	x, y;
	int	u, v;
} TXYU;

extern TXYU txyuv[];
extern s32 D_00001060;
extern s32 D_00001064;
extern s32 D_00001068;
extern u16 B_0000B8A8;
extern char RO_STR_00000FA4[];

s32 func_00000090(s8 *p);
void func_000001D0(s32 dx, s32 dy);

u_long *KanjiFntFlush(int id)
{
	KENTRY *kp;
	POLY_FT4 *pk;
	u_long *ot;
	s8 *p;
	int s, t;
	int xmax, ymax;
	int i, n;
	u_char u, v;
	int prop, nl;

	prop = 0;
	if (id < 0 || id >= D_00001060) {
		id = D_00001064;
		if (KanjiFont[id].pkadr == NULL) {
			return NULL;
		}
	}
	kp = &KanjiFont[id];
	ot = (u_long *)&kp->drmode;
	p = (s8 *)kp->pkadr;
	n = kp->pnum;
	s = kp->tile.x0;
	t = kp->tile.y0;
	xmax = s + kp->tile.w;
	ymax = t + kp->tile.h;
	D_00001068 = 0;
	TermPrim(ot);
	while (*p != 0) {
		if (n == 0)
			break;
		nl = 0;
		switch (*p) {
		case '~':
			if (p[1] == 'p') {
				prop = 1;
				p++;
			}
			goto line;
		case '\t':
			s += 64;
			if (s >= xmax)
				nl = 1;
			goto line;
		case '\n':
			nl = 1;
			goto line;
		case ' ':
			s += 16;
			if (s >= xmax)
				nl = 1;
			goto line;
		default:
			if (((u_char)*p - 0x81) < 0x18U) {
				if (func_00000090(p) < 0)
					goto error;
				txyuv[D_00001068].x = s;
				txyuv[D_00001068].y = t;
				D_00001068++;
				p++;
				break;
			}
			if (((u_char)*p - 0x20) < 0x5FU) {
				if (func_00000090(p) < 0)
					goto error;
			} else {
				if (func_00000090((s8 *)RO_STR_00000FA4) < 0)
					goto error;
			}
			txyuv[D_00001068].x = s;
			txyuv[D_00001068].y = t;
			D_00001068++;
			break;
		}
		if (prop && *p >= 'a' && *p <= 'z')
			s += 12;
		else
			s += 16;
width:
		if (s >= xmax)
			nl = 1;
line:
		if (nl) {
			t += 16;
			s = kp->tile.x0;
			if (t >= ymax)
				break;
		}
		p++;
		n--;
	}
done:
	func_000001D0(kp->dx, kp->dy);
	pk = kp->pk;
	for (i = 0; i < D_00001068; i++, pk++) {
		pk->tpage = B_0000B8A8;
		s = txyuv[i].x;
		t = txyuv[i].y;
		u = txyuv[i].u;
		v = txyuv[i].v;
		setUVWH(pk, u, v, 15, 15);
		setXYWH(pk, s, t, 15, 15);
		AddPrim(ot, pk);
	}
	if (kp->tile.code != 0)
		AddPrim(ot, kp);
	DrawOTag(ot);
error:
	kp->p = 0;
	*kp->pkadr = 0;
	return ot;
}
