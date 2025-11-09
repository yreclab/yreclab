/* getnewenv.f -- translated by f2c (version 20061008).
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
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    doublereal ep, et, er, es, ed, eo, ebeta, edel[3], efxion[3], evel;
} envprt_;

#define envprt_1 envprt_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    doublereal htoler[10]	/* was [5][2] */, fcorr0, fcorri, fcorr, 
	    hpttol[12];
    integer niter1, niter2, niter3;
} ctol_;

#define ctol_1 ctol_

struct {
    doublereal cdh, etadh0, etadh1, zdh[18], xxdh, yydh, zzdh, dhnue[18];
    logical ldh;
} debhu_;

#define debhu_1 debhu_

struct {
    doublereal enverr, envbeg, envmin, envmax;
} intenv_;

#define intenv_1 intenv_

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
    doublereal spotf, spotx;
    logical lsdepth;
} spots_;

#define spots_1 spots_

/* Table of constant values */

static doublereal c_b2 = 4.;
static doublereal c_b7 = 10.;
static integer c__1 = 1;

/* $$$$$$ */
/* MHP 07/02 NEW SUBROUTINE TO MOVE THE OUTER FITTING POINT WHEN */
/* THE TOTAL MASS IS BEING DECREASED; ADD NEW POINTS BY DROPPING */
/* A SINKLINE FROM THE SURFACE DOWN AND INCLUDING NEW POINTS UP TO */
/* THE DESIRED ENVELOPE MASS */
/* Subroutine */ int getnewenv_(doublereal *senvold, doublereal *hcomp, 
	doublereal *hd, doublereal *hl, doublereal *hp, doublereal *hr, 
	doublereal *hs, doublereal *hs1, doublereal *hs2, doublereal *hstot, 
	doublereal *ht, logical *lc, doublereal *eta2, doublereal *hi, 
	doublereal *hjm, doublereal *qiw, doublereal *r0, doublereal *hkerot, 
	doublereal *bl, doublereal *sjtot, doublereal *skerot, doublereal *
	teffl, integer *m, logical *lnew)
{
    /* Format strings */
    static char fmt_910[] = "(1x,\002NEW INTERIOR POINTS FROM CHANGE IN ENVE"
	    "LOPE MASS\002/\002 J,LOG RHO, LOG L, LOG P, LOG R, LOG M, LOG T,"
	    " CONV T/F\002)";
    static char fmt_911[] = "(i5,1p6e16.8,l2)";
    static char fmt_597[] = "(5x,\002***** NEW ENVELOPE MASS CALCULATED **"
	    "***\002/8x,\002OLD SENV \002,1pe22.13,\002  NEW SENV\002,e22.13)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), pow_dd(doublereal *, doublereal *), d_lg10(
	    doublereal *);
    /* Subroutine */ void s_stop(char *, ftnlen);
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);

    /* Local variables */
    static doublereal b;
    static integer i__, j, k;
    static doublereal x, z__, w0, x0, x1, x2, dd, hj, gl;
    static integer mm;
    static doublereal rl, dp, dt, dr;
    static integer jm;
    static doublereal fx, fpl, ftl;
    static integer ixx;
    static doublereal dum1[4], dum2[3], dum3[3], dum4[3];
    static integer jend, katm, idum;
    static doublereal plim;
    static integer kenv;
    static doublereal ebeg0;
    static logical lprt;
    static doublereal test, sumj;
    static logical lsbc0;
    static doublereal emin0, emax0, senv1, test2;
    static integer ksaha;
    static doublereal omega[5000], sumke, ateffl, hsbase;
    extern /* Subroutine */ int envint_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, logical *, 
	    logical *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, logical *);
    static integer numnew;
    extern /* Subroutine */ int getrot_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static logical lpulpt;

    /* Fortran I/O blocks */
    static cilist io___49 = { 0, 6, 0, fmt_910, 0 };
    static cilist io___50 = { 0, 6, 0, fmt_911, 0 };
    static cilist io___51 = { 0, 6, 0, fmt_597, 0 };


