/* Retained DAF3_CM.C: Adiv_f3, with extracted private symbol names. */
static void func_000003AC(u_long *scratch, GsADIV_F3 *ifo, int level)
{
    register GsADIV_P_F3 *in, *out;
    register POLY_F3 *si;
    VECTOR tmp;
    static void func_000006E8();
    static int func_000007C8();
    static void func_00000914();

    in = (GsADIV_P_F3 *)scratch;
    scratch += sizeof(GsADIV_P_F3) / 4;
    out = (GsADIV_P_F3 *)scratch;

    gte_ldv3(&in->vt[0].vx, &in->vt[1].vx, &in->vt[2].vx);
    gte_rtpt();
    si = &ifo->si;
    gte_stflg(&ifo->flg);
    gte_stsxy3_f3((long *)si);
    gte_avsz3();
    gte_stszotz(&ifo->otz);

    if (func_000007C8(si, ifo))
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
        *(ifo->pk + 1) = *((u_long *)si + 1);
        *(ifo->pk + 2) = *((u_long *)si + 2);
        *(ifo->pk + 3) = *((u_long *)si + 3);
        *(ifo->pk + 4) = *((u_long *)si + 4);
        ifo->tag = ifo->org + (ifo->otz >> ifo->shift);
        *(u_long *)ifo->pk = (*ifo->tag & 0x00ffffff) | 0x04000000;
        *ifo->tag = (u_long)ifo->pk & 0x00ffffff;
        ifo->pk += sizeof(POLY_F3) / 4;
        return;
    }
    level++;
    out->vt[0] = in->vt[0];
    func_00000914(&out->vt[1], &in->vt[0], &in->vt[1]);
    func_00000914(&out->vt[2], &in->vt[0], &in->vt[2]);
    func_000006E8(&in->vt[0], &in->vt[1], &out->vt[1], ifo);
    func_000003AC(scratch, ifo, level);

    func_00000914(&out->vt[0], &in->vt[1], &in->vt[2]);
    func_000003AC(scratch, ifo, level);

    out->vt[2] = in->vt[1];
    func_000006E8(&in->vt[1], &in->vt[2], &out->vt[0], ifo);
    func_000003AC(scratch, ifo, level);

    out->vt[1] = in->vt[2];
    func_00000914(&out->vt[2], &in->vt[0], &in->vt[2]);
    func_000006E8(&in->vt[2], &in->vt[0], &out->vt[2], ifo);
    func_000003AC(scratch, ifo, level);
}
