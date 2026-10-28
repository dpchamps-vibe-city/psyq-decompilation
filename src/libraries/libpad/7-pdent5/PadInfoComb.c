#include "common.h"
#include <libpad.h>
#include "libpad-internal.h"

/* Local view of the per-port record until the owned header carries these
 * fields. Offsets match libpad-internal.h's PadInfo2 exactly. */
typedef struct {
    u8 count;
    u8 pad01[3];
    u8 *data;
} PadCombEntry;

typedef struct {
    u8 pad00[8];
    PadCombEntry *combTable;
    u8 pad0C[0xEA - 0x0C];
    u8 combCount;
} PadCombView;

int PadInfoComb(int port, int slot, int id) {
    PadCombView *info = (PadCombView *)_padFuncPort2Info(port);
    PadCombEntry *entry;

    if (slot < 0) {
        return info->combCount;
    }
    if (slot < info->combCount) {
        entry = &info->combTable[slot];
        if (id < 0) {
            return entry->count;
        }
        if (id < entry->count) {
            return entry->data[id];
        }
        return 0;
    }
    return 0;
}
