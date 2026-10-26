#include "common.h"
#include <sys/types.h>
#include <libgte.h>

void SubPol4(POL4 *p, SPOL *sp, int ndiv)
{
    int i, j, k;
    int d, h, index;
    short code;
    SPOL *sp0, *sp2, *sp1, *sp3, *corner;

    code = p->code;
    sp3 = sp;
    sp2 = sp + 72;
    sp1 = sp + 8;
    corner = sp + 80;
    sp3->xy[0] = p->sxy[0][0];
    sp3->xy[1] = p->sxy[0][1];
    sp3->xy[2] = p->sz[0][0];
    sp1->xy[0] = p->sxy[1][0];
    sp1->xy[1] = p->sxy[1][1];
    sp1->xy[2] = p->sz[1][0];
    sp2->xy[0] = p->sxy[2][0];
    sp2->xy[1] = p->sxy[2][1];
    sp2->xy[2] = p->sz[2][0];
    corner->xy[0] = p->sxy[3][0];
    corner->xy[1] = p->sxy[3][1];
    corner->xy[2] = p->sz[3][0];

    sp0 = sp3;
    switch (code) {
    case 5:
        sp3->rgb[0] = p->rgb[0][0];
        sp3->rgb[1] = p->rgb[0][1];
        sp3->rgb[2] = p->rgb[0][2];
        break;
    case 6:
        sp3->uv[0] = p->uv[0][0];
        sp3->uv[1] = p->uv[0][1];
        sp1->uv[0] = p->uv[1][0];
        sp1->uv[1] = p->uv[1][1];
        sp2->uv[0] = p->uv[2][0];
        sp2->uv[1] = p->uv[2][1];
        corner->uv[0] = p->uv[3][0];
        corner->uv[1] = p->uv[3][1];
        break;
    case 8:
        sp3->uv[0] = p->uv[0][0];
        sp3->uv[1] = p->uv[0][1];
        sp1->uv[0] = p->uv[1][0];
        sp1->uv[1] = p->uv[1][1];
        sp2->uv[0] = p->uv[2][0];
        sp2->uv[1] = p->uv[2][1];
        corner->uv[0] = p->uv[3][0];
        corner->uv[1] = p->uv[3][1];
    case 7:
        sp3->rgb[0] = p->rgb[0][0];
        sp3->rgb[1] = p->rgb[0][1];
        sp3->rgb[2] = p->rgb[0][2];
        sp1->rgb[0] = p->rgb[1][0];
        sp1->rgb[1] = p->rgb[1][1];
        sp1->rgb[2] = p->rgb[1][2];
        sp2->rgb[0] = p->rgb[2][0];
        sp2->rgb[1] = p->rgb[2][1];
        sp2->rgb[2] = p->rgb[2][2];
        corner->rgb[0] = p->rgb[3][0];
        corner->rgb[1] = p->rgb[3][1];
        corner->rgb[2] = p->rgb[3][2];
        break;
    }

    for (k = 0; k < ndiv; k++) {
        d = 8 >> k;
        h = d >> 1;
        for (i = 0; i < 9; i += d) {
            for (j = 0; j < 8; j += d) {
                SPOL *sp2;
                index = i * 9 + j;
                sp1 = &sp[index];
                sp2 = &sp[index + d];
                sp3 = &sp[index + h];
                sp3->xy[0] = (sp1->xy[0] + sp2->xy[0]) >> 1;
                sp3->xy[1] = (sp1->xy[1] + sp2->xy[1]) >> 1;
                sp3->xy[2] = (sp1->xy[2] + sp2->xy[2]) >> 1;
                switch (code) {
                case 5:
                    sp3->rgb[0] = sp0->rgb[0];
                    sp3->rgb[1] = sp0->rgb[1];
                    sp3->rgb[2] = sp0->rgb[2];
                    break;
                case 6:
                    sp3->uv[0] = (sp1->uv[0] + sp2->uv[0]) >> 1;
                    sp3->uv[1] = (sp1->uv[1] + sp2->uv[1]) >> 1;
                    break;
                case 8:
                    sp3->uv[0] = (sp1->uv[0] + sp2->uv[0]) >> 1;
                    sp3->uv[1] = (sp1->uv[1] + sp2->uv[1]) >> 1;
                case 7:
                    sp3->rgb[0] = (sp1->rgb[0] + sp2->rgb[0]) >> 1;
                    sp3->rgb[1] = (sp1->rgb[1] + sp2->rgb[1]) >> 1;
                    sp3->rgb[2] = (sp1->rgb[2] + sp2->rgb[2]) >> 1;
                    break;
                }
            }
        }
        for (i = 0; i < 8; i += d) {
            for (j = 0; j < 9; j += d) {
                index = i * 9 + j;
                sp1 = &sp[index];
                sp2 = &sp[index + d * 8 + d];
                sp3 = &sp[index + h * 8 + h];
                sp3->xy[0] = (sp1->xy[0] + sp2->xy[0]) >> 1;
                sp3->xy[1] = (sp1->xy[1] + sp2->xy[1]) >> 1;
                sp3->xy[2] = (sp1->xy[2] + sp2->xy[2]) >> 1;
                switch (code) {
                case 5:
                    sp3->rgb[0] = sp0->rgb[0];
                    sp3->rgb[1] = sp0->rgb[1];
                    sp3->rgb[2] = sp0->rgb[2];
                    break;
                case 6:
                    sp3->uv[0] = (sp1->uv[0] + sp2->uv[0]) >> 1;
                    sp3->uv[1] = (sp1->uv[1] + sp2->uv[1]) >> 1;
                    break;
                case 8:
                    sp3->uv[0] = (sp1->uv[0] + sp2->uv[0]) >> 1;
                    sp3->uv[1] = (sp1->uv[1] + sp2->uv[1]) >> 1;
                case 7:
                    sp3->rgb[0] = (sp1->rgb[0] + sp2->rgb[0]) >> 1;
                    sp3->rgb[1] = (sp1->rgb[1] + sp2->rgb[1]) >> 1;
                    sp3->rgb[2] = (sp1->rgb[2] + sp2->rgb[2]) >> 1;
                    break;
                }
            }
        }
        for (i = 0; i < 8; i += d) {
            for (j = 0; j < 8; j += d) {
                index = i * 9 + j + h;
                sp1 = &sp[index];
                sp2 = &sp[index + d * 8 + d];
                sp3 = &sp[index + h * 8 + h];
                sp3->xy[0] = (sp1->xy[0] + sp2->xy[0]) >> 1;
                sp3->xy[1] = (sp1->xy[1] + sp2->xy[1]) >> 1;
                sp3->xy[2] = (sp1->xy[2] + sp2->xy[2]) >> 1;
                switch (code) {
                case 5:
                    sp3->rgb[0] = sp0->rgb[0];
                    sp3->rgb[1] = sp0->rgb[1];
                    sp3->rgb[2] = sp0->rgb[2];
                    break;
                case 6:
                    sp3->uv[0] = (sp1->uv[0] + sp2->uv[0]) >> 1;
                    sp3->uv[1] = (sp1->uv[1] + sp2->uv[1]) >> 1;
                    break;
                case 8:
                    sp3->uv[0] = (sp1->uv[0] + sp2->uv[0]) >> 1;
                    sp3->uv[1] = (sp1->uv[1] + sp2->uv[1]) >> 1;
                case 7:
                    sp3->rgb[0] = (sp1->rgb[0] + sp2->rgb[0]) >> 1;
                    sp3->rgb[1] = (sp1->rgb[1] + sp2->rgb[1]) >> 1;
                    sp3->rgb[2] = (sp1->rgb[2] + sp2->rgb[2]) >> 1;
                    break;
                }
            }
        }
    }
}
