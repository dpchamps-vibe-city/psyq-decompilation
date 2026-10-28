/* Original member: LIBMCX.LIB[26] MCXCMD27.OBJ */
#include "common.h"

int chkMemArea(int arg0, unsigned int addr) {
    unsigned int area;

    area = addr & 0xff000000;
    if (area == 0x00000000 || area == 0x06000000 ||
        (unsigned int)(area - 0x0a000000) <= 0x03000000) {
        return 1;
    }
    if (area == 0x02000000 || area == 0x04000000 || area == 0x08000000) {
        if (arg0 == 0) {
            return 1;
        }
    }
    return 0;
}
