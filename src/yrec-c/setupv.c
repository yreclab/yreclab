/* setupv.f -- translated by f2c (version 20061008).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal amum[5000], cpm[5000], delm[5000], delam[5000], delrm[5000], 
	    esumm[5000], om[5000], qdtm[5000], thdifm[5000], velm[5000], 
	    viscm[5000], epsm[5000];
} mdphy_;

#define mdphy_1 mdphy_

struct {
    doublereal fact1[5000], fact2[5000], fact3[5000], fact4[5000], fact5[5000]
	    , fact7[5000], fact8[5000];
} vfact_;

#define vfact_1 vfact_

struct {
    doublereal faci[20000]	/* was [4][5000] */;
} intfac_;

#define intfac_1 intfac_

struct {
    doublereal fact6[5000], fes1[5000], fes2[5000], fgsfj[5000], fgsfk[5000], 
	    fes3[5000];
} taukh_;

#define taukh_1 taukh_

struct {
    doublereal alm[5000], delami[5000], delmi[5000], dm[5000], epsilm[5000], 
	    hgm[5000], hs3[5000], pm[5000], qdtmi[5000], rm[5000], tm[5000];
} intvar_;

#define intvar_1 intvar_

struct {
    doublereal tho[5000], thn[5000], thm[5000], ddelm[5000], festime[5000], 
	    thp[5000], qwrst[5000], wmst[5000], qwrmst[5000];
} oldrot2_;

#define oldrot2_1 oldrot2_

struct {
    doublereal sqod[5000], sqot[5000], sqed[5000], sqet[5000], fracnuc[5000];
} rotder_;

#define rotder_1 rotder_

struct {
    doublereal eqqcod[5000], eqqqcod[5000], qqcod[5000], qqqcod[5000];
} egridder_;

#define egridder_1 egridder_

struct {
    doublereal facd2[5000], facd3[5000], vesd2[5000], vesd3[5000], ecod5[5000]
	    , ecod6[5000], fgeom[5000], fv0[5000], fv1a[5000], fv1b[5000], 
	    fv2a[5000], fv2b[5000], ev0[5000], ev1a[5000], ev1b[5000], ev2a[
	    5000], ev2b[5000], dss[5000], dgsf[5000], ess[5000], egsf[5000];
} difad3_;

#define difad3_1 difad3_

struct {
    doublereal vfc[5000];
    logical lvfc, ldifad;
} varfc_;

#define varfc_1 varfc_

/* Table of constant values */

static doublereal c_b8 = 10.;

/* $$$$$$ */
/*       SUBROUTINE SETUPV(HD,HG,HL,HP,HR,HS1,HT,IMIN,IMAX,LCZ,M,HRU,  ! KC 2025-05-31 */
/* Subroutine */ int setupv_(doublereal *hd, doublereal *hg, doublereal *hl, 
	doublereal *hp, doublereal *hr, doublereal *hs1, doublereal *ht, 
	integer *imin, integer *imax, integer *m, doublereal *hru, doublereal 
	*qwrmax)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double exp(doublereal), d_lg10(doublereal *), sqrt(doublereal), pow_dd(
	    doublereal *, doublereal *);

    /* Local variables */
    static integer i__;
    static doublereal c1, d1, d2, d3, d4;
    static integer i0, i1;
    static doublereal f1, f2, f3, v0, a21, a31, a41, a42, a43, a32, cg, ff, 
	    em, fl, dr, cg2, xa1, xa2, xa3, xa4, fac, eta, qdr, opm[5000], 
	    htm, htp, fnu, qc1r, htp2, ddel, cpmi[5000], dmin__, hpsc, htsc, 
	    qetm, qhtr, cpigi, delmu, qchit, qqc1rr, qqchitr;

/* MHP 06/02 ADDED FACT7 AND FACT8 FOR DIF/AD TREATMENT */
/* MHP 3/92 COMMON BLOCK ADDED FOR SHEAR VELOCITY */
/* MHP 06/02 */
/* Time change of theta */
/* CAPPA AND EPSILON DERIVATIVES */
/* DEFINITION TERMS FOR THE SECOND AND THIRD DERIVATIVE */
/* TERMS IN THE ZAHN FORMULATION */
/* MHP 06/02 */
/* HIGHER ORDER TERMS IN M.C. VELOCITY */
/* JvS 09/25 CHANGED CPM --> CPMI TO AVOID CONFLICT IN MDPHY */
/*      *          HT(JSON),LCZ(JSON),HRU(JSON),QWRMAX(JSON),  ! KC 2025-05-31 */
/*   THE PROCEDURE FOR CALCULATING STABILITY AGAINST ROTATIONALLY INDUCED */
/*   MIXING IS AS FOLLOWS: */
/*      STABILITY IS CALCULATED FOR THE I/I-1 INTERFACE; QUANTITIES RELATED */
/*      TO STABILITY AT THIS INTERFACE ARE STORED IN ARRAY ELEMENT(S) I. */
/*      EACH STABILITY CRITERION IS EXPRESSED AS FOLLOWS: */
/*         A COMBINATION OF VARIABLES(RHO,P,ETC.)STORED AT EACH SHELL */
/*         MULTIPLIED BY A GRADIENT BETWEEN THE SHELLS MUST BE LESS THAN */
/*         SOME CRITICAL NUMBER. */
/*  SETUPV CALCULATES THE FACTORS WHICH ARE BASED ON */
/*  QUANTITIES WHICH DO NOT CHANGE DURING A DIFFUSION TIMESTEP. */

