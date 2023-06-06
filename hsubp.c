/* hsubp.f -- translated by f2c (version 20100827).
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
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal cdh, etadh0, etadh1, zdh[18], xxdh, yydh, zzdh, dhnue[18];
    logical ldh;
} debhu_;

#define debhu_1 debhu_

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     HSUBP */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int hsubp_(doublereal *hcomp, doublereal *hd, doublereal *hp,
	 doublereal *hr, doublereal *hs, doublereal *ht, integer *jedge, 
	doublereal *pscahe)
{
    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal d__, p, t, x, z__, dl, pl, rl, sl, tl, eta, qap, amu, 
	    qcp, qdp, emu, qat, qdt, rmu, dela, beta, qcpp, qcpt, qdtp, qdtt, 
	    beta14, betai;
    static integer ksaha;
    static doublereal pscap;
    static logical latmo;
    static doublereal fxion[3];
    static logical lderiv;
    extern /* Subroutine */ int eqstat_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     logical *, integer *);

/* DBG 7/92 COMMON BLOCK ADDED TO COMPUTE DEBYE-HUCKEL CORRECTION. */
/* *** CALCULATES THE LOCAL PRESSURE SCALE HEIGHT AT THE EDGE OF A */
/*     CONVECTIVE REGION (PD DEC. 1984) 2/91 MHP REVISED FOR YREC/MARK6*** */

/*  CALL EQUATION OF STATE TO DETERMINE THE MEAN MOLECULAR WEIGHT. */
    /* Parameter adjustments */
    --ht;
    --hs;
    --hr;
    --hp;
    --hd;
    hcomp -= 16;

    /* Function Body */
    lderiv = FALSE_;
    latmo = TRUE_;
    ksaha = 0;
    x = hcomp[*jedge * 15 + 1];
    z__ = hcomp[*jedge * 15 + 3];
    pl = hp[*jedge];
    tl = ht[*jedge];
    dl = hd[*jedge];
    if (debhu_1.ldh) {
	debhu_1.xxdh = hcomp[*jedge * 15 + 1];
	debhu_1.yydh = hcomp[*jedge * 15 + 2] + hcomp[*jedge * 15 + 4];
	debhu_1.zzdh = hcomp[*jedge * 15 + 3];
	debhu_1.zdh[0] = hcomp[*jedge * 15 + 5] + hcomp[*jedge * 15 + 6];
	debhu_1.zdh[1] = hcomp[*jedge * 15 + 7] + hcomp[*jedge * 15 + 8];
	debhu_1.zdh[2] = hcomp[*jedge * 15 + 9] + hcomp[*jedge * 15 + 10] + 
		hcomp[*jedge * 15 + 11];
    }
    eqstat_(&tl, &t, &pl, &p, &dl, &d__, &x, &z__, &beta, &betai, &beta14, 
	    fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &dela, &qdtt, &
	    qdtp, &qat, &qap, &qcpt, &qcpp, &lderiv, &latmo, &ksaha);
/*  COMPUTE PRESSURE SCALE HEIGHT. */
    sl = hs[*jedge];
    rl = hr[*jedge];
    pscap = rmu * exp(const1_1.cln * (tl - const2_1.cgl - sl + rl + rl));
    *pscahe = exp(const1_1.cln * (pl + rl * 2. - dl - const2_1.cgl - sl));
    return 0;
} /* hsubp_ */

