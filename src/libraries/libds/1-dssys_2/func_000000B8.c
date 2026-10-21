INCLUDE_ASM("build/libraries/nonmatchings/libds_1", func_000000B8);


/* PARKED by /auto_decompilation_loop on 2026-10-20T20:06:08.061Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libds_1::func_000000B8.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"

typedef struct {
    DsCommand command[8];
    s32 index;
    s32 field4;
    s32 count;
} DsQueue;

extern DsQueue $LB_000015B8 __asm__("B_000015B8");
extern DsCommand commands[] __asm__("B_000015B8");
extern s32 $LB_00001678 __asm__("B_00001678");

static void func_000000B8(void) __asm__("func_000000B8");

static void func_000000B8(void) {
    s32 *ip;
    s32 *jp;
    s32 *cnt;
    DsCommand *cmdq;
    s32 id;
    DsCommand *cmd;
    void (*self)(void);

    self = func_000000B8;
    (void) self;
    ip = &$LB_000015B8.index;
    cnt = &$LB_000015B8.count;
    cmdq = (DsCommand *) ((u8 *) ip - 0xC0);
    id = commands[*ip].active;
    jp = ip;
loop:
    if (*cnt <= 0) {
        goto done;
    }
    cmd = &cmdq[$LB_00001678];
    func_00000088(cmd);

    (*jp)++;
    if (*jp >= 8) {
        *jp = 0;
    }
    jp[2]--;
    if (commands[*jp].active == id) {
        goto loop;
    }
done:
    {
        s32 *fp = &$LB_000015B8.field4;
        *fp = fp[-1];
    }
}
#endif