/*      *                     HSTOT,HT,LC,ETA2,HG,HI,HJM,QIW,R0,  ! KC 2025-05-31 */
/* SENV IS THE DIFFERENCE IN MASS BETWEEN THE TOTAL AND THE LAST MODEL */
/* POINT.  IT IS SET TO A DIFFERENT VALUE IN THIS ROUTINE. */
/* PHYSICAL CONSTANTS. */
/* EXTENDED COMPOSITION FLAG */
/* LROT NEEDED TO KNOW IF YOU HAVE TO COMPUTE ROTATION TERMS. */
/* HPTTOL USED TO SET THE SPATIAL RESOLUTION OF THE ENVELOPE INTEGRATION */
/* TERMS NEEDED TO COMPUTE THE DEBYE-HUCKEL CORRECTION IN THE E.O.S. */
/* TOLERANCES FOR THE ENVELOPE INTEGRATION; TEMPORARILY ASSIGN NEW */
/* VALUES FOR THE INTEGRATION TO FIND THE NEW POINTS AND THEN RESET. */
/* STORED CONTENTS OF THE ENVELOPE INTEGRATION. */
/* KC 2025-05-30 reordered common block elements */
/* JvS 08/25 Updated with new elements */
/*      * HKEROT(JSON),HG(JSON),DUM1(4),DUM2(3),DUM3(3),DUM4(3)  ! KC 2025-05-31 */
/* G Somers 10/14, Add spot common block */
/* G Somers END */
    /* Parameter adjustments */
    --hkerot;
    --r0;
    --qiw;
    --hjm;
    --hi;
    --eta2;
    --lc;
    --ht;
    --hs2;
    --hs1;
    --hs;
    --hr;
    --hp;
    --hl;
    --hd;
    hcomp -= 16;

    /* Function Body */
    if (flag_1.lexcom) {
	jend = 15;
    } else {
	jend = 11;
    }
/* RESTRICT THE ENVELOPE MASS TO A MINIMUM OF 10**-12. */
    *senvold = min(*senvold,-1e-12);
/* SAVE CURRENT VALUES OF THE TOTAL NUMBER OF POINTS AND ENVELOPE MASS. */
    mm = *m;
    senv1 = comp_1.senv;
/* SET NUMERICAL PARAMETERS OF THE ENVELOPE INTEGRATION */
    emax0 = intenv_1.envmax;
    emin0 = intenv_1.envmin;
    ebeg0 = intenv_1.envbeg;
    intenv_1.envmax = ctol_1.hpttol[7];
    intenv_1.envmin = ctol_1.hpttol[7];
    intenv_1.envbeg = ctol_1.hpttol[7];
    lsbc0 = FALSE_;
    lprt = TRUE_;
    katm = 0;
    kenv = 0;
    ksaha = 0;
/* SET THE PHYSICAL PROPERTIES OF THE ENVELOPE SOLUTION */
/* LUMINOSITY */
    b = exp(const1_1.cln * *bl);
/* RADIUS */
    rl = (*bl + const_1.clsunl - *teffl * 4. - const1_1.c4pil - 
	    const2_1.csigl) * .5;
/* SURFACE GRAVITY */
    gl = const2_1.cgl + comp_1.stotal - rl - rl;
/* COMPOSITION */
    x = hcomp[*m * 15 + 1];
    z__ = hcomp[*m * 15 + 3];
/* NEGLECT ROTATIONAL DISTORTION */
    fpl = 1.;
    ftl = 1.;
/* PREVENT THE INTEGRATION FROM SHOOTING PAST THE */
/* PRESSURE OF THE OUTER MODEL POINT, AT LEAST THE */
/* FIRST TIME IT TRIES TO DO SO. */
    plim = hp[*m];
/* DO NOT DO SOLAR PULSATION OUTPUT */
    lpulpt = FALSE_;
/* SET UP VALUES FOR THE EQUATION OF STATE CALCULATION */
    ixx = 0;
    if (debhu_1.ldh) {
	debhu_1.xxdh = hcomp[*m * 15 + 1];
	debhu_1.yydh = hcomp[*m * 15 + 2] + hcomp[*m * 15 + 4];
	debhu_1.zzdh = hcomp[*m * 15 + 3];
	debhu_1.zdh[0] = hcomp[*m * 15 + 5] + hcomp[*m * 15 + 6];
	debhu_1.zdh[1] = hcomp[*m * 15 + 7] + hcomp[*m * 15 + 8];
	debhu_1.zdh[2] = hcomp[*m * 15 + 9] + hcomp[*m * 15 + 10] + hcomp[*m *
		 15 + 11];
    }
