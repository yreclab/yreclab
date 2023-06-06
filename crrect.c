/* crrect.f -- translated by f2c (version 20100827).
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
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    logical lscrib, lpshll, lchemo, lconzo, ljout, lprtin, lpenv;
} ccout_;

#define ccout_1 ccout_

struct {
    logical ldebug, lcorr, lmilne, ltrack, lstore, lstpch;
    integer npunch;
} ccout2_;

#define ccout2_1 ccout2_

struct {
    doublereal tridt, tridl, senv0;
    logical lsenv0, lnew0;
} cenv_;

#define cenv_1 cenv_

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
    doublereal htoler[10]	/* was [5][2] */, fcorr0, fcorri, fcorr, 
	    hpttol[12];
    integer niter1, niter2, niter3;
} ctol_;

#define ctol_1 ctol_

struct {
    doublereal atmstp, envstp;
    logical lenvg;
} envgen_;

#define envgen_1 envgen_

struct {
    logical lkuthe;
} heflsh_;

#define heflsh_1 heflsh_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    integer niter4;
    logical lnews, lsnu;
} neweng_;

#define neweng_1 neweng_

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
} oldmod_;

#define oldmod_1 oldmod_

struct {
    doublereal cdh, etadh0, etadh1, zdh[18], xxdh, yydh, zzdh, dhnue[18];
    logical ldh;
} debhu_;

#define debhu_1 debhu_

/* Table of constant values */

static integer c__1 = 1;

/*     JANUARY 28, 1991: */
/*     REPLACED EGEN SO THAT IT FOLLOWS FULL CNO NOT CN IN EQUILIBRIUM AND */
/*     FEBRUARY 11, 1991: */
/*     REPLACED CONVEC SO THAT WOULD CALCULATE OVERSHOOT CORRECTLY. */
/*     ADDED ROUTINES OVERSH AND HSUBP. */


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* CRRECT */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int crrect_(doublereal *delts, integer *m, integer *niter, 
	logical *lfini, logical *large, logical *lnew, logical *lreset, 
	logical *lsbc, doublereal *trit, doublereal *tril, doublereal *cfenv, 
	doublereal *ps, doublereal *ts, doublereal *rs, doublereal *ftri, 
	integer *istore, doublereal *estore, doublereal *hstot, doublereal *
	bl, doublereal *teffl, doublereal *hd, doublereal *hha, doublereal *
	hhb, doublereal *hhc, doublereal *hl, doublereal *hmax, doublereal *
	hp, doublereal *hpp, doublereal *hr, doublereal *hs, doublereal *hs1, 
	doublereal *hs2, doublereal *hsrf, doublereal *ht, doublereal *htt, 
	doublereal *hcomp, logical *lc, integer *nhmax, doublereal *tlumx, 
	logical *latmo, logical *lderiv, logical *lmix, logical *locond, 
	doublereal *qdt, doublereal *qdp, integer *model, doublereal *fp, 
	doublereal *ft, doublereal *eta2, doublereal *omega, doublereal *r0, 
	integer *itdone, doublereal *hg, doublereal *hi, doublereal *hjm, 
	integer *itlvl, logical *lcz, integer *mrzone, integer *mxzone, 
	integer *nrzone, integer *nzone, doublereal *qiw, doublereal *hkerot, 
	doublereal *hkerot0)
{
    /* Format strings */
    static char fmt_20[] = "(\002 R.H.S. BELOW TOLERANCES--P\002,1pe9.2,\002"
	    "  T \002,e9.2,\002  R \002,e9.2,\002  L \002,e9.2)";
    static char fmt_75[] = "(10x,\002MODEL CONVERGED AFTER \002,i4,\002  ITE"
	    "RATIONS\002)";
    static char fmt_60[] = "(1x,\002DEL-L/L  \002,l2,1p2e12.4,5x,i5)";
    static char fmt_70[] = "(\002 CORR\002,i5,\002P\002,1pe9.2,i5,\002T\002,"
	    "e9.2,i5,\002R\002,e9.2,i5,\002L\002,e9.2,\002  F=\002,0pf5.3,"
	    "\002  E-HY\002,1pe10.3,\002 HE\002,e10.3,\002 NU\002,e10.3,\002 G"
	    "\002,e10.3)";
    static char fmt_80[] = "(1x,\002-----CORRECTIONS EXCEEDED TOLERANCES\002)"
	    ;

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2, d__3, d__4;

    /* Builtin functions */
    double d_lg10(doublereal *);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__, j;
    static doublereal x, z__, hj;
    static integer ij;
    static doublereal fpl, ftl;
    extern /* Subroutine */ int mix_(doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     logical *, integer *, doublereal *, doublereal *, doublereal *, 
	    integer *, integer *, integer *, integer *);
    static doublereal thl, fact;
    static integer katm;
    static logical lflp;
    extern /* Subroutine */ int fpft_(doublereal *, doublereal *, doublereal *
	    , integer *, doublereal *, doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *);
    static doublereal plim;
    static integer kenv, jenv, iter;
    static doublereal temp, test, ddage;
    static integer ksaha, jcore;
    static doublereal hlmax, tlumh;
    static integer mxzon0[24]	/* was [12][2] */;
    extern /* Subroutine */ int coefft_(doublereal *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, logical *, doublereal *, logical *, 
	    logical *, logical *, logical *, doublereal *, doublereal *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *), surfbc_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, logical *, logical *, 
	    logical *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, logical *, doublereal *), hsolve_(
	    integer *, doublereal *, doublereal *, doublereal *);
    static doublereal tlumhe;
    extern /* Subroutine */ int getrot_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

    /* Fortran I/O blocks */
    static cilist io___19 = { 0, 0, 0, fmt_20, 0 };
    static cilist io___20 = { 0, 0, 0, fmt_75, 0 };
    static cilist io___27 = { 0, 0, 0, fmt_60, 0 };
    static cilist io___28 = { 0, 0, 0, fmt_70, 0 };
    static cilist io___29 = { 0, 0, 0, fmt_75, 0 };
    static cilist io___30 = { 0, 0, 0, fmt_80, 0 };
    static cilist io___31 = { 0, 0, 0, fmt_80, 0 };


