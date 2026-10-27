#include "common.h"
#include <libmath.h>
#include <stdarg.h>

#define LONGINT 0x01
#define LONGDBL 0x02
#define SHORTINT 0x04
#define ALT 0x08
#define LADJUST 0x10
#define ZEROPAD 0x20
#define HEXPREFIX 0x40

#define BUF 0x15C

extern u8 _ctype_[];

extern char RO_STR_00001608[];
extern char RO_STR_0000161C[];
extern char RO_STR_00001624[];
extern double RO_00001638;

extern int putchar();
extern u8 *memchr(u8 *, s32, s32);
extern u32 strlen(u8 *);
static int func_00000AD8(double number, int prec, int flags, s8 *signp,
    unsigned char fmt, s8 *startp, s8 *endp);

#define isascii(c) ((u32)(c) < 0x80)
#define isdigit(c) ((_ctype_ + 1)[(u8)(c)] & 4)
#define todigit(c) ((c) - '0')

#define VA_INT() (*(s32 *)((argp += 4) - 4))
#define VA_SHORT() (*(u16 *)((argp += 4) - 4))
#define VA_CHAR() (*(u8 *)((argp += 4) - 4))
#define VA_INT_PTR() (*(s32 **)((argp += 4) - 4))
#define VA_SHORT_PTR() (*(s16 **)((argp += 4) - 4))
#define VA_STR() (*(s8 **)((argp += 4) - 4))
#define VA_DBL() (*(double *)((argp += 8) - 8))

#define ARG() \
    _ulong = flags & LONGINT ? VA_INT() : flags & SHORTINT ? VA_SHORT() : VA_INT();

static int func_000000EC(char *dest, char *fmt0, va_list args, int mode) {
    u8 *argp;
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
    s8 fsign;
    char *digs;
    u8 *argp0;
    s8 buf[BUF + 4];
    double number;

    argp = (u8 *)args;
    argp0 = argp;
    if (fmt0 == ((void *)0)) {
        return 0;
    }
    fmt = (u8 *)fmt0;
    digs = RO_STR_00001608;
    for (cnt = 0;; ++fmt) {
        ch = *fmt;
        if (!ch) {
            return cnt;
        }
        if (ch != '%') {
            if (mode) {
                *dest = ch;
                dest[1] = 0;
                dest++;
            } else {
                dest = (char *)putchar(ch);
            }
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
            *(t = (s8 *)buf) = VA_CHAR();
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
        case 'E':
        case 'G':
        case 'e':
        case 'f':
        case 'g':
            if (!mode && argp == argp0) {
                argp += 4;
            } else if ((mode != 1 || argp != argp0) && ((int)argp & 7)) {
                argp += 4;
            }
            number = VA_DBL();
            if (prec >= 40) {
                if ((*fmt != 'g' && *fmt != 'G') || (flags & ALT)) {
                    fpprec = prec - 39;
                }
                prec = 39;
            } else if (prec == -1) {
                prec = 6;
            }
            if (number < 0 && number != RO_00001638) {
                fsign = '-';
                number = -number;
            } else {
                fsign = 0;
            }
            *buf = 0;
            size = func_00000AD8(number, prec, flags, &fsign, *fmt,
                                 (s8 *)buf, (s8 *)buf + BUF);
            if (fsign) {
                sign = '-';
            }
            if (*buf) {
                t = (s8 *)buf;
            } else {
                t = (s8 *)buf + 1;
            }
            goto pforw;
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
            _ulong = (u32)VA_INT();
            base = 16;
            goto nosign;
        case 's':
            if (!(t = VA_STR())) {
                t = (s8 *)RO_STR_0000161C;
            }
            if (prec >= 0) {
                s8 *p;

                if ((p = (s8 *)memchr((u8 *)t, 0, prec))) {
                    size = p - t;
                    if (size > prec) {
                        size = prec;
                    }
                } else {
                    size = prec;
                }
            } else {
                size = strlen((u8 *)t);
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
            digs = RO_STR_00001624;
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
            t = (s8 *)buf + BUF;
            if (_ulong != 0 || dprec != 0) {
                do {
                    *--t = digs[_ulong % base];
                    _ulong /= base;
                } while (_ulong);
                digs = RO_STR_00001608;
                if (flags & ALT && base == 8 && *t != '0') {
                    *--t = '0';
                }
            }
            size = (s8 *)buf + BUF - t;

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
                    if (mode) {
                        *dest = ' ';
                        dest[1] = 0;
                        dest++;
                    } else {
                        dest = (char *)putchar(' ');
                    }
                }
            }
            if (sign) {
                if (mode) {
                    *dest = sign;
                    dest[1] = 0;
                    dest++;
                } else {
                    dest = (char *)putchar(sign);
                }
            }
            if (flags & HEXPREFIX) {
                if (mode) {
                    *dest = '0';
                    dest[1] = 0;
                    dest++;
                } else {
                    dest = (char *)putchar('0');
                }
                if (mode) {
                    *dest = *fmt;
                    dest[1] = 0;
                    dest++;
                } else {
                    dest = (char *)putchar((s8)*fmt);
                }
            }
            if ((flags & (LADJUST | ZEROPAD)) == ZEROPAD) {
                for (n = realsz; n < width; n++) {
                    if (mode) {
                        *dest = '0';
                        dest[1] = 0;
                        dest++;
                    } else {
                        dest = (char *)putchar('0');
                    }
                }
            }
            for (n = fieldsz; n < dprec; n++) {
                if (mode) {
                    *dest = '0';
                    dest[1] = 0;
                    dest++;
                } else {
                    dest = (char *)putchar('0');
                }
            }
            for (n = size; --n >= 0;) {
                if (mode) {
                    *dest = *t++;
                    dest[1] = 0;
                    dest++;
                } else {
                    dest = (char *)putchar(*t++);
                }
            }
            while (--fpprec >= 0) {
                if (mode) {
                    *dest = '0';
                    dest[1] = 0;
                    dest++;
                } else {
                    dest = (char *)putchar('0');
                }
            }
            if (flags & LADJUST) {
                for (n = realsz; n < width; n++) {
                    if (mode) {
                        *dest = ' ';
                        dest[1] = 0;
                        dest++;
                    } else {
                        dest = (char *)putchar(' ');
                    }
                }
            }
            cnt += width > realsz ? width : realsz;
            break;
        case '\0':
            return cnt;
        default:
            if (mode) {
                *dest = *fmt;
                dest[1] = 0;
                dest++;
            } else {
                dest = (char *)putchar((s8)*fmt);
            }
            cnt++;
            break;
        }
    }
}