/* INTEGRATE DOWN TO THE CURRENT FITTING POINT USING THE SURFACE L AND TEFF. */
/* MHP 10/02  define ISTORE - used in ENVINT */
    idum = 0;
/* G Somers 10/14, FOR SPOTTED RUNS, FIND THE */
/* PRESSURE AT THE AMBIENT TEMPERATURE ATEFFL */
    if (lc[*m] && spots_1.spotf != 0.f && spots_1.spotx != 1.f) {
	d__1 = spots_1.spotf * pow_dd(&spots_1.spotx, &c_b2) + 1.f - 
		spots_1.spotf;
	ateffl = *teffl - d_lg10(&d__1) * .25f;
    } else {
	ateffl = *teffl;
    }
    envint_(&b, &fpl, &ftl, &gl, hstot, &ixx, &lprt, &lsbc0, &plim, &rl, &
	    ateffl, &x, &z__, dum1, &idum, &katm, &kenv, &ksaha, dum2, dum3, 
	    dum4, &lpulpt);
/* G Somers END */
/* RESET THE NUMERICAL PARAMETERS FOR THE ENVELOPE INTEGRATION */
    intenv_1.envmax = emax0;
    intenv_1.envmin = emin0;
    intenv_1.envbeg = ebeg0;
    comp_1.senv = *senvold;
/* STOP IF THE DESIRED NUMBER OF POINTS EXCEEDS THE ARRAY DIMENSIONS */
    if (*m + envstruct_1.numenv >= 5000) {
	s_stop("9999", (ftnlen)4);
    }
/* THE FIRST POINT IN THE ENVELOPE SOLUTION IS THE SET OF PROPERTIES */
/* OBTAINED AT A MASS EQUAL TO THE LAST INTERIOR POINT.  USE THIS TO */
/* ENFORCE CONSISTENCY WITH THE INTERIOR SOLUTION; */
/* ADJUST THE (P, RHO, T, R) POINTS TO BE CONSISTENT */
/* WITH THE LAST MODEL POINT AND SHIFT ALL OF THE POINTS DOWN BY ONE. */
    dp = hp[*m] - envstruct_1.envp[0];
    dd = hd[*m] - envstruct_1.envd[0];
    dt = ht[*m] - envstruct_1.envt[0];
    dr = hr[*m] - envstruct_1.envr[0];
    test = hs[*m];
    numnew = 0;
    i__1 = envstruct_1.numenv - 1;
    for (j = 1; j <= i__1; ++j) {
	test2 = comp_1.stotal + envstruct_1.envs[j];
	if (test2 - test > 1e-10) {
	    envstruct_1.envd[j - 1] = envstruct_1.envd[j] + dd;
	    envstruct_1.envp[j - 1] = envstruct_1.envp[j] + dp;
	    envstruct_1.envr[j - 1] = envstruct_1.envr[j] + dr;
	    envstruct_1.envs[j - 1] = envstruct_1.envs[j];
	    envstruct_1.envt[j - 1] = envstruct_1.envt[j] + dt;
	    envstruct_1.envx[j - 1] = envstruct_1.envx[j];
	    envstruct_1.envz[j - 1] = envstruct_1.envz[j];
	    test = test2;
	    ++numnew;
	}
    }
    envstruct_1.numenv = numnew;
