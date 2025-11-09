/* taucal.f -- translated by f2c (version 20061008).
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
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal drate[5000], drate0[5000], fmassacc;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    logical lnewtcz, lcalcenv;
    doublereal taucz, taucz0, pphot, pphot0, fracstep;
} ovrtrn_;

#define ovrtrn_1 ovrtrn_

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;

/* $$$$$$ */
/*       SUBROUTINE TAUCAL(HCOMP,HS2,HS1,LCZ,HR,HP,HD,HG,M,SVEL,DEL1,DEL2,MINT)  ! KC 2025-05-31 */
/* Subroutine */ int taucal_(doublereal *hs2, doublereal *hs1, logical *lcz, 
	doublereal *hr, doublereal *hp, doublereal *hd, doublereal *hg, 
	integer *m, doublereal *svel, doublereal *del1, doublereal *del2)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), d_lg10(doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer i__, j, k;
    static doublereal fx, dd1, dd2, ps1, ps2, tol, psca, cvel;
    static integer imax;
    static doublereal umer, envr;
    static logical lflag;
    static doublereal denom, hsbot;
    static logical lczex;
    static doublereal envrl, hstop, cveavg;
    static logical lallcz;
    static doublereal czwide;
    static integer icztop;
    static doublereal rtestl;
    static logical ltwocz, lczsur;

    /* Fortran I/O blocks */
    static cilist io___28 = { 0, 6, 0, 0, 0 };


/* G Somers 3/17, ADDING NEW TAUCZ COMMON BLOCK */
/*       DIMENSION HCOMP(15,JSON),HS2(JSON),LCZ(JSON),  ! KC 2025-05-31 */
/* XSUM(15) */
/* JVS 02/12 CALCULATE THE LOCAL CONVECTIVE OVERTURN TIMESCALE AT THE BASE */
/* OF THE CZ. IN OLDER VERSIONS THIS WAS ONLY DONE FOR ROTATING MODELS; */
/* THIS MAKES IT SO TAUCZ IS CALCULATED FOR ALL MODELS. THIS PARTICULAR SUBROUTINE */
/* DOES CALCULATES THE OVERTURN TIMESCALES IN MODELS WHERE THE CZ IS WITHIN */
/* THE ENVELOPE */
/* THIS CODE SNAGGED FROM MIDMOD */
/*  DETERMINE EXTENT OF SURFACE CONVECTION ZONE. */
    /* Parameter adjustments */
    --del2;
    --del1;
    --svel;
    --hg;
    --hd;
    --hp;
    --hr;
    --lcz;
    --hs1;
    --hs2;

    /* Function Body */
    lallcz = FALSE_;
/* JVS Allows the last point to be stable. */
/* JVS 05/14 removed requirement for last point to be convective, since this routine */
/* is only called from ENVINT, the near surface points in the envelope are often */
/* radiative, despite the fact that a convective envelope exists. Code now checks */
/* to make sure there is a CZ somewhere in the envelope. */
/*      IF(LCZ(M) .OR. LCZ(M-1) .OR. LCZ(M-2))THEN */
/*  SURFACE C.Z. EXISTS.  FIND LOWEST SHELL (IMAX), WHICH IS ALSO THE */
/*  UPPERMOST ZONE CONSIDERED FOR STABILITY AGAINST ROTATIONALLY INDUCED MIXING. */
/*         DO 71 I = M-1,1,-1 */
/*            IF(.NOT.LCZ(I)) GOTO 81 */
/*   71    CONTINUE */
/*         LALLCZ = .TRUE. */
/*         I = 0 */
/*   81    IMAX = I + 1 */
/* DEAL THE POSSIBILITY OF TWO OR MORE SURFACE CONVECTION ZONES IN THE ENVELOPE */
    lflag = FALSE_;
    ltwocz = FALSE_;
    lczex = FALSE_;
/* Flag for the existence of a CZ */
    for (i__ = *m - 1; i__ >= 1; --i__) {
	if (! lcz[i__] && ! lflag && lczex) {
/* EXITING CZ */
	    imax = i__ + 1;
	    lflag = TRUE_;
	} else if (lflag && lcz[i__]) {
/* TWO CZS WITH RADIATIVE ZONE BETWEEN */
	    lflag = FALSE_;
	    ltwocz = TRUE_;
	    icztop = i__;
	} else if (lcz[i__] && ! lczex) {
/* First convective point from surface */
	    lczex = TRUE_;
	}
/* L71: */
    }
    if (imax < 1) {
	lallcz = TRUE_;
    }
    if (lczex) {
/*  HSTOP IS THE MASS AT THE TOP OF THE C.Z. */
/*  HSBOT IS THE MASS AT THE BOTTOM OF THE C.Z. */
/* REPLACES "IF(LCZ(M)" THEN JVS 05/14 */
	hstop = hs1[*m];
	if (imax > 1) {
	    hsbot = (hs1[imax] + hs1[imax - 1]) * .5;
	} else {
	    hsbot = hs1[1];
	}
/*  LCZSUR=T IF A SURFACE C.Z.DEEP ENOUGH FOR ANGULAR MOMENTUM LOSS EXISTS */
	if ((hstop - hsbot) / const_1.cmsun > 0.) {
	    lczsur = TRUE_;
	} else {
	    lczsur = FALSE_;
	}
    } else {
/*  NO SURFACE C.Z. */
	imax = *m;
	lczsur = FALSE_;
    }
/* JVS 10/11/13 Concerned that this is inappropriate for LCZSUR = FALSE. */
/* Should never be the case, but removed it. */
/*      IF(LCZSUR)THEN */
    if (! lallcz) {
	if (! rot_1.lrot) {
	    hg[imax] = hs1[imax] * exp(const1_1.cln * (const2_1.cgl - hr[imax]
		     * 2.));
	    hg[imax - 1] = hs1[imax - 1] * exp(const1_1.cln * (const2_1.cgl - 
		    hr[imax - 1] * 2.));
	}
/* PINPOINT RCZ */
	dd2 = del1[imax - 1] - del2[imax - 1];
	dd1 = del1[imax] - del2[imax];
	fx = dd2 / (dd2 - dd1);
/* INFER HP */
	envrl = hr[imax - 1] + fx * (hr[imax] - hr[imax - 1]);
	envr = exp(const1_1.cln * envrl);
	ps2 = exp(const1_1.cln * (hp[imax] - hd[imax])) / hg[imax];
	ps1 = exp(const1_1.cln * (hp[imax - 1] - hd[imax - 1])) / hg[imax - 1]
		;
	psca = ps1 + fx * (ps2 - ps1);
	d__1 = envr + psca;
	rtestl = d_lg10(&d__1);
/* JVS 03/14 WHEN THERE ARE TWO CZS, THE DEEPER ONE CAN BE ~HP THICK. IN */
/* THIS CASE, WE"LL WANT AND AVERAGE CONVECTIVE VELOCITY ACROSS THE REGION */
/* -------------------------------------------------------------- */
	tol = .5f;
/*            IF(ABS(1.0 - ((DEXP(CLN*(RTESTL-HR(IMAX))) - 1.0)/ */
/*     *         (DEXP(CLN*(HR(ICZTOP)-HR(IMAX))) - 1.0))) .LT. TOL */
/*     *          .AND. LTWOCZ) THEN */
	if ((d__1 = 1.f - (exp(const1_1.cln * (rtestl - hr[imax])) - 1.f) / (
		exp(const1_1.cln * (hr[icztop] - hr[imax])) - 1.f), abs(d__1))
		 < tol || ltwocz) {
/* TAKE AVERAGE CONV VELOCITY */
	    cveavg = 0.f;
/*                  DENOM = ABS(HS1(ICZTOP)-HS1(IMAX))/DEXP(CLN*STOTAL) ! MASS IN CZ */
	    denom = 0.f;
	    umer = 0.f;
	    czwide = (d__1 = exp(const1_1.cln * hr[icztop]) - exp(
		    const1_1.cln * hr[imax]), abs(d__1));
	    i__1 = icztop;
	    for (j = imax; j <= i__1; ++j) {
		denom += hs2[j];
		umer += (svel[j] + svel[j + 1]) * .5 * hs2[j];
	    }
	    cveavg = umer / denom;
	    ovrtrn_1.taucz = czwide / cveavg;
	} else {
/*             (ORIGINAL ROUTINE) */
/*             FIND V */
	    i__1 = *m;
	    for (k = imax + 1; k <= i__1; ++k) {
		if (hr[k] > rtestl) {
		    fx = (rtestl - hr[k - 1]) / (hr[k] - hr[k - 1]);
		    cvel = svel[k - 1] + fx * (svel[k] - svel[k - 1]);
		    goto L85;
		}
	    }
	    cvel = svel[*m];
L85:
/*                  DEFINE TAUCZ */
	    ovrtrn_1.taucz = psca / cvel;
	}
/* JVS 10/11/13 */
/*         ELSE */
/* C INFER HP */
/*            IF(.NOT.LROT)THEN */
/*               HG(1)=HS1(1)*EXP(CLN*(CGL-2.0D0*HR(1))) */
/*            ENDIF */
/*            PSCA2 = EXP(CLN*(HP(1)-HD(1)))/HG(1) */
/*            RTEST2 = EXP(CLN*HR(1)) */
/*            IF(PSCA2.LE.RTEST2)THEN */
/* C HP < R AT THE FIRST POINT.  ASSUME V CONSTANT INSIDE AND HP = K/R FOR */
/* C SLOWLY VARYING DENSITY AND PRESSURE NEAR THE CENTER. */
/*               CVEL = SVEL(1) */
/*               PSCA = (PSCA2*RTEST2)**0.5D0 */
/*               TAUCZ = PSCA/CVEL */
/*            ELSE */
/*               DO K = 2,M */
/*                  PSCA1 = PSCA2 */
/*                  RTEST1 = RTEST2 */
/*                  IF(.NOT.LROT)THEN */
/*                     HG(K)=HS1(K)*EXP(CLN*(CGL-2.0D0*HR(K))) */
/*                  ENDIF */
/*                  PSCA2 = EXP(CLN*(HP(K)-HD(K)))/HG(K) */
/*                  RTEST2 = EXP(CLN*HR(K)) */
/* C FIND LOCATION WHERE HP = R */
/*                  IF(PSCA2.LE.RTEST2)THEN */
/*                     FX = (RTEST1-PSCA1)/((PSCA2-RTEST2)-(PSCA1-RTEST1)) */
/* C FIND V */
/*                     CVEL = SVEL(K-1)+FX*(SVEL(K)-SVEL(K-1)) */
/*                     PSCA = PSCA1+FX*(PSCA2-PSCA1) */
/* C DEFINE TAUCZ */
/*                     TAUCZ = PSCA/CVEL */
/*                     GOTO 95 */
/*                  ENDIF */
/*               END DO */
/*               K = M */
/*               CVEL = SVEL(M) */
/*               PSCA = PSCA2 */
/*               TAUCZ = PSCA/CVEL */
/* 95            CONTINUE */
/*            ENDIF */
/*         ENDIF */
    } else {
	ovrtrn_1.taucz = 0.;
    }
    s_wsle(&io___28);
    do_lio(&c__9, &c__1, "TauCal", (ftnlen)6);
    e_wsle();
/* END JVS */
    return 0;
} /* taucal_ */

