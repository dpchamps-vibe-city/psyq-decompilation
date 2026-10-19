/* GETS.OBJ from LIBC2.LIB */
#include "common.h"

extern s32 getchar(void);
extern void putchar(s8);
extern s8 _ctype_[];

s8 *gets(s8 *s) {
    s8 *p = s;
    s8 *end = s + 0x7D;
    s8 c;

    for (;;) {
        c = getchar();
        switch (c) {
        case 0x16:
            c = getchar();
            if (p < end) {
                *p++ = c;
                putchar(c);
            } else {
                putchar('\a');
            }
            break;
        case '\n':
        case '\r':
            putchar('\n');
            *p = 0;
            return s;
        case '\b':
        case 0x7F:
            if (p > s) {
                p--;
                putchar('\b');
                putchar(' ');
                putchar('\b');
            }
            break;
        case '\t':
            c = ' ';
            /* fall through */
        default:
            if (((_ctype_ + 1)[(u8)c] & 0x97) && p < end) {
                *p++ = c;
                putchar(c);
            } else {
                putchar('\a');
            }
            break;
        }
    }
}