/* ASSIGN NEW POINTS */
    i__1 = *m + envstruct_1.numenv;
    for (j = *m + 1; j <= i__1; ++j) {
	jm = j - *m;
/* LUMINOSITY ASSUMED CONSTANT */
	hl[j] = hl[*m];
/* INCLUDE NEW POINTS UP TO THE DIFFERENT DESIRED FITTING POINT */
	if (envstruct_1.envs[jm - 1] < comp_1.senv) {
	    hd[j] = envstruct_1.envd[jm - 1];
	    hp[j] = envstruct_1.envp[jm - 1];
	    hr[j] = envstruct_1.envr[jm - 1];
	    hs[j] = envstruct_1.envs[jm - 1] + comp_1.stotal;
	    ht[j] = envstruct_1.envt[jm - 1];
	    hcomp[j * 15 + 1] = envstruct_1.envx[jm - 1];
	    hcomp[j * 15 + 3] = envstruct_1.envz[jm - 1];
	    i__2 = jend;
	    for (k = 4; k <= i__2; ++k) {
		hcomp[k + j * 15] = hcomp[k + *m * 15];
	    }
	    hcomp[j * 15 + 2] = 1. - hcomp[j * 15 + 1] - hcomp[j * 15 + 3] - 
		    hcomp[j * 15 + 4];
	    lc[j] = envstruct_1.lcenv[jm - 1];
	} else {
/* POINTS BEYOND THIS ARE ABOVE THE NEW DESIRED FITTING POINT; */
/* INTERPOLATE LINEARLY, SET NEW NUMBER OF TOTAL POINTS, AND EXIT */
	    if (jm == 1) {
/* INTERPOLATE BETWEEN THE LAST INTERIOR POINT AND THE FIRST ENVELOPE POINT */
		x0 = hs[*m];
		x1 = comp_1.stotal + comp_1.senv;
		x2 = envstruct_1.envs[jm - 1] + comp_1.stotal;
		if (x2 - x0 < 1e-14) {
		    s_stop("9998", (ftnlen)4);
		}
		fx = (x1 - x0) / (x2 - x0);
		hd[j] = hd[*m] + fx * (envstruct_1.envd[jm - 1] - hd[*m]);
		hp[j] = hp[*m] + fx * (envstruct_1.envp[jm - 1] - hp[*m]);
		hr[j] = hr[*m] + fx * (envstruct_1.envr[jm - 1] - hr[*m]);
		hs[j] = x1;
		ht[j] = ht[*m] + fx * (envstruct_1.envt[jm - 1] - ht[*m]);
		hcomp[j * 15 + 1] = hcomp[*m * 15 + 1] + fx * (hcomp[*m * 15 
			+ 1] - envstruct_1.envx[jm - 1]);
		hcomp[j * 15 + 3] = hcomp[*m * 15 + 3] + fx * (hcomp[*m * 15 
			+ 3] - envstruct_1.envz[jm - 1]);
		i__2 = jend;
		for (k = 4; k <= i__2; ++k) {
		    hcomp[k + j * 15] = hcomp[k + *m * 15];
		}
		hcomp[j * 15 + 2] = 1. - hcomp[j * 15 + 1] - hcomp[j * 15 + 3]
			 - hcomp[j * 15 + 4];
		if (envstruct_1.lcenv[jm - 1] || lc[*m]) {
		    lc[j] = TRUE_;
		} else {
		    lc[j] = FALSE_;
		}
	    } else {
/* INTERPOLATE BETWEEN THE LAST 2 ENVELOPE POINTS */
		x0 = envstruct_1.envs[jm - 2] + comp_1.stotal;
		x1 = comp_1.stotal + comp_1.senv;
		x2 = envstruct_1.envs[jm - 1] + comp_1.stotal;
		if (x2 - x0 < 1e-14) {
		    s_stop("9998", (ftnlen)4);
		}
		fx = (x1 - x0) / (x2 - x0);
		hd[j] = envstruct_1.envd[jm - 2] + fx * (envstruct_1.envd[jm 
			- 1] - envstruct_1.envd[jm - 2]);
		hp[j] = envstruct_1.envp[jm - 2] + fx * (envstruct_1.envp[jm 
			- 1] - envstruct_1.envp[jm - 2]);
		hr[j] = envstruct_1.envr[jm - 2] + fx * (envstruct_1.envr[jm 
			- 1] - envstruct_1.envr[jm - 2]);
		hs[j] = x1;
		ht[j] = envstruct_1.envt[jm - 2] + fx * (envstruct_1.envt[jm 
			- 1] - envstruct_1.envt[jm - 2]);
		hcomp[j * 15 + 1] = envstruct_1.envx[jm - 2] + fx * (
			envstruct_1.envx[jm - 1] - envstruct_1.envx[jm - 2]);
		hcomp[j * 15 + 3] = envstruct_1.envz[jm - 2] + fx * (
			envstruct_1.envz[jm - 1] - envstruct_1.envz[jm - 2]);
		i__2 = jend;
		for (k = 4; k <= i__2; ++k) {
		    hcomp[k + j * 15] = hcomp[k + *m * 15];
		}
		hcomp[j * 15 + 2] = 1. - hcomp[j * 15 + 1] - hcomp[j * 15 + 3]
			 - hcomp[j * 15 + 4];
		if (envstruct_1.lcenv[jm - 1] || envstruct_1.lcenv[jm - 2]) {
		    lc[j] = TRUE_;
		} else {
		    lc[j] = FALSE_;
		}
	    }
	    *m = j;
	    goto L587;
	}
    }