/* INPUTS ASSUMES GIVEN LOG(TE) AS TEFFL */
/*        ASSUMES GIVEN LOG(L/LSUN) AS BL */
/*        DELTS = TIME STEP IN SECONDS */
/*        NITER = ITERATION NUMBER */
/* OUTPUTS  LFINI = .T. IF MODEL HAS CONVERGED */
/*          LARGE = .T. IF CORRECTIONS ARE TOO LARGE */
/* DBG 7/92 COMMON BLOCK ADDED TO COMPUTE DEBYE-HUCKEL CORRECTION. */
/* MHP 10/02 ADDED MISSING DIMENSION STATEMENTS */
    /* Parameter adjustments */
    --hkerot0;
    --hkerot;
    --qiw;
    mxzone -= 13;
    mrzone -= 14;
    --lcz;
    --hjm;
    --hi;
    --hg;
    --r0;
    --omega;
    --eta2;
    --ft;
    --fp;
    --tlumx;
    --nhmax;
    --lc;
    hcomp -= 16;
    --htt;
    --ht;
    --hsrf;
    --hs2;
    --hs1;
    --hs;
    --hr;
    --hpp;
    --hp;
    --hmax;
    --hl;
    --hhc;
    hhb -= 5;
    hha -= 13;
    --hd;
    --estore;
    --rs;
    --ts;
    --ps;
    --cfenv;
    --tril;
    --trit;

    /* Function Body */
    if (*niter <= 0) {
	return 0;
    }
    *bl = d_lg10(&hl[*m]);
/* ZERO COUNTERS */
    kenv = 0;
    katm = 0;
    ksaha = 0;
    comp_1.senv = hs[*m] - *hstot;
    if (*lnew || *lreset && *itlvl == 2) {
	*lsbc = TRUE_;
    }
