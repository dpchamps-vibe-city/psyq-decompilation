#include "common.h"
#include <libapi.h>
#include "libmcrd_internal.h"

static s32 func_000017FC(s32);

static s32 func_00000D14(s32 *arg)
{
    volatile long *event;
    long *fd;
    s32 result;

    switch (arg[0]) {
    case 0:
        D_00001B34 = 0;
        UserFuncOpen(func_000001FC);
        arg[0] = 10;
        break;

    case 10:
        event = &((McrdState *)&B_00001B78)->unk04;
        if (*event != 0)
            return 1;
        fd = (long *)(event + 4);
        while (lseek(fd[0], fd[1], 0) != fd[1]) {
        }
        _clr_card_event();
        fd = &((McrdState *)&B_00001B78)->unk14;
        while (write(fd[0], (void *)fd[3], fd[2]) != 0) {
        }
        arg[0] = 30;
        break;

    case 30:
        if (_chk_card_event() == 0)
            return 0;
        result = _get_card_event();
        if (result != 0) {
            if (++D_00001B34 < 4) {
                arg[0] = 10;
                break;
            }
            if (result == 4) {
                _clr_card_event();
                _card_clear(((McrdState *)&B_00001B78)->unk10);
                arg[0] = 32;
                break;
            }
        }
        ((McrdState *)&B_00001B78)->unk04 = func_000017FC(result);
        return 1;

    case 32:
        if (_chk_card_event_x() != 0) {
            _get_card_event_x();
            arg[0] = 0;
        }
        break;
    }
    return 0;
}
