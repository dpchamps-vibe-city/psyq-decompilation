INCLUDE_ASM("build/libraries/nonmatchings/libgs_42", GsSetLightMatrix);

/* PARKED by /auto_decompilation_loop on 2026-10-23T21:53:35.000Z.
 * Reason: blocked.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgs_42::GsSetLightMatrix.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
void GsSetLightMatrix(MATRIX *mp) {
    MATRIX m = GsLIGHTWSMATRIX;

    PushMatrix(GsLIGHTWSMATRIX.t[0], &GsLIGHTWSMATRIX);
    MulMatrix(&m, mp);
    PopMatrix();
    SetLightMatrix(&m);
}
#endif