/*  FIND UNLOGGED RADII OF THE MODEL POINTS. */
    /* Parameter adjustments */
    --qwrmax;
    --hru;
    --ht;
    --hs1;
    --hr;
    --hp;
    --hl;
    --hg;
    --hd;

    /* Function Body */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	hru[i__] = exp(const1_1.cln * hr[i__]);
/* L5: */
    }
/*  FIND LOCATION (IN RADIUS) OF THE MIDPOINTS OF THE INTERFACES. */
    i__1 = *m;
    for (i__ = 2; i__ <= i__1; ++i__) {
	intvar_1.rm[i__ - 1] = (hru[i__] + hru[i__ - 1]) * .5;
/* L10: */
    }
/*  FIND 4 POINT LAGRANGIAN INTERPOLATION FACTORS FOR ALL INTERFACES. */
/*  INTERFACE BETWEEN FIRST AND SECOND POINT USES THE FIRST 4 POINTS FOR */
/*  INTERPOLATION; BETWEEN LAST AND SECOND TO LAST USES THE LAST FOUR POINTS */
/*  AND BETWEEN I AND I-1 USES I-2,I-1,I,I+1. */
/*  TREATMENT OF FIRST INTERFACE. */
    if (*imin < 3) {
	a43 = hru[4] - hru[3];
	a42 = hru[4] - hru[2];
	a41 = hru[4] - hru[1];
	a32 = hru[3] - hru[2];
	a31 = hru[3] - hru[1];
	a21 = hru[2] - hru[1];
	d1 = -a21 * a31 * a41;
	d2 = a21 * a32 * a42;
	d3 = -a31 * a32 * a43;
	d4 = a41 * a42 * a43;
	xa1 = intvar_1.rm[1] - hru[1];
	xa2 = intvar_1.rm[1] - hru[2];
	xa3 = intvar_1.rm[1] - hru[3];
	xa4 = intvar_1.rm[1] - hru[4];
	intfac_1.faci[4] = xa2 * xa3 * xa4 / d1;
	intfac_1.faci[5] = xa1 * xa3 * xa4 / d2;
	intfac_1.faci[6] = xa1 * xa2 * xa4 / d3;
	intfac_1.faci[7] = xa1 * xa2 * xa3 / d4;
	i0 = 3;
	intvar_1.pm[1] = exp(const1_1.cln * (hp[1] * intfac_1.faci[4] + hp[2] 
		* intfac_1.faci[5] + hp[3] * intfac_1.faci[6] + hp[4] * 
		intfac_1.faci[7]));
	intvar_1.tm[1] = exp(const1_1.cln * (ht[1] * intfac_1.faci[4] + ht[2] 
		* intfac_1.faci[5] + ht[3] * intfac_1.faci[6] + ht[4] * 
		intfac_1.faci[7]));
	intvar_1.dm[1] = exp(const1_1.cln * (hd[1] * intfac_1.faci[4] + hd[2] 
		* intfac_1.faci[5] + hd[3] * intfac_1.faci[6] + hd[4] * 
		intfac_1.faci[7]));
	intvar_1.delmi[1] = mdphy_1.delrm[0] * intfac_1.faci[4] + 
		mdphy_1.delrm[1] * intfac_1.faci[5] + mdphy_1.delrm[2] * 
		intfac_1.faci[6] + mdphy_1.delrm[3] * intfac_1.faci[7];
	intvar_1.delami[1] = mdphy_1.delam[0] * intfac_1.faci[4] + 
		mdphy_1.delam[1] * intfac_1.faci[5] + mdphy_1.delam[2] * 
		intfac_1.faci[6] + mdphy_1.delam[3] * intfac_1.faci[7];
	intvar_1.qdtmi[1] = mdphy_1.qdtm[0] * intfac_1.faci[4] + mdphy_1.qdtm[
		1] * intfac_1.faci[5] + mdphy_1.qdtm[2] * intfac_1.faci[6] + 
		mdphy_1.qdtm[3] * intfac_1.faci[7];
	intvar_1.hs3[1] = hs1[1] * intfac_1.faci[4] + hs1[2] * intfac_1.faci[
		5] + hs1[3] * intfac_1.faci[6] + hs1[4] * intfac_1.faci[7];
	intvar_1.epsilm[1] = mdphy_1.esumm[0] * intfac_1.faci[4] + 
		mdphy_1.esumm[1] * intfac_1.faci[5] + mdphy_1.esumm[2] * 
		intfac_1.faci[6] + mdphy_1.esumm[3] * intfac_1.faci[7];
	intvar_1.alm[1] = const_1.clsun * (hl[1] * intfac_1.faci[4] + hl[2] * 
		intfac_1.faci[5] + hl[3] * intfac_1.faci[6] + hl[4] * 
		intfac_1.faci[7]);
	intvar_1.hgm[1] = hg[1] * intfac_1.faci[4] + hg[2] * intfac_1.faci[5] 
		+ hg[3] * intfac_1.faci[6] + hg[4] * intfac_1.faci[7];
/*  opacity. */
	opm[1] = mdphy_1.om[0] * intfac_1.faci[4] + mdphy_1.om[1] * 
		intfac_1.faci[5] + mdphy_1.om[2] * intfac_1.faci[6] + 
		mdphy_1.om[3] * intfac_1.faci[7];
/*  specific heat */
	cpmi[1] = mdphy_1.cpm[0] * intfac_1.faci[4] + mdphy_1.cpm[1] * 
		intfac_1.faci[5] + mdphy_1.cpm[2] * intfac_1.faci[6] + 
		mdphy_1.cpm[3] * intfac_1.faci[7];
    } else {
	i0 = *imin;
    }
