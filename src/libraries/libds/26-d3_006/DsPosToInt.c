#include "common.h"
#include <sys/types.h>
#include <libds.h>

int DsPosToInt(DslLOC*p) {
    u8 temp_a1;
    u8 temp_a2;
    u8 temp_v1;

    temp_v1 = p->minute;
    temp_a2 = p->second;
    temp_a1 = p->sector;
    return (((((((temp_v1 >> 4) * 0xA) + (temp_v1 & 0xF)) * 0x3C) + (((temp_a2 >> 4) * 0xA) + (temp_a2 & 0xF))) * 0x4B) + (((temp_a1 >> 4) * 0xA) + (temp_a1 & 0xF))) - 0x96;
}
