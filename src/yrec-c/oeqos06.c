/* oeqos06.f -- translated by f2c (version 20061008).
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
    logical ldebug, lcorr, lmilne, ltrack, lstpch;
} ccout2_;

#define ccout2_1 ccout2_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal esact, eos[10];
} eeos06_;

#define eeos06_1 eeos06_

/* Table of constant values */

static doublereal c_b2 = 10.;
static integer c__9 = 9;
static integer c__1 = 1;

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*     2006 OPAL Equation of State */

/*     LLP   October 17, 2006 */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/* Routines associated with 2001 OPAL EOS */

/*     SUBROUTINE OEOS06 */
/*     SUBROUTINE ESAC06 */
/*     SUBROUTINE T6RINTEOS06 */
/*     SUBROUTINE READCOEOS06 */
/*     FUNCTION QUADEOS06 */
/*     FUNCTION GMASS06 */
/*     SUBROUTINE RADSUB06 */
/*     FUNCTION RHOOFP06 */
/*     SUBROUTINE EQBOUND06 */
/*     SUBROUTINE MU is also used */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*     OEQOS06 */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int oeqos06_(doublereal *t10, doublereal *t, doublereal *p10,
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
    extern /* Subroutine */ int esac06_(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *);
    static integer iorder;
    extern doublereal rhoofp06_(doublereal *, doublereal *, doublereal *, 
	    integer *);

    /* Fortran I/O blocks */
    static cilist io___9 = { 0, 0, 0, 0, 0 };


/*       DIMENSION ATOMWT(4) */
/*      DATA NZP1/12/ */
/*      DATA ATOMWT/0.9921D0,0.24975D0,0.08322D0,0.4995D0/ */

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
    if (t6 < .00187 || t6 > 200.) {
	return 1;
    }
    x = *xc;
    ztab = *z__;
/*       R=RHOOFP06(X,ZTAB,T6,P12,IRAD)  ! KC 2025-05-31 */
    r__ = rhoofp06_(&x, &t6, &p12, &irad);
    if (r__ <= -998.) {
	return 1;
    }
    *d__ = r__;
    *d10 = d_lg10(d__);
/*       CALL ESAC06(X,ZTAB,T6,R,IORDER,IRAD,*999)  ! KC 2025-05-31 */
    switch (esac06_(&x, &t6, &r__, &iorder, &irad)) {
	case 1:  goto L999;
    }
/*      IF(ABS((P12-EOS(1))/P12).GT.0.5D-6)THEN */
/*         WRITE(ISHORT,*)'***** RUN TERMINATED --ERROR IN OEQOS06 PTOT' */
/*         WRITE(ISHORT,*) 'P12,EOS(1) Differ: P12,EOS(1),T6,R,X,ZTAB=', */
/*     *         P12,EOS(1),T6,R,X,ZTAB */
/*         STOP ' ERROR IN OEQOS06 PTOT' */
/*      ENDIF */
    *qdp = 1. / eeos06_1.eos[5];
/* O2006 EOS(6) is dlogP/dlogRho at const T6 */
    *qdt = -eeos06_1.eos[6] / eeos06_1.eos[5];
/* O2006 EOS(7) is dlogp/dlogT6 at const Rho */
    *qcp = eeos06_1.eos[4] * 1e6 * eeos06_1.eos[7] / eeos06_1.eos[5];
/*              at const Vol */
/* O2006 EOS(8) is gamma1 */
/* O2006 EOS(5) is the specific heat. dE/dT6 */
    *dela = 1. / eeos06_1.eos[8];
/* O2006 EOS(9) is gamma2/(gamma2-1) */
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
    io___9.ciunit = luout_1.ishort;
    s_wsle(&io___9);
    do_lio(&c__9, &c__1, "WARNNING... OPAL TBL FAIL", (ftnlen)25);
    e_wsle();
    return 1;
} /* oeqos06_ */

