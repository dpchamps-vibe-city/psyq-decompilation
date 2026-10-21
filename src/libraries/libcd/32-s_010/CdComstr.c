#include "common.h"

extern char *CD_comstr[];
extern char RO_STR_000000B0[];

char *CdComstr(u8 com) {
    if (com >= 0x1C) {
        return RO_STR_000000B0;
    }
    return CD_comstr[com];
}
