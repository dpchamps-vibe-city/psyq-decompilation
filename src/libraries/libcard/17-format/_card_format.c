#include "common.h"
#include <libapi.h>
#include <memory.h>

typedef struct {
    u8 data[0x20];
} CardBlock;

typedef struct {
    u8 data[4];
} CardWord;

typedef struct {
    u32 cmd;
    u32 unk4;
    u16 unk8;
    u8 pad[0x16];
} CardEntry;

extern s32 func_00000070(s32 chan, s32 block, u8 *buf) __asm__("$Lfunc_00000070");

extern CardEntry $LB_00000430[];
extern u32 $LB_00000610[];
extern u8 $LB_00000660[];

long _card_format(long chan) {
    long i;
    long stat;
    long one;
    u8 *buf;
    u8 *buf2;
    long base;
    long neg;

    i = 0;
    buf = $LB_00000660;
    base = (long)$LB_00000430;
    while (i < 15) {
        bzero(buf, 0x80);
        bzero((u8 *)(i * 0x20 + base), 0x20);
        $LB_00000430[i].cmd = 0xA0;
        $LB_00000430[i].unk4 = 0;
        $LB_00000430[i].unk8 = 0xFFFF;
        one = 1;
        *(CardBlock *)buf = *(CardBlock *)(i * 0x20 + base);
        if (func_00000070(chan, i + 1, buf) != one) {
            return 0;
        }
        i++;
    }

    i = 0;
    neg = -1;
    buf2 = buf;
    for (; i < 20; i++) {
        $LB_00000610[i] = neg;
        bzero(buf2, 0x80);
        *(CardWord *)buf2 = *(CardWord *)&$LB_00000610[i];
        if (func_00000070(chan, i + 0x10, buf2) != 1) {
            return 0;
        }
    }

    stat = (long)buf2;
    bzero((u8 *)stat, 0x80);
    ((u8 *)stat)[0] = 0x4D;
    ((u8 *)stat)[1] = 0x43;
    stat = func_00000070(chan, 0, (u8 *)stat);
    if (stat != 1) {
        return 0;
    }

    bzero(buf2, 0x80);
    _new_card();
    if (_card_read(chan, 0, buf2) == stat) {
        while ((_card_status(chan >> 4) & 1) == 0) {
        }
        stat = 1;
    } else {
        stat = 0;
    }
    if (stat != 1) {
        return 0;
    }
    _new_card();
    if (_card_load(chan) != stat) {
        return 0;
    }
    while ((_card_status(chan >> 4) & 1) == 0) {
    }
    return 1;
}
