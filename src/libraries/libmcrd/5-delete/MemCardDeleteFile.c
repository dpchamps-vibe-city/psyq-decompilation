#include "common.h"
#include <libapi.h>
#include <libmcrd.h>
#include <stdio.h>
#include <string.h>
#include "libmcrd_internal.h"
#include "libmcrd_delete_helpers.h"

long MemCardDeleteFile(long chan, char *file)
{
    char path[32];
    long result = 0;
    long errors = 0;
    long retries = 0;
    long i;
    long fd;
    s32 *state;

    state = McrdGetGlobalStructure();
    if (state[0] != 0) {
        printf(RO_STR_00000388);
        return -1;
    }
    card_file_path(chan, path);
    strcat(path, file);
    state[3] |= 1 << chan;
    i = 0;
    while (i < 4) {
        if ((fd = open(path, 1)) >= 0) {
            break;
        }
        i++;
    }
    if (fd < 0) {
        PushCallbackFunc();
        MemCardAccept(chan);
        MemCardSync(0, NULL, &result);
        PullCallbackFunc();
        if (result == 0 || result == 3) {
            result = 5;
        }
        goto done;
    }
    close(fd);
    for (;;) {
        _clr_card_event();
        result = erase(path);
        if (result == 1) {
            return 0;
        }
        result = _get_card_event_x();
        switch (result) {
        case 0:
            retries = 0;
            PushCallbackFunc();
            MemCardAccept(chan);
            MemCardSync(0, NULL, &result);
            PullCallbackFunc();
            if (result != 4) {
                result = 0;
            }
            goto done;
        case 1:
            i = 0;
            do {
                i++;
                _clr_card_event();
                _card_info(chan);
                result = _get_card_event_x();
            } while (i < 2);
            retries++;
            PushCallbackFunc();
            MemCardAccept(chan);
            MemCardSync(0, NULL, &result);
            PullCallbackFunc();
            if (retries >= 4) {
                result = 2;
                goto done;
            }
            break;
        case 4:
            retries = 0;
            errors = 0;
            _clr_card_event();
            _card_clear(chan);
            _get_card_event_x();
            break;
        default:
            retries = 0;
            errors++;
            if (errors >= 4) {
                long mapped = 0;

                if (result != 1) {
                    if (result < 2) {
                        if (result != 0) {
                            mapped = result | 0x8000;
                        }
                    } else if (result == 2) {
                        mapped = 1;
                    } else if (result == 4) {
                        mapped = 3;
                    } else {
                        mapped = result | 0x8000;
                    }
                } else {
                    mapped = 2;
                }
                result = mapped;
                goto done;
            }
            break;
        }
    }
done:
    return result;
}
