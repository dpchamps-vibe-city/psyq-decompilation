#include "common.h"
#include <sys/types.h>
#include <libcd.h>
#include <libetc.h>
#include <stdio.h>
#include <strings.h>

extern char str_command_error[] __asm__("$LRO_STR_000001E0");

int CdGetDiskType(void) {
    CdlLOC sp10;
    u8 sp18[0x800];
    u8 sp818[8];
    u8 sp820;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    s32 var_v0;

    sp820 = 0x80;
    CdControl(1, NULL, sp818);
    var_v0 = 0x10;
    if (!(sp818[0] & 0x10)) {
        CdIntToPos(0x10, &sp10);
        CdControl(0xE, &sp820, NULL);
        VSync(3);
        CdControl(0x1B, &sp10.minute, NULL);
        var_s0 = 0;
        var_s1 = 1;
        while (1) {
            temp_v0 = CdReady(0, sp818);
            var_s0++;
            if (temp_v0 == var_s1) {
                break;
            }
            if (var_s0 >= 0xA) {
                break;
            }
            CdControl(0x1B, &sp10.minute, NULL);
        }
        if (temp_v0 != 1) {
            var_v0 = 0x10;
            if (!(sp818[0] & 0x10)) {
                if ((sp818[0] & 1) && (sp818[1] & 0x40)) {
                    printf(str_command_error);
                    return 1;
                }
                var_v0 = sp818[0] & 2;
                return var_v0 != 0;
            }
            return var_v0;
        }
        CdControl(9, NULL, NULL);
        CdGetSector(sp18, 0x200);
        if (strncmp(&sp18[1], str_command_error + 16, 5) != 0) {
            return 1;
        }
        return 2;
    }
    return var_v0;
}
