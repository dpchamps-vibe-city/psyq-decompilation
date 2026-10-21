#include "common.h"
#include <sys/types.h>
#include <libds.h>

extern char DS_intstr[][12];
extern char D_STR_00000110[];

char *DsIntstr(u_char intr) {
    if (intr >= 8) {
        return D_STR_00000110;
    }
    return DS_intstr[intr];
}
