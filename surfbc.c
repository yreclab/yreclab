/* surfbc.f -- translated by f2c (version 20100827).
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
    integer npenv, nprt1, nprt2, nprtpt, npoint;
} ccout1_;

#define ccout1_1 ccout1_

struct {
    doublereal tridt, tridl, senv0;
    logical lsenv0, lnew0;
} cenv_;

#define cenv_1 cenv_

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
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal al_tefflmin__, al_tefflmax__;
} alatm05_;

#define alatm05_1 alatm05_

struct {
    doublereal hras;
    integer kttau;
} atmos_;

#define atmos_1 atmos_

/* Table of constant values */

static integer c__1 = 1;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* SURFBC */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int surfbc_(doublereal *trit, doublereal *tril, doublereal *
	cfenv, doublereal *ps, doublereal *ts, doublereal *rs, doublereal *
	ftri, integer *istore, doublereal *estore, logical *lnew, logical *
	lreset, logical *lsbc, integer *ksaha, integer *kenv, integer *katm, 
	doublereal *hstot, doublereal *bl, doublereal *teffl, doublereal *x, 
	doublereal *z__, doublereal *fpl, doublereal *ftl, logical *lflp, 
	doublereal *plim)
{
    /* Initialized data */

    static integer numenv = 0;

    /* Format strings */
    static char fmt_5[] = "(\002LOG TEFF OF \002,f7.3,\002 ABOVE 3.95 - SWIT"
	    "CH\002,\002TO GRAY ATMOSPHERE BOUNDARY CONDITION\002)";
    static char fmt_7[] = "(\002LOG TEFF OF \002,f7.3,\002 ABOVE Allard Tabl"
	    "e max \002,f7.3,\002  - SWITCH TO GRAY ATMOSPHERE BOUNDARY CONDI"
	    "TION\002)";
    static char fmt_30[] = "(/,\002 NEW ENVELOPE NO.\002,i2,\002 LOG(TE) "
	    "=\002,f9.5,\002  LOG(L) =\002,f8.5)";
    static char fmt_50[] = "(\002 ENVELOPE TRIANGLE  LOG(TE)  LOG(L)   LOG(P"
	    ")   LOG(T)\002,3x,\002LOG(R)   COEFFICIENTS\002/i14,l1,2x,5f9.5,"
	    "8x,\002LOG(R)\002,3f10.5/i14,l1,2x,5f9.5,5x,\002LOG(L/L0)\002,3f"
	    "10.5/i14,l1,2x,5f9.5,7x,\002LOG(TE)\002,3f10.5)";
    static char fmt_70[] = "(\002 ENVELOPE TRIANGLE NOT CHANGED\002)";

    /* Builtin functions */
    integer s_wsle(cilist *), e_wsle(void), s_wsfe(cilist *), do_fio(integer *
	    , char *, ftnlen), e_wsfe(void);
    double exp(doublereal);

    /* Local variables */
    static doublereal b;
    static integer i__, j, i1, i2, i3;
    static doublereal gl, rl;
    static integer ixx;
    static doublereal temp;
    static logical ltri[3], lsbc0;
    static doublereal temp1, temp2;
    static logical lrenv;
    static doublereal trierr;
    extern /* Subroutine */ int envint_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, logical *, 
	    logical *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, logical *);
    static logical lpulpt;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 6, 0, 0, 0 };
    static cilist io___3 = { 0, 6, 0, fmt_5, 0 };
    static cilist io___4 = { 0, 6, 0, 0, 0 };
    static cilist io___5 = { 0, 6, 0, 0, 0 };
    static cilist io___6 = { 0, 6, 0, fmt_7, 0 };
    static cilist io___7 = { 0, 6, 0, 0, 0 };
    static cilist io___19 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___20 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___26 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___28 = { 0, 0, 0, fmt_70, 0 };


/* INPUTS   LNEW = .T.    START UP WITH 3 NEW ENVELOPES ABOUT(TEFFL,BL) */
/* INPUTS   LRESET = .T.  REDO ALL 3 ENVELOPES AND RETRIANGULATE IF NEED */
/* BOTH LNEW AND LRESET ARE RESET TO .FALSE. */
/* MHP 9/01 ADDED COMMON BLOCK */
/* NEEDED TO SWITCH TO GRAY ATMOSPHERE FROM KURUCZ/AH ABOVE LOG */
/* TEFF = 3.95 */
    /* Parameter adjustments */
    --estore;
    --rs;
    --ts;
    --ps;
    --cfenv;
    --tril;
    --trit;

    /* Function Body */
/* MHP 9/01 */
    if (atmos_1.kttau == 3) {
	if (*teffl >= 3.95) {
	    s_wsle(&io___2);
	    e_wsle();
	    s_wsfe(&io___3);
	    do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	    e_wsfe();
	    s_wsle(&io___4);
	    e_wsle();
	    atmos_1.kttau = 0;
	    *lnew = TRUE_;
	}
    }
    if (atmos_1.kttau == 4) {
	if (*teffl >= alatm05_1.al_tefflmax__) {
	    s_wsle(&io___5);
	    e_wsle();
	    s_wsfe(&io___6);
	    do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&alatm05_1.al_tefflmax__, (ftnlen)sizeof(
		    doublereal));
	    e_wsfe();
	    s_wsle(&io___7);
	    e_wsle();
	    atmos_1.kttau = 0;
	    *lnew = TRUE_;
	}
    }
    *lflp = FALSE_;
