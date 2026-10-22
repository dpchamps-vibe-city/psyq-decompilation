#include "common.h"
#include <memory.h>

extern u16 D_000005D0[19][2];
extern u16 D_0000069C[19][2];
extern u16 D_0000061C[32][2];

s32 kanjitrans(u16 scode)
{
    int ret = 0;
    u8 ss[2];
    u8 stmp;

    bcopy((u8 *)&scode, ss, 2);

    switch (ss[1]) {
    case 0x81:
        if ((ss[0] >= 0x40) && (ss[0] <= 0x7e))
            stmp = 0;
        else
        if ((ss[0] >= 0x80) && (ss[0] <= 0xac))
            stmp = 1;
        else
        if ((ss[0] >= 0xb8) && (ss[0] <= 0xbf))
            stmp = 2;
        else
        if ((ss[0] >= 0xc8) && (ss[0] <= 0xce))
            stmp = 3;
        else
        if ((ss[0] >= 0xda) && (ss[0] <= 0xe8))
            stmp = 4;
        else
        if ((ss[0] >= 0xf0) && (ss[0] <= 0xf7))
            stmp = 5;
        else
        if (ss[0] == 0xfc)
            stmp = 6;
        else {
            ret = -1;
            break;
        }
        ret = scode - D_000005D0[stmp][0] + D_000005D0[stmp][1];
        break;

    case 0x82:
        if ((ss[0] >= 0x4f) && (ss[0] <= 0x58))
            stmp = 7;
        else
        if ((ss[0] >= 0x60) && (ss[0] <= 0x79))
            stmp = 8;
        else
        if ((ss[0] >= 0x81) && (ss[0] <= 0x9a))
            stmp = 9;
        else
        if ((ss[0] >= 0x9f) && (ss[0] <= 0xf1))
            stmp = 10;
        else {
            ret = -1;
            break;
        }
        ret = scode - D_000005D0[stmp][0] + D_000005D0[stmp][1];
        break;

    case 0x83:
        if ((ss[0] >= 0x40) && (ss[0] <= 0x7e))
            stmp = 11;
        else
        if ((ss[0] >= 0x80) && (ss[0] <= 0x96))
            stmp = 12;
        else
        if ((ss[0] >= 0x9f) && (ss[0] <= 0xb6))
            stmp = 13;
        else
        if ((ss[0] >= 0xbf) && (ss[0] <= 0xd6))
            stmp = 14;
        else {
            ret = -1;
            break;
        }
        ret = scode - D_000005D0[stmp][0] + D_000005D0[stmp][1];
        break;

    case 0x84:
        if ((ss[0] >= 0x40) && (ss[0] <= 0x60))
            stmp = 15;
        else
        if ((ss[0] >= 0x70) && (ss[0] <= 0x7e))
            stmp = 16;
        else
        if ((ss[0] >= 0x80) && (ss[0] <= 0x91))
            stmp = 17;
        else
        if ((ss[0] >= 0x9f) && (ss[0] <= 0xbe))
            stmp = 18;
        else {
            ret = -1;
            break;
        }
        ret = scode - D_000005D0[stmp][0] + D_000005D0[stmp][1];
        break;

    case 0x85:
        if ((ss[0] >= 0x40) && (ss[0] <= 0x44))
            stmp = 0;
        else
        if (ss[0] == 0x46)
            stmp = 1;
        else
        if ((ss[0] >= 0x48) && (ss[0] <= 0x49))
            stmp = 2;
        else
        if (ss[0] == 0x4b)
            stmp = 3;
        else
        if ((ss[0] >= 0x50) && (ss[0] <= 0x5b))
            stmp = 4;
        else
        if ((ss[0] >= 0xa0) && (ss[0] <= 0xac))
            stmp = 5;
        else
        if ((ss[0] >= 0xb0) && (ss[0] <= 0xbc))
            stmp = 6;
        else {
            ret = -1;
            break;
        }
        ret = scode - D_0000069C[stmp][0] + D_0000069C[stmp][1];
        break;

    case 0x86:
        if ((ss[0] >= 0x40) && (ss[0] <= 0x41))
            stmp = 7;
        else
        if (ss[0] == 0x43)
            stmp = 8;
        else
        if (ss[0] == 0x45)
            stmp = 9;
        else
        if ((ss[0] >= 0x47) && (ss[0] <= 0x48))
            stmp = 10;
        else
        if ((ss[0] >= 0x4a) && (ss[0] <= 0x4c))
            stmp = 11;
        else
        if ((ss[0] >= 0x4e) && (ss[0] <= 0x4f))
            stmp = 12;
        else
        if ((ss[0] >= 0x60) && (ss[0] <= 0x6f))
            stmp = 13;
        else
        if ((ss[0] >= 0x9f) && (ss[0] <= 0xb6))
            stmp = 14;
        else
        if ((ss[0] >= 0xb8) && (ss[0] <= 0xf5))
            stmp = 15;
        else {
            ret = -1;
            break;
        }
        ret = scode - D_0000069C[stmp][0] + D_0000069C[stmp][1];
        break;

    case 0x87:
        if ((ss[0] >= 0x40) && (ss[0] <= 0x5a))
            stmp = 16;
        else
        if ((ss[0] >= 0x5c) && (ss[0] <= 0x62))
            stmp = 17;
        else
        if ((ss[0] >= 0x64) && (ss[0] <= 0x96))
            stmp = 18;
        else {
            ret = -1;
            break;
        }
        ret = scode - D_0000069C[stmp][0] + D_0000069C[stmp][1];
        break;

    default:
        if ((ss[1] > 0x98) || ((ss[1] == 0x98) && (ss[0] > 0x72)) ||
            (ss[1] < 0x88) || ((ss[1] == 0x88) && (ss[0] < 0x9f)) ||
            (ss[0] > 0xfc) || (ss[0] < 0x40) ||
            ((ss[0] > 0x7e) && (ss[0] < 0x80))) {
            ret = -1;
            break;
        }
        stmp = ((ss[1] - 0x88) * 2) + ((ss[0] < 0x7f) ? 0 : 1) - 1;
        ret = scode - D_0000061C[stmp][0] + D_0000061C[stmp][1];
    }

    return ret;
}