/*  FIND NEW FP AND FT IF MODEL IS ROTATING */
    if (rot_1.lrot && *lsbc) {
	fpl = fp[*m];
	ftl = ft[*m];
    } else {
	fpl = 1.;
	ftl = 1.;
    }
/* SET UP SURFACE BOUNDARY CONDITIONS-2ND AND 3RD LEVELS OF ITER ONLY */
/* FIND ENVELOPE MASS AND SET X AND Z TO ENVELOPE VALUES */
    if (*lsbc) {
	x = comp_1.xnew;
	z__ = comp_1.znew;
	plim = hp[*m];
	if (debhu_1.ldh) {
	    debhu_1.xxdh = hcomp[*m * 15 + 1];
	    debhu_1.yydh = hcomp[*m * 15 + 2] + hcomp[*m * 15 + 4];
	    debhu_1.zzdh = hcomp[*m * 15 + 3];
	    debhu_1.zdh[0] = hcomp[*m * 15 + 5] + hcomp[*m * 15 + 6];
	    debhu_1.zdh[1] = hcomp[*m * 15 + 7] + hcomp[*m * 15 + 8];
	    debhu_1.zdh[2] = hcomp[*m * 15 + 9] + hcomp[*m * 15 + 10] + hcomp[
		    *m * 15 + 11];
	}
	surfbc_(&trit[1], &tril[1], &cfenv[1], &ps[1], &ts[1], &rs[1], ftri, 
		istore, &estore[1], lnew, lreset, lsbc, &ksaha, &kenv, &katm, 
		hstot, bl, teffl, &x, &z__, &fpl, &ftl, &lflp, &plim);
    }
/* 7/91 ADD CALL TO MIX */
    if (*itlvl > 2 && *delts > 0.) {
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    for (j = 1; j <= 11; ++j) {
		hcomp[j + i__ * 15] = oldmod_1.hcompp[j + i__ * 15 - 16];
/* L1: */
	    }
/* L2: */
	}
	mix_(delts, &hcomp[16], &hd[1], &hl[1], &hp[1], &hr[1], &hs[1], &hs1[
		1], &hs2[1], hstot, &ht[1], itlvl, &lc[1], m, qdt, qdp, &
		ddage, &jcore, &jenv, &mxzone[13], mxzon0);
    }
