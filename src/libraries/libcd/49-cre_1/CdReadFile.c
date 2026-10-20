#include "common.h"
#include <sys/types.h>
#include <libcd.h>
#include <strings.h>

extern CdlFILE B_00000208 __asm__("$LB_00000208");
extern char CdReadFile_ver[] __asm__("$LRO_STR_000001F8");

int CdReadFile(char *file, u_long *addr, int nbyte) {
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
            strcat(name, CdReadFile_ver);
        }
        if (CdSearchFile(&B_00000208, name) == 0) {
            return 0;
        }
    }
    if (nbyte == 0 || B_00000208.size < nbyte) {
        nbyte = B_00000208.size;
    }
    if (CdControl(CdlSetloc, (u_char *)&B_00000208.pos, 0) == 0) {
        return 0;
    }
    nsec = (nbyte + 0x7ff) / 0x800;
    if (CdRead(nsec, addr, 0x80) == 0) {
        return 0;
    }
    CdIntToPos(CdPosToInt(&B_00000208.pos) + nsec, &B_00000208.pos);
    B_00000208.size -= nsec;
    return nbyte;
}
