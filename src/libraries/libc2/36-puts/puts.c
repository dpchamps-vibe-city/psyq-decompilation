#include "common.h"

extern s8 $LRO_STR_000000D8[];
extern void _putchar(s8 c);
extern void _putchar_flash(void);

void puts(s8 *s) {
    s8 c;

    if (s == ((void *)0)) {
        s = $LRO_STR_000000D8;
    }
    while ((c = *s++) != 0) {
        _putchar(c);
    }
    _putchar_flash();
}
