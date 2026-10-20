#include "common.h"

extern char *CD_intstr[];
extern char RO_STR_000000B0[] __asm__("$LRO_STR_000000B0");

char *CdIntstr(unsigned char intr) {
    if (intr >= 7U) {
        return RO_STR_000000B0;
    }
    return CD_intstr[intr];
}
