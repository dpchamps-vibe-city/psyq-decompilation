#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <libetc.h>

/* Volatile: the disk-retry counter is written by the ready-system callback.
 * The qualifier is also required for the original code shape: reorg.c's
 * redundant_insn() bails out when the delay-slot candidate references a
 * volatile memory location (resource_conflicts_p() -> res->volatil), so the
 * loop's GD_retry reload is not elided and the two surrounding delay slots are
 * filled from the fall-through path. */
extern volatile s32 GD_retry;
extern s32 GD_disk_kind;

s32 DS_system_status(s32 arg0);
s32 ER_active(void);
extern int _DsPacket2(u8 mode, DslLOC *pos, u8 com, DslCB func, int count, int flag);
static void func_0000022C(u_char, u_char *);

int DsGetDiskType(void) {
    DslLOC pos;
    int retry_no_disk;
    int retry_busy;
    int ready = 1;
    int busy = 2;
    int mute = 0xC;
    int nocd = 3;

    while (DsSystemStatus() != ready) {
        if (DS_system_status(0) == busy && DS_system_status(1) == mute) {
            return 0x10;
        }
        if (DsSystemStatus() == nocd) {
            return 1;
        }
    }
    retry_no_disk = 0;
    retry_busy = 0;
    GD_retry = 0;
    DsIntToPos(0x10, &pos);
    do {
        if (ER_active() != 0) {
            DsEndReadySystem();
        }
        if (GD_retry == 2) {
            VSync(4);
        }
        GD_retry = 0;
        GD_disk_kind = 0;
        if (_DsPacket2(0x20, &pos, 0x1B, func_0000022C, 0, 0) == 0) {
            return 2;
        }
        while (GD_disk_kind == 0) {
            if (DS_system_status(0) == 2 && DS_system_status(1) == 0xC) {
                return 0x10;
            }
        }
        if (GD_retry == 1) {
            if (++retry_no_disk >= 6) {
                return 2;
            }
        }
        if (GD_retry == 2) {
            if (++retry_busy >= 0xB) {
                return 2;
            }
        }
    } while (GD_retry != 0);
    return GD_disk_kind;
}
