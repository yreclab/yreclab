/* rhoofp.f -- translated by f2c (version 20061008).
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
    integer itime;
} lreadco_;

#define lreadco_1 lreadco_

struct {
    doublereal xz[215600]	/* was [5][10][56][77] */, t6list[4312]	/* 
	    was [77][56] */, rho[77], t6a[56], esk[4312]	/* was [56][
	    77] */, esk2[4312]	/* was [56][77] */, dfsx[5], dfs[56], dfsr[77]
	    , xa[5];
    integer m, mf;
} a_;

#define a_1 a_

struct {
    doublereal zz[5];
    integer iri[10], index[10], nta[77];
} b_;

#define b_1 b_

struct {
    doublereal esact, eos[10];
} e_;

#define e_1 e_

/* Table of constant values */

static integer c__1 = 1;

/* ******************************************************************** */
/*       REAL*8 FUNCTION RHOOFP(X,ZTAB,T6,P,IRAD)  ! KC 2025-05-31 */
doublereal rhoofp_(doublereal *x, doublereal *t6, doublereal *p, integer *
	irad)
{
    /* Initialized data */

    static doublereal sigmacc = .0018914785;
    static integer nra[56] = { 77,77,77,77,77,77,77,76,76,74,74,72,72,70,70,
	    68,67,66,65,64,63,61,60,59,58,57,55,54,53,52,51,49,49,48,47,47,46,
	    45,45,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,37,37 };

    /* System generated locals */
    doublereal ret_val, d__1;

    /* Local variables */
    static doublereal p1, p2, p3, pr;
    static integer ihi, imd, ilo;
    static doublereal rat;
    static integer mlo, klo;
    static doublereal pnr;
    static integer idbg;
    extern /* Subroutine */ int esac_(doublereal *, doublereal *, doublereal *
	    , integer *, integer *);
    static doublereal rdbg, xdbg, pmin, pmax, t6dbg, rhog1, rhog2, rhog3;
    static integer icount;

    rat = sigmacc;
    pr = 0.;
/*      IF(IRAD .EQ. 1) PR=4.D0/3.D0*RAT*T6**4   ! MB */
    pnr = *p - pr;
    if (lreadco_1.itime != 12345678) {
	xdbg = .5;
	t6dbg = 1.;
	rdbg = .001;
	idbg = 1;
/*       CALL ESAC (XDBG,ZTAB,T6DBG,RDBG,IDBG,IRAD,*999)  ! KC 2025-05-31 */
	switch (esac_(&xdbg, &t6dbg, &rdbg, &idbg, irad)) {
	    case 1:  goto L999;
	}
    }
    ilo = 2;
    ihi = 5;
L8:
    if (ihi - ilo > 1) {
	imd = (ihi + ilo) / 2;
	if (*x <= a_1.xa[imd - 1] + 1e-7) {
	    ihi = imd;
	} else {
	    ilo = imd;
	}
	goto L8;
    }
    mlo = ilo;
    ilo = 56;
    ihi = 2;
L11:
    if (ilo - ihi > 1) {
	imd = (ihi + ilo) / 2;
	if (*t6 == a_1.t6list[imd * 77 - 77]) {
	    ilo = imd;
	    goto L14;
	}
	if (*t6 <= a_1.t6list[imd * 77 - 77]) {
	    ihi = imd;
	} else {
	    ilo = imd;
	}
	goto L11;
    }
L14:
    klo = ilo;
/* Computing 4th power */
    d__1 = *t6, d__1 *= d__1;
    pmax = a_1.xz[mlo + ((klo + nra[klo - 1] * 56) * 10 + 1) * 5 - 2856] * *
	    t6 * a_1.rho[nra[klo - 1] - 1] + *irad * 4. / 3. * rat * (d__1 * 
	    d__1);
/* Computing 4th power */
    d__1 = *t6, d__1 *= d__1;
    pmin = a_1.xz[mlo + ((klo + 56) * 10 + 1) * 5 - 2856] * *t6 * a_1.rho[0] 
	    + *irad * 4. / 3. * rat * (d__1 * d__1);
    if (pnr > pmax * 1.25 || pnr < pmin) {
/*      WRITE(ISHORT,'(" THE REQUESTED PRESSURE-TEMPERATURE NOT IN ", */
/*     *       "TABLE")') */
/*     STOP */
/*      WRITE(ISHORT,'("PNR, PMAX,PMIN=",3E14.4)') PNR,PMAX,PMIN */
	goto L999;
    }
    rhog1 = a_1.rho[nra[klo - 1] - 1] * pnr / pmax;
/*       CALL ESAC (X,ZTAB,T6,RHOG1,1,IRAD,*999)  ! KC 2025-05-31 */
    switch (esac_(x, t6, &rhog1, &c__1, irad)) {
	case 1:  goto L999;
    }
    p1 = e_1.eos[0];
    if (p1 > pnr) {
	p2 = p1;
	rhog2 = rhog1;
	rhog1 *= .2;
	if (rhog1 < 1e-14) {
	    rhog1 = 1e-14;
	}
/*           CALL ESAC (X,ZTAB,T6,RHOG1,1,IRAD,*999)  ! KC 2025-05-31 */
	switch (esac_(x, t6, &rhog1, &c__1, irad)) {
	    case 1:  goto L999;
	}
	p1 = e_1.eos[0];
    } else {
	rhog2 = rhog1 * 5.;
/*          IF(RHOG2 .GT. RHO(KLO)) RHOG2=RHO(KLO) ! Corrected below  llp 8/19/08 */
	if (rhog2 > a_1.rho[nra[klo - 1] - 1]) {
	    rhog2 = a_1.rho[nra[klo - 1] - 1];
	}
/*           CALL ESAC (X,ZTAB,T6,RHOG2,1,IRAD,*999)  ! KC 2025-05-31 */
/* Had wrong pointer, see RHOG1= ten lines up */
	switch (esac_(x, t6, &rhog2, &c__1, irad)) {
	    case 1:  goto L999;
	}
	p2 = e_1.eos[0];
    }
    icount = 0;
L1:
    ++icount;
    rhog3 = rhog1 + (rhog2 - rhog1) * (pnr - p1) / (p2 - p1);
/*       CALL ESAC (X,ZTAB,T6,RHOG3,1,IRAD,*999)  ! KC 2025-05-31 */
    switch (esac_(x, t6, &rhog3, &c__1, irad)) {
	case 1:  goto L999;
    }
    p3 = e_1.eos[0];
/*      IF (ABS((P3-PNR)/PNR) .LT. 1.D-5) THEN */
    if ((d__1 = (p3 - pnr) / pnr, abs(d__1)) < 5e-8) {
	ret_val = rhog3;
/*      WRITE(ISHORT,*)RHOG3,P,PNR,P3 */
/*      WRITE(ISHORT,*)X,ZTAB,T6,P,RHOG3,IORDER,IRAD */
	return ret_val;
    }
    if (p3 > pnr) {
	rhog2 = rhog3;
	p2 = p3;
	if (icount < 11) {
	    goto L1;
	}
/*        WRITE(ISHORT,'("NO CONVERGENCE AFTER 10 TRIES")') */
	goto L999;
/*        STOP */
    } else {
	rhog1 = rhog3;
	p1 = p3;
	if (icount < 11) {
	    goto L1;
	}
/*        WRITE(ISHORT,'("NO CONVERGENCE AFTER 10 TRIES")') */
	goto L999;
/*        STOP */
    }
L999:
    ret_val = -999.;
/*      WRITE(ISHORT,'("FAIL TO FIND RHO")') */
    return ret_val;
} /* rhoofp_ */

