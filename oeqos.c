/* oeqos.f -- translated by f2c (version 20100827).
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
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    logical ldebug, lcorr, lmilne, ltrack, lstore, lstpch;
    integer npunch;
} ccout2_;

#define ccout2_1 ccout2_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal esact, eos[10];
} e_;

#define e_1 e_

/* Table of constant values */

static doublereal c_b2 = 10.;
static integer c__5 = 5;
static integer c__1 = 1;
static integer c__9 = 9;


/*     OPAL EQUATION OF STATE */

/*     IMPLIMENTED BY YC    (FEB. 21, 1995) */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/* INDEX TO THIS FILE: */
/*     SUBROUTINE OEQOS */
/*     SUBROUTINE MU */
/*     SUBROUTINE ESAC */
/*     SUBROUTINE T6RINTERP */
/*     SUBROUTINE READCO */
/*     FUNCTION QUAD */
/*     FUNCTION GMASS */
/*     SUBROUTINE RADSUB */
/*     FUNCTION RHOOFP */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MEQOS */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int oeqos_(doublereal *t10, doublereal *t, doublereal *p10, 
	doublereal *p, doublereal *d10, doublereal *d__, doublereal *xc, 
	doublereal *z__, doublereal *beta, doublereal *betai, doublereal *
	beta14, doublereal *rmu, doublereal *amu, doublereal *emu, doublereal 
	*qdt, doublereal *qdp, doublereal *qcp, doublereal *dela)
{

    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), d_lg10(doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal r__, x, t6, p12;
    extern /* Subroutine */ int mu_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal rmu2;
    extern /* Subroutine */ int esac_(doublereal *, doublereal *, doublereal *
	    , doublereal *, integer *, integer *);
    static integer irad;
    static doublereal ztab;
    static integer iorder;
    extern doublereal rhoofp_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *);

    /* Fortran I/O blocks */
    static cilist io___10 = { 0, 0, 0, 0, 0 };
    static cilist io___12 = { 0, 0, 0, 0, 0 };



/*      CA3=2.5214D-15 */

    *t = pow_dd(&c_b2, t10);
    *p = pow_dd(&c_b2, p10);
    t6 = *t / 1e6;
    p12 = *p / 1e12;
    if (t6 < .005 || t6 > 100.) {
	return 1;
    }
    x = *xc;
    ztab = *z__;
    irad = 1;
    iorder = 10;
    r__ = rhoofp_(&x, &ztab, &t6, &p12, &irad);
    if (r__ <= -998.) {
	return 1;
    }
    *d__ = r__;
    *d10 = d_lg10(d__);
    switch (esac_(&x, &ztab, &t6, &r__, &iorder, &irad)) {
	case 1:  goto L999;
    }
    if ((d__1 = (p12 - e_1.eos[0]) / p12, abs(d__1)) > 5e-7) {
	io___10.ciunit = luout_1.ishort;
	s_wsle(&io___10);
	do_lio(&c__5, &c__1, (char *)&p12, (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&e_1.eos[0], (ftnlen)sizeof(doublereal));
	e_wsle();
	s_stop(" ERROR IN OEQOS PTOT", (ftnlen)20);
    }
    *qdp = 1. / e_1.eos[5];
    *qdt = -e_1.eos[6] / e_1.eos[5];
    *qcp = e_1.eos[4] * 1e6 * e_1.eos[7] / e_1.eos[5];
    *dela = 1. / e_1.eos[8];
    *beta14 = t6 * .002521971383 * t6 * (t6 * t6 / p12);
    *beta = 1. - *beta14;
    *betai = 1. / *beta;
    *rmu = *p * *beta / (*d__ * *t);
    mu_(t, p, d__, xc, z__, &rmu2, amu, emu, beta);
    if (*emu <= 0.) {
	*emu = 0.;
	*amu = *rmu / const2_1.cgas - *emu;
    }
    return 0;
L999:
    io___12.ciunit = luout_1.ishort;
    s_wsle(&io___12);
    do_lio(&c__9, &c__1, "WARNNING... OPAL TBL FAIL", (ftnlen)25);
    e_wsle();
    return 1;
} /* oeqos_ */

