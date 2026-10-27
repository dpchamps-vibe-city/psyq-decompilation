INCLUDE_ASM("build/libraries/nonmatchings/libhmd_295", func_00000068);


/* PARKED by /auto_decompilation_loop on 2026-10-27T00:07:49.766Z.
 * Reason: asm-needs-human-approval.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libhmd_295::func_00000068.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include "hmd-localadd.h"

static long func_00000068(LVECTOR *v0, LVECTOR *v1)
{
    long min,b,c,d;
    long r;
    LVECTOR v2;

    {						/* preVectorNormal */
	long d;

	min= 100;
	d= gte_lzc_nom(v0->vx);
	if (min>d) min=d;
	d= gte_lzc_nom(v0->vy);
	if (min>d) min=d;
	d= gte_lzc_nom(v0->vz);
	if (min>d) min=d;

	min=18-min;				/* up to 2^14 */

	if (min>0){
	    v0->vx >>=min; v0->vy >>=min; v0->vz >>=min;
	} else{
	    min=0;
	}
    }

    gte_ldlvl_1(v0->vx);
    gte_ldlvl_2(v0->vy);
    gte_ldlvl_3(v0->vz);
    gte_sqr12();
    v2.vx=gte_stmac_1();
    v2.vy=gte_stmac_2();
    v2.vz=gte_stmac_3();

    b=v2.vx+v2.vy+v2.vz;			/* b= |v0|^2 */

#define VECTORLENMIN 10
    if (b<VECTORLENMIN){
	v1->vx=4096;
	v1->vy=0;
	v1->vz=0;
	return 0;
    }

    InvSquareRoot(b, &c, &d);	/* sqrt(1/(b*4096)) = (c/4096) * (1>>d) */

    /* v1= v0 * sqrt(1/b) = v0 * (c/4096) * (1>>d) * sqrt(4096) */
    v1->vx = ((v0->vx/64)*c)>>d;
    v1->vy = ((v0->vy/64)*c)>>d;
    v1->vz = ((v0->vz/64)*c)>>d;

    /* v1/v0 = (1<<min) * sqrt(b) = (1<<min) * (4096/c) * (1<<d) / sqrt(4096) */
    if (c){
	r=(1<<(min+d+6))/c;
	return r;

    } else{
	v1->vx=4096;
	v1->vy=0;
	v1->vz=0;
	return 0;
    }
}
#endif
