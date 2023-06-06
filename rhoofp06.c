/* rhoofp06.f -- translated by f2c (version 20100827).
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
    doublereal xz[1664650]	/* was [5][10][197][169] */, t6list[33293]	
	    /* was [169][197] */, rho[169], t6a[197], esk[33293]	/* 
	    was [197][169] */, esk2[33293]	/* was [197][169] */, dfsx[5],
	     dfs[197], dfsr[169];
    integer m, mf;
    doublereal xa[5];
} aeos06_;

#define aeos06_1 aeos06_

struct {
    integer iri[10], index[10], nta[169];
    doublereal zz[5];
    integer nra[197];
} beos06_;

#define beos06_1 beos06_

struct {
    doublereal esact, eos[10];
} eeos06_;

#define eeos06_1 eeos06_

/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*     RHOOFP06 */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
doublereal rhoofp06_(doublereal *x, doublereal *ztab, doublereal *t6, 
	doublereal *p, integer *irad)
{
    /* Initialized data */

    static doublereal sigmacc = .0018914785;

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
    extern /* Subroutine */ int esac06_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *);
    static integer icount;

/* -------------------------------------------------------------------- */
    rat = sigmacc;
    pr = 0.;
    if (*irad == 1) {
/* Computing 4th power */
	d__1 = *t6, d__1 *= d__1;
	pr = rat * 1.3333333333333333 * (d__1 * d__1);
    }
/* Mb */
    pnr = *p - pr;
    if (lreadco_1.itime != 12345678) {
	xdbg = .5;
	t6dbg = 1.;
	rdbg = .001;
	idbg = 1;
	switch (esac06_(&xdbg, ztab, &t6dbg, &rdbg, &idbg, irad)) {
	    case 1:  goto L999;
	}
    }
    ilo = 2;
    ihi = 5;
L8:
    if (ihi - ilo > 1) {
	imd = (ihi + ilo) / 2;
	if (*x <= aeos06_1.xa[imd - 1] + 1e-7) {
	    ihi = imd;
	} else {
	    ilo = imd;
	}
	goto L8;
    }
    mlo = ilo;
    ilo = 197;
    ihi = 2;
L11:
    if (ilo - ihi > 1) {
	imd = (ihi + ilo) / 2;
	if (*t6 == aeos06_1.t6list[imd * 169 - 169]) {
	    ilo = imd;
	    goto L14;
	}
	if (*t6 <= aeos06_1.t6list[imd * 169 - 169]) {
	    ihi = imd;
	} else {
	    ilo = imd;
	}
	goto L11;
    }
L14:
    klo = ilo;
    pmax = aeos06_1.xz[mlo + ((klo + beos06_1.nra[klo - 1] * 197) * 10 + 1) * 
	    5 - 9906] * *t6 * aeos06_1.rho[beos06_1.nra[klo - 1] - 1];
    pmin = aeos06_1.xz[mlo + ((klo + 197) * 10 + 1) * 5 - 9906] * *t6 * 
	    aeos06_1.rho[0];
    if (pnr > pmax * 1.25 || pnr < pmin) {
/*      write (ISHORT,'(" The requested pressure-temperature not in", */
/*     x   " the OPAL 2006 EOS table")') */
/*     stop */
/*      write (ISHORT,'("pnr, pmax,pmin=",3e14.4)') pnr,pmax,pmin */
	goto L999;
/* RHOOFP06 error exit */
    }
    rhog1 = aeos06_1.rho[beos06_1.nra[klo - 1] - 1] * pnr / pmax;
    switch (esac06_(x, ztab, t6, &rhog1, &c__1, &c__0)) {
	case 1:  goto L999;
    }
    p1 = eeos06_1.eos[0];
    if (p1 > pnr) {
	p2 = p1;
	rhog2 = rhog1;
	rhog1 *= .2;
	if (rhog1 < 1e-14) {
	    rhog1 = 1e-14;
	}
	switch (esac06_(x, ztab, t6, &rhog1, &c__1, &c__0)) {
	    case 1:  goto L999;
	}
	p1 = eeos06_1.eos[0];
    } else {
	rhog2 = rhog1 * 5.;
/*          if(rhog2 .gt. rho(klo)) rhog2=rho(klo)  ! Corrected below   llp  8/19/08 */
	if (rhog2 > aeos06_1.rho[beos06_1.nra[klo - 1] - 1]) {
	    rhog2 = aeos06_1.rho[beos06_1.nra[klo - 1] - 1];
	}
/* Had wrong pointer, see rhog1= ten lines up */
	switch (esac06_(x, ztab, t6, &rhog2, &c__1, &c__0)) {
	    case 1:  goto L999;
	}
	p2 = eeos06_1.eos[0];
    }
    icount = 0;
L1:
    ++icount;
    rhog3 = rhog1 + (rhog2 - rhog1) * (pnr - p1) / (p2 - p1);
    switch (esac06_(x, ztab, t6, &rhog3, &c__1, &c__0)) {
	case 1:  goto L999;
    }
    p3 = eeos06_1.eos[0];
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
/*        write (ISHORT,'("Rhoofp06: No convergence after 10 tries")') */
	goto L999;
/*        stop */
/* RHOOFP06 error exit */
    } else {
	rhog1 = rhog3;
	p1 = p3;
	if (icount < 11) {
	    goto L1;
	}
/*        write (ISHORT,'("RHOOFP06: No convergence after 10 tries")') */
	goto L999;
/*        stop */
/* RHOOFP06 error exit */
    }
L999:
    ret_val = -999.;
/*      WRITE(ISHORT,'("RHOOFP06: FAILED TO FIND RHO")') */
    return ret_val;
} /* rhoofp06_ */

