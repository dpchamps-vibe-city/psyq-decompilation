INCLUDE_ASM("build/libraries/nonmatchings/libmcrd_1", func_000001FC);


/* PARKED by /auto_decompilation_loop on 2026-10-27T16:33:21.187Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libmcrd_1::func_000001FC.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <libapi.h>
#include <stdio.h>
#include "libmcrd_internal.h"

extern s32 B_00001B48;
extern volatile s32 B_00001B4C;
extern u32 D_00001B28;
extern s32 D_00001B2C;
extern char RO_STR_00001980[];

extern void _clr_card_event(void);
extern long _chk_card_event(void);
extern long _get_card_event(void);
extern long _chk_card_event_x(void);
extern long _get_card_event_x(void);

static s32 func_000017FC(s32);

static s32 func_000001FC(s32 *arg)
{
    McrdState *mcrd;
    long *p;
    long *q;
    long *slot;
    s32 ev;
    s32 v;
    s32 w;
    s32 retryState = 10;

    switch (arg[0]) {
    case 0:
        p = &((McrdState *)&B_00001B78)->unk10;
        B_00001B4C = 0;
        B_00001B48 = 0;
        arg[0] = retryState;
        v = p[0];
        p += 16;
        slot = &p[v >> 4];
        v = *slot;
        *slot = 0;
        D_00001B28 = v;
        /* fall through */
    case 10:
        _clr_card_event();
        _card_info(((McrdState *)&B_00001B78)->unk10);
        arg[0] = arg[0] + 1;
        goto complete;

    case 11:
        if (_chk_card_event() == 0)
            return 0;
        ev = _get_card_event();
        B_00001B4C = ev;
        p = &((McrdState *)&B_00001B78)->unk10;
        q = p + 14;
        v = p[0];
        slot = &q[v >> 4];
        w = *slot;
        D_00001B2C = w;
        switch (ev) {
        case 4:
            if (w != 0)
                goto retry;
            if (D_00001B28 >= 0x80U)
                goto retry;
            _clr_card_event();
            _card_clear(p[0]);
            arg[0] = 21;
            goto complete;
        retry:
            p = &((McrdState *)&B_00001B78)->unk10;
            p[(p[0] >> 4) + 14] = 1;
            p -= 4;
            p[1] = func_000017FC(B_00001B4C);
            return 1;

        case 0:
            if ((p[-1] & (1 << v)) == 0)
                B_00001B4C = 4;
            *slot = 0;
            ((McrdState *)&B_00001B78)->unk04 = func_000017FC(B_00001B4C);
            return 1;

        case 2:
            if (++B_00001B48 >= 3) {
                *slot = 1;
                ((McrdState *)&B_00001B78)->unk04 = func_000017FC(2);
                return 1;
            }
            goto retry_info;

        case 1:
            if (++B_00001B48 < 0x11) {
        retry_info:
                arg[0] = retryState;
                return 0;
            }
            ((McrdState *)&B_00001B78)->unk04 = func_000017FC(1);
            q[p[0] >> 4] = 0;
            return 1;

        default:
            mcrd = (McrdState *)&B_00001B78;
            mcrd->unk04 = func_000017FC(B_00001B4C);
            (&mcrd->unk48)[mcrd->unk10 >> 4] = 0;
            return 1;
        }

    case 21:
        if (_chk_card_event_x() != 0) {
            _get_card_event_x();
            arg[0] = 0;
        }
        return 0;

    default:
        printf(RO_STR_00001980);
        break;
    }
complete:
    return 0;
}
#endif
