/* oeqos01.f -- translated by f2c (version 20100827).
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
} eeos_;

#define eeos_1 eeos_

/* Table of constant values */

static doublereal c_b2 = 10.;
static integer c__9 = 9;
static integer c__1 = 1;

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*     2001 OPAL Equation of State */

/*     LLP   August 10, 2003 */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/* Routines associated with 2001 OPAL EOS */

/*     SUBROUTINE OEOS01 */
/*     SUBROUTINE ESAC01 */
/*     SUBROUTINE T6RINTEOS01 */
/*     SUBROUTINE READCOEOS01 */
/*     FUNCTION QUADEOS01 */
/*     FUNCTION GMASS01 */
/*     SUBROUTINE RADSUB01 */
/*     FUNCTION RHOOFP01 */
/*     SUBROUTINE EQBOUND01 */
/*     SUBROUTINE MU is also used */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*     OEQOS01 */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int oeqos01_(doublereal *t10, doublereal *t, doublereal *p10,
	 doublereal *p, doublereal *d10, doublereal *d__, doublereal *xc, 
	doublereal *z__, doublereal *beta, doublereal *betai, doublereal *
	beta14, doublereal *rmu, doublereal *amu, doublereal *emu, doublereal 
	*qdt, doublereal *qdp, doublereal *qcp, doublereal *dela)
{

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), d_lg10(doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static doublereal r__, x, t6, p12;
    extern /* Subroutine */ int mu_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal rmu2;
    static integer irad;
    static doublereal ztab;
    extern /* Subroutine */ int esac01_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *);
    static integer iorder;
    extern doublereal rhoofp01_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *);

    /* Fortran I/O blocks */
    static cilist io___11 = { 0, 0, 0, 0, 0 };



    iorder = 9;
/*                  in esac01. */
/*     NOTE: irad=0 does not add radiation; irad=1 adds radiation */
/* gives all 1st and 2nd order data. See instructions */
    irad = 1;
/* does add radiation  corrections */
    *t = pow_dd(&c_b2, t10);
    *p = pow_dd(&c_b2, p10);
    t6 = *t / 1e6;
    p12 = *p / 1e12;
    if (t6 < .002 || t6 > 100.) {
	return 1;
    }
    x = *xc;
    ztab = *z__;
    r__ = rhoofp01_(&x, &ztab, &t6, &p12, &irad);
    if (r__ <= -998.) {
	return 1;
    }
    *d__ = r__;
    *d10 = d_lg10(d__);
    switch (esac01_(&x, &ztab, &t6, &r__, &iorder, &irad)) {
	case 1:  goto L999;
    }
/*      IF(ABS((P12-EOS(1))/P12).GT.0.5D-6)THEN */
/*         WRITE(ISHORT,*)'***** RUN TERMINATED --ERROR IN OEQOS01 PTOT' */
/*         WRITE(ISHORT,*) 'P12,EOS(1) Differ: P12,EOS(1),T6,R,X,ZTAB=', */
/*     *         P12,EOS(1),T6,R,X,ZTAB */
/*         STOP ' ERROR IN OEQOS01 PTOT' */
/*      ENDIF */
/*      QDP=1.0D0/EOS(6) */
    *qdp = 1. / eeos_1.eos[4];
/*      QDT= -EOS(7)/ EOS(6) */
    *qdt = -eeos_1.eos[5] / eeos_1.eos[4];
/*      QCP=1.0D6*EOS(5)*EOS(8)/EOS(6) */
    *qcp = eeos_1.eos[3] * 1e6 * eeos_1.eos[6] / eeos_1.eos[4];
/*      DELA=1.0D0/EOS(9) */
    *dela = 1. / eeos_1.eos[7];
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
    io___11.ciunit = luout_1.ishort;
    s_wsle(&io___11);
    do_lio(&c__9, &c__1, "WARNNING... OPAL TBL FAIL", (ftnlen)25);
    e_wsle();
    return 1;
} /* oeqos01_ */

