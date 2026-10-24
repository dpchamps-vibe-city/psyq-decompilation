#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsGetTimInfo(unsigned long *im, GsIMAGE *tim) {
    unsigned long *p;

    tim->pmode = im[0];
    if ((tim->pmode >> 3) & 1) {
        im++;
        p = im + (im[0] >> 2);
        im++;
        tim->cx = (s16) ((u16 *) im)[0];
        tim->cy = (s16) ((u16 *) im)[1];
        im++;
        tim->cw = (u16) ((u16 *) im)[0];
        tim->ch = (u16) ((u16 *) im)[1];
        im++;
        tim->clut = im;
        p++;
        tim->px = (s16) ((u16 *) p)[0];
        tim->py = (s16) ((u16 *) p)[1];
        p++;
        tim->pw = (u16) ((u16 *) p)[0];
        tim->ph = (u16) ((u16 *) p)[1];
        p++;
        tim->pixel = p;
    } else {
        im += 2;
        tim->px = (s16) ((u16 *) im)[0];
        tim->py = (s16) ((u16 *) im)[1];
        im++;
        tim->pw = (u16) ((u16 *) im)[0];
        tim->ph = (u16) ((u16 *) im)[1];
        im++;
        tim->pixel = im;
    }
}