/* ASSIGN THE BOUNDARY AT THE PHOTOSPHERE FOR ENVELOPE MASS BELOW 1.0D-12. */
    *m += envstruct_1.numenv;
L587:
/* ADD THE UNLOGGED MASSES OF THE NEW SHELLS (HS1) AND COMPUTE THE */
/* MASS CONTENTS OF THE NEW SHELLS (HS2). */
    i__1 = *m;
    for (j = mm; j <= i__1; ++j) {
	hs1[j] = pow_dd(&c_b7, &hs[j]);
    }
    i__1 = *m - 1;
    for (j = mm; j <= i__1; ++j) {
	hs2[j] = (hs1[j + 1] - hs1[j - 1]) * .5;
    }
    hsbase = (hs1[*m] + hs1[*m - 1]) * .5;
    hs2[*m] = pow_dd(&c_b7, hstot) - hsbase;
/* RECOMPUTE TERMS RELATED TO ROTATION. */
    if (rot_1.lrot) {
/* FIRST GUESS AT THE ROTATION RATES; ASSIGN A */
/* VECTOR OF OMEGA SUCH THAT */
/* OMEGA*R**WALPCZ = CONSTANT. */
	if (rot_1.walpcz <= -2.) {
/* CONSTANT J/M */
	    i__1 = *m;
	    for (j = mm + 1; j <= i__1; ++j) {
		hjm[j] = hjm[mm];
		d__1 = hr[j] * 2.;
		hi[j] = const1_1.cc23 * pow_dd(&c_b7, &d__1);
		omega[j - 1] = hjm[j] / hi[j];
	    }
	} else if (rot_1.walpcz >= 0.) {
/* SOLID BODY ROTATION */
	    i__1 = *m;
	    for (j = mm + 1; j <= i__1; ++j) {
		omega[j - 1] = omega[mm - 1];
		d__1 = hr[j] * 2.;
		hi[j] = const1_1.cc23 * pow_dd(&c_b7, &d__1);
		hjm[j] = omega[mm - 1] * hi[j];
	    }
	} else {
/* GENERAL CASE */
	    d__1 = hr[mm] * rot_1.walpcz;
	    w0 = omega[mm - 1] * pow_dd(&c_b7, &d__1);
	    i__1 = *m;
	    for (j = mm + 1; j <= i__1; ++j) {
		d__1 = hr[j] * rot_1.walpcz;
		omega[j - 1] = w0 / pow_dd(&c_b7, &d__1);
		d__1 = hr[j] * 2.;
		hi[j] = const1_1.cc23 * pow_dd(&c_b7, &d__1);
		hjm[j] = omega[j - 1] * hi[j];
	    }
	}
	getrot_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &lc[1], m, &eta2[1],
		 &hi[1], omega, &qiw[1], &r0[1]);
/* GIVEN OMEGA AND I, FIND ANGULAR MOMENTUM AND ROTATIONAL K.E. */
	sumj = 0.;
	sumke = 0.;
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* MHP 10/02 logic reversed! */
/*          HJM(I) = HJ/HS2(I) */
	    hj = hjm[i__] * hs2[i__];
	    hkerot[i__] = omega[i__ - 1] * .5 * hj;
	    sumj += hj;
	    sumke += hkerot[i__];
/* L550: */
	}
	*sjtot = sumj;
	*skerot = sumke;
    }
    s_wsfe(&io___49);
    e_wsfe();
    s_wsfe(&io___50);
    i__1 = *m;
    for (j = mm; j <= i__1; ++j) {
	do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hd[j], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hl[j], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hp[j], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hr[j], (ftnlen)sizeof(doublereal));
	d__1 = hs[j] - comp_1.stotal;
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ht[j], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&lc[j], (ftnlen)sizeof(logical));
    }
    e_wsfe();
    *lnew = TRUE_;
    s_wsfe(&io___51);
    do_fio(&c__1, (char *)&senv1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&comp_1.senv, (ftnlen)sizeof(doublereal));
    e_wsfe();
    return 0;
} /* getnewenv_ */

