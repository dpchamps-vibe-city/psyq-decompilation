INCLUDE_ASM("build/libraries/nonmatchings/libmcrd_4", _card_create2);


/* PARKED by /auto_decompilation_loop on 2026-10-27T21:04:42.202Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libmcrd_4::_card_create2.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <libapi.h>
#include <memory.h>
#include <libmcrd.h>
#include <stdio.h>
#include "libmcrd_internal.h"

#include "libmcrd_create2_context.h"
#include "libmcrd_create2_io.h"

#include "libmcrd_create2_checked_io.h"

long _card_create2(long chan, char *name, long blocks)
{
    u8 *p;
    u8 *dst;
    u8 *src;
    u8 sum;
    long i;
    long j;
    long n = 0;
    long ev;
    long prev;
    long loadretry;
    long size;
    u32 next;
    u32 ff;
    long sector;
    s8 one;

    loadretry = 0;
    bzero(B_00000D58, 0x80);
    i = 0;

    ev = card_read_wait(chan, 0, B_00000D58);
    if (ev != 0)
        return ev;
    if (B_00000D58[0] != 0x4D)
        return -2;
    if (B_00000D58[1] != 0x43)
        return -2;

    i = 0;
    dst = (u8 *)B_00000B18;
    for (; i < 15; i++) {
        B_00000D48[i] = 0;
        bzero(B_00000D58, 0x80);
        ev = card_read_wait(chan, i + 1, B_00000D58);
        if (ev != 0)
            return ev;
        memcpy(dst, B_00000D58, 0x20);
        dst += 0x20;
    }

    for (i = 0; i < 15; i++) {
        if (B_00000B18[i].type != 0x51)
            continue;
        B_00000D48[i] = 1;
        j = i;
        while (B_00000B18[j].next != 0xFFFF) {
            next = B_00000B18[j].next;
            j = next;
            if (next >= 0xF)
                break;
            B_00000D48[j] = 1;
        }
    }

    for (i = 0; i < 15; i++) {
        if (B_00000D48[i] == 0)
            B_00000B18[i].type = 0xA0;
    }

    for (i = 0; i < 15; i++) {
        if (B_00000B18[i].type == 0x51 &&
            strcmp(B_00000B18[i].name, name) == 0) {
            printf(RO_STR_00000B08, B_00000B18[i].name, name);
            return -3;
        }
    }

    for (i = 0; i < 15; i++) {
        B_00000D48[i] = 0;
        if ((B_00000B18[i].type & 0xF0) == 0xA0)
            n++;
    }
    if (n < blocks)
        return -1;

    n = 0;
    prev = 0;
    i = 0;
    size = blocks << 13;
    one = 1;
    {
        u8 *base = B_00000B18[0].name;
        McrdLowDirectoryEntry *entry = (McrdLowDirectoryEntry *)((char *)base - 10);
        char *namep = (char *)base;
        s8 *usedp = B_00000D48;

        for (; i < 15; entry++, usedp++, i++, namep += 0x20) {
            if ((entry->type & 0xF0) != 0xA0)
                continue;
            if (n == 0) {
                entry->type = 0x51;
                B_00000B18[i].size = size;
                strncpy(namep, name, 0x14);
                prev = i;
            } else {
                B_00000B18[prev].next = i;
                prev = i;
                entry->type = 0x52;
            }
            *usedp = one;
            n++;
            ff = 0xFFFF;
            if (n >= blocks) {
                B_00000B18[i].next = ff;
                if (n >= 2)
                    entry->type = 0x53;
                break;
            }
        }
    }

    src = (u8 *)&B_00000B18[0xE];
    for (i = 0xE; i >= 0; i--, src -= 0x20) {
        if (B_00000D48[i] == 0)
            continue;
        bzero(B_00000D58, 0x80);
        memcpy(B_00000D58, src, 0x20);
        sector = i + 1;
        ev = card_write_checked(chan, sector, B_00000D58);
        if (ev != 0)
            return ev;
    }

    for (;;) {
        _clr_card_event();
        _card_load(chan);
        ev = _get_card_event();
        if (ev == 0)
            return 0;
        _clr_card_event();
        _card_clear(chan);
        _get_card_event_x();
        if (++loadretry >= 8)
            break;
    }
    return ev;
}
#endif