/*  TREATMENT OF LAST INTERFACE. */
    if (*imax == *m) {
	a43 = hru[*m] - hru[*m - 1];
	a42 = hru[*m] - hru[*m - 2];
	a41 = hru[*m] - hru[*m - 3];
	a32 = hru[*m - 1] - hru[*m - 2];
	a31 = hru[*m - 1] - hru[*m - 3];
	a21 = hru[*m - 2] - hru[*m - 3];
	d1 = -a21 * a31 * a41;
	d2 = a21 * a32 * a42;
	d3 = -a31 * a32 * a43;
	d4 = a41 * a42 * a43;
	xa1 = intvar_1.rm[*m - 1] - hru[*m - 3];
	xa2 = intvar_1.rm[*m - 1] - hru[*m - 2];
	xa3 = intvar_1.rm[*m - 1] - hru[*m - 1];
	xa4 = intvar_1.rm[*m - 1] - hru[*m];
	intfac_1.faci[(*m << 2) - 4] = xa2 * xa3 * xa4 / d1;
	intfac_1.faci[(*m << 2) - 3] = xa1 * xa3 * xa4 / d2;
	intfac_1.faci[(*m << 2) - 2] = xa1 * xa2 * xa4 / d3;
	intfac_1.faci[(*m << 2) - 1] = xa1 * xa2 * xa3 / d4;
	i1 = *m - 1;
	intvar_1.pm[*m - 1] = exp(const1_1.cln * (hp[*m - 3] * intfac_1.faci[(
		*m << 2) - 4] + hp[*m - 2] * intfac_1.faci[(*m << 2) - 3] + 
		hp[*m - 1] * intfac_1.faci[(*m << 2) - 2] + hp[*m] * 
		intfac_1.faci[(*m << 2) - 1]));
	intvar_1.tm[*m - 1] = exp(const1_1.cln * (ht[*m - 3] * intfac_1.faci[(
		*m << 2) - 4] + ht[*m - 2] * intfac_1.faci[(*m << 2) - 3] + 
		ht[*m - 1] * intfac_1.faci[(*m << 2) - 2] + ht[*m] * 
		intfac_1.faci[(*m << 2) - 1]));
	intvar_1.dm[*m - 1] = exp(const1_1.cln * (hd[*m - 3] * intfac_1.faci[(
		*m << 2) - 4] + hd[*m - 2] * intfac_1.faci[(*m << 2) - 3] + 
		hd[*m - 1] * intfac_1.faci[(*m << 2) - 2] + hd[*m] * 
		intfac_1.faci[(*m << 2) - 1]));
	intvar_1.delmi[*m - 1] = mdphy_1.delrm[*m - 4] * intfac_1.faci[(*m << 
		2) - 4] + mdphy_1.delrm[*m - 3] * intfac_1.faci[(*m << 2) - 3]
		 + mdphy_1.delrm[*m - 2] * intfac_1.faci[(*m << 2) - 2] + 
		mdphy_1.delrm[*m - 1] * intfac_1.faci[(*m << 2) - 1];
	intvar_1.delami[*m - 1] = mdphy_1.delam[*m - 4] * intfac_1.faci[(*m <<
		 2) - 4] + mdphy_1.delam[*m - 3] * intfac_1.faci[(*m << 2) - 
		3] + mdphy_1.delam[*m - 2] * intfac_1.faci[(*m << 2) - 2] + 
		mdphy_1.delam[*m - 1] * intfac_1.faci[(*m << 2) - 1];
	intvar_1.qdtmi[*m - 1] = mdphy_1.qdtm[*m - 4] * intfac_1.faci[(*m << 
		2) - 4] + mdphy_1.qdtm[*m - 3] * intfac_1.faci[(*m << 2) - 3] 
		+ mdphy_1.qdtm[*m - 2] * intfac_1.faci[(*m << 2) - 2] + 
		mdphy_1.qdtm[*m - 1] * intfac_1.faci[(*m << 2) - 1];
	intvar_1.hs3[*m - 1] = hs1[*m - 3] * intfac_1.faci[(*m << 2) - 4] + 
		hs1[*m - 2] * intfac_1.faci[(*m << 2) - 3] + hs1[*m - 1] * 
		intfac_1.faci[(*m << 2) - 2] + hs1[*m] * intfac_1.faci[(*m << 
		2) - 1];
	intvar_1.epsilm[*m - 1] = mdphy_1.esumm[*m - 4] * intfac_1.faci[(*m <<
		 2) - 4] + mdphy_1.esumm[*m - 3] * intfac_1.faci[(*m << 2) - 
		3] + mdphy_1.esumm[*m - 2] * intfac_1.faci[(*m << 2) - 2] + 
		mdphy_1.esumm[*m - 1] * intfac_1.faci[(*m << 2) - 1];
	intvar_1.alm[*m - 1] = const_1.clsun * (hl[*m - 3] * intfac_1.faci[(*
		m << 2) - 4] + hl[*m - 2] * intfac_1.faci[(*m << 2) - 3] + hl[
		*m - 1] * intfac_1.faci[(*m << 2) - 2] + hl[*m] * 
		intfac_1.faci[(*m << 2) - 1]);
	intvar_1.hgm[*m - 1] = hg[*m - 3] * intfac_1.faci[(*m << 2) - 4] + hg[
		*m - 2] * intfac_1.faci[(*m << 2) - 3] + hg[*m - 1] * 
		intfac_1.faci[(*m << 2) - 2] + hg[*m] * intfac_1.faci[(*m << 
		2) - 1];
/*  opacity. */
	opm[*m - 1] = mdphy_1.om[*m - 4] * intfac_1.faci[(*m << 2) - 4] + 
		mdphy_1.om[*m - 3] * intfac_1.faci[(*m << 2) - 3] + 
		mdphy_1.om[*m - 2] * intfac_1.faci[(*m << 2) - 2] + 
		mdphy_1.om[*m - 1] * intfac_1.faci[(*m << 2) - 1];
/*  specific heat */
	cpmi[*m - 1] = mdphy_1.cpm[*m - 4] * intfac_1.faci[(*m << 2) - 4] + 
		mdphy_1.cpm[*m - 3] * intfac_1.faci[(*m << 2) - 3] + 
		mdphy_1.cpm[*m - 2] * intfac_1.faci[(*m << 2) - 2] + 
		mdphy_1.cpm[*m - 1] * intfac_1.faci[(*m << 2) - 1];
    } else {
	i1 = *imax;
    }
