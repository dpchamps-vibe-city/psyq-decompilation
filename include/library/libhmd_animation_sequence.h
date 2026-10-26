#ifndef LIBHMD_ANIMATION_SEQUENCE_CONTEXT_H
#define LIBHMD_ANIMATION_SEQUENCE_CONTEXT_H

/* Original 03000000.c and GsSEQ accesses in 03000000.OBJ. */
typedef struct {
    u_long *base;
    u_long *src;
    u_long *dst;
    u_long *intr;
} GsARGANIM_OPAQ;

/* Retained 03000000.OBJ assertion strings, .rdata +0 and +0x28. */
extern char RO_STR_000007B0[];
extern char RO_STR_000007D8[];

/* Sequence command format and walker from original Sony 03000000.c. */
typedef unsigned long DWORD;
#define IS_NOT_NORM(x) (((x) & 0x80000000) != 0)
#define IS_JUMP(x) (((x) & 0xc0000000) == 0x80000000)
#define IS_CTRL(x) (((x) & 0xc0000000) == 0xc0000000)
#define TYPE_IDX(x) (((x) & 0x7f000000) >> 24)
#define TFRAME(x) (((x) & 0x00ff0000) >> 16)
#define PARAM_IDX(x) ((x) & 0x0000ffff)
#define SID_DST(x) (((x) & 0x3f800000) >> 23)
#define SID_CND(x) (((x) & 0x007f0000) >> 16)
#define SEQ_IDX(x) ((x) & 0x0000ffff)
#define CODE(x) (((x) & 0x3f800000) >> 23)
#define P1(x) (((x) & 0x007f0000) >> 16)
#define CODE_END 0x01

static u_short get_tctr(u_short idx, DWORD *p, GsSEQ *seq)
{
    int dir = seq->speed < 0 ? -1 : 1;
    DWORD dw;

    while (dw = p[idx], IS_NOT_NORM(dw)) {
        if (IS_JUMP(dw)) {
            int cnd = SID_CND(dw);

            if (cnd == 0 || seq->sid == cnd) {
                int dst = SID_DST(dw);

                if (cnd != 0 || dst != 0) {
                    seq->sid = dst;
                }
                idx = SEQ_IDX(dw);
                continue;
            }
        } else if (IS_CTRL(dw)) {
            int cnd = P1(dw);

            if (CODE(dw) == CODE_END
            && (cnd == 0 || seq->sid == cnd)) {
                return 0xffff;
            }
        } else {
            printf(RO_STR_000007B0, RO_STR_000007D8, 85);
            exit(1);
        }
        idx += dir;
    }
    return idx;
}

#endif
