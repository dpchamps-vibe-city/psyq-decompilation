/* Original TU: library-input/psyq/LIB/LIBGPU.LIB[0] FONT.OBJ
 * sha256: b8d50d7d5bc6fbc4b8ba61fc10c0fee835e3a28f94379709519f7561defea4d7
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: SetDumpFnt, FntLoad, FntOpen, FntFlush, FntPrint
 */
#include "common.h"
#include "include_asm.h"

#include <sys/types.h>
#include <libgte.h>

/* The reference libgpu.h declares FntPrint with an old-style empty parameter
 * list in its C branch, which cannot be followed by the variadic definition
 * the original object shows (FNT.OBJ's FntPrint saves $4-$7 and takes the
 * address of its first parameter for va_start).  Keep the header's other
 * declarations and supply the real prototype. */
#define _FNTPRINT_
#include <libgpu.h>

int FntPrint(int id, ...);

/* FONT.OBJ's font state table.  The original relocations address each entry
 * member directly (Font+16 drmode, Font+28 step, Font+32/36 sprt/text,
 * Font+40 pos, Font+44 flag) with a 0x30 stride, so Font is an array of these
 * entries.  FntLoad clears the table with memset(Font, 0, 0x180). */
typedef struct {
	TILE		tile;		/* 0x000 */
	DR_MODE		drmode;		/* 0x010 */
	int		step;		/* 0x01C */
	SPRT_8		*sprt;		/* 0x020 */
	u_char		*text;		/* 0x024 */
	int		pos;		/* 0x028 */
	int		flag;		/* 0x02C */
} FENTRY;				/* 0x030 */

extern FENTRY Font[];