/*  COMPUTE INTERPOLATION FACTORS FOR ALL OTHER POINTS. */
    i__1 = i1;
    for (i__ = i0; i__ <= i__1; ++i__) {
	a43 = hru[i__ + 1] - hru[i__];
	a42 = hru[i__ + 1] - hru[i__ - 1];
	a41 = hru[i__ + 1] - hru[i__ - 2];
	a32 = hru[i__] - hru[i__ - 1];
	a31 = hru[i__] - hru[i__ - 2];
	a21 = hru[i__ - 1] - hru[i__ - 2];
	d1 = -a21 * a31 * a41;
	d2 = a21 * a32 * a42;
	d3 = -a31 * a32 * a43;
	d4 = a41 * a42 * a43;
	xa1 = intvar_1.rm[i__ - 1] - hru[i__ - 2];
	xa2 = intvar_1.rm[i__ - 1] - hru[i__ - 1];
	xa3 = intvar_1.rm[i__ - 1] - hru[i__];
	xa4 = intvar_1.rm[i__ - 1] - hru[i__ + 1];
	intfac_1.faci[(i__ << 2) - 4] = xa2 * xa3 * xa4 / d1;
	intfac_1.faci[(i__ << 2) - 3] = xa1 * xa3 * xa4 / d2;
	intfac_1.faci[(i__ << 2) - 2] = xa1 * xa2 * xa4 / d3;
	intfac_1.faci[(i__ << 2) - 1] = xa1 * xa2 * xa3 / d4;
/* L20: */
    }
    cg = exp(const1_1.cln * const2_1.cgl);
