#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void gte_init(void);

static DISPENV *func_000000E4(u16 x, u16 y, u16 intmode, u16 dith, u16 varmmode);
static void func_00000268(u16 x, u16 y);

void GsInitGraph(unsigned short x, unsigned short y, unsigned short intmode, unsigned short dith, unsigned short varmmode) {
    func_000000E4(x, y, intmode, dith, varmmode);
    gte_init();
    PSDIDX = 0;
    func_00000268(x, y);
    GsSetDrawBuffClip();
    GsSetDrawBuffOffset();
}
