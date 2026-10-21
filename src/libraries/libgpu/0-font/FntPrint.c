#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <stdarg.h>
#include <strings.h>

extern s32 D_00000D30;
extern s32 D_00000D34;
extern u_char *D_0000173C;

typedef s8 *S8P;
typedef u_char *UCHARP;

int FntPrint(int id, ...) {
    va_list ap;
    u_char buf[0x200];
    FENTRY *fp;
    s8 *p;
    u_char *bp;
    int c;
    u_int v;
    int count;
    int width;
    s8 zero;
    int sign;

    va_start(ap, id);
    if (((int)id < 0) || (id >= D_00000D30)) {
        p = (s8 *)id;
        id = D_00000D34;
        if (Font[id].text == 0) {
            return -1;
        }
    } else {
        p = *(S8P *)(*(int **)&ap)++;
    }
    fp = &Font[id];
    if (fp->pos >= fp->step) {
        return -1;
    }
    for (; (c = *p) != 0; p++) {
        switch (c) {
        case '%':
            p++;
            c = *p;
            if (c == '%') {
            copy:
                fp->text[fp->pos++] = c;
                if (fp->pos >= fp->step) {
                    return -1;
                }
            } else {
                width = 0;
                zero = (c == '0');
                while ((u_int)(c - '0') < 10) {
                    width = width * 10 + (c - '0');
                    p++;
                    c = *p;
                }
                if (width <= 0) {
                    width = 1;
                }
                bp = &buf[0x200];
                switch (c) {
                case 'd':
                    v = *(*(int **)&ap)++;
                    if ((int)v < 0) {
                        v = -v;
                        sign = '-';
                    } else {
                        sign = 0;
                    }
                    count = 0;
                    do {
                        *--bp = v % 10 + '0';
                        count++;
                        v /= 10;
                    } while (count == 0 || v != 0);
                    if (sign != 0) {
                        *--bp = sign;
                        count++;
                    }
                    break;
                case 'X':
                case 'x':
                    v = *(*(u_int **)&ap)++;
                    count = 0;
                    do {
                        *--bp = D_0000173C[v & 0xF];
                        v >>= 4;
                        count++;
                    } while (count == 0 || v != 0);
                    if (zero != 0) {
                        while (count < width) {
                            *--bp = '0';
                            count++;
                        }
                    }
                    break;
                case 'c':
                    *--bp = *(u_char *)(*(int **)&ap)++;
                    count = 1;
                    break;
                case 's':
                    bp = *(UCHARP *)(*(int **)&ap)++;
                    count = strlen(bp);
                    break;
                }
                while (count < width) {
                    fp->text[fp->pos++] = ' ';
                    if (fp->pos >= fp->step) {
                        return -1;
                    }
                    width--;
                }
                while (count-- != 0) {
                    fp->text[fp->pos++] = *bp++;
                    if (fp->pos >= fp->step) {
                        return -1;
                    }
                }
            }
            break;
        default:
            goto copy;
        }
    }
    fp->text[fp->pos] = 0;
    return fp->pos;
}