/* Computing 2nd power */
    d__1 = cg;
    cg2 = d__1 * d__1;
    i__1 = i1;
    for (i__ = i0; i__ <= i__1; ++i__) {
/*  USE 4-POINT LAGRANGIAN INTERPOLATION TO FIND PHYSICAL VARIABLES */
/*  AT THE INTERFACES. */
/*  PRESSURE. */
	intvar_1.pm[i__ - 1] = exp(const1_1.cln * (hp[i__ - 2] * 
		intfac_1.faci[(i__ << 2) - 4] + hp[i__ - 1] * intfac_1.faci[(
		i__ << 2) - 3] + hp[i__] * intfac_1.faci[(i__ << 2) - 2] + hp[
		i__ + 1] * intfac_1.faci[(i__ << 2) - 1]));
/*  TEMPERATURE. */
	intvar_1.tm[i__ - 1] = exp(const1_1.cln * (ht[i__ - 2] * 
		intfac_1.faci[(i__ << 2) - 4] + ht[i__ - 1] * intfac_1.faci[(
		i__ << 2) - 3] + ht[i__] * intfac_1.faci[(i__ << 2) - 2] + ht[
		i__ + 1] * intfac_1.faci[(i__ << 2) - 1]));
/*  DENSITY. */
	intvar_1.dm[i__ - 1] = exp(const1_1.cln * (hd[i__ - 2] * 
		intfac_1.faci[(i__ << 2) - 4] + hd[i__ - 1] * intfac_1.faci[(
		i__ << 2) - 3] + hd[i__] * intfac_1.faci[(i__ << 2) - 2] + hd[
		i__ + 1] * intfac_1.faci[(i__ << 2) - 1]));
/*  DEL (ACTUAL). */
/*  DEL (RADIATIVE) IS INTERPOLATED, AND DEL IS THE MIN OF DELA,DELR. */
	intvar_1.delmi[i__ - 1] = mdphy_1.delrm[i__ - 3] * intfac_1.faci[(i__ 
		<< 2) - 4] + mdphy_1.delrm[i__ - 2] * intfac_1.faci[(i__ << 2)
		 - 3] + mdphy_1.delrm[i__ - 1] * intfac_1.faci[(i__ << 2) - 2]
		 + mdphy_1.delrm[i__] * intfac_1.faci[(i__ << 2) - 1];
/*  DEL(ADIABATIC). */
	intvar_1.delami[i__ - 1] = mdphy_1.delam[i__ - 3] * intfac_1.faci[(
		i__ << 2) - 4] + mdphy_1.delam[i__ - 2] * intfac_1.faci[(i__ 
		<< 2) - 3] + mdphy_1.delam[i__ - 1] * intfac_1.faci[(i__ << 2)
		 - 2] + mdphy_1.delam[i__] * intfac_1.faci[(i__ << 2) - 1];
/*  D LN RHO/D LN T. */
	intvar_1.qdtmi[i__ - 1] = mdphy_1.qdtm[i__ - 3] * intfac_1.faci[(i__ 
		<< 2) - 4] + mdphy_1.qdtm[i__ - 2] * intfac_1.faci[(i__ << 2) 
		- 3] + mdphy_1.qdtm[i__ - 1] * intfac_1.faci[(i__ << 2) - 2] 
		+ mdphy_1.qdtm[i__] * intfac_1.faci[(i__ << 2) - 1];
/*  UNLOGGED MASS INTERIOR TO THE INTERFACE. */
	intvar_1.hs3[i__ - 1] = hs1[i__ - 2] * intfac_1.faci[(i__ << 2) - 4] 
		+ hs1[i__ - 1] * intfac_1.faci[(i__ << 2) - 3] + hs1[i__] * 
		intfac_1.faci[(i__ << 2) - 2] + hs1[i__ + 1] * intfac_1.faci[(
		i__ << 2) - 1];
/*  SPECIFIC ENERGY GENERATION RATE. */
	intvar_1.epsilm[i__ - 1] = mdphy_1.esumm[i__ - 3] * intfac_1.faci[(
		i__ << 2) - 4] + mdphy_1.esumm[i__ - 2] * intfac_1.faci[(i__ 
		<< 2) - 3] + mdphy_1.esumm[i__ - 1] * intfac_1.faci[(i__ << 2)
		 - 2] + mdphy_1.esumm[i__] * intfac_1.faci[(i__ << 2) - 1];
/*  LUMINOSITY. */
	intvar_1.alm[i__ - 1] = const_1.clsun * (hl[i__ - 2] * intfac_1.faci[(
		i__ << 2) - 4] + hl[i__ - 1] * intfac_1.faci[(i__ << 2) - 3] 
		+ hl[i__] * intfac_1.faci[(i__ << 2) - 2] + hl[i__ + 1] * 
		intfac_1.faci[(i__ << 2) - 1]);
/*  LOCAL AVERAGE FORCE OF GRAVITY. */
	intvar_1.hgm[i__ - 1] = hg[i__ - 2] * intfac_1.faci[(i__ << 2) - 4] + 
		hg[i__ - 1] * intfac_1.faci[(i__ << 2) - 3] + hg[i__] * 
		intfac_1.faci[(i__ << 2) - 2] + hg[i__ + 1] * intfac_1.faci[(
		i__ << 2) - 1];
/*  opacity. */
	opm[i__ - 1] = mdphy_1.om[i__ - 3] * intfac_1.faci[(i__ << 2) - 4] + 
		mdphy_1.om[i__ - 2] * intfac_1.faci[(i__ << 2) - 3] + 
		mdphy_1.om[i__ - 1] * intfac_1.faci[(i__ << 2) - 2] + 
		mdphy_1.om[i__] * intfac_1.faci[(i__ << 2) - 1];
/*  specific heat */
	cpmi[i__ - 1] = mdphy_1.cpm[i__ - 3] * intfac_1.faci[(i__ << 2) - 4] 
		+ mdphy_1.cpm[i__ - 2] * intfac_1.faci[(i__ << 2) - 3] + 
		mdphy_1.cpm[i__ - 1] * intfac_1.faci[(i__ << 2) - 2] + 
		mdphy_1.cpm[i__] * intfac_1.faci[(i__ << 2) - 1];
/* L30: */
    }
    i__1 = *imax;
    for (i__ = *imin; i__ <= i__1; ++i__) {
/* Computing MIN */
	d__1 = intvar_1.delmi[i__ - 1], d__2 = intvar_1.delami[i__ - 1];
	intvar_1.delmi[i__ - 1] = min(d__1,d__2);
/* L35: */
    }
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	taukh_1.fes1[i__ - 1] = 0.;
	taukh_1.fes2[i__ - 1] = 0.;
	taukh_1.fes3[i__ - 1] = 0.;
	taukh_1.fgsfj[i__ - 1] = 0.;
	taukh_1.fgsfk[i__ - 1] = 0.;
	vfact_1.fact1[i__ - 1] = 0.;
	vfact_1.fact2[i__ - 1] = 0.;
	vfact_1.fact3[i__ - 1] = 0.;
	vfact_1.fact4[i__ - 1] = 0.;
	vfact_1.fact5[i__ - 1] = 0.;
/* MHP 06/02 */
	oldrot2_1.festime[i__ - 1] = 0.;
	oldrot2_1.thm[i__ - 1] = 0.;
	vfact_1.fact7[i__ - 1] = 0.;
	vfact_1.fact8[i__ - 1] = 0.;
    }
    i__1 = *m;
    for (i__ = 2; i__ <= i__1; ++i__) {
/* ADDED FOR D THETA/DT TERM FROM ZAHN&MAEDER 1998 */
	fac = (hr[i__] + hr[i__ - 1]) * 2. - (d_lg10(&hs1[i__]) + d_lg10(&hs1[
		i__ - 1])) * .5 - const2_1.cgl;
	oldrot2_1.thm[i__ - 1] = exp(const1_1.cln * fac);
    }
