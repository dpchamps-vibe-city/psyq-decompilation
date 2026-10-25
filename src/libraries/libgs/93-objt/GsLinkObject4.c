INCLUDE_ASM("build/libraries/nonmatchings/libgs_93", GsLinkObject4);


/* PARKED by /auto_decompilation_loop on 2026-10-25T06:40:35.543Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgs_93::GsLinkObject4.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <stdio.h>

void GsLinkObject4(unsigned long tmd_base, GsDOBJ2 *objp, int n) {
    unsigned int *temp_a0;
    unsigned int *var_s0;
    unsigned int *var_s5;
    unsigned int temp_a0_2;
    unsigned int temp_s6;
    unsigned int temp_v0;
    unsigned int var_s1;
    unsigned int var_s3;
    unsigned int var_s4;
    int var_v0;
    int temp_v1;
    short var_s2;

    var_s3 = 0;
    var_s1 = 0;
    var_s4 = 0;
    var_s2 = 0;
    temp_a0 = (unsigned int *) (tmd_base + (n * 0x1C));
    objp->tmd = temp_a0;
    var_s0 = *(unsigned int **) ((unsigned char *) temp_a0 + 0x10);
    temp_s6 = *(unsigned int *) ((unsigned char *) temp_a0 + 0x14);
    var_s5 = var_s0;
    if (temp_s6 != 0) {
        do {
            temp_v0 = *var_s0;
            temp_v1 = var_s3;
            temp_a0_2 = var_s1;
            var_s3 = temp_v0 >> 0x18;
            var_s1 = temp_v0 >> 0x10;
            if ((temp_v1 & 0xFF) != 0) {
                if ((var_s3 != (temp_v1 & 0xFF)) || ((var_s1 & 0xFF) != (temp_a0_2 & 0xFF))) {
                    *(short *) ((unsigned char *) var_s5 + 0) = var_s2;
                    var_s2 = 0;
                    var_s5 = var_s0;
                    goto block_6;
                }
            } else {
block_6:
                ;
            }
            switch (var_s3 & 0xFD) {
            case 0x20:
                if (var_s1 & 4) {
            case 0x24:
            case 0x31:
block_10:
                    var_s0 += 6;
                } else {
                    goto block_4;
                }
                break;
            case 0x30:
                if (var_s1 & 4) {
            case 0x25:
            case 0x34:
            case 0x39:
                    var_s0 += 7;
                } else {
                    goto block_5;
                }
                break;
            case 0x28:
                if (var_s1 & 4) {
            case 0x2C:
            case 0x2D:
                    var_s0 += 8;
                } else {
block_5:
                    var_s0 += 5;
                }
                break;
            case 0x21:
            case 0x29:
block_4:
                var_s0 += 4;
                break;
            case 0x3D:
                var_s0 += 0xB;
                break;
            case 0x38:
                if (var_s1 & 4) {
            case 0x35:
            case 0x3C:
                    var_s0 += 9;
                } else {
                    goto block_10;
                }
                break;
            default:
                printf("GPU CODE %02xH not assigned.\n", var_s3);
                break;
            }
            var_s4 += 1;
            var_s2 += 1;
        } while (var_s4 < temp_s6);
    }
    *(short *) ((unsigned char *) var_s5 + 0) = var_s2;
}
#endif
