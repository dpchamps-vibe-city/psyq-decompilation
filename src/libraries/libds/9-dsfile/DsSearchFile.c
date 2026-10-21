#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <stdio.h>
#include <strings.h>

/* The low-level file table: DslMAXFILE (64) DslFILE records in .bss. Its
 * name field is the listing's B_00000BE0 (record base + 8). */
extern DslFILE B_00000BD8[64];
extern s32 DS_shell;
extern char RO_STR_000009D8[];
extern char RO_STR_000009F4[];
extern char RO_STR_00000A0C[];
extern char RO_STR_00000A28[];
extern char RO_STR_00000A48[];
extern char RO_STR_00000A54[];

static s32 func_00000358(char *, char *);
static s32 func_00000378(void);
s32 func_0000063C(s32, char *);
s32 func_000006E0(s32);

DslFILE *DsSearchFile(DslFILE *fp, char *name) {
    char path[32];
    char *p;
    char *q;
    char c;
    int level;
    int n;

    if (DS_shell < DsShellOpen()) {
        if (func_00000378() == 0) {
            return 0;
        }
        DS_shell = DsShellOpen();
    }
    if (*name != '\\') {
        return 0;
    }
    path[0] = 0;
    level = 1;
    p = name;
    n = 0;
    for (;;) {
        q = path;
        while (*p != '\\') {
            c = *p;
            if (c == 0) {
                goto done;
            }
            *q = c;
            p++;
            q++;
        }
        if (*p == 0) {
            goto done;
        }
        p++;
        *q = 0;
        level = func_0000063C(level, path);
        if (level == -1) {
            path[0] = 0;
            goto done;
        }
        n++;
        if (n >= 8) {
            goto done;
        }
    }
done:
    if (n >= 8) {
        if (CD_debug > 0) {
            printf(RO_STR_000009D8, name, n);
        }
        return 0;
    }
    if (path[0] == 0) {
        if (CD_debug > 0) {
            printf(RO_STR_000009F4, name);
        }
        return 0;
    }
    *q = 0;
    if (func_000006E0(level) == 0) {
        if (CD_debug > 0) {
            puts(RO_STR_00000A0C);
        }
        return 0;
    }
    if (CD_debug >= 2) {
        printf(RO_STR_00000A28, path);
    }
    for (n = 0; n < 64; n++) {
        if (B_00000BD8[n].name[0] == 0) {
            break;
        }
        if (func_00000358(B_00000BD8[n].name, path) != 0) {
            if (CD_debug >= 2) {
                printf(RO_STR_00000A48, path);
            }
            *fp = B_00000BD8[n];
            return &B_00000BD8[n];
        }
    }
    if (CD_debug > 0) {
        printf(RO_STR_00000A54, path);
    }
    return 0;
}