/*  NOW COMPUTE STRUCTURAL QUANTITIES NEEDED TO EVALUATE VELOCITIES AT */
/*  ALL INTERFACES. */
    cpigi = 4. / const1_1.c4pi / cg;
    i__1 = *imax;
    for (i__ = *imin; i__ <= i__1; ++i__) {
	if (! varfc_1.ldifad) {
	    delmu = (d_lg10(&mdphy_1.amum[i__ - 1]) - d_lg10(&mdphy_1.amum[
		    i__ - 2])) / (hp[i__] - hp[i__ - 1]);
	} else {
	    delmu = 0.;
	}
	if (i__ == *imin) {
/* Computing MAX */
	    d__1 = .001, d__2 = (mdphy_1.delam[*imin] - mdphy_1.delm[*imin]) *
		     .5 + delmu;
	    dmin__ = max(d__1,d__2);
	} else if (i__ == *imax) {
/* Computing MAX */
	    d__1 = .001, d__2 = (mdphy_1.delam[*imax - 2] - mdphy_1.delm[*
		    imax - 2]) * .5 + delmu;
	    dmin__ = max(d__1,d__2);
	} else {
	    dmin__ = .001;
	}
/* Computing MAX */
	d__1 = intvar_1.delami[i__ - 1] - intvar_1.delmi[i__ - 1];
	ddel = max(d__1,dmin__);
/* MHP 06/02 */
/* ADDED FOR ALTERNATE TREATMENT OF MU GRADIENTS */
/*         DDELM(I) = 0.5D0*(DELAMI(I)+DELAMI(I-1)- */
/*     *                     DELMI(I)-DELMI(I-1)) */
/*         DDELM(I) = DDEL */
/* Computing MAX */
	d__1 = intvar_1.delami[i__ - 1] - intvar_1.delmi[i__ - 1] + delmu;
	oldrot2_1.ddelm[i__ - 1] = max(d__1,dmin__);
/*         FESTIME(I) = PM(I)/(HGM(I)*DDEL*DM(I)*TM(I)) */
	oldrot2_1.festime[i__ - 1] = intvar_1.pm[i__ - 1] / (intvar_1.hgm[i__ 
		- 1] * ddel * intvar_1.dm[i__ - 1]);
/* Computing 2nd power */
	d__1 = intvar_1.rm[i__ - 1];
	hpsc = intvar_1.pm[i__ - 1] * (d__1 * d__1) / intvar_1.dm[i__ - 1] / 
		intvar_1.hs3[i__ - 1] / cg;
	htsc = hpsc / intvar_1.delmi[i__ - 1];
/* Computing 3rd power */
	d__1 = intvar_1.rm[i__ - 1];
	eta = const1_1.cc23 * 2. * (d__1 * (d__1 * d__1)) / cg / intvar_1.hs3[
		i__ - 1];
/*        TTHERM = 8.0d0*CC23*CSIG*TM(I)**3/OPM(I)/DM(I)**2/CPM(I) */
	taukh_1.fgsfk[i__ - 1] = hpsc * 8. * eta / ddel;
	ff = intvar_1.pm[i__ - 1] / (intvar_1.hgm[i__ - 1] * ddel * cpmi[i__ 
		- 1] * intvar_1.dm[i__ - 1] * intvar_1.tm[i__ - 1]);
	fac = eta * 2. * ff;
	em = intvar_1.alm[i__ - 1] / intvar_1.hs3[i__ - 1];
	taukh_1.fes1[i__ - 1] = fac * (em - intvar_1.epsilm[i__ - 1]);
	taukh_1.fes2[i__ - 1] = fac * -.5 * em * cpigi / intvar_1.dm[i__ - 1];
	taukh_1.fes3[i__ - 1] = em * ff * const1_1.cc13 * cpigi * intvar_1.rm[
		i__ - 1] / intvar_1.dm[i__ - 1];
/*         FES3(I) = EM*FF*CPIGI*(3.0D0*HTSC-RM(I))/DM(I) */
	difad3_1.fv0[i__ - 1] = ff;
	difad3_1.fv1a[i__ - 1] = taukh_1.fes1[i__ - 1] / ff;
	difad3_1.fv1b[i__ - 1] = taukh_1.fes2[i__ - 1] / ff;
	difad3_1.fv2a[i__ - 1] = em * cpigi * 3. * htsc / intvar_1.dm[i__ - 1]
		;
	difad3_1.fv2b[i__ - 1] = -em * cpigi * intvar_1.rm[i__ - 1] / 
		intvar_1.dm[i__ - 1];
	taukh_1.fgsfj[i__ - 1] = (d__1 = fac * em * htsc, abs(d__1)) * 
		intvar_1.rm[i__ - 1];
/*  EDDINGTON CIRCULATION VELOCITY IS DEFINED AS */
/*  VES = FACT1*FACT2*OMEGA**2 (ENDAL AND SOFIA PAPER II). */
/*  NOTE THAT TO AVOID OVERFLOW 1/(DEL(AD)-DEL)IS SET TO A MAXIMUM OF 10^6. */
/*  THIS SHOULD ONLY BE AN ISSUE IF YOU HAVE ZERO OVERSHOOT AT THE BOUNDARY */
/*  OF A CONVECTION ZONE.  CAVEAT EMPTOR. */
/* Computing MAX */
	d__1 = intvar_1.delami[i__ - 1] - intvar_1.delmi[i__ - 1];
	vfact_1.fact1[i__ - 1] = 1. / intvar_1.qdtmi[i__ - 1] / max(d__1,.001)
		;
/*         FACT2(I) = DELAMI(I)*ALM(I)*(RM(I)**3/CG2/HS3(I)**2)* */
/*     *              (2.0D0*RM(I)**2*(EPSILM(I)/ALM(I) - 1.0D0/HS3(I)) */
/*    *              - 3.0D0/(C4PI*DM(I)*RM(I))) */
	fac = intvar_1.delami[i__ - 1] / intvar_1.hgm[i__ - 1];
	vfact_1.fact2[i__ - 1] = fac * eta * (intvar_1.epsilm[i__ - 1] - em);
	taukh_1.fact6[i__ - 1] = -fac * em / const1_1.c4pi / cg / intvar_1.dm[
		i__ - 1] / intvar_1.rm[i__ - 1];
/* GSF VELOCITY IS DEFINED AS */
/* VGSF = VES*FACT3/Hj**2/(2OMEGA/(D OMEGA/D LNR) + 1) */
/* WHERE HJ IS THE SPECIFIC ANGULAR MOMENTUM SCALE HEIGHT. */
/* AND FACT3 IS THE TEMPERATURE SCALE HEIGHT TIMES THE RADIUS. */
/*  HT = (DEL*D(LN P)/DR)**-1 = P*R**2/(DEL*RHO*GM) */
/*        FACT3(I) = PM(I)*RM(I)**3/(DELMI(I)*DM(I)*CG*HS3(I)) */
	vfact_1.fact3[i__ - 1] = (d__1 = htsc * intvar_1.rm[i__ - 1], abs(
		d__1));
/*  FICTITIOUS MU CURRENTS THAT OPPOSE ES AND GSF CIRCULATION CALCULATED HERE. */
/*  VMU = FMU*FACT1*FACT4*mu*del(mu), FACT4=(D RHO/D MU)*PSCALH/TKH/MU */
/*  (KIPPENHAHN, IAU#66,P.22) USING TKH* = THE LOCAL KELVIN-HELMHOLTZ TIMESCALE. */
/*  FMU IS A USER PARAMETER, DMU IS DELTA MU BETWEEN THE SHELLS, AND QDMU IS */
/*  THE DERIVATIVE OF THE DENSITY WITH RESPECT TO MU. */
/*  IF VMU EXCEEDS VES AND VGSF THE INTERFACE IS STABLE. */
/*  D RHO/DMU = (1-(a/3)*T**4/P)*P*MU/(RHO*T*CGAS) */
/*  THE PRESSURE SCALE HEIGHT IS CGAS*T*R**2/GM (EXCLUDING A FACTOR MU */
/*  WHICH CANCELS WITH ANOTHER FACTOR OF MU WHICH ARISES ELSEWHERE) AND */
/*  THE KELVIN-HELMHOLTZ TIMESCALE IS G*M**2/(R*L). */
/*         FACT4(I) = ALM(I)*(RM(I)/HS3(I))**3/CG2/DM(I)* */
/*     *              (PM(I)-CA3*TM(I)**4) */
/* Computing 2nd power */
	d__1 = intvar_1.rm[i__ - 1];
/* Computing 4th power */
	d__2 = intvar_1.tm[i__ - 1], d__2 *= d__2;
	vfact_1.fact4[i__ - 1] = d__1 * d__1 / intvar_1.hs3[i__ - 1] / cg / 
		intvar_1.dm[i__ - 1] * (intvar_1.pm[i__ - 1] - const2_1.ca3 * 
		(d__2 * d__2)) / sqrt(intvar_1.hgm[i__ - 1]);
/*  DYNAMICAL SHEAR INSTABILITY. */
/*  AN INTERFACE IS STABLE AGAINST THIS SHEAR WHENEVER THE RICHARDSON NUMBER */
/*  RICHNO = (RHO/P)*(DEL(AD)-DEL)*g**2/(D OMEGA/D LN R)**2>.25. */
/* Computing MAX */
	d__1 = intvar_1.delami[i__ - 1] - intvar_1.delmi[i__ - 1];
	qwrmax[i__] = sqrt(intvar_1.dm[i__ - 1] / intvar_1.pm[i__ - 1] * max(
		d__1,.001)) * 2. * intvar_1.hgm[i__ - 1];
/*  THE DIFFUSIVE SHEAR IS INHIBITED BY MU GRADIENTS. */
/*  AN INTERFACE IS STABLE AGAINST THE DIFFUSIVE SHEAR IF */
/*  RICHARDSON NUMBER = FACT5*DMU/MU/(D OMEGA/D LNR)**2 > .25, WHERE */
/*  FACT5 = RHO/P*(-d lnT/d lnMU)/(del LN P)*G**2 AND */
/*   -d lnT/d lnMU = (CON-1)/(1+3CON),CON=(a/3)T**4/P */
/*  GIVEN (1 - CON)P = CGAS*RHO*T/MU */
/*  1 - CON IS BETA(CORRECTION FOR RADIATION PRESSURE). */
/* Computing 2nd power */
	d__1 = intvar_1.hgm[i__ - 1];
/* Computing 4th power */
	d__2 = intvar_1.tm[i__ - 1], d__2 *= d__2;
/* Computing 4th power */
	d__3 = intvar_1.tm[i__ - 1], d__3 *= d__3;
	vfact_1.fact5[i__ - 1] = intvar_1.dm[i__ - 1] * (d__1 * d__1) / 
		intvar_1.pm[i__ - 1] / const1_1.cln / (hp[i__] - hp[i__ - 1]) 
		* (const2_1.ca3 * (d__2 * d__2) / intvar_1.pm[i__ - 1] - 1.) /
		 (const2_1.ca3 * 3. * (d__3 * d__3) / intvar_1.pm[i__ - 1] + 
		1.);
/* MHP 3/92 ADD VECTOR FOR LOCAL KELVIN-HELMHOLTZ TIME SCALE. */
/*         TKH(I) = CG*HS3(I)**2/ABS(ALM(I))/RM(I) */
/* L40: */
    }
