/* Original member: LIBC2.LIB[33] PRNT.OBJ */
#include "common.h"

#define LONGINT 0x01
#define LONGDBL 0x02
#define SHORTINT 0x04
#define ALT 0x08
#define LADJUST 0x10
#define ZEROPAD 0x20
#define HEXPREFIX 0x40

#define BUF 40

extern u8 _ctype_[];

extern void _putchar();
extern void _putchar_flash();
extern void *memchr();
extern unsigned int strlen();

#define isascii(c) ((unsigned)(c) < 0x80)
#define isdigit(c) (((_ctype_ + 1))[(u8)(c)] & 4)
#define todigit(c) ((c) - '0')

#define VA_INT() (*(s32 *)((argp += 4) - 4))
#define VA_SHORT() (*(s16 *)((argp += 4) - 4))
#define VA_CHAR() (*(u8 *)((argp += 4) - 4))
#define VA_INT_PTR() (*(s32 **)((argp += 4) - 4))
#define VA_SHORT_PTR() (*(s16 **)((argp += 4) - 4))
#define VA_VOID_PTR() (*(void **)((argp += 4) - 4))
#define VA_STR() (*(s8 **)((argp += 4) - 4))

#define ARG() \
    _ulong = flags & LONGINT ? VA_INT() : flags & SHORTINT ? VA_SHORT() : VA_INT();

int prnt(void *unused, u8 *fmt0, u8 *argp) {
    u8 *fmt;
    int ch;
    int cnt;
    int n;
    s8 *t;
    u32 _ulong;
    int base;
    int dprec;
    int fieldsz;
    int flags;
    int fpprec;
    int prec;
    int realsz;
    int size;
    int width;
    s8 sign;
    char *digs;
    s8 buf[BUF];

    if (fmt0 == ((void *)0)) {
        return 0;
    }
    fmt = fmt0;
    digs = (char *)"0123456789abcdef";
    for (cnt = 0;; ++fmt) {
        if (!(ch = *fmt)) {
            _putchar_flash();
            return cnt;
        }
        if (ch != '%') {
            _putchar(ch);
            continue;
        }
        flags = 0;
        dprec = 0;
        fpprec = 0;
        width = 0;
        prec = -1;
        sign = '\0';

    rflag:
        switch (*++fmt) {
        case ' ':
            if (!sign) {
                sign = ' ';
            }
            goto rflag;
        case '#':
            flags |= ALT;
            goto rflag;
        case '*':
            if ((width = VA_INT()) >= 0) {
                goto rflag;
            }
            width = -width;
        case '-':
            flags |= LADJUST;
            goto rflag;
        case '+':
            sign = '+';
            goto rflag;
        case '.':
            if (*++fmt == '*') {
                n = VA_INT();
            } else {
                n = 0;
                while (isascii(*fmt) && isdigit(*fmt)) {
                    n = 10 * n + todigit(*fmt++);
                }
                --fmt;
            }
            prec = n < 0 ? -1 : n;
            goto rflag;
        case '0':
            flags |= ZEROPAD;
            goto rflag;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            n = 0;
            do {
                n = 10 * n + todigit(*fmt);
            } while (isascii(*++fmt) && isdigit(*fmt));
            width = n;
            --fmt;
            goto rflag;
        case 'L':
            flags |= LONGDBL;
            goto rflag;
        case 'h':
            flags |= SHORTINT;
            goto rflag;
        case 'l':
            flags |= LONGINT;
            goto rflag;
        case 'c':
            *(t = buf) = VA_CHAR();
            size = 1;
            sign = '\0';
            goto pforw;
        case 'D':
            flags |= LONGINT;
        case 'd':
        case 'i':
            ARG();
            if ((s32)_ulong < 0) {
                _ulong = -_ulong;
                sign = '-';
            }
            base = 10;
            goto number;
        case 'n':
            if (flags & LONGINT) {
                *VA_INT_PTR() = cnt;
            } else if (flags & SHORTINT) {
                *VA_SHORT_PTR() = cnt;
            } else {
                *VA_INT_PTR() = cnt;
            }
            break;
        case 'O':
            flags |= LONGINT;
        case 'o':
            ARG();
            base = 8;
            goto nosign;
        case 'p':
            _ulong = (u32)VA_VOID_PTR();
            base = 16;
            goto nosign;
        case 's':
            if (!(t = VA_STR())) {
                t = (s8 *)"(null)";
            }
            if (prec >= 0) {
                s8 *p;

                if ((p = memchr((u8 *)t, 0, prec))) {
                    size = p - t;
                    if (size > prec) {
                        size = prec;
                    }
                } else {
                    size = prec;
                }
            } else {
                size = strlen((char *)t);
            }
            sign = '\0';
            goto pforw;
        case 'U':
            flags |= LONGINT;
        case 'u':
            ARG();
            base = 10;
            goto nosign;
        case 'X':
            digs = (char *)"0123456789ABCDEF";
        case 'x':
            ARG();
            base = 16;
            if (flags & ALT && _ulong != 0) {
                flags |= HEXPREFIX;
            }
        nosign:
            sign = '\0';
        number:
            if ((dprec = prec) >= 0) {
                flags &= ~ZEROPAD;
            }
            t = buf + BUF;
            if (_ulong != 0 || prec != 0) {
                do {
                    *--t = digs[_ulong % base];
                    _ulong /= base;
                } while (_ulong);
                digs = (char *)"0123456789abcdef";
                if (flags & ALT && base == 8 && *t != '0') {
                    *--t = '0';
                }
            }
            size = buf + BUF - t;

        pforw:
            fieldsz = size + fpprec;
            if (sign) {
                fieldsz++;
            }
            if (flags & HEXPREFIX) {
                fieldsz += 2;
            }
            realsz = dprec > fieldsz ? dprec : fieldsz;

            if ((flags & (LADJUST | ZEROPAD)) == 0 && width) {
                for (n = realsz; n < width; n++) {
                    _putchar(' ');
                }
            }
            if (sign) {
                _putchar(sign);
            }
            if (flags & HEXPREFIX) {
                _putchar('0');
                _putchar((s8)*fmt);
            }
            if ((flags & (LADJUST | ZEROPAD)) == ZEROPAD) {
                for (n = realsz; n < width; n++) {
                    _putchar('0');
                }
            }
            for (n = fieldsz; n < dprec; n++) {
                _putchar('0');
            }
            for (n = size; --n >= 0;) {
                _putchar(*t++);
            }
            while (--fpprec >= 0) {
                _putchar('0');
            }
            if (flags & LADJUST) {
                for (n = realsz; n < width; n++) {
                    _putchar(' ');
                }
            }
            cnt += width > realsz ? width : realsz;
            break;
        case '\0':
            _putchar_flash();
            return cnt;
        default:
            cnt++;
            _putchar((s8)*fmt);
            break;
        }
    }
}
/* rdata tail padding (12 bytes) */
static const u8 rdata_tail_pad[12] = {0};
