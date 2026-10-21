#include "common.h"
#include <sys/types.h>
#include <libcd.h>
#include <libds.h>

void data_ready_callback();                         /* extern */
void func_0000013C(u8, u8 *);                       /* static */
extern s32 StMode;

int DsRead2(DslLOC*pos, int mode) {
    s32 var_v0;
    void (*temp_s0)(u8, u8 *);
    void (*temp_s1)();

    if (mode & 0x100) {
        if (mode & 0x20) {
            StMode = 0;
        } else {
            StMode = 1;
        }
        temp_s1 = DsDataCallback(data_ready_callback);
        temp_s0 = DsReadyCallback(func_0000013C);
        var_v0 = DsPacket(mode & 0xFF, pos, 0x1BU, NULL, -1);
        if (var_v0 == 0) {
            DsDataCallback(temp_s1);
            DsReadyCallback(temp_s0);
            return 0;
        }
        /* Duplicate return node #7. Try simplifying control flow for better match */
        return var_v0;
    }
    var_v0 = DsPacket(mode & 0xFF, pos, 0x1BU, NULL, -1);
    return var_v0;
}
