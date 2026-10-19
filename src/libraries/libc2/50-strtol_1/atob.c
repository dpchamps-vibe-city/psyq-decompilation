#include "common.h"

extern long strtol(const s8 *, char **, s32);

s8 *atob(const s8 *nptr, s32 *value) {
    char *end;

    *value = strtol(nptr, &end, 10);
    return end;
}
