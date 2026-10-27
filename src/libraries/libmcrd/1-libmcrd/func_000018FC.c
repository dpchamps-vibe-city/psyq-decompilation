#include "common.h"
#include <libapi.h>
#include <libmcrd.h>
#include <string.h>
#include "libmcrd_internal.h"

void func_000018FC(long chan, char *path)
{
    memcpy(path, RO_STR_00001B1C, 6);
    path[2] = chan / 16 + '0';
    path[3] = chan % 16 + '0';
}
