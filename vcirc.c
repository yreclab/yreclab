/* vcirc.f -- translated by f2c (version 20100827).
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
    logical lscrib, lpshll, lchemo, lconzo, ljout, lprtin, lpenv;
} ccout_;

#define ccout_1 ccout_

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
	    hgm[5000], hs3[5000], pm[5000], qdtm[5000], rm[5000], tm[5000];
} intvar_;

#define intvar_1 intvar_

struct {
    doublereal amum[5000], thdifm[5000], viscm[5000], wm[5000];
} intvr2_;

#define intvr2_1 intvr2_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal hamu[5000], cp[5000], delm[5000], delam[5000], delrm[5000], 
	    sesum[5000], om[5000], sqdt[5000], thdif[5000], svel[5000], visc[
	    5000], epsm[5000];
} mdphy_;

#define mdphy_1 mdphy_

struct {
    doublereal ves[5000], ves0[5000], vss[5000], vss0[5000], hle[5000], vgsf[
	    5000], vgsf0[5000], vmu[5000];
} temp2_;

#define temp2_1 temp2_

struct {
    doublereal fact1[5000], fact2[5000], fact3[5000], fact4[5000], fact5[5000]
	    , fact7[5000], fact8[5000];
} vfact_;

#define vfact_1 vfact_

struct {
    doublereal fw, fc, fo, fes, fgsf, fmu, fss, rcrit;
} vmult_;

#define vmult_1 vmult_

struct {
    doublereal fesc, fssc, fgsfc;
    integer ies, igsf, imu;
} vmult2_;

#define vmult2_1 vmult2_

struct {
    doublereal vmup[5000];
} prevmu_;

#define prevmu_1 prevmu_

struct {
    doublereal phisp[5000], phirot[5000], phidis[5000], rat[5000];
} quadd_;

#define quadd_1 quadd_

struct {
    doublereal quad[5000], gg[5000];
} quadru_;

#define quadru_1 quadru_

struct {
    logical lnoj;
} notran_;

#define notran_1 notran_

struct {
    doublereal vfc[5000];
    logical lvfc, ldifad;
} varfc_;

#define varfc_1 varfc_

struct {
    doublereal vesa[5000], vesa0[5000], vesd[5000], vesd0[5000];
} difad2_;

#define difad2_1 difad2_

struct {
    doublereal facd2[5000], facd3[5000], vesd2[5000], vesd3[5000], ecod5[5000]
	    , ecod6[5000], fgeom[5000], fv0[5000], fv1a[5000], fv1b[5000], 
	    fv2a[5000], fv2b[5000], ev0[5000], ev1a[5000], ev1b[5000], ev2a[
	    5000], ev2b[5000], dss[5000], dgsf[5000], ess[5000], egsf[5000];
} difad3_;

#define difad3_1 difad3_

struct {
    doublereal tho[5000], thn[5000], thm[5000], ddelm[5000], festime[5000], 
	    thp[5000], qwrst[5000], wmst[5000], qwrmst[5000];
} oldrot2_;

#define oldrot2_1 oldrot2_

struct {
    doublereal eqqcod[5000], eqqqcod[5000], qqcod[5000], qqqcod[5000];
} egridder_;

#define egridder_1 egridder_

/* Table of constant values */

static integer c__1 = 1;

