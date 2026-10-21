#include "common.h"
#include <sys/types.h>
#include <libds.h>

extern char DS_comstr[][12];
extern char D_STR_00000230[];

char *DsComstr(u_char com) {
    if (com >= 0x1C) {
        return D_STR_00000230;
    }
    return DS_comstr[com];
}