/*      IF(LROT)THEN */
/*         CALL OVROT(HCOMP,HD,HP,HR,HS,HT,LC,M,LCZ,MRZONE,MXZONE, */
/*     *        NRZONE,NZONE) */
/*      ENDIF */
/*  IF MODEL CONVERGED ON THE PREVIOUS LEVEL OF ITERATION AND */
/*  THE TRIANGLE WAS CHECKED AND NOT FLIPPED,SKIP CORRECTION ROUTINE. */
    if (*lsbc && ! lflp && *lfini) {
	return 0;
    }
    *lfini = FALSE_;
    i__1 = *niter;
    for (iter = 1; iter <= i__1; ++iter) {
/* DO HENYEY REDUCTION */
	hmax[1] = 0.;
	hmax[2] = 0.;
	hmax[3] = 0.;
	hmax[4] = 0.;
	coefft_(delts, m, &hd[1], &hha[13], &hhb[5], &hhc[1], &hl[1], &hmax[1]
		, &hp[1], &hpp[1], &hr[1], &hs[1], &hs1[1], &hs2[1], &ht[1], &
		htt[1], &hcomp[16], &lc[1], &tlumx[1], latmo, lderiv, lmix, 
		locond, qdt, qdp, &ksaha, model, &fp[1], &ft[1], &hkerot[1], &
		hkerot0[1], &jenv);
/* RENORMALIZE TLUMX-S */
/* CC   TAKE OUT RENORMALIZATION DURING HE FLASH (NON-THERMAL EQUALIBRIUM) */
	thl = tlumx[1] + tlumx[2] + tlumx[3] + tlumx[4] + tlumx[5] + tlumx[6] 
		+ tlumx[7] + tlumx[8];
	if (! heflsh_1.lkuthe && thl > 0.) {
	    temp = hl[*m] / thl;
	    for (j = 1; j <= 8; ++j) {
		tlumx[j] *= temp;
/* L10: */
	    }
	}
/* CHECK ON SIGNIFICANCE OF R.H.S. EQUATIONS FOR P AND T */
/* N.B.  DOES NOT CHECK DIFFERENCES IN BOUNDARY EQUATIONS */
	if (iter > 1) {
	    if (hmax[1] <= ctol_1.htoler[4] && hmax[2] <= ctol_1.htoler[9] && 
		    hmax[3] <= ctol_1.htoler[4] && hmax[4] <= ctol_1.htoler[9]
		    ) {
		io___19.ciunit = luout_1.ishort;
		s_wsfe(&io___19);
		for (j = 1; j <= 4; ++j) {
		    do_fio(&c__1, (char *)&hmax[j], (ftnlen)sizeof(doublereal)
			    );
		}
		e_wsfe();
		io___20.ciunit = luout_1.ishort;
		s_wsfe(&io___20);
		i__2 = *itdone + 1;
		do_fio(&c__1, (char *)&i__2, (ftnlen)sizeof(integer));
		e_wsfe();
		*lfini = TRUE_;
		return 0;
	    }
	}
/* SET UP HENYEY COEFFICIENTS FOR SURFACE */
	hsrf[1] = -cfenv[1];
	hsrf[2] = -cfenv[2];
	hsrf[3] = cfenv[1] * hp[*m] + cfenv[2] * ht[*m] + cfenv[3] - hr[*m];
	temp = const1_1.cln * hl[*m];
	hsrf[4] = -temp * cfenv[4];
	hsrf[5] = -temp * cfenv[5];
	hsrf[6] = temp * (cfenv[4] * hp[*m] + cfenv[5] * ht[*m] + cfenv[6] - *
		bl);
/* DO BACK SOLUTION FOR CORRECTIONS */
	hsolve_(m, &hha[13], &hhb[5], &hsrf[1]);
/* CHECK ON MAXIMUM CORRECTIONS */
	for (j = 1; j <= 4; ++j) {
	    hmax[j] = (d__1 = hhb[j + 4], abs(d__1));
	    nhmax[j] = 1;
/* L30: */
	}
	i__2 = *m;
	for (i__ = 2; i__ <= i__2; ++i__) {
	    test = (d__1 = hhb[(i__ << 2) + 1], abs(d__1));
	    if (hmax[1] <= test) {
		hmax[1] = test;
		nhmax[1] = i__;
	    }
	    test = (d__1 = hhb[(i__ << 2) + 2], abs(d__1));
	    if (hmax[2] <= test) {
		hmax[2] = test;
		nhmax[2] = i__;
	    }
	    test = (d__1 = hhb[(i__ << 2) + 3], abs(d__1));
	    if (hmax[3] <= test) {
		hmax[3] = test;
		nhmax[3] = i__;
	    }
/* Computing MIN */
	    d__3 = (d__1 = hhb[(i__ << 2) + 4], abs(d__1)), d__4 = (d__2 = 
		    hhb[(i__ << 2) + 4] / hl[i__], abs(d__2));
	    test = min(d__3,d__4);
	    if (hmax[4] <= test) {
		hmax[4] = test;
		nhmax[4] = i__;
	    }
/* L40: */
	}
/* CC   HE FLASH -- OK FOR ALL */
	hlmax = hmax[4];
/* LFINI = T IF MAX CORRECTIONS LESS THAN CONVERGENCE CRITERIA SET IN */
/* HTOLER. LARGE = T IF MAX CORRECTIONS GREATER THAN LARGEST CORRECTIONS */
/* ALLOWED, ALSO SET IN HTOLER */
	*lfini = hmax[1] < ctol_1.htoler[0] && hmax[2] < ctol_1.htoler[1] && 
		hmax[3] < ctol_1.htoler[2] && hmax[4] < ctol_1.htoler[3];
	*large = hmax[1] > ctol_1.htoler[5] || hmax[2] > ctol_1.htoler[6] || 
		hmax[3] > ctol_1.htoler[7] || hmax[4] > ctol_1.htoler[8];
	for (j = 1; j <= 4; ++j) {
	    ij = nhmax[j];
	    hmax[j] = hhb[j + (ij << 2)];
/* L50: */
	}
	if (ctol_1.fcorr0 > 0.) {
/* Computing MIN */
	    d__1 = 1., d__2 = ctol_1.fcorr + ctol_1.fcorri;
	    ctol_1.fcorr = min(d__1,d__2);
	}
/* HE FLASH CHANGE */
	fact = ctol_1.fcorr;
	if (heflsh_1.lkuthe) {
	    if (hlmax <= .5) {
		fact = .8;
	    }
	    if (hlmax <= .005) {
		fact = 1.;
	    }
	}
	tlumh = tlumx[1] + tlumx[2] + tlumx[3] + tlumx[4];
	tlumhe = tlumx[5] + tlumx[8];
	if (ccout2_1.lcorr) {
	    io___27.ciunit = luout_1.ishort;
	    s_wsfe(&io___27);
	    do_fio(&c__1, (char *)&(*lfini), (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&hmax[4], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ctol_1.htoler[3], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&nhmax[4], (ftnlen)sizeof(integer));
	    e_wsfe();
	    io___28.ciunit = luout_1.ishort;
	    s_wsfe(&io___28);
	    for (j = 1; j <= 4; ++j) {
		do_fio(&c__1, (char *)&nhmax[j], (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&hmax[j], (ftnlen)sizeof(doublereal));
	    }
	    do_fio(&c__1, (char *)&fact, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&tlumh, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&tlumhe, (ftnlen)sizeof(doublereal));
	    for (j = 6; j <= 7; ++j) {
		do_fio(&c__1, (char *)&tlumx[j], (ftnlen)sizeof(doublereal));
	    }
	    e_wsfe();
	    if (*lfini) {
		io___29.ciunit = luout_1.ishort;
		s_wsfe(&io___29);
		i__2 = *itdone + 1;
		do_fio(&c__1, (char *)&i__2, (ftnlen)sizeof(integer));
		e_wsfe();
	    }
	}
	if (*large) {
	    io___30.ciunit = luout_1.iowr;
	    s_wsfe(&io___30);
	    e_wsfe();
	    io___31.ciunit = luout_1.ishort;
	    s_wsfe(&io___31);
	    e_wsfe();
	    return 0;
	}
/* APPLY CORRECTIONS */
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    temp = fact * hhb[(i__ << 2) + 1];
	    hp[i__] += temp;
	    hpp[i__] += temp;
	    temp = fact * hhb[(i__ << 2) + 2];
	    ht[i__] += temp;
	    htt[i__] += temp;
	    hr[i__] += fact * hhb[(i__ << 2) + 3];
	    hl[i__] += fact * hhb[(i__ << 2) + 4];
/* L90: */
	}
	*bl = d_lg10(&hl[*m]);
	*teffl = cfenv[7] * hp[*m] + cfenv[8] * ht[*m] + cfenv[9];
	if (rot_1.lrot) {
	    getrot_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &lcz[1], m, &
		    eta2[1], &hi[1], &omega[1], &qiw[1], &r0[1]);
	    fpft_(&hd[1], &hr[1], &hs[1], m, &omega[1], &eta2[1], &fp[1], &ft[
		    1], &hg[1], &r0[1]);
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		hj = hjm[i__] * hs2[i__];
		hkerot[i__] = omega[i__] * .5 * hj;
	    }
	}
	++(*itdone);
	if (*lfini) {
	    return 0;
	}
/* L100: */
    }
    return 0;
} /* crrect_ */