/* $$$$$$ */
/* Subroutine */ int vcirc_(doublereal *hjm, doublereal *hr, doublereal *hru, 
	integer *imin, integer *imax, integer *it, logical *lcz, integer *m, 
	doublereal *omega, logical *ldo, doublereal *qwlnr, doublereal *
	qwrmax, doublereal *hv, doublereal *cltot, doublereal *dt, doublereal 
	*hp)
{

    /* Format strings */
    static char fmt_303[] = "(i5,\002 RAT \002,1pe10.3,\002 POT SPH,CYL,QU"
	    "A\002,3e10.3/\002 QUA,G,R \002,6e12.3)";
    static char fmt_9911[] = "(1x,\002DYNAMICAL SHEAR-SHELL\002,i5,1p,\002 W"
	    "TOP\002,e11.3,\002 WBOT\002,e11.3,\002 LIMIT\002,e11.3)";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double log(doublereal), exp(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double sqrt(doublereal), d_lg10(doublereal *);

    /* Local variables */
    static integer i__, i0, i1;
    static doublereal q0, q1, q2, v2, dr, qp, qq, fx, qw, fx2, qmu, qqq, fxx, 
	    qwr, phi2, fxx2, ddel, gmid, rmid, wmin, wmid, dell, phis2, qwrmx,
	     qwrmx2, ddtest, dlnwdr, phistd, ddtest2, dlnwdr0, dlnjmdr, 
	    dlnjmdr0;

    /* Fortran I/O blocks */
    static cilist io___11 = { 0, 6, 0, fmt_303, 0 };
    static cilist io___36 = { 0, 6, 0, fmt_9911, 0 };


/* MHP 3/92 COMMON BLOCKS ADDED FOR SHEAR VELOCITY AND MU INHIBITION. */
/* MHP 06/02 ADDED FACT7 AND FACT8 FOR DIF/AD TREATMENT */
/* 3/93 QUADRUPOLE DRIVING TERM ADDED. */
/* MHP 9/93 */
/* MHP 11/94 ADVECTIVE VELOCITY AND DIFFUSIVE COMPONENT. */
/* MHP 06/02 */
/* HIGHER ORDER TERMS IN M.C. VELOCITY */
/* Time change of theta */
/* DEFINITION TERMS FOR THE SECOND AND THIRD DERIVATIVE */
/* TERMS */
/* SPEED OF LIGHT. */
    /* Parameter adjustments */
    --hp;
    --hv;
    --qwrmax;
    --qwlnr;
    --omega;
    --lcz;
    --hru;
    --hr;
    --hjm;

    /* Function Body */
/*   SKIPPING CONVECTIVE REGIONS, CHECK FOR INSTABILITY AGAINST EACH */
/*   SECULAR MECHANISM.IF UNSTABLE,COMPUTE A CIRCULATION VELOCITY. */
/*   THE PROCEDURE FOR CALCULATING STABILITY IS AS FOLLOWS: */
/*      STABILITY IS CALCULATED FOR THE I/I-1 INTERFACE. */
/*      EACH STABILITY CRITERION IS EXPRESSED AS FOLLOWS: */
/*       A COMBINATION OF VARIABLES(RHO,P,ETC.)STORED AT EACH SHELL */
/*       MULTIPLIED BY A GRADIENT BETWEEN THE SHELLS MUST BE LESS THAN */
/*       SOME CRITICAL NUMBER. */
    *ldo = FALSE_;
/*  STORE THE OLD VELOCITY ESTIMATES FOR LATER USE. */
    if (*it > 1) {
	i__1 = *imax;
	for (i__ = *imin; i__ <= i__1; ++i__) {
	    prevmu_1.vmup[i__ - 1] = temp2_1.vmu[i__ - 1];
	    temp2_1.vgsf0[i__ - 1] = temp2_1.vgsf[i__ - 1];
	    temp2_1.ves0[i__ - 1] = temp2_1.ves[i__ - 1];
	    temp2_1.vss0[i__ - 1] = temp2_1.vss[i__ - 1];
/* L5: */
	}
	if (varfc_1.ldifad) {
	    i__1 = *imax;
	    for (i__ = *imin; i__ <= i__1; ++i__) {
		difad2_1.vesa0[i__ - 1] = difad2_1.vesa[i__ - 1];
		difad2_1.vesd0[i__ - 1] = difad2_1.vesd[i__ - 1];
	    }
	}
    }
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	hv[i__] = 0.;
	temp2_1.ves[i__ - 1] = 0.;
	temp2_1.vgsf[i__ - 1] = 0.;
	temp2_1.vss[i__ - 1] = 0.;
	temp2_1.vmu[i__ - 1] = 0.;
/* L10: */
    }
/*  MEAN MOLECULAR WEIGHT (AS WELL AS QUANTITIES WHICH DEPEND ON IT) AND */
/*  THE ANGULAR VELOCITY DISTRIBUTION CHANGE DURING A DIFFUSION TIMESTEP. */
/*  FIND THE NEW VALUES AT THE MIDPOINT IN RADIUS BETWEEN MASS SHELLS */
/*  WHERE STABILITY IS EVALUATED.  4 POINT LAGRANGIAN INTERPOLATION IS USED */
/*  FOR THE KINEMATIC VISCOSITY AND THERMAL DIFFUSIVITY. */
/*  TREATMENT OF FIRST INTERFACE. */
    if (*imin < 3) {
	intvr2_1.viscm[1] = exp(log(mdphy_1.visc[0]) * intfac_1.faci[4] + log(
		mdphy_1.visc[1]) * intfac_1.faci[5] + log(mdphy_1.visc[2]) * 
		intfac_1.faci[6] + log(mdphy_1.visc[3]) * intfac_1.faci[7]);
	intvr2_1.thdifm[1] = exp(log(mdphy_1.thdif[0]) * intfac_1.faci[4] + 
		log(mdphy_1.thdif[1]) * intfac_1.faci[5] + log(mdphy_1.thdif[
		2]) * intfac_1.faci[6] + log(mdphy_1.thdif[3]) * 
		intfac_1.faci[7]);
	i0 = 3;
    } else {
	i0 = *imin;
    }
/*  TREATMENT OF LAST INTERFACE. */
    if (*imax == *m) {
	intvr2_1.viscm[*m - 1] = exp(log(mdphy_1.visc[*m - 4]) * 
		intfac_1.faci[(*m << 2) - 4] + log(mdphy_1.visc[*m - 3]) * 
		intfac_1.faci[(*m << 2) - 3] + log(mdphy_1.visc[*m - 2]) * 
		intfac_1.faci[(*m << 2) - 2] + log(mdphy_1.visc[*m - 1]) * 
		intfac_1.faci[(*m << 2) - 1]);
	intvr2_1.thdifm[*m - 1] = exp(log(mdphy_1.thdif[*m - 4]) * 
		intfac_1.faci[(*m << 2) - 4] + log(mdphy_1.thdif[*m - 3]) * 
		intfac_1.faci[(*m << 2) - 3] + log(mdphy_1.thdif[*m - 2]) * 
		intfac_1.faci[(*m << 2) - 2] + log(mdphy_1.thdif[*m - 1]) * 
		intfac_1.faci[(*m << 2) - 1]);
	i1 = *m - 1;
    } else {
	i1 = *imax;
    }
/*  GENERAL CASE. */
    i__1 = i1;
    for (i__ = i0; i__ <= i__1; ++i__) {
	intvr2_1.viscm[i__ - 1] = exp(log(mdphy_1.visc[i__ - 3]) * 
		intfac_1.faci[(i__ << 2) - 4] + log(mdphy_1.visc[i__ - 2]) * 
		intfac_1.faci[(i__ << 2) - 3] + log(mdphy_1.visc[i__ - 1]) * 
		intfac_1.faci[(i__ << 2) - 2] + log(mdphy_1.visc[i__]) * 
		intfac_1.faci[(i__ << 2) - 1]);
	intvr2_1.thdifm[i__ - 1] = exp(log(mdphy_1.thdif[i__ - 3]) * 
		intfac_1.faci[(i__ << 2) - 4] + log(mdphy_1.thdif[i__ - 2]) * 
		intfac_1.faci[(i__ << 2) - 3] + log(mdphy_1.thdif[i__ - 1]) * 
		intfac_1.faci[(i__ << 2) - 2] + log(mdphy_1.thdif[i__]) * 
		intfac_1.faci[(i__ << 2) - 1]);
/* L20: */
    }
/* USE LINEAR INTERPOLATION FOR OMEGA AND MU. */
    i__1 = *m;
    for (i__ = 2; i__ <= i__1; ++i__) {
	intvr2_1.amum[i__ - 1] = (mdphy_1.hamu[i__ - 1] + mdphy_1.hamu[i__ - 
		2]) * .5;
	intvr2_1.wm[i__ - 1] = (omega[i__] + omega[i__ - 1]) * .5;
    }
/* MHP 8/03 OMITTED OLD KM1974 MERIDIONAL CIRCULATION VELOCITY ESTIMATE. */
/* THE IES FLAG IS THEREFORE NO LONGER IN USE. */

/* KIPPENHAHN AND MOLLENHOF(1974) MERIDIONAL CIRCULATION VELOCITY. */
/*      IF(IES.EQ.2)THEN */
/*         DO 30 I = IMIN,IMAX */
/*  SKIP CONVECTIVE INTERFACES. */
/*            IF(LCZ(I).AND.LCZ(I-1))GOTO 30 */
/*  EDDINGTON CIRCULATION.  VELOCITY DEFINED IN SR SETUPV. */
/*            DR = HRU(I)-HRU(I-1) */
/*            DV = ((OMEGA(I)*HRU(I))**2-(OMEGA(I-1)*HRU(I-1))**2)/DR */
/* QUADRUPOLE TERM, AS PER ZAHN (1992), ADDED. */
/*            GMID = 0.5D0*(GG(I)+GG(I-1)) */
/* THE VARIATION IN GRAVITY ON A LEVEL SURFACE CAN BE EXPRESSED IN */
/* GENERAL AS 1/3 OMEGA**2 *D/DR((R**2 - PHI)/G), WHERE G IS THE */
/* LOCAL AVERAGE GRAVITY (~GM/R**2) AND PHI IS THE QUADRUPOLE MOMENT. */
/* THE CLASSICAL EXPRESSION NEGLECTS THE QUADRUPOLE AND THE SPATIAL */
/* DERIVATIVE OF THE MASS (PHISTD).  THE VELOCITY ESTIMATE FOR */
/* MERIDIONAL CIRCULATION IS THEREFORE MULTIPLED BY THE RATIO OF */
/* THE CORRECTED EXPRESSION TO THE CLASSICAL ONE (RAT). */
/*            PHISTD = 2.0D0*CC23*WM(I)**2*RM(I)/GMID */
/*            PHIS2 = CC13*WM(I)**2*(HRU(I)**2/GG(I)- */
/*     *              HRU(I-1)**2/GG(I-1))/DR */
/*            PHI2 = (QUAD(I-1)/GG(I-1)-QUAD(I)/GG(I))/DR */
/*            RAT(I) = (PHIS2+PHI2)/PHISTD */
/*            RAT(I) = PHIS2/PHISTD */
/*            VES(I) = ABS(FACT1(I)*(FACT2(I)*RAT(I)*WM(I)**2 */
/*     *               +FACT6(I)*DV)) */
/*   30    CONTINUE */
/*      ELSE */
/* ZAHN (1991) VELOCITY ESTIMATE. */
    i__1 = *imax;
    for (i__ = *imin; i__ <= i__1; ++i__) {
	if (lcz[i__] && lcz[i__ - 1]) {
	    goto L31;
	}
/* ORIGINAL ESTIMATE,USING DG/G = W**2 R**3 / GM. */
/* Computing 2nd power */
	d__1 = intvr2_1.wm[i__ - 1];
/* Computing 2nd power */
	d__2 = intvr2_1.wm[i__ - 1];
	temp2_1.ves[i__ - 1] = d__1 * d__1 * (taukh_1.fes1[i__ - 1] + d__2 * 
		d__2 * taukh_1.fes2[i__ - 1]);
/* QUADRUPOLE TERM ADDED, DG/G COMPUTED AS PER ZAHN 1992. */
	dr = hru[i__] - hru[i__ - 1];
	gmid = (quadru_1.gg[i__ - 1] + quadru_1.gg[i__ - 2]) * .5;
/* Computing 2nd power */
	d__1 = intvr2_1.wm[i__ - 1];
	phistd = const1_1.cc23 * 2. * (d__1 * d__1) * intvar_1.rm[i__ - 1] / 
		gmid;
/* Computing 2nd power */
	d__1 = intvr2_1.wm[i__ - 1];
/* Computing 2nd power */
	d__2 = hru[i__];
/* Computing 2nd power */
	d__3 = hru[i__ - 1];
	phis2 = const1_1.cc13 * (d__1 * d__1) * (d__2 * d__2 / quadru_1.gg[
		i__ - 1] - d__3 * d__3 / quadru_1.gg[i__ - 2]) / dr;
	phi2 = (quadru_1.quad[i__ - 2] / quadru_1.gg[i__ - 2] - quadru_1.quad[
		i__ - 1] / quadru_1.gg[i__ - 1]) / dr;
	qw = intvr2_1.wm[i__ - 1] * (omega[i__] - omega[i__ - 1]) / dr;
	quadd_1.rat[i__ - 1] = (phis2 + phi2) / phistd;
	if (quadd_1.rat[i__ - 1] < 0.) {
	    s_wsfe(&io___11);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&quadd_1.rat[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&phistd, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&phis2, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&phi2, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&quadru_1.quad[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&quadru_1.quad[i__ - 2], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&quadru_1.gg[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&quadru_1.gg[i__ - 2], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&hru[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hru[i__ - 1], (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
	if (! varfc_1.ldifad) {
	    temp2_1.ves[i__ - 1] = (d__1 = quadd_1.rat[i__ - 1] * temp2_1.ves[
		    i__ - 1] - taukh_1.fes3[i__ - 1] * qw, abs(d__1));
	} else {
/* MHP 05/02 ADD FACTOR OF 1/5 HERE */
/*               VESA(I) = RAT(I)*VES(I) */
/*               VESD(I) = ABS(FES3(I)*WM(I)**2) */
/* MHP 06/02 ADDED D THETA/DT TERM */
	    oldrot2_1.thn[i__ - 1] = oldrot2_1.festime[i__ - 1] * (
		    oldrot2_1.thm[i__ - 1] * qw - oldrot2_1.thp[i__ - 1]) / *
		    dt;
	    difad2_1.vesa[i__ - 1] = (quadd_1.rat[i__ - 1] * temp2_1.ves[i__ 
		    - 1] + oldrot2_1.thn[i__ - 1]) * .2;
/* Computing 2nd power */
	    d__1 = intvr2_1.wm[i__ - 1];
	    q1 = vfact_1.fact7[i__ - 1] * (d__1 * d__1);
	    q2 = vfact_1.fact8[i__ - 1] * qw;
/* Computing 2nd power */
	    d__1 = intvr2_1.wm[i__ - 1];
	    q0 = taukh_1.fes3[i__ - 1] * (d__1 * d__1);
/*               VESD(I) = 0.2D0*ABS(FES3(I)*WM(I)**2) */
/*               VESD(I) = 0.2D0*ABS(Q0+Q1+Q2) */
	    difad2_1.vesd[i__ - 1] = (q0 + q1 + q2) * .2;
/* SECOND ORDER TERM */
	    difad3_1.vesd2[i__ - 1] = difad3_1.facd2[i__ - 1] * .2 * 
		    intvr2_1.wm[i__ - 1];
/* THIRD ORDER TERM */
	    difad3_1.vesd3[i__ - 1] = difad3_1.facd3[i__ - 1] * .2 * 
		    intvr2_1.wm[i__ - 1];
/*               VES(I) = ABS(RAT(I)*VES(I)+THN(I)-FES3(I)*QW) */
/* Computing 2nd power */
	    d__1 = (omega[i__] - omega[i__ - 1]) / dr;
	    temp2_1.ves[i__ - 1] = quadd_1.rat[i__ - 1] * temp2_1.ves[i__ - 1]
		     + oldrot2_1.thn[i__ - 1] + (taukh_1.fes3[i__ - 1] + 
		    vfact_1.fact7[i__ - 1]) * qw + vfact_1.fact8[i__ - 1] * (
		    d__1 * d__1);
	    egridder_1.eqqcod[i__ - 1] = egridder_1.qqcod[i__ - 1] * 
		    intvr2_1.wm[i__ - 1];
	}
L31:
	;
    }
/*      ENDIF */
/* INHIBITION CAUSED BY GRADIENTS IN MEAN MOLECULAR WEIGHT. */
/* INCLUDE ONLY THE ZAHN & MAEDER 1998 TREATMENT, WHERE (DEL - DEL AD) IS */
/* REPLACED BY (DEL + DEL MU - DEL AD).  RETAIN IMU FLAG FOR LATER USE. */
/*      IF(IMU.EQ.3)THEN */
/*  FICTITIOUS MU CURRENTS THAT OPPOSE ES CIRCULATION CALCULATED HERE. */
/*         DO 32 I = IMIN,IMAX */
/*            IF(LCZ(I).AND.LCZ(I-1))GOTO 32 */
/* SQUARE ROOT OF TKH*,KIPPENHAHN,IAU#66,P.23,USING EQ.(12)FOR D ON P.25. */
/* NOTE FACTOR OF G IS SUBSUMED IN FACT4. */
/*            TKHS = SQRT(VISCM(I)*CC/THDIFM(I)) */
/*            QMU = (HAMU(I)-HAMU(I-1))/(HRU(I)-HRU(I-1)) */
/*            VMU(I) = ABS(FMU*FACT1(I)*FACT4(I)*AMUM(I)*QMU/TKHS) */
/*            VMU2(I)=FMU*HGM(I)*ABS(QMU)/AMUM(I)/WM(I)**2 */
/*   32    CONTINUE */
/* LOCAL TIMESCALE ESTIMATE FOR MU INHIBITION. */
/* ASSUMES V/L = OMEGA. */
/*      ELSE IF(IMU.EQ.2)THEN */
/* MHP 06/02 REPLACE WITH THE ZAHN&MAEDER 1998 PRESCRIPTION */
    i__1 = *imax;
    for (i__ = *imin; i__ <= i__1; ++i__) {
	qmu = log(mdphy_1.hamu[i__ - 1]) - log(mdphy_1.hamu[i__ - 2]);
	qp = const1_1.cln * (hp[i__] - hp[i__ - 1]);
	ddel = oldrot2_1.ddelm[i__ - 1] + qmu / qp;
/* Computing MAX */
	d__1 = oldrot2_1.ddelm[i__ - 1];
	ddtest = max(d__1,.001);
	ddtest2 = max(ddel,.001);
	qqq = ddtest / ddtest2;
	temp2_1.ves[i__ - 1] *= qqq;
	if (varfc_1.ldifad) {
	    difad2_1.vesa[i__ - 1] *= qqq;
	    difad2_1.vesd[i__ - 1] *= qqq;
	    difad3_1.vesd2[i__ - 1] *= qqq;
	    difad3_1.vesd3[i__ - 1] *= qqq;
	}
/* Computing 2nd power */
	d__1 = intvr2_1.wm[i__ - 1];
	q1 = vfact_1.fact7[i__ - 1] * (d__1 * d__1) * qqq;
/* Computing 2nd power */
	d__1 = intvr2_1.wm[i__ - 1];
	q0 = taukh_1.fes3[i__ - 1] * (d__1 * d__1) * qqq;
	dr = hru[i__] - hru[i__ - 1];
	v2 = (q0 + q1) * .2 * (omega[i__] - omega[i__ - 1]) / dr / 
		intvr2_1.wm[i__ - 1];
/* ADD MU GRADIENTS TO VELOCITY ESTIMATES */
	oldrot2_1.festime[i__ - 1] *= qqq;
	difad3_1.fv0[i__ - 1] *= qqq;
/*         WRITE(*,911)I,WM(I),VESA(I),V2,Q0,Q1,THN(I),VES(I),QQQ */
/* 911           FORMAT(I5,1P8E12.3) */
    }
/*         DO 33 I = IMIN,IMAX */
/*            IF(LCZ(I).AND.LCZ(I-1))GOTO 33 */
/*            DR = HRU(I) - HRU(I-1) */
/*            VMU(I)=FMU*HGM(I)*ABS(HAMU(I)-HAMU(I-1))/DR/AMUM(I) */
/*     *             /WM(I)**2 */
/*   33    CONTINUE */
/* ALTERNATE EXPRESSION : D = D0/(1+R*DEL MU/MU) */
/* THIS IS ACTUALLY SIMILAR TO THE ZM98 FORMULA, THEREFORE OBSOLETE. */
/* SHOULD HAVE PUBLISHED IT - OH WELL. */
/*      ELSE */
/*         DO 34 I = IMIN,IMAX */
/*            IF(LCZ(I).AND.LCZ(I-1))GOTO 34 */
/*            DR = HRU(I) - HRU(I-1) */
/*            DDEL = DELAMI(I)/MAX(1.0D-6,DELAMI(I)-DELMI(I)) */
/*            VMU(I)=FMU*RM(I)*DDEL*ABS(HAMU(I)-HAMU(I-1))/DR/AMUM(I) */
/* 34         CONTINUE */
/*      ENDIF */
/*  GSF INSTABILITY.  VELOCITY DEFINED IN SR SETUPV. */
/* OMIT ALL BUT THE KIPPENHAHN 1980 ESTIMATE. */
/* IGSF IS RETAINED, AND THE VALUE DETERMINES WHAT IS PERMITTED TO */
/* INHIBIT IT. */
/* IGSF = 0: INHIBITED BY VISCOSITY AND MU GRADIENTS */
/* IGSF = 1: NEITHER VISCOSITY NOR MU GRADIENTS INHIBIT */
/* IGSF = 2: INHIBITED BY VISCOSITY ONLY */
/* NOTE THAT THE ABCD INSTABILITY - RELATED TO THE GSF INSTABILITY - */
/* WOULD NOT BE INHIBITED BY VISCOSITY/MU GRADIENTS, SO INCLUDING IT */
/* IS EQUIVALENT TO SETTING IGSF=1 (THE ORIGINAL K1980 ESTIMATE). */
/* THE INHIBITION FACTORS COME FROM SUBSEQUENT WORK BY SPRUIT. */
/*      IF(IGSF.EQ.0 .OR. IGSF.EQ.2 .OR. IGSF.EQ.1)THEN */
/* KIPPENHAHN (1980) ESTIMATE */
    i__1 = *imax;
    for (i__ = *imin; i__ <= i__1; ++i__) {
	if (lcz[i__] && lcz[i__ - 1]) {
	    goto L40;
	}
/* MHP 8/93 STABILITY CONDITION ADDED, NEGLECTING THE EFFECTS OF */
/* MU GRADIENTS. */
	if (vmult2_1.igsf == 2 || vmult2_1.igsf == 0) {
	    qwrmx = sqrt(intvr2_1.viscm[i__ - 1] / intvr2_1.thdifm[i__ - 1]) *
		     2. * qwrmax[i__];
	    if ((d__1 = qwlnr[i__], abs(d__1)) < qwrmx) {
		temp2_1.vgsf[i__ - 1] = 0.;
		goto L40;
	    } else {
		fxx = sqrt(((d__1 = qwlnr[i__], abs(d__1)) - qwrmx) / qwrmx);
	    }
	} else {
	    fxx = 1.;
	}
	dr = hru[i__] - hru[i__ - 1];
	if (vmult2_1.igsf == 0) {
	    qwrmx = sqrt(intvar_1.hgm[i__ - 1] * (d__1 = mdphy_1.hamu[i__ - 1]
		     - mdphy_1.hamu[i__ - 2], abs(d__1)) / dr / intvr2_1.amum[
		    i__ - 1]) * 2.;
	    if ((d__1 = qwlnr[i__], abs(d__1)) < qwrmx) {
		temp2_1.vgsf[i__ - 1] = 0.;
		goto L40;
	    } else {
/* MHP 05/02 ADDED TESTS TO AVOID DIVIDE BY ZERO */
/*                  FXX2 = SQRT((ABS(QWLNR(I))-QWRMX)/QWRMX) */
		qq = qwlnr[i__] * .01;
		if (abs(qwrmx) < abs(qq)) {
		    fxx2 = 1.;
		} else {
		    if (abs(qwrmx) < 1e-20) {
			fxx2 = 1.;
		    } else {
			fxx2 = sqrt(((d__1 = qwlnr[i__], abs(d__1)) - qwrmx) /
				 qwrmx);
		    }
		}
		fxx = min(fxx,fxx2);
	    }
	}
	rmid = (hru[i__] + hru[i__ - 1]) * .5;
	dlnwdr = (d__1 = log(omega[i__]) - log(omega[i__ - 1]), abs(d__1)) / 
		dr;
/* GSF IS TRIGGERED BY D OMEGA/DZ NONZERO (I.E. ROTATION NOT */
/* ON CYLINDERS,WHICH IS TRUE IN GENERAL IN OUR MODELS), OR */
/* BY D LN(J/M)/DR < 0, WHICH SOMETIMES OCCURS. */
/* IF D LN(J/M)/DR < 0, CHECK SECOND CRITERIA AND USE THE LARGEST */
/* VELOCITY; OTHERWISE,USE ONLY D OMEGA/DZ NON-ZERO CRITERION. */
/* Computing 2nd power */
	d__1 = hru[i__];
/* Computing 2nd power */
	d__2 = hru[i__ - 1];
	if (omega[i__] * (d__1 * d__1) < omega[i__ - 1] * (d__2 * d__2)) {
	    dlnjmdr = (d__1 = 2. / rmid + (log(omega[i__]) - log(omega[i__ - 
		    1])) / dr, abs(d__1));
/* Computing MAX */
	    d__1 = dlnjmdr * 2., d__2 = dlnwdr * .25;
	    fx = max(d__1,d__2);
/* FACTOR OF R IN THE DENOMINATOR OCCURS BECAUSE ALL THE CIRCULATION */
/* VELOCITIES ARE LATER MULTIPLIED BY R (THE "LENGTH SCALE"). */
/* Computing 2nd power */
	    d__1 = intvr2_1.wm[i__ - 1];
	    temp2_1.vgsf[i__ - 1] = taukh_1.fgsfk[i__ - 1] * fx * 
		    intvr2_1.thdifm[i__ - 1] * (d__1 * d__1) / rmid;
	} else {
/* Computing 2nd power */
	    d__1 = intvr2_1.wm[i__ - 1];
	    temp2_1.vgsf[i__ - 1] = taukh_1.fgsfk[i__ - 1] * .25 * 
		    intvr2_1.thdifm[i__ - 1] * dlnwdr * (d__1 * d__1) / rmid;
	}
	temp2_1.vgsf[i__ - 1] = (d__1 = fxx * temp2_1.vgsf[i__ - 1], abs(d__1)
		);
L40:
	;
    }
/* OMIT JAMES AND KAHN ESTIMATE */
/*      ELSE */
/* JAMES AND KAHN (1971) ESTIMATE. */
/* NOTE FACTOR OF OMEGA**4, WHICH IS PART OF THE MERIDIONAL */
/* CIRCULATION VELOCITY ESTIMATE. */
/*         DO 41 I = IMIN,IMAX */
/*            IF(LCZ(I).AND.LCZ(I-1))GOTO 41 */
/* MHP 8/93 STABILITY CONDITION ADDED, NEGLECTING THE EFFECTS OF */
/* MU GRADIENTS. */
/*            QWRMX = 2.0D0*SQRT(VISCM(I)/THDIFM(I))*QWRMAX(I) */
/*            IF(ABS(QWLNR(I)).LT.QWRMX)THEN */
/*               VGSF(I) = 0.0D0 */
/*               GOTO 41 */
/*            ELSE */
/*               FXX = SQRT((ABS(QWLNR(I))-QWRMX)/QWRMX) */
/*            ENDIF */
/*            DR = HRU(I)-HRU(I-1) */
/*            RMID = 0.5D0*(HRU(I)+HRU(I-1)) */
/*            DLNJMDR = ABS(2.0D0/RMID+(LOG(OMEGA(I))- */
/*     *                LOG(OMEGA(I-1)))/DR) */
/*            IF(IGSF.EQ.3)THEN */
/*               DWDR = abs(OMEGA(I)-OMEGA(I-1))/DR */
/*               VGSF(I) = 2.0D0*FGSFJ(I)*DWDR**2 */
/*               VGSF(I) = ABS(VGSF(I)) */
/*            ELSE IF(IES.EQ.2)THEN */
/*               VGSF(I) = 2.0D0*VES(I)*FACT3(I)*DLNJMDR**2 */
/*            ELSE */
/*               VGSF(I) = 2.0D0*FGSFJ(I)*(DLNJMDR*WM(I))**2 */
/*               VGSF(I) = ABS(FXX*VGSF(I)) */
/*            ENDIF */
/*   41    CONTINUE */
/*      ENDIF */
/*  DIFFUSIVE AND DYNAMICAL SHEAR INSTABILITIES - REF. ENDAL&SOFIA PAPER II. */
    i__1 = *imax;
    for (i__ = *imin; i__ <= i__1; ++i__) {
/*  CHECK FOR OPERATION OF DYNAMICAL SHEAR. */
/*  IF DYNAMICAL SHEAR IS OPERATING,SET SECULAR SHEAR VELOCITY TO MAXIMUM */
/*  VALUE AND COMPUTE (LARGE) DYNAMICAL SHEAR VELOCITY. */
	if ((d__1 = qwlnr[i__], abs(d__1)) > qwrmax[i__]) {
	    qwr = (d__1 = qwlnr[i__], abs(d__1));
/* Computing 2nd power */
	    d__1 = qwr / qwrmax[i__];
	    temp2_1.vss[i__ - 1] = intvr2_1.thdifm[i__ - 1] * 
		    .17777777777777778 * (d__1 * d__1) / intvar_1.rm[i__ - 1];
/*  CORRECT GSF VELOCITY AS WELL. */
	    dr = hru[i__] - hru[i__ - 1];
	    rmid = (hru[i__] + hru[i__ - 1]) * .5;
	    if (omega[i__] < omega[i__ - 1]) {
		wmin = omega[i__] + qwrmax[i__] * const1_1.cln * (hr[i__] - 
			hr[i__ - 1]);
		wmid = omega[i__] + qwrmax[i__] * const1_1.cln * (hr[i__] - 
			d_lg10(&rmid));
	    } else {
		wmin = omega[i__] - qwrmax[i__] * const1_1.cln * (hr[i__] - 
			hr[i__ - 1]);
		wmid = omega[i__] - qwrmax[i__] * const1_1.cln * (hr[i__] - 
			d_lg10(&rmid));
	    }
	    dlnwdr0 = (d__1 = log(omega[i__]) - log(omega[i__ - 1]), abs(d__1)
		    ) / dr;
	    dlnjmdr0 = (d__1 = 2. / rmid + (log(omega[i__]) - log(omega[i__ - 
		    1])) / dr, abs(d__1));
	    dlnjmdr = (d__1 = 2. / rmid + (log(omega[i__]) - log(wmin)) / dr, 
		    abs(d__1));
	    dlnwdr = (d__1 = log(omega[i__]) - log(wmin), abs(d__1)) / dr;
/* MHP 05/02 ADDED FIRST BRANCH FOR IGSF=0 - SOMEHOW */
/* MISSED IN CODE CHANGES EARLIER! */
/* kippenhahn (1980) estimate */
/* OMIT BRANCH FOR JAMES AND KAHN. */
/*            IF(IGSF.EQ.2 .OR. IGSF.EQ.1 .OR. IGSF.EQ.0)THEN */
/* Computing 2nd power */
	    d__1 = hru[i__];
/* Computing 2nd power */
	    d__2 = hru[i__ - 1];
	    if (omega[i__] * (d__1 * d__1) < wmin * (d__2 * d__2)) {
/* Computing MAX */
		d__1 = dlnjmdr * 2., d__2 = dlnwdr * .25;
		fx = max(d__1,d__2);
/* Computing MAX */
		d__1 = dlnjmdr0 * 2., d__2 = dlnwdr0 * .25;
		fx2 = max(d__1,d__2);
		temp2_1.vgsf[i__ - 1] = temp2_1.vgsf[i__ - 1] * fx / fx2;
	    } else {
		temp2_1.vgsf[i__ - 1] = temp2_1.vgsf[i__ - 1] * dlnwdr / 
			dlnwdr0;
	    }
/*            ELSE IF(IGSF.EQ.3)THEN */
/*               DWDR = abs(OMEGA(I)-WMIN)/DR */
/*               DWDR0 = ABS(OMEGA(I)-OMEGA(I-1))/DR */
/*               VGSF(I) = VGSF(I)*(DWDR/DWDR0)**2 */
/*            ELSE IF(IES.EQ.2)THEN */
/*               VGSF(I) = VGSF(I)*(DLNJMDR/DLNJMDR0)**2 */
/*            ELSE */
/*               WMID0 = 0.5D0*(OMEGA(I)+OMEGA(I-1)) */
/*               VGSF(I) = VGSF(I)*(DLNJMDR*WMID/DLNJMDR0/WMID0)**2 */
/*            ENDIF */
	    s_wsfe(&io___36);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&omega[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&omega[i__ - 1], (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&wmin, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	    goto L60;
/* *** END OF CHANGED SECTION */
	}
/*   FIND MAXIMUM GRADIENT IN OMEGA ALLOWED BY SECULAR SHEAR. */
/*   THE RUN OF QWRMAX INPUT IS THAT ALLOWED BY THE DYNAMICAL SHEAR; */
/*   THE SECULAR SHEAR RICHARDSON # IS RELATED BY */
/*   RICHNO(SECULAR) = PRANDTL# * CRITICAL REYNOLDS#/8 * RICHNO(DYNAMICAL) */
/*   PRANDTL # = KINEMATIC VISCOSITY/THERMOMETRIC DIFFUSIVITY. */
/* MHP 3/92 SQUARE ROOT OF PR# NEEDED, NOT PR # - ERROR CORRECTED! */
/* THE VELOCITY ESTIMATE HERE IS FROM ZAHN 1991. */
	qwrmx = sqrt(intvr2_1.viscm[i__ - 1] / intvr2_1.thdifm[i__ - 1] * 
		.125 * vmult_1.rcrit) * qwrmax[i__];
	if ((d__1 = qwlnr[i__], abs(d__1)) > qwrmx) {
/*  UNSTABLE; CHECK FOR MU GRADIENTS. */
	    if ((d__1 = (mdphy_1.hamu[i__ - 1] - mdphy_1.hamu[i__ - 2]) / 
		    intvr2_1.amum[i__ - 1], abs(d__1)) < 1e-10) {
		qwrmx2 = 0.;
		qwr = (d__1 = qwlnr[i__], abs(d__1)) - qwrmx;
/* Computing 2nd power */
		d__1 = qwr / qwrmax[i__];
		temp2_1.vss[i__ - 1] = intvr2_1.thdifm[i__ - 1] * 
			.17777777777777778 * (d__1 * d__1) / intvar_1.rm[i__ 
			- 1];
	    } else {
/*  CHECK FOR EFFECTS OF MU GRADIENT. */
/*  RICHNO = RHO/P*(-d lnT/d lnMU)*(del MU)/(del P)*(G/QWLNR)**2 */
/*  WHERE -d lnT/d lnMU = (CON-1)/(1+3CON),CON=(a/3)T**4/P */
/*  GIVEN (1 - CON)P = CGAS*RHO*T/MU */
/*      FACT = (RHOM/PM)*QTMU*DMU/AMUM/DP*HGM**2 */
/* Computing MAX */
		d__2 = 1e-20, d__3 = vfact_1.fact5[i__ - 1] * (d__1 = (
			mdphy_1.hamu[i__ - 1] - mdphy_1.hamu[i__ - 2]) / 
			intvr2_1.amum[i__ - 1], abs(d__1));
		qwrmx2 = sqrt((max(d__2,d__3))) * 2.;
		if ((d__1 = qwlnr[i__], abs(d__1)) > qwrmx2) {
/*  INTERFACE UNSTABLE WITH RESPECT TO BOTH CONDITIONS; CHOOSE THE */
/*  MAXIMUM GRADIENT IMPLIED BY THE SECOND CONDITION IF IT'S LARGER */
/*  THAN THE FIRST(I.E. IF A MU GRADIENT IS SLOWING J TRANSPORT). */
		    qwrmx = max(qwrmx2,qwrmx);
		    qwr = (d__1 = qwlnr[i__], abs(d__1)) - qwrmx;
/* Computing 2nd power */
		    d__1 = qwr / qwrmax[i__];
		    temp2_1.vss[i__ - 1] = intvr2_1.thdifm[i__ - 1] * 
			    .17777777777777778 * (d__1 * d__1) / intvar_1.rm[
			    i__ - 1];
		}
	    }
	}
L60:
	;
    }
/*  NOW DETERMINE WHETHER OR NOT MU GRADIENTS ARE STEEP ENOUGH TO */
/*  INHIBIT TRANSPORT.  MULTIPLY THE RESULTING VELOCITY ESTIMATES */
/*  BY THE USER DEFINED PARAMETERS FES AND FGSF. */
/*  IMU=3 KIPPENHAHN AND MOLLENHOF(1974)METHOD;IMU=2 LOCAL DAMPING */
/*  FACTOR METHOD. */
/* AGAIN, OMIT OBSOLETE MU GRADIENT TREATMENTS. */
/*      IF(IMU.EQ.3)THEN */
/*         IF(IT.GT.1)THEN */
/*            DO I = 1,M */
/*               VMU(I) = 0.5D0*(VMU(I)+VMUP(I)) */
/*            END DO */
/*         ENDIF */
/*         DO I = IMIN,IMAX */
/*            FM = 1.0D0+VMU2(I) */
/*            RMID = 0.5D0*(HRU(I)+HRU(I-1)) */
/*            FCC = SQRT(FC*FESC) */
/*            VEST=MAX(0.0D0,FES*VES(I)-SQRT(FES*VES(I)*RMID) */
/*     *               *FCC*VMU(I)) */
/*            IF(VEST.LE.0.0D0)THEN */
/*               VES(I) = ABS(FES*VES(I)/FM) */
/*            ELSE */
/*               VES(I) = VEST */
/*            ENDIF */
/*            FCC = SQRT(FC*FGSFC) */
/*            IF(VGSF(I).GT.0.0D0)THEN */
/*               VGSFT=MAX(0.0D0,FGSF*VGSF(I)-SQRT(FGSF*VGSF(I)*RMID) */
/*     *               *FCC*VMU(I)) */
/*            ELSE */
/*               VGSFT = 0.0D0 */
/*            ENDIF */
/*            IF(VGSFT.LE.0.0D0)THEN */
/*               VGSF(I) = ABS(FES*VGSF(I)/FM) */
/*            ELSE */
/*               VGSF(I) = VGSFT */
/*            ENDIF */
/*            VSS(I)=MAX(0.0D0,FSS*VSS(I)) */
/*         END DO */
/*      ELSE */
/*            IF(IMU.NE.2)THEN */
/*               FM = 1.0D0+VMU(I) */
/*            ELSE */
/*               FM = 1.0D0 */
/*            ENDIF */
/*            VES(I)=ABS(FES*VES(I)/FM) */
/* MHP 05/02 ONLY DO THIS IF MU GRADIENTS NOT */
/* ALREADY ACCOUNTED FOR */
/*            VGSF(I)=ABS(FGSF*VGSF(I)/FM) */
/*            IF(IGSF.NE.0)THEN */
/*               VGSF(I)=ABS(FGSF*VGSF(I)/FM) */
/*            ELSE */
/*               VGSF(I) = FGSF*VGSF(I) */
/*            ENDIF */
/* ALREADY INCLUDED - ONLY USE SCALE FACTOR */
/*            VSS(I)=ABS(FSS*VSS(I)/FM) */
/*            VSS(I)= FSS*VSS(I) */
/*         END DO */
/* MHP 8/03 MULTIPLY VELOCITY ESTIMATES BY USER PARAMETER */
/* SCALE FACTORS */
    i__1 = *imax;
    for (i__ = *imin; i__ <= i__1; ++i__) {
	temp2_1.ves[i__ - 1] = (d__1 = vmult_1.fes * temp2_1.ves[i__ - 1], 
		abs(d__1));
	temp2_1.vgsf[i__ - 1] = vmult_1.fgsf * temp2_1.vgsf[i__ - 1];
	temp2_1.vss[i__ - 1] = vmult_1.fss * temp2_1.vss[i__ - 1];
    }
/* MHP 11/94 */
/* REPEAT FOR DIF+AD */
    if (varfc_1.ldifad) {
	i__1 = *imax;
	for (i__ = *imin; i__ <= i__1; ++i__) {
	    difad2_1.vesd[i__ - 1] = (d__1 = vmult_1.fes * difad2_1.vesd[i__ 
		    - 1], abs(d__1));
	    difad2_1.vesa[i__ - 1] = vmult_1.fes * difad2_1.vesa[i__ - 1];
	}
    }
/*               IF(IMU.NE.2)THEN */
/*                  FM = 1.0D0+VMU(I) */
/*               ELSE */
/*                  FM = 1.0D0 */
/*               ENDIF */
/*               FM = 1.0D0+VMU(I) */
/*               VESD(I)=ABS(FES*VESD(I)/FM) */
/*               VESA(I)=FES*VESA(I)/FM */
/*            END DO */
/*         ENDIF */
/*      ENDIF */
    if (varfc_1.ldifad) {
/* MHP 05/02 */
/* CHANGED TO REFLECT THE DIFFERENT TREATMENT OF THE GSF INSTABILITY. */
/* THE ENDAL AND SOFIA VARIANT HAD V=THDIF*DLNWDR*W**2/R WHICH WAS */
/* THEN ADDED TO A DIFFUSION EQUATION D/DR(CON*V*R*DW/DR). */
/* IN THE ZAHN FORMULISM, WE ARE SOLVING AN EQUATION OF THE FORM */
/* D/DR(CON*V*W).  BECAUSE THE VELOCITY ESTIMATE ITSELF INCLUDES */
/* DW/DR THIS IS IN EFFECT A DIFFUSION TERM.  SO...WE NEED TO */
/* MULTIPLY THE ORIGINAL VELOCITY BY W AND DIVIDE BY DW/DR TO CAST */
/* IT AS AN ENTRY IN THE DIFFUSION EQUATION. */
	i__1 = *imax;
	for (i__ = *imin; i__ <= i__1; ++i__) {
	    difad2_1.vesd[i__ - 1] += intvar_1.rm[i__ - 1] * ((d__1 = 
		    temp2_1.vgsf[i__ - 1], abs(d__1)) + (d__2 = temp2_1.vss[
		    i__ - 1], abs(d__2)));
	    difad3_1.dss[i__ - 1] = intvar_1.rm[i__ - 1] * (d__1 = 
		    temp2_1.vss[i__ - 1], abs(d__1));
	    difad3_1.dgsf[i__ - 1] = intvar_1.rm[i__ - 1] * (d__1 = 
		    temp2_1.vgsf[i__ - 1], abs(d__1));
/*            IF(VGSF(I).GT.0.0D0)THEN */
/* D LN W/DR */
/*               DR = HRU(I) - HRU(I-1) */
/*               QLNWR = ABS(LOG(OMEGA(I))-LOG(OMEGA(I-1))/DR) */
/* CEILING SET BY DYNAMICAL SHEAR */
/*               QLNWRMAX = ABS(QWRMAX(I)/(WM(I)*RM(I))) */
/* TAKE THE SMALLER OF THE TWO */
/*               QLNWR = MIN(QLNWR,QLNWRMAX) */
/*               IF(QLNWR.GT.1.0D-32)VESD(I) = VESD(I)+ABS(VGSF(I)/QLNWR) */
/*            ENDIF */
/*            IF(VSS(I).GT.0.0D0)THEN */
/*               VESD(I) = VESD(I)+ABS(VSS(I)*RM(I)) */
/*            ENDIF */
	}
    }
/*  AVERAGE PREVIOUS AND NEW VELOCITY ESTIMATES AFTER THE FIRST ITERATION. */
    if (*it > 1) {
	i__1 = *imax;
	for (i__ = *imin; i__ <= i__1; ++i__) {
	    temp2_1.vgsf[i__ - 1] = (temp2_1.vgsf[i__ - 1] + temp2_1.vgsf0[
		    i__ - 1]) * .5;
	    temp2_1.ves[i__ - 1] = (temp2_1.ves[i__ - 1] + temp2_1.ves0[i__ - 
		    1]) * .5;
	    temp2_1.vss[i__ - 1] = (temp2_1.vss[i__ - 1] + temp2_1.vss0[i__ - 
		    1]) * .5;
/* L70: */
	}
/* MHP 11/94 */
	if (varfc_1.ldifad) {
	    i__1 = *imax;
	    for (i__ = *imin; i__ <= i__1; ++i__) {
		difad2_1.vesa[i__ - 1] = (difad2_1.vesa[i__ - 1] + 
			difad2_1.vesa0[i__ - 1]) * .5;
		difad2_1.vesd[i__ - 1] = (difad2_1.vesd[i__ - 1] + 
			difad2_1.vesd0[i__ - 1]) * .5;
	    }
	}
    }
    i__1 = *imax;
    for (i__ = *imin; i__ <= i__1; ++i__) {
	hv[i__] = temp2_1.vgsf[i__ - 1] + temp2_1.ves[i__ - 1] + temp2_1.vss[
		i__ - 1];
	if (hv[i__] < 1e-20) {
	    hv[i__] = 0.;
	}
	if (hv[i__] > 0.) {
	    *ldo = TRUE_;
	}
/* L80: */
    }
/* 9/93 MIXING WITHOUT TRANSPORT ADDED. */
/* ZERO OUT COEFFICIENTS IN CORE TO AVOID NUMERICAL PROBLEMS IN */
/* THE H-BURNING SHELL. */
    if (notran_1.lnoj) {
	i__1 = *imax;
	for (i__ = *imin; i__ <= i__1; ++i__) {
	    dell = intvar_1.alm[i__ - 1] / *cltot;
	    if (dell < .99) {
		hv[i__] = 0.;
		temp2_1.vgsf[i__ - 1] = 0.;
		temp2_1.ves[i__ - 1] = 0.;
		temp2_1.vss[i__ - 1] = 0.;
/* MHP 11/94 */
		difad2_1.vesa[i__ - 1] = 0.;
		difad2_1.vesd[i__ - 1] = 0.;
	    } else {
		goto L81;
	    }
	}
L81:
	;
    }
    return 0;
} /* vcirc_ */

