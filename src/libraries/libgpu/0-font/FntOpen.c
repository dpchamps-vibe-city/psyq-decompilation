#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <strings.h>

extern u16 B_00005B48;
extern u16 B_00005B4A;
extern u_char B_00001740[];
extern u_long B_00001B48[];
extern s32 D_00000D30;
extern s32 D_00001738;

#define ENTP	((FENTRY *)((u_char *)Font + D_00000D30 * 0x30))

int FntOpen(int x, int y, int w, int h, int isbg, int n) {
	RECT	rect;
	SPRT_8	*sprt;
	int	i;

	if (D_00000D30 >= 8) {
		return -1;
	}
	if (D_00000D30 == 0) {
		D_00001738 = 0;
	}
	Font[D_00000D30].flag = (w == 0);
	if ((D_00001738 + n) >= 0x401) {
		n = 0x400 - D_00001738;
	}
	rect.x = 0;
	rect.y = 0;
	rect.w = 0x100;
	rect.h = 0x100;
	SetDrawMode(&Font[D_00000D30].drmode, 0, 0, B_00005B48, &rect);
	if (isbg != 0) {
		SetTile(&ENTP->tile);
		ENTP->tile.r0 = 0;
		ENTP->tile.g0 = 0;
		ENTP->tile.b0 = 0;
		SetSemiTrans(&ENTP->tile, isbg == 2);
	}
	ENTP->tile.x0 = x;
	ENTP->tile.y0 = y;
	ENTP->tile.w = w;
	ENTP->tile.h = h;
	Font[D_00000D30].text = &B_00001740[D_00001738 + D_00000D30];
	Font[D_00000D30].step = n;
	Font[D_00000D30].sprt = (SPRT_8 *)&B_00001B48[D_00001738 * 4];
	Font[D_00000D30].pos = 0;
	*Font[D_00000D30].text = 0;
	sprt = Font[D_00000D30].sprt;
	for (i = 0; i < n; i++) {
		SetSprt8(sprt);
		sprt->clut = B_00005B4A;
		sprt++;
	}
	D_00001738 += n;
	return D_00000D30++;
}
