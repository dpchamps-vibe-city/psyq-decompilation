#ifndef LIBMCRD_DELETE_HELPERS_H
#define LIBMCRD_DELETE_HELPERS_H

/* Matched LIBMCRD.OBJ definitions: the state base is a word pointer;
 * Push takes no arguments, Pull returns the restored callback. */
extern s32 *McrdGetGlobalStructure(void);
extern void PushCallbackFunc(void);
extern MemCB PullCallbackFunc(void);

/* DELETE.OBJ retained .rdata+0 device template and +8 busy diagnostic. */
extern char RO_STR_00000380[];
extern char RO_STR_00000388[];

/* Device-path template copy and channel digit rendering, the same
 * six-byte template + div/mod idiom as LIBMCRD.OBJ func_000018FC. */
static __inline__ void card_file_path(long chan, char *path)
{
    memcpy(path, RO_STR_00000380, 6);
    path[2] = chan / 16 + '0';
    path[3] = chan % 16 + '0';
}

/* Event-to-status mapping used by the default arm's error dispatch. */
static __inline__ long card_event_result(long event)
{
    long mapped = 0;

    switch (event) {
    case 0:
        break;
    case 1:
        mapped = 2;
        break;
    case 2:
        mapped = 1;
        break;
    case 4:
        mapped = 3;
        break;
    default:
        mapped = event | 0x8000;
        break;
    }
    return mapped;
}

#endif
