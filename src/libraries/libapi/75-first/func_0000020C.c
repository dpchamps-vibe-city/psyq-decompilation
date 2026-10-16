/* Unexported device-table interposer used by firstfile. Its original entry is
 * witnessed by the section-relative callback-address relocation. */

static int func_0000020C(int *arg0, int arg1, int arg2) {
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
