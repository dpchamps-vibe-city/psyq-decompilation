/* Retained DAFT3_CM.C: bunV, with extracted private symbol name. */
static void func_000009EC(VERTC *out, VERTC *in1, VERTC *in2)
{
    out->vx = (in1->vx + in2->vx) / 2;
    out->vy = (in1->vy + in2->vy) / 2;
    out->vz = (in1->vz + in2->vz) / 2;

    out->tu = (in1->tu + in2->tu) / 2;
    out->tv = (in1->tv + in2->tv) / 2;
}
