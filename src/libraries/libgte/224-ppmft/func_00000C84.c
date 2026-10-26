#include "common.h"
#include <sys/types.h>
#include <libgte.h>

/* Private helpers: original 0x1310 interpolates xyz; 0x13D8 copies xyz. */
static void func_00001310(VECTOR *, VECTOR *, VECTOR *, s32);
static void func_000013D8(VECTOR *, VECTOR *);

static int func_00000C84(VECTOR *v, int unused, int plane, VECTOR *out)
{
    int flags[4];
    VECTOR tmp[3];
    int mask;
    int i;

    mask = 0;
    for (i = 0; i < 4; i++) {
        if (v[i].vz < 8) flags[i] = 1;
        else flags[i] = 0;
        mask += flags[i] << i;
    }
    switch (mask) {
    case 0:
        for (i = 0; i < 4; i++) {
            out[i].vx = v[i].vx;
            out[i].vy = v[i].vy;
            out[i].vz = v[i].vz;
        }
        return 1;
    case 1:
        func_00001310(&v[0], &v[1], &tmp[0], plane);
        func_00001310(&v[0], &v[3], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[2], &out[1]);
        func_000013D8(&v[3], &out[2]);
        func_000013D8(&tmp[1], &out[3]);
        func_000013D8(&tmp[0], &out[4]);
        func_000013D8(&v[1], &out[5]);
        func_000013D8(&v[2], &out[6]);
        func_000013D8(&tmp[0], &out[7]);
        return 2;
    case 2:
        func_00001310(&v[1], &v[2], &tmp[0], plane);
        func_00001310(&v[1], &v[0], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[3], &out[1]);
        func_000013D8(&v[0], &out[2]);
        func_000013D8(&tmp[1], &out[3]);
        func_000013D8(&tmp[0], &out[4]);
        func_000013D8(&v[2], &out[5]);
        func_000013D8(&v[3], &out[6]);
        func_000013D8(&tmp[0], &out[7]);
        return 2;
    case 3:
        func_00001310(&v[0], &v[3], &tmp[0], plane);
        func_00001310(&v[1], &v[2], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&tmp[1], &out[1]);
        func_000013D8(&v[2], &out[2]);
        func_000013D8(&v[3], &out[3]);
        return 1;
    case 4:
        func_00001310(&v[2], &v[3], &tmp[0], plane);
        func_00001310(&v[2], &v[1], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[0], &out[1]);
        func_000013D8(&v[1], &out[2]);
        func_000013D8(&tmp[1], &out[3]);
        func_000013D8(&tmp[0], &out[4]);
        func_000013D8(&v[3], &out[5]);
        func_000013D8(&v[0], &out[6]);
        func_000013D8(&tmp[0], &out[7]);
        return 2;
    case 5:
        return 0;
    case 6:
        func_00001310(&v[1], &v[0], &tmp[0], plane);
        func_00001310(&v[2], &v[3], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&tmp[1], &out[1]);
        func_000013D8(&v[3], &out[2]);
        func_000013D8(&v[0], &out[3]);
        return 1;
    case 7:
        func_00001310(&v[3], &v[2], &tmp[0], plane);
        func_00001310(&v[3], &v[0], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[3], &out[1]);
        func_000013D8(&tmp[1], &out[2]);
        func_000013D8(&tmp[0], &out[3]);
        return 1;
    case 8:
        func_00001310(&v[3], &v[0], &tmp[0], plane);
        func_00001310(&v[3], &v[2], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[1], &out[1]);
        func_000013D8(&v[2], &out[2]);
        func_000013D8(&tmp[1], &out[3]);
        func_000013D8(&tmp[0], &out[4]);
        func_000013D8(&v[0], &out[5]);
        func_000013D8(&v[1], &out[6]);
        func_000013D8(&tmp[0], &out[7]);
        return 2;
    case 9:
        func_00001310(&v[3], &v[2], &tmp[0], plane);
        func_00001310(&v[0], &v[1], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&tmp[1], &out[1]);
        func_000013D8(&v[1], &out[2]);
        func_000013D8(&v[2], &out[3]);
        return 1;
    case 10:
        return 0;
    case 11:
        func_00001310(&v[2], &v[1], &tmp[0], plane);
        func_00001310(&v[2], &v[3], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[2], &out[1]);
        func_000013D8(&tmp[1], &out[2]);
        func_000013D8(&tmp[0], &out[3]);
        return 1;
    case 12:
        func_00001310(&v[2], &v[1], &tmp[0], plane);
        func_00001310(&v[3], &v[0], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&tmp[1], &out[1]);
        func_000013D8(&v[0], &out[2]);
        func_000013D8(&v[1], &out[3]);
        return 1;
    case 13:
        func_00001310(&v[1], &v[0], &tmp[0], plane);
        func_00001310(&v[1], &v[2], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[1], &out[1]);
        func_000013D8(&tmp[1], &out[2]);
        func_000013D8(&tmp[0], &out[3]);
        return 1;
    case 14:
        func_00001310(&v[0], &v[3], &tmp[0], plane);
        func_00001310(&v[0], &v[1], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[0], &out[1]);
        func_000013D8(&tmp[1], &out[2]);
        func_000013D8(&tmp[0], &out[3]);
        return 1;
    case 15:
        return 0;
    }
}


