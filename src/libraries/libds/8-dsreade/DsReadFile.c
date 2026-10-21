#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <strings.h>

extern DslFILE B_000001F8;
extern char RO_STR_000001E8[];

int DsReadFile(char *file, u_long *addr, int nbyte) {
    s8 name[80];
    int nsec;
    u_char c;

    if (file != 0) {
        strcpy(name, file);
        for (nsec = 0; name[nsec] != 0; nsec++) {
            c = name[nsec];
            if ((u_char)(c - 'a') < 26) {
                name[nsec] = c - 0x20;
            }
        }
        if (name[nsec - 2] != ';') {
            strcat(name, RO_STR_000001E8);
        }
        if (DsSearchFile(&B_000001F8, name) == 0) {
            return 0;
        }
    }
    if (nbyte == 0 || B_000001F8.size < nbyte) {
        nbyte = B_000001F8.size;
    }
    nsec = (nbyte + 0x7ff) / 0x800;
    if (DsRead(&B_000001F8.pos, nsec, addr, 0x80) == 0) {
        return 0;
    }
    DsIntToPos(DsPosToInt(&B_000001F8.pos) + nsec, &B_000001F8.pos);
    B_000001F8.size -= nsec;
    return nbyte;
}
