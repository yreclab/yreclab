/* rhoofp01.f -- translated by f2c (version 20100827).
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
    integer itime;
} lreadco_;

#define lreadco_1 lreadco_

struct {
    doublereal xz[1613950]	/* was [5][10][191][169] */, t6list[32279]	
	    /* was [169][191] */, rho[169], t6a[191], esk[32279]	/* 
	    was [191][169] */, esk2[32279]	/* was [191][169] */, dfsx[5],
	     dfs[191], dfsr[169];
    integer m, mf;
    doublereal xa[5];
} aeos_;

#define aeos_1 aeos_

struct {
    integer iri[10], index[10], nta[169];
    doublereal zz[5];
} beos_;

#define beos_1 beos_

struct {
    doublereal esact, eos[10];
} eeos_;

#define eeos_1 eeos_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* Table of constant values */

static integer c__1 = 1;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*     RHOOFP01 */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
doublereal rhoofp01_(doublereal *x, doublereal *ztab, doublereal *t6, 
	doublereal *p, integer *irad)
{
    /* Initialized data */

    static doublereal sigmacc = .0018914785;
    static integer nra[191] = { 169,169,169,169,169,169,169,169,169,169,169,
	    169,169,169,169,169,168,167,166,165,164,164,163,162,162,161,160,
	    159,159,143,143,143,143,137,137,137,137,137,134,134,134,134,134,
	    134,125,125,123,123,123,123,123,122,122,121,121,121,121,121,121,
	    119,119,119,119,116,116,116,116,116,116,116,116,115,115,115,115,
	    115,115,113,113,113,113,113,113,113,113,111,111,111,111,111,111,
	    111,110,110,110,110,110,110,109,109,109,109,109,109,109,109,109,
	    109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,
	    109,109,109,109,109,109,109,109,109,107,104,100,100,100,100,100,
	    100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
	    100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
	    100,100,100,99,99,99,99,99,99,99,99,99,99,98,97,96,95,94,93,92 };

    /* System generated locals */
    doublereal ret_val, d__1;

    /* Local variables */
    static doublereal p1, p2, p3, pr;
    static integer ihi, imd, ilo;
    static doublereal rat;
    static integer mlo, klo;
    static doublereal pnr;
    static integer idbg;
    static doublereal rdbg, xdbg, pmin, pmax, t6dbg, rhog1, rhog2, rhog3;
    extern /* Subroutine */ int esac01_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *);
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
	switch (esac01_(&xdbg, ztab, &t6dbg, &rdbg, &idbg, irad)) {
	    case 1:  goto L999;
	}
    }
    ilo = 2;
    ihi = 5;
L8:
    if (ihi - ilo > 1) {
	imd = (ihi + ilo) / 2;
	if (*x <= aeos_1.xa[imd - 1] + 1e-7) {
	    ihi = imd;
	} else {
	    ilo = imd;
	}
	goto L8;
    }
    mlo = ilo;
    ilo = 191;
    ihi = 2;
L11:
    if (ilo - ihi > 1) {
	imd = (ihi + ilo) / 2;
	if (*t6 == aeos_1.t6list[imd * 169 - 169]) {
	    ilo = imd;
	    goto L14;
	}
	if (*t6 <= aeos_1.t6list[imd * 169 - 169]) {
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
    pmax = aeos_1.xz[mlo + ((klo + nra[klo - 1] * 191) * 10 + 1) * 5 - 9606] *
	     *t6 * aeos_1.rho[nra[klo - 1] - 1] + *irad * 4. / 3. * rat * (
	    d__1 * d__1);
/* Computing 4th power */
    d__1 = *t6, d__1 *= d__1;
    pmin = aeos_1.xz[mlo + ((klo + 191) * 10 + 1) * 5 - 9606] * *t6 * 
	    aeos_1.rho[0] + *irad * 4. / 3. * rat * (d__1 * d__1);
    if (pnr > pmax * 1.25 || pnr < pmin) {
/*      write (ISHORT,'(" The requested pressure-temperature not in ", */
/*     X       "table")') */
/*     stop */
/*      write (ISHORT,'("pnr, pmax,pmin=",3e14.4)') pnr,pmax,pmin */
	goto L999;
    }
    rhog1 = aeos_1.rho[nra[klo - 1] - 1] * pnr / pmax;
    switch (esac01_(x, ztab, t6, &rhog1, &c__1, irad)) {
	case 1:  goto L999;
    }
    p1 = eeos_1.eos[0];
    if (p1 > pnr) {
	p2 = p1;
	rhog2 = rhog1;
	rhog1 *= .2;
	if (rhog1 < 1e-14) {
	    rhog1 = 1e-14;
	}
	switch (esac01_(x, ztab, t6, &rhog1, &c__1, irad)) {
	    case 1:  goto L999;
	}
	p1 = eeos_1.eos[0];
    } else {
	rhog2 = rhog1 * 5.;
/*          if(rhog2 .gt. rho(klo)) rhog2=rho(klo)  ! Corrected below llp 8/19/08 */
	if (rhog2 > aeos_1.rho[nra[klo - 1] - 1]) {
	    rhog2 = aeos_1.rho[nra[klo - 1] - 1];
	}
/* Had wrong pointer, see rhog1= ten lines up */
	switch (esac01_(x, ztab, t6, &rhog2, &c__1, irad)) {
	    case 1:  goto L999;
	}
	p2 = eeos_1.eos[0];
    }
    icount = 0;
L1:
    ++icount;
    rhog3 = rhog1 + (rhog2 - rhog1) * (pnr - p1) / (p2 - p1);
    switch (esac01_(x, ztab, t6, &rhog3, &c__1, irad)) {
	case 1:  goto L999;
    }
    p3 = eeos_1.eos[0];
/*      if (abs((p3-pnr)/pnr) .lt. 1.D-5) then */
    if ((d__1 = (p3 - pnr) / pnr, abs(d__1)) < 5e-8) {
	ret_val = rhog3;
	return ret_val;
    }
    if (p3 > pnr) {
	rhog2 = rhog3;
	p2 = p3;
	if (icount < 11) {
	    goto L1;
	}
/*        write (ISHORT,'("No convergence after 10 tries")') */
	goto L999;
/*        stop */
    } else {
	rhog1 = rhog3;
	p1 = p3;
	if (icount < 11) {
	    goto L1;
	}
/*        write (*,'("No convergence after 10 tries")') */
	goto L999;
/*        stop */
    }
L999:
    ret_val = -999.;
/*      WRITE(ISHORT,'("FAIL TO FIND RHO")') */
    return ret_val;
} /* rhoofp01_ */