/* PARKED by /auto_decompilation_loop on 2026-10-26T11:37:10.414Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgte_224::pers_map.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>

/* Private helpers: original 0x1310 interpolates xyz; 0x13D8 copies xyz. */
static void func_00001310(VECTOR *, VECTOR *, VECTOR *, s32);
static void func_000013D8(VECTOR *, VECTOR *);

static int func_00000C84(VECTOR *v, int (*tex)[2], int plane, VECTOR *out,
                         int (*clipTex)[2])
{
    int flags[4];
    VECTOR tmp[3];
    int mask;
    int i;

    mask = 0;
    for (i = 0; i < 4; i++) {
        if (v[i].vz < 8) flags[i] = 1;
        else flags[i] = 0;
        mask += flags[i] << i;
    }
    switch (mask) {
    case 0:
        for (i = 0; i < 4; i++) {
            out[i].vx = v[i].vx;
            out[i].vy = v[i].vy;
            out[i].vz = v[i].vz;
        }
        return 1;
    case 1:
        func_00001310(&v[0], &v[1], &tmp[0], plane);
        func_00001310(&v[0], &v[3], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[2], &out[1]);
        func_000013D8(&v[3], &out[2]);
        func_000013D8(&tmp[1], &out[3]);
        func_000013D8(&tmp[0], &out[4]);
        func_000013D8(&v[1], &out[5]);
        func_000013D8(&v[2], &out[6]);
        func_000013D8(&tmp[0], &out[7]);
        return 2;
    case 2:
        func_00001310(&v[1], &v[2], &tmp[0], plane);
        func_00001310(&v[1], &v[0], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[3], &out[1]);
        func_000013D8(&v[0], &out[2]);
        func_000013D8(&tmp[1], &out[3]);
        func_000013D8(&tmp[0], &out[4]);
        func_000013D8(&v[2], &out[5]);
        func_000013D8(&v[3], &out[6]);
        func_000013D8(&tmp[0], &out[7]);
        return 2;
    case 3:
        func_00001310(&v[0], &v[3], &tmp[0], plane);
        func_00001310(&v[1], &v[2], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&tmp[1], &out[1]);
        func_000013D8(&v[2], &out[2]);
        func_000013D8(&v[3], &out[3]);
        return 1;
    case 4:
        func_00001310(&v[2], &v[3], &tmp[0], plane);
        func_00001310(&v[2], &v[1], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[0], &out[1]);
        func_000013D8(&v[1], &out[2]);
        func_000013D8(&tmp[1], &out[3]);
        func_000013D8(&tmp[0], &out[4]);
        func_000013D8(&v[3], &out[5]);
        func_000013D8(&v[0], &out[6]);
        func_000013D8(&tmp[0], &out[7]);
        return 2;
    case 5:
        return 0;
    case 6:
        func_00001310(&v[1], &v[0], &tmp[0], plane);
        func_00001310(&v[2], &v[3], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&tmp[1], &out[1]);
        func_000013D8(&v[3], &out[2]);
        func_000013D8(&v[0], &out[3]);
        return 1;
    case 7:
        func_00001310(&v[3], &v[2], &tmp[0], plane);
        func_00001310(&v[3], &v[0], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[3], &out[1]);
        func_000013D8(&tmp[1], &out[2]);
        func_000013D8(&tmp[0], &out[3]);
        return 1;
    case 8:
        func_00001310(&v[3], &v[0], &tmp[0], plane);
        func_00001310(&v[3], &v[2], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[1], &out[1]);
        func_000013D8(&v[2], &out[2]);
        func_000013D8(&tmp[1], &out[3]);
        func_000013D8(&tmp[0], &out[4]);
        func_000013D8(&v[0], &out[5]);
        func_000013D8(&v[1], &out[6]);
        func_000013D8(&tmp[0], &out[7]);
        return 2;
    case 9:
        func_00001310(&v[3], &v[2], &tmp[0], plane);
        func_00001310(&v[0], &v[1], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&tmp[1], &out[1]);
        func_000013D8(&v[1], &out[2]);
        func_000013D8(&v[2], &out[3]);
        return 1;
    case 10:
        return 0;
    case 11:
        func_00001310(&v[2], &v[1], &tmp[0], plane);
        func_00001310(&v[2], &v[3], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[2], &out[1]);
        func_000013D8(&tmp[1], &out[2]);
        func_000013D8(&tmp[0], &out[3]);
        return 1;
    case 12:
        func_00001310(&v[2], &v[1], &tmp[0], plane);
        func_00001310(&v[3], &v[0], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&tmp[1], &out[1]);
        func_000013D8(&v[0], &out[2]);
        func_000013D8(&v[1], &out[3]);
        return 1;
    case 13:
        func_00001310(&v[1], &v[0], &tmp[0], plane);
        func_00001310(&v[1], &v[2], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[1], &out[1]);
        func_000013D8(&tmp[1], &out[2]);
        func_000013D8(&tmp[0], &out[3]);
        return 1;
    case 14:
        func_00001310(&v[0], &v[3], &tmp[0], plane);
        func_00001310(&v[0], &v[1], &tmp[1], plane);
        func_000013D8(&tmp[0], &out[0]);
        func_000013D8(&v[0], &out[1]);
        func_000013D8(&tmp[1], &out[2]);
        func_000013D8(&tmp[0], &out[3]);
        return 1;
    case 15:
        return 0;
    }
}
#endif
