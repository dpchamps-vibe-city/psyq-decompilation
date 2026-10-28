#include "common.h"
#include "libpad-internal.h"

/* Write cursor for the combination-table payload area inside the record. */
extern u8 *B_00001FA0;

/* Local view of an 8-byte combination-table entry (see PadInfoComb). */
typedef struct {
    u8 count;
    u8 pad01[3];
    u8 *data;
} PadCombEntry;

static s32 func_000010AC(PadInfo2 *info) {
    u8 *data;
    u8 *src;
    u8 *base;
    int size;
    int hi;
    PadCombEntry *comb;
    int len;

    switch (info->commandState) {
    case 2: {
        u8 *data = info->data3C;
        if (data[2] != 0 || data[3] != 0)
            return 0;
        info->idTable[info->pad47[0]] = (data[4] << 8) + data[5];
        if ((*(u16 *)&info->padEA[4]) != info->idTable[info->pad47[0]]) {
            (*(u16 *)&info->padEA[4]) = info->idTable[info->pad47[0]];
            return 0;
        }
        (*(u16 *)&info->padEA[4]) = 0;
        info->padEA[1] = 0;
        if (++info->pad47[0] < info->idCount)
            return 0;
        info->pad47[0] = 0;
        return 1;
    }
    case 3:
        data = info->data3C;
        if (data[2] != 0 || data[3] != 0)
            return 0;
        src = info->actAlignData + info->pad47[0] * 5;
        if (src[0] == data[4] && src[1] == (data[5] & 0x7F)
            && src[2] == data[6] && src[3] == data[7]) {
            hi = data[5];
            if (src[4] == (hi >> 7))
                (*(u16 *)&info->padEA[4]) = 0;
            else
                (*(u16 *)&info->padEA[4]) = 0xFFFF;
        } else
            (*(u16 *)&info->padEA[4]) = 0xFFFF;
        src[0] = info->data3C[4];
        src[1] = info->data3C[5] & 0x7F;
        src[2] = info->data3C[6];
        src[3] = info->data3C[7];
        hi = info->data3C[5];
        src[4] = hi >> 7;
        if ((*(u16 *)&info->padEA[4]) != 0)
            return 0;
        info->padEA[1] = 0;
        if (++info->pad47[0] < info->actAlignCount)
            return 0;
        info->pad47[0] = 0;
        info->pad47[1] = 0;
        break;
    case 4:
        data = info->data3C;
        if (data[2] != 0) {
            info->pad47[1] = 0;
            return 0;
        }
        comb = (PadCombEntry *)(info->combTable + info->pad47[0] * 8);
        if (info->pad47[1] == 0) {
            comb->count = info->pad47[1] = data[4];
            len = 3;
            src = info->data3C + 5;
            if (info->pad47[0] == 0) {
                base = info->combTable;
                size = info->padEA[0] * 8;
            } else {
                base = comb[-1].data;
                size = (comb[-1].count + 3) & 0x1FC;
            }
            base += size;
            B_00001FA0 = comb->data = base;
        } else {
            len = 5;
            src = info->data3C + 3;
        }
        while (--len != -1) {
            if (info->pad47[1] == 0)
                break;
            if (B_00001FA0 >= (u8 *)&info->idCount) {
                info->pad47[0] = 0;
                info->pad47[1] = 0;
                return 0;
            }
            if (*B_00001FA0 != *src)
                (*(u16 *)&info->padEA[4]) = 0xFFFF;
            *B_00001FA0++ = *src++;
            info->pad47[1]--;
        }
        if (info->pad47[1] != 0)
            return 0;
        if ((*(u16 *)&info->padEA[4]) != 0) {
            (*(u16 *)&info->padEA[4]) = 0;
            info->pad47[1] = 0;
            return 0;
        }
        if (++info->pad47[0] >= info->padEA[0]) {
            info->state = 6;
            info->commandState = 0xFE;
            info->padEA[1] = 0;
            return 0;
        }
        info->pad47[1] = 0;
        info->padEA[1] = 0;
        return 0;
    }
    return 1;
}
