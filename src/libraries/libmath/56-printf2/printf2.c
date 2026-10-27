#include "common.h"
#include <libmath.h>
#include <stdarg.h>

/* Original formatter consumes destination, format, va_list and output mode;
 * its null-format path and count return are explicit in the original code. */
static int func_000000EC(char *destination, char *format, va_list args, int mode);

int printf2(char *format, ...)
{
    va_list args;

    va_start(args, format);
    return func_000000EC(0, format, args, 0);
}
