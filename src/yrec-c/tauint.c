/* tauint.f -- translated by f2c (version 20061008).
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
    integer imax1, imax2;
    logical ljvs;
} jtest_;

#define jtest_1 jtest_

struct {
    doublereal envp[5000], envt[5000], envs[5000], envd[5000], envr[5000], 
	    envx[5000], envz[5000];
    logical lcenv[5000];
    doublereal edels[15000]	/* was [3][5000] */, evels[5000], ebetas[5000]
	    , egam1[5000], eqcp[5000], efxions[15000]	/* was [3][5000] */, 
	    envo[5000], envl[5000], eqdt[5000];
    integer numenv;
} envstruct_;

#define envstruct_1 envstruct_

struct {
    logical lnewtcz, lcalcenv;
    doublereal taucz, taucz0, pphot, pphot0, fracstep;
} ovrtrn_;

#define ovrtrn_1 ovrtrn_

/* Table of constant values */

static doublereal c_b5 = .5;

/* $$$$$$ */
/*       SUBROUTINE TAUINT(HCOMP,HS2,HS1,LCZ,HR,HP,HD,HG,M,SVEL,DEL1,DEL2)  ! KC 2025-05-31 */
/* Subroutine */ int tauint_(doublereal *hs1, logical *lcz, doublereal *hr, 
	doublereal *hp, doublereal *hd, doublereal *hg, integer *m, 
	doublereal *svel, doublereal *del1, doublereal *del2)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), d_lg10(doublereal *), pow_dd(doublereal *, 
	    doublereal *);

    /* Local variables */
    static integer i__, k;
    static doublereal fx, dd1, dd2, ps1, ps2, psca, cvel;
    static integer imax;
    static doublereal psca1, psca2, envrc, hsbot, hstop, rtest1, rtest2;
    static logical lallcz;
    static doublereal envrcl, rtestl;
    static logical lczsur;

/* Needs access to this common block: grants knowledge of envellope */
/* KC 2025-05-30 reordered common block elements */
/* JvS 08/25 Updated with new elements */
/* G Somers 3/17, ADDING NEW TAUCZ COMMON BLOCK */
/*       DIMENSION HCOMP(15,JSON),HS2(JSON),LCZ(JSON), */
/* XSUM(15) */
/* JVS 02/12 CALCULATE THE LOCAL CONVECTIVE OVERTURN TIMESCALE AT THE BASE */
/* OF THE CZ. IN OLDER VERSIONS THIS WAS ONLY DONE FOR ROTATING MODELS; */
/* THIS MAKES IT SO TAUCZ IS CALCULATED FOR ALL MODELS. */
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

    /* Function Body */
    lallcz = FALSE_;
