#include "common.h"
#include <libapi.h>
#include <libmcrd.h>

extern s32 B_00001B78;
extern volatile long B_00001B68[];

extern void UserFuncExecute(void);
extern s32 UserFuncComplete(void);

static void func_00001850(u8 prio, u8 *buf, s32 *cmds, s32 *rslt)
{
    if (UserFuncComplete() == 0) {
        UserFuncExecute();
        if (UserFuncComplete() != 0) {
            McrdState *mcrd = (McrdState *)&B_00001B78;
            MemCB cb;

            mcrd->unk08 = 1;
            B_00001B68[0] = mcrd->unk00;
            B_00001B68[1] = mcrd->unk04;
            cb = mcrd->callback;
            mcrd->unk00 = 0;
            mcrd->unk04 = 0;
            if (cb != 0)
                cb(B_00001B68[0], B_00001B68[1]);
        }
    }

    {
        McrdState *mcrd = (McrdState *)&B_00001B78;

        mcrd->unk50++;
        mcrd->unk54++;
    }
}
