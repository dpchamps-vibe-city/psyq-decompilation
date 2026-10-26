/* Retained DAFT3_CM.C: Adiv_ft3, with extracted private symbol names. */
static void func_00000400(u_long *scratch, GsADIV_FT3 *ifo, int level)
{
    register GsADIV_P_FT3 *in, *out;
    register POLY_FT3 *si;
    VECTOR tmp;
    static void func_00000788();
    static int func_000008A0();
    static void func_000009EC();

    in = (GsADIV_P_FT3 *)scratch;
    scratch += sizeof(GsADIV_P_FT3) / 4;
    out = (GsADIV_P_FT3 *)scratch;
    gte_ldv3(&in->vt[0].vx, &in->vt[1].vx, &in->vt[2].vx);
    gte_rtpt();
    si = &ifo->si;
    *(u_short *)&si->u0 = *(u_short *)&in->vt[0].tu;
    *(u_short *)&si->u1 = *(u_short *)&in->vt[1].tu;
    *(u_short *)&si->u2 = *(u_short *)&in->vt[2].tu;
    gte_stflg(&ifo->flg);
    gte_stsxy3_ft3((long *)si);
    gte_avsz3();
    gte_stszotz(&ifo->otz);
    if (func_000008A0(si, ifo))
        return;
    if (ifo->limit == level) {
        if (ifo->flg & 0x7f85e000)
            return;
        else
            goto aaa;
    }
    if (ifo->flg >= 0 && ifo->maxx - ifo->minx < ifo->adivw &&
        ifo->maxy - ifo->miny < ifo->adivh) {
    aaa:
        *ifo->pk = *(u_long *)si;
        *(ifo->pk + 1) = *(u_long *)((u_long *)si + 1);
        *(ifo->pk + 2) = *(u_long *)((u_long *)si + 2);
        *(ifo->pk + 3) = *(u_long *)((u_long *)si + 3);
        *(ifo->pk + 4) = *(u_long *)((u_long *)si + 4);
        *(ifo->pk + 5) = *(u_long *)((u_long *)si + 5);
        *(ifo->pk + 6) = *(u_long *)((u_long *)si + 6);
        *(ifo->pk + 7) = *(u_long *)((u_long *)si + 7);
        ifo->tag = ifo->org + (ifo->otz >> ifo->shift);
        *(u_long *)ifo->pk = (*ifo->tag & 0x00ffffff) | 0x07000000;
        *ifo->tag = (u_long)ifo->pk & 0x00ffffff;
        ifo->pk += sizeof(POLY_FT3) / 4;
        return;
    }
    level++;
    out->vt[0] = in->vt[0];
    func_000009EC(&out->vt[1], &in->vt[0], &in->vt[1]);
    func_000009EC(&out->vt[2], &in->vt[0], &in->vt[2]);
    func_00000400(scratch, ifo, level);
    func_00000788(&in->vt[0], &in->vt[1], &out->vt[1], ifo);

    func_000009EC(&out->vt[0], &in->vt[1], &in->vt[2]);
    func_00000400(scratch, ifo, level);

    out->vt[2] = in->vt[1];
    func_00000400(scratch, ifo, level);
    func_00000788(&in->vt[1], &in->vt[2], &out->vt[0], ifo);

    out->vt[1] = in->vt[2];
    func_000009EC(&out->vt[2], &in->vt[0], &in->vt[2]);
    func_00000400(scratch, ifo, level);
    func_00000788(&in->vt[2], &in->vt[0], &out->vt[2], ifo);
}