/* JVS Allows the last point to be stable. */
    if (lcz[*m] || lcz[*m - 1]) {
/*  SURFACE C.Z. EXISTS.  FIND LOWEST SHELL (IMAX), WHICH IS ALSO THE */
/*  UPPERMOST ZONE CONSIDERED FOR STABILITY AGAINST ROTATIONALLY INDUCED MIXING. */
	for (i__ = *m - 1; i__ >= 1; --i__) {
	    if (! lcz[i__]) {
		goto L81;
	    }
/* L71: */
	}
	lallcz = TRUE_;
	i__ = 0;
L81:
	imax = i__ + 1;
/*  HSTOP IS THE MASS AT THE TOP OF THE C.Z. */
/*  HSBOT IS THE MASS AT THE BOTTOM OF THE C.Z. */
	hstop = hs1[*m];
	if (imax > 1) {
	    hsbot = (hs1[imax] + hs1[imax - 1]) * .5;
	} else {
	    hsbot = 0.;
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
    if (lczsur) {
	if (! lallcz) {
	    if (! rot_1.lrot) {
		hg[imax] = hs1[imax] * exp(const1_1.cln * (const2_1.cgl - hr[
			imax] * 2.));
		hg[imax - 1] = hs1[imax - 1] * exp(const1_1.cln * (
			const2_1.cgl - hr[imax - 1] * 2.));
	    }
/* PINPOINT RCZ */
	    dd2 = del1[imax - 1] - del2[imax - 1];
	    dd1 = del1[imax] - del2[imax];
	    fx = dd2 / (dd2 - dd1);
/* INFER HP */
	    envrcl = hr[imax - 1] + fx * (hr[imax] - hr[imax - 1]);
	    envrc = exp(const1_1.cln * envrcl);
	    ps2 = exp(const1_1.cln * (hp[imax] - hd[imax])) / hg[imax];
	    ps1 = exp(const1_1.cln * (hp[imax - 1] - hd[imax - 1])) / hg[imax 
		    - 1];
	    psca = ps1 + fx * (ps2 - ps1);
	    d__1 = envrc + psca;
	    rtestl = d_lg10(&d__1);
/* FIND V */
	    i__1 = *m;
	    for (k = imax + 1; k <= i__1; ++k) {
		if (hr[k] > rtestl) {
		    fx = (rtestl - hr[k - 1]) / (hr[k] - hr[k - 1]);
		    cvel = svel[k - 1] + fx * (svel[k] - svel[k - 1]);
		    goto L85;
		}
	    }
/* One pressure scale height overshoots edge of interior */
/* calculation. Stitch on the envelope for more room */
	    i__1 = envstruct_1.numenv;
	    for (k = 2; k <= i__1; ++k) {
		if (envstruct_1.envr[k - 1] > rtestl && envstruct_1.evels[k - 
			1] > 0.f) {
		    fx = (rtestl - hr[*m]) / (envstruct_1.envr[k - 1] - hr[*m]
			    );
		    cvel = svel[*m] + fx * (envstruct_1.evels[k - 1] - svel[*
			    m]);
		    goto L85;
		}
	    }
	    cvel = svel[*m];
L85:
/* DEFINE TAUCZ */
	    ovrtrn_1.taucz = psca / cvel;
	} else {
/* INFER HP */
	    if (! rot_1.lrot) {
		hg[1] = hs1[1] * exp(const1_1.cln * (const2_1.cgl - hr[1] * 
			2.));
	    }
	    psca2 = exp(const1_1.cln * (hp[1] - hd[1])) / hg[1];
	    rtest2 = exp(const1_1.cln * hr[1]);
	    if (psca2 <= rtest2) {
/* HP < R AT THE FIRST POINT.  ASSUME V CONSTANT INSIDE AND HP = K/R FOR */
/* SLOWLY VARYING DENSITY AND PRESSURE NEAR THE CENTER. */
		cvel = svel[1];
		d__1 = psca2 * rtest2;
		psca = pow_dd(&d__1, &c_b5);
		ovrtrn_1.taucz = psca / cvel;
	    } else {
		i__1 = *m;
		for (k = 2; k <= i__1; ++k) {
		    psca1 = psca2;
		    rtest1 = rtest2;
		    if (! rot_1.lrot) {
			hg[k] = hs1[k] * exp(const1_1.cln * (const2_1.cgl - 
				hr[k] * 2.));
		    }
		    psca2 = exp(const1_1.cln * (hp[k] - hd[k])) / hg[k];
		    rtest2 = exp(const1_1.cln * hr[k]);
/* FIND LOCATION WHERE HP = R */
		    if (psca2 <= rtest2) {
			fx = (rtest1 - psca1) / (psca2 - rtest2 - (psca1 - 
				rtest1));
/* FIND V */
			cvel = svel[k - 1] + fx * (svel[k] - svel[k - 1]);
			psca = psca1 + fx * (psca2 - psca1);
/* DEFINE TAUCZ */
			ovrtrn_1.taucz = psca / cvel;
			goto L95;
		    }
		}
		k = *m;
		cvel = svel[*m];
		psca = psca2;
		ovrtrn_1.taucz = psca / cvel;
L95:
		;
	    }
	}
    } else {
	ovrtrn_1.taucz = 0.;
    }
/* -------------------------------------------------------------- */
/*                  OPEN(UNIT=100,FILE='diagnostic.out',STATUS='OLD') */
/*                  DO 1505 I=1,M */
/*                  IF (LCZ(I)) HOLD = 1.0 */
/*                  IF (.NOT.LCZ(I)) HOLD = 0.0 */
/*                              WRITE(100,1504), HS2(I), HS1(I), HR(I),HOLD, */
/*     *                  DEL1(I), DEL2(I), SVEL(I), */
/* 1505                  CONTINUE */
/* 1504                  FORMAT(1X,7E16.8) */
/*                  CLOSE(100) */
/* ---------------------------------------------------------------- */
/* END JVS */
    return 0;
} /* tauint_ */

