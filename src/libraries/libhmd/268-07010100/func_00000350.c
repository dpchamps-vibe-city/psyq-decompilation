/* scale_view_param from the retained 07010100.C. */
static long func_0000043C(HMD_P_CAMERA *);
static long func_00000504(long);

static void func_00000350(HMD_P_CAMERA *in, GsRVIEWUNIT *out)
{
    int len;

    len = func_00000504(func_0000043C(in));
    if (len > 15) {
        len -= 15;
        out->vpx = in->vpx >> len;
        out->vpy = in->vpy >> len;
        out->vpz = in->vpz >> len;
        out->vrx = in->vrx >> len;
        out->vry = in->vry >> len;
        out->vrz = in->vrz >> len;
    } else {
        out->vpx = in->vpx;
        out->vpy = in->vpy;
        out->vpz = in->vpz;
        out->vrx = in->vrx;
        out->vry = in->vry;
        out->vrz = in->vrz;
    }
}