/* MHP 06/02 ADDED TERMS OF ORDER DW/DR FROM ZAH&MAEDER 1998 */
    if (varfc_1.ldifad) {
	htm = exp(const1_1.cln * (hp[*imin - 1] + hr[*imin - 1] * 2. - hd[*
		imin - 1])) / hs1[*imin - 1] / cg / mdphy_1.delrm[*imin - 2];
	egridder_1.qqqcod[*imin - 2] = htm;
	i__1 = *imax;
	for (i__ = *imin; i__ <= i__1; ++i__) {
/*         DDEL = MAX(DELAMI(I)-DELMI(I),1.0D-3) */
/* Computing 2nd power */
	    d__1 = intvar_1.rm[i__ - 1];
	    hpsc = intvar_1.pm[i__ - 1] * (d__1 * d__1) / intvar_1.dm[i__ - 1]
		     / intvar_1.hs3[i__ - 1] / cg;
	    htsc = hpsc / intvar_1.delmi[i__ - 1];
	    f1 = intvar_1.pm[i__ - 1] / (intvar_1.hgm[i__ - 1] * 
		    oldrot2_1.ddelm[i__ - 1] * cpmi[i__ - 1] * intvar_1.dm[
		    i__ - 1] * intvar_1.tm[i__ - 1]);
	    f2 = intvar_1.alm[i__ - 1] * intvar_1.rm[i__ - 1] / intvar_1.hs3[
		    i__ - 1] / 3.;
/* Computing 3rd power */
	    d__1 = intvar_1.rm[i__ - 1];
	    f3 = intvar_1.hs3[i__ - 1] * .75 / (const1_1.cpi * intvar_1.dm[
		    i__ - 1] * (d__1 * (d__1 * d__1)));
	    v0 = -f1 * f2 * f3;
/*         V0 = -PM(I)*ALM(I)/(C4PI*CG**2*HS3(I)*DDEL*CPM(I)* */
/*     *         DM(I)**2*TM(I)) */
/* Computing 3rd power */
	    d__1 = intvar_1.rm[i__ - 1];
	    ff = d__1 * (d__1 * d__1) / intvar_1.hs3[i__ - 1];
/* Computing 4th power */
	    d__1 = intvar_1.rm[i__ - 1], d__1 *= d__1;
	    c1 = const1_1.cc23 * (d__1 * d__1) / cg / intvar_1.hs3[i__ - 1];
	    egridder_1.qqcod[i__ - 1] = c1;
	    qc1r = const1_1.cc23 * 4. * ff / cg * (1. - const1_1.cpi * 
		    intvar_1.dm[i__ - 1] * ff);
	    dr = pow_dd(&c_b8, &hr[i__]) - pow_dd(&c_b8, &hr[i__ - 1]);
	    qdr = (pow_dd(&c_b8, &hd[i__]) - pow_dd(&c_b8, &hd[i__ - 1])) / 
		    dr;
/* Computing 2nd power */
	    d__1 = const1_1.cpi * intvar_1.dm[i__ - 1] * ff;
	    qqc1rr = ff * 8. / cg / intvar_1.rm[i__ - 1] * (1. - 
		    const1_1.cc13 * const1_1.cpi * ff * (intvar_1.dm[i__ - 1] 
		    * 10. - intvar_1.rm[i__ - 1] * qdr) + const1_1.cc13 * 8. *
		     (d__1 * d__1));
/* D LN CHI/D LN T = 3 - D LN CAPPA/D LN T */
	    qchit = 3. - (rotder_1.sqot[i__ - 1] + rotder_1.sqot[i__ - 2]) * 
		    .5;
	    qqchitr = (rotder_1.sqot[i__ - 2] - rotder_1.sqot[i__ - 1]) / dr;
	    htp = exp(const1_1.cln * (hp[i__] + hr[i__] * 2. - hd[i__])) / 
		    hs1[i__] / cg / mdphy_1.delm[i__ - 1];
	    egridder_1.qqqcod[i__ - 1] = htp;
	    htp2 = dr / const1_1.cln / (ht[i__ - 1] - ht[i__]);
	    qhtr = (abs(htp) - abs(htm)) / dr;
	    htm = htp;
	    qetm = (rotder_1.sqet[i__ - 1] + rotder_1.sqet[i__ - 2]) * .5;
	    fnu = (rotder_1.fracnuc[i__ - 1] + rotder_1.fracnuc[i__ - 2]) * 
		    .5;
/*         FACT7(I)= -V0*(QQCHITR*C1+QCHIT*QC1R) */
/*         FACT7(I)= -V0*(QQCHITR*C1) */
	    vfact_1.fact7[i__ - 1] = -f1 * c1 * (fnu * qetm + intvar_1.epsilm[
		    i__ - 1] * (1. - fnu - qchit));
	    difad3_1.fv2b[i__ - 1] += vfact_1.fact7[i__ - 1] / f1;
/*         FACT7(I)=V0*((QHTR-QCHIT)*QC1R-QQCHITR*C1+HTSC*QQC1RR) */
/*     *            - F1*EPSILM(I)*(HTSC*QC1R + C1*(QETM - QCHIT)) */
	    vfact_1.fact8[i__ - 1] = 0.;
/*         FACT8(I)=V0*((QHTR-QCHIT)*C1+HTSC*2.0D0*QC1R) */
/*     *            - F1*EPSILM(I)*HTSC*C1 */
/* Q variables not used */
/*         Q1 = -V0*(QQCHITR*C1) */
/*         Q2 = -F1*C1*FNU*QETM */
/*         Q3 = -F1*C1*EPSILM(I)*(1.0D0 - FNU - QCHIT) */
/*         Q4 = F1*FL*QCHIT */
/*         Q5 = -F1*EPSILM(I)*HTSC */
/* Computing 2nd power */
	    d__1 = intvar_1.rm[i__ - 1];
	    fl = intvar_1.alm[i__ - 1] / const1_1.c4pi / intvar_1.dm[i__ - 1] 
		    / (d__1 * d__1);
	    difad3_1.facd2[i__ - 1] = f1 * (fl * qchit - intvar_1.epsilm[i__ 
		    - 1] * htsc);
	    difad3_1.facd3[i__ - 1] = -f1 * fl;
/*         WRITE(*,911)I,V0,FES3(I),FACT7(I),FACD2(I),FACD3(I),DDELM(I) */
/*         WRITE(*,912)Q1,Q2,Q3,Q4,Q5 */
/* 911     FORMAT(I5,1P6E12.3) */
/* 912     FORMAT(5X,1P5E12.3) */
	}
    }
    return 0;
} /* setupv_ */