/* IF LNEW0, REDO ALL 3 ENVELOPES EVERY MODEL */
    if (*lnew || *lreset) {
/* REDO ALL THREE ENVELOPES */
	ltri[0] = FALSE_;
	ltri[1] = FALSE_;
	ltri[2] = FALSE_;
	*istore = 0;
	trierr = 0.;
	*lreset = FALSE_;
    } else {
	ltri[0] = TRUE_;
	ltri[1] = TRUE_;
	ltri[2] = TRUE_;
	trierr = 0.;
    }
    if (*lnew) {
/* STARTING PROCEDURE */
	*ftri = 1.;
	trit[3] = *teffl;
	trit[1] = trit[3] - cenv_1.tridt * .5;
	trit[2] = trit[1] + cenv_1.tridt;
	tril[3] = *bl + cenv_1.tridl * .5;
	tril[1] = tril[3] - cenv_1.tridl;
	tril[2] = tril[1];
	*lnew = FALSE_;
    } else {
/* CHECK TRIANGULATION OF POINT (TEFFL,BL) */
L10:
	for (i1 = 1; i1 <= 3; ++i1) {
	    i2 = i1 % 3 + 1;
	    i3 = i2 % 3 + 1;
	    temp = *ftri * ((tril[i2] - tril[i3]) * (*teffl - trit[i2]) + (
		    trit[i3] - trit[i2]) * (*bl - tril[i2]));
	    if (temp < -trierr) {
		*ftri = -(*ftri);
		trit[i1] = trit[i2] + trit[i3] - trit[i1];
		tril[i1] = tril[i2] + tril[i3] - tril[i1];
		ltri[i1 - 1] = FALSE_;
		trierr = 0.;
		goto L10;
	    }
/* L20: */
	}
    }
/* COMPUTE NEW ENVELOPES IF NECESSARY */
    lrenv = FALSE_;
    for (i__ = 1; i__ <= 3; ++i__) {
	if (! ltri[i__ - 1]) {
/* NEW ENVELOPE NEEDED */
	    *lflp = TRUE_;
	    *teffl = trit[i__];
	    b = exp(const1_1.cln * tril[i__]);
	    rl = (tril[i__] + const_1.clsunl - *teffl * 4. - const1_1.c4pil - 
		    const2_1.csigl) * .5;
	    gl = const2_1.cgl + comp_1.stotal - rl - rl;
	    ++numenv;
	    ccout_1.lpenv = numenv % ccout1_1.npenv == 0;
	    if (! ccout_1.lscrib) {
		ccout_1.lpenv = FALSE_;
	    }
	    if (ccout_1.lpenv) {
		io___19.ciunit = luout_1.imodpt;
		s_wsfe(&io___19);
		do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&trit[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&tril[i__], (ftnlen)sizeof(doublereal));
		e_wsfe();
		io___20.ciunit = luout_1.ishort;
		s_wsfe(&io___20);
		do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&trit[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&tril[i__], (ftnlen)sizeof(doublereal));
		e_wsfe();
	    }
	    ixx = i__;
	    lsbc0 = TRUE_;
/* DBG PULSE: DO NOT DO PULSE OUTPUT */
	    lpulpt = FALSE_;
	    envint_(&b, fpl, ftl, &gl, hstot, &ixx, &ccout_1.lpenv, &lsbc0, 
		    plim, &rl, teffl, x, z__, &estore[1], istore, katm, kenv, 
		    ksaha, &ps[1], &rs[1], &ts[1], &lpulpt);
	    lrenv = TRUE_;
	}
/* L40: */
    }
    if (lrenv) {
/* RECOMPUTE COEFFICIENTS */
	temp = 1. / (ts[2] - ts[1]);
	temp1 = (ts[3] - ts[1]) * temp;
	temp2 = 1. / (ps[3] - ps[1] - temp1 * (ps[2] - ps[1]));
	cfenv[1] = (rs[3] - rs[1] - temp1 * (rs[2] - rs[1])) * temp2;
	cfenv[4] = (tril[3] - tril[1] - temp1 * (tril[2] - tril[1])) * temp2;
	cfenv[7] = (trit[3] - trit[1] - temp1 * (trit[2] - trit[1])) * temp2;
	cfenv[2] = (rs[2] - rs[1] - cfenv[1] * (ps[2] - ps[1])) * temp;
	cfenv[5] = (tril[2] - tril[1] - cfenv[4] * (ps[2] - ps[1])) * temp;
	cfenv[8] = (trit[2] - trit[1] - cfenv[7] * (ps[2] - ps[1])) * temp;
	cfenv[3] = rs[1] - cfenv[1] * ps[1] - cfenv[2] * ts[1];
	cfenv[6] = tril[1] - cfenv[4] * ps[1] - cfenv[5] * ts[1];
	cfenv[9] = trit[1] - cfenv[7] * ps[1] - cfenv[8] * ts[1];
	io___26.ciunit = luout_1.ishort;
	s_wsfe(&io___26);
	for (i__ = 1; i__ <= 3; ++i__) {
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&ltri[i__ - 1], (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&trit[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&tril[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ps[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ts[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rs[i__], (ftnlen)sizeof(doublereal));
	    for (j = 1; j <= 3; ++j) {
		do_fio(&c__1, (char *)&cfenv[i__ + i__ + i__ - 3 + j], (
			ftnlen)sizeof(doublereal));
	    }
	}
	e_wsfe();
/* L60: */
    } else {
	io___28.ciunit = luout_1.ishort;
	s_wsfe(&io___28);
	e_wsfe();
    }
    return 0;
} /* surfbc_ */

