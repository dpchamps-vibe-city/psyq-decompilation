#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <stdarg.h>
#include <strings.h>

extern s32 D_00001060;
extern s32 D_00001064;
extern u_char *D_00001090;

typedef s8 *S8P;
typedef u_char *UCHARP;

int KanjiFntPrint(int id, ...) {
    va_list ap;
    u_char buf[0x200];
    KENTRY *kp;
    s8 *p;
    u_char *bp;
    int c;
    u_int v;
    u_short ch;
    int count;
    int width;
    s8 zero;
    s16 sign;
    s16 z;

    va_start(ap, id);
    if (((int)id < 0) || (id >= D_00001060)) {
        p = (s8 *)id;
        id = D_00001064;
        if (KanjiFont[id].pkadr == 0) {
            return -1;
        }
    } else {
        p = *(S8P *)(*(int **)&ap)++;
    }
    kp = &KanjiFont[id];
    if ((kp->p >> 1) >= kp->pnum) {
        return -1;
    }
    for (; (c = *p) != 0; p++) {
        switch (c) {
        case '%':
            p++;
            c = *p;
            if (c == '%') {
            copy:
                kp->pkadr[kp->p++] = c;
                if ((kp->p >> 1) >= kp->pnum) {
                    goto end;
                }
            } else {
                width = 0;
                zero = (c == '0');
                while ((u_int)(c - '0') < 10) {
                    width = width * 10 + (c - '0');
                    p++;
                    c = *p;
                }
                width = width * 2;
                if (width <= 0) {
                    width = 1;
                }
                bp = &buf[0x200];
                switch (c) {
                case 'd':
                    v = *(*(int **)&ap)++;
                    if ((int)v < 0) {
                        v = -v;
                        sign = 0x815B;
                    } else {
                        sign = 0;
                    }
                    count = 0;
                    do {
                        *--bp = v % 10 + 0x4F;
                        count += 2;
                        *--bp = (v % 10 + 0x824F) >> 8;
                        v /= 10;
                    } while (count == 0 || v != 0);
                    if (sign != 0) {
                        *--bp = sign;
                        *--bp = sign >> 8;
                        count += 2;
                    }
                    break;
                case 'X':
                case 'x':
                    v = *(*(u_int **)&ap)++;
                    count = 0;
                    do {
                        *--bp = D_00001090[(v & 0xF) * 2 + 1];
                        *--bp = D_00001090[(v & 0xF) * 2];
                        v >>= 4;
                        count += 2;
                    } while (count == 0 || v != 0);
                    if (zero != 0) {
                        z = 0x824F;
                        while (count < width) {
                            *--bp = 0x4F;
                            *--bp = z >> 8;
                            count += 2;
                        }
                    }
                    break;
                case 'c':
                    ch = *(u_short *)(*(int **)&ap)++;
                    if ((u_int)((ch >> 8) - 0x81) < 0x18) {
                        *--bp = ch;
                        *--bp = ch >> 8;
                        count = 2;
                    } else {
                        *--bp = ch;
                        count = 1;
                    }
                    break;
                case 's':
                    bp = *(UCHARP *)(*(int **)&ap)++;
                    count = strlen(bp);
                    break;
                }
                while (count < width) {
                    kp->pkadr[kp->p++] = ' ';
                    if ((kp->p >> 1) >= kp->pnum) {
                        goto end;
                    }
                    width -= 2;
                }
                while (count-- != 0) {
                    kp->pkadr[kp->p++] = *bp++;
                    if ((kp->p >> 1) >= kp->pnum) {
                        goto end;
                    }
                }
            }
            break;
        default:
            goto copy;
        }
    }
end:
    kp->pkadr[kp->p] = 0;
    return kp->p;
}
