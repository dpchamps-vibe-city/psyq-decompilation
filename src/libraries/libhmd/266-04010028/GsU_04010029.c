/*
	RstNrmMIMe primitive driver.

		Originally written by S.Aoki.
		Aug 24,1997	N.Yoshioka.
*/

u_long *
GsU_04010029(GsARGUNIT *sp)
{
	GsARGUNIT_RstVNMIMe	*ap = (GsARGUNIT_RstVNMIMe *)sp;
	u_long		*pMIMeDiffSect	= ap->mime_diff_sect;
	SVECTOR		*pOrgsVNSect	= ap->orgs_vn_sect;
	SVECTOR		*pVNSect	= ap->norm_sect;
	RstVNMIMePrim	*pPrim		= (RstVNMIMePrim *)ap->primp;

	GsRestoreOrgsVNMIMe(pPrim,
		pMIMeDiffSect,	/* MIMeDiffSect ptr */
		pOrgsVNSect,	/* OrgsVNSect ptr */
		pVNSect		/* VNSect ptr */);

	return &((u_long *)pPrim)[pPrim->nSize];
}
