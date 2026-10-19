#include "common.h"
#include "library/11-putc.h"
#include <ctype.h>

extern void _putchar(s8 c);
extern void _putchar_flash(void);

void putchar(s8 c) {
    _putchar(c);
    _putchar_flash();
}
