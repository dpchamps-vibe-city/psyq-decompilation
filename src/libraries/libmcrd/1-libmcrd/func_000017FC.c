#include "common.h"

int func_000017FC(int event)
{
    int ret = 0;

    switch (event) {
    case 0:
        break;
    case 2:
        ret = 1;
        break;
    case 4:
        ret = 3;
        break;
    case 1:
        ret = 2;
        break;
    default:
        ret = event | 0x8000;
        break;
    }

    return ret;
}
