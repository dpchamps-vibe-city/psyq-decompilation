#include "common.h"
#include "libpad-internal.h"

int _padGetActSize(PadInfo2 *info)
{
    int idBytes;
    int actBytes;

    idBytes = ((info->idCount + 1) / 2) * 4;
    actBytes = ((info->actAlignCount * 5 + 3) & 0xFFC) + 4;
    return idBytes + actBytes + *(u16 *)((u8 *)info + 0xEC);
}
