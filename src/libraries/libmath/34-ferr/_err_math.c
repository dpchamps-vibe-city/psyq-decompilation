#include "common.h"
#include <libapi.h>
#include "library/libmath_ferr.h"

int _err_math(int error, int point)
{
    math_errno = error;
    math_err_point = point;
    switch (error) {
    case 33:
        DeliverEvent(0xF4000002UL, 0x301);
        break;
    case 34:
        DeliverEvent(0xF4000002UL, 0x302);
        break;
    }
    return 0;
}
