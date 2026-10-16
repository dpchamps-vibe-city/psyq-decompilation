/*
 * Static device-table interposer used by firstfile. The original member's
 * .text holds two functions under the single `firstfile` symbol; the second
 * has no original symbol and is defined here so the production translation
 * unit reproduces the member's full .text.
 */

static int firstfile_hook(int *arg0, int arg1, int arg2) {
    struct device_table *dev;
    struct device_table *end;
    struct device_table *limit;
    int (*saved)();

    if (*arg0 == 0) {
        *arg0 = 1;
    }
    saved = B_00000310;
    dev = *(struct device_table **)0x150;
    end = dev + (*(u32 *)0x154 / 0x50);
    if (dev < end) {
        limit = end;
        do {
            if ((dev->dt_string != 0) && (strcmp(dev->dt_string, (char *)B_00000318) == 0)) {
                dev->dt_firstfile = saved;
                break;
            }
            dev++;
        } while (dev < limit);
    }
    return B_00000310(arg0, arg1, arg2);
}
