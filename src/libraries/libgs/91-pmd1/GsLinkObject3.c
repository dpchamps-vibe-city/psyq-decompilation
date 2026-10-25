#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

u_long GsLinkObject3(unsigned long pmdBase, GsDOBJ3 *objp)
{
	GsDOBJ3 *obj = objp;
	unsigned long *pmd = (unsigned long *)pmdBase;
	unsigned long base = (unsigned long)pmd;
	unsigned long num;
	int count;
	int i, j;
	int n;

	pmd += 2;
	num = *pmd;
	pmd += 1;
	count = (int)*pmd;
	pmd += 1;
	num = num >> 2 << 2;
	pmdBase += num;
	for (i = 0; i < count; i++) {
		obj->pmd = (unsigned long *)base;
		obj->sv = (unsigned long *)pmdBase;
		obj->base = pmd;
		n = (int)*pmd;
		pmd++;
		j = 0;
		while (j < n) {
			j++;
			pmd++;
		}
		obj++;
	}
	return (u_long)count;
}
