#include "common.h"
#include "_shared-0.h"

extern int strcmp();
extern int firstfile2(char *, int);

static int firstfile_hook(int *, int, int);

int firstfile(char *name, int dir) {
    struct device_table *dev;
    struct device_table *end;
    struct device_table *limit;
    s8 *src;
    u8 *dst;
    u8 c;
    int found;

    src = name;
    dst = B_00000318;
    if (*src >= 0x3B) {
        do {
            c = *src;
            src++;
            *dst = c;
            dst++;
        } while (*src >= 0x3B);
    }
    *dst = 0;

    dev = *(struct device_table **)0x150;
    end = dev + (*(u32 *)0x154 / 0x50);
    if (dev < end) {
        limit = end;
        do {
            if ((dev->dt_string != 0) && (strcmp(dev->dt_string, (char *)B_00000318) == 0)) {
                B_00000310 = dev->dt_firstfile;
                found = 1;
                goto done;
            }
            dev++;
        } while (dev < limit);
    }
    found = 0;
done:
    if (!found) {
        return 0;
    }

    dev = *(struct device_table **)0x150;
    end = dev + (*(u32 *)0x154 / 0x50);
    if (dev < end) {
        limit = end;
        do {
            if ((dev->dt_string != 0) && (strcmp(dev->dt_string, (char *)B_00000318) == 0)) {
                dev->dt_firstfile = firstfile_hook;
                break;
            }
            dev++;
        } while (dev < limit);
    }
    return firstfile2(name, dir);
}

#include "_firstfile_hook.h"
