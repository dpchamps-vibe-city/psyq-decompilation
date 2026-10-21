#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <strings.h>

typedef struct {
	TILE		tile;		/* 0x00 */
	DR_MODE		drmode;		/* 0x10 */
	int		pnum;		/* 0x1C */
	POLY_FT4	*pk;		/* 0x20 */
	u_char		*pkadr;		/* 0x24 */
	int		p;		/* 0x28 */
	int		dx, dy;		/* 0x2C, 0x30 */
} KENTRY;				/* 0x34 */

extern KENTRY KanjiFont[];
extern u_long kanjiclut;
extern s32 D_00001060;
extern s32 D_0000108C;
extern u_char B_000010A0[];
extern u_char B_000018A8[];
extern u16 B_0000B8A8;
extern u_char B_0000B8B0[];

#define ENTP	((KENTRY *)((u_char *)KanjiFont + D_00001060 * 0x34))

int KanjiFntOpen(int x, int y, int w, int h, int dx, int dy, int cx, int cy, int isbg, int n)
{
	POLY_FT4 *pk;
	int i;

	bzero(B_0000B8B0, 0x2000);
	memset(ENTP, 0, sizeof(KENTRY));
	DrawSync(0);
	*(u16 *)((u8 *)&B_0000B8A8 + 2) = LoadClut2(&kanjiclut, cx, cy);
	if (D_00001060 >= 4) {
		return -1;
	}
	if (D_00001060 == 0) {
		D_0000108C = 0;
	}
	if ((D_0000108C + n) >= 0x401) {
		return -1;
	}
	if (isbg != 0) {
		SetTile(&ENTP->tile);
		ENTP->tile.r0 = 0;
		ENTP->tile.g0 = 0;
		ENTP->tile.b0 = 0;
	}
	ENTP->tile.x0 = x;
	ENTP->tile.y0 = y;
	ENTP->tile.w = w;
	ENTP->tile.h = h;
	KanjiFont[D_00001060].pkadr = &B_000010A0[D_0000108C * 2 + D_00001060];
	KanjiFont[D_00001060].pnum = n;
	KanjiFont[D_00001060].pk = (POLY_FT4 *)&B_000018A8[D_0000108C * 0x28];
	KanjiFont[D_00001060].p = 0;
	*KanjiFont[D_00001060].pkadr = 0;
	pk = KanjiFont[D_00001060].pk;
	KanjiFont[D_00001060].dx = dx;
	KanjiFont[D_00001060].dy = dy;
	for (i = 0; i < n; i++) {
		SetPolyFT4(pk);
		SetShadeTex(pk, 1);
		pk->clut = *(u16 *)((u8 *)&B_0000B8A8 + 2);
		pk++;
	}
	D_0000108C += n;
	return D_00001060++;
}
