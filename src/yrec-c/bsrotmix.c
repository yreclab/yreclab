/* bsrotmix.f -- translated by f2c (version 20061008).
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
    doublereal hcompi[825000]	/* was [11][15][5000] */, hcompa[75000]	/* 
	    was [15][5000] */, hcompe[75000]	/* was [15][5000] */;
} bsburn_;

#define bsburn_1 bsburn_

/* Table of constant values */

static integer c__1 = 1;

/* $$$$$$ */
/* MHP 6/00 SUBROUTINE.  MIXING AND BURNING ARE PERFORMED SEQUENTIALLY */
/* FOR AN INCREASING NUMBER OF SUBSTEPS FOR A GIVEN TOTAL STEP.  THIS ROUTINE */
/* EXTRAPOLATES TO ZERO TIMESTEP, */
/* Subroutine */ int bsrotmix_(doublereal *delts, doublereal *hcomp, integer *
	iest, integer *m, integer *jbeg, integer *nspec, integer *nseq, 
	logical *lconv)
{
    /* Format strings */
    static char fmt_10[] = "(5x,\002ITER\002,i3,\002 MAX ERR \002,1pe10.2"
	    ",\002 SPECIES \002,i3,\002 SHELL \002,i5,\002 ABUND\002,2e12.4)";

    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;

    /* Builtin functions */
    /* Subroutine */ void s_stop(char *, ftnlen);
    double log(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double exp(doublereal);

    /* Local variables */
    static logical lcncheck;
    static doublereal d__[75000]	/* was [15][5000] */;
    static integer i__, j;
    static doublereal q, x[11], f1, f2;
    static integer j1, k1, jj[15];
    static doublereal x12, x13, x14, x16;
    static logical ldo[15];
    static doublereal sum;
    static logical lhe3[5000], lcno[5000];
    static integer imax, jmax, nmax;
    static doublereal xest, delta, errmax;
    static integer icount;

    /* Fortran I/O blocks */
    static cilist io___26 = { 0, 6, 0, fmt_10, 0 };


/*      SAVE X,D,JJ,LDO,NMAX,LCNO,LCNCHECK */
/* DETERMINE WHICH SPECIES REQUIRE CALCULATION */
    /* Parameter adjustments */
    --nseq;
    hcomp -= 16;

    /* Function Body */
    if (*iest == 1) {
	i__1 = *nspec;
	for (j = *jbeg; j <= i__1; ++j) {
	    ldo[j - 1] = FALSE_;
	    for (i__ = *m; i__ >= 1; --i__) {
		if (hcomp[j + i__ * 15] > 1e-14) {
		    ldo[j - 1] = TRUE_;
		    goto L5;
		}
	    }
L5:
	    ;
	}
	if (ldo[3]) {
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		if (hcomp[i__ * 15 + 4] > 1e-24) {
		    lhe3[i__ - 1] = TRUE_;
		} else {
		    lhe3[i__ - 1] = FALSE_;
		}
	    }
	}
/* CHECK FOR ALTERNATE METHOD FOR DOING CNO ABUNDANCES; SOLVE FOR */
/* C13/C12, N14/C12, O16/N14, SUM OF CNO NUCLEI RATHER THAN FOR */
/* THE INDIVIDUAL ABUNDANCES OF C12,C13,N14,O16. */
	if (ldo[4] && ldo[5] && ldo[6] && ldo[8]) {
	    lcncheck = TRUE_;
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		if (hcomp[i__ * 15 + 5] > 1e-24 && hcomp[i__ * 15 + 6] > 
			1e-24 && hcomp[i__ * 15 + 7] > 1e-24 && hcomp[i__ * 
			15 + 9] > 1e-24) {
		    lcno[i__ - 1] = TRUE_;
		} else {
		    lcno[i__ - 1] = FALSE_;
		}
	    }
	} else {
	    lcncheck = FALSE_;
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		lcno[i__ - 1] = FALSE_;
	    }
	}
	icount = 1;
	i__1 = *nspec;
	for (i__ = *jbeg; i__ <= i__1; ++i__) {
	    if (ldo[i__ - 1]) {
		jj[icount - 1] = i__;
		++icount;
	    }
	}
	nmax = icount - 1;
	if (nmax < 1) {
	    s_stop("999", (ftnlen)3);
	}
    }
/* STORE CURRENT RESULTS IN VECTOR OF COMPOSITION (HCOMPA) AND */
/* ERROR (DCOMPA) */
    i__1 = nmax;
    for (j1 = 1; j1 <= i__1; ++j1) {
	j = jj[j1 - 1];
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    bsburn_1.hcompa[j + i__ * 15 - 16] = hcomp[j + i__ * 15];
	    bsburn_1.hcompe[j + i__ * 15 - 16] = hcomp[j + i__ * 15];
	}
    }
/* EXTRAPOLATE IN THE LOG OF HE3 RATHER THAN ABSOLUTE ABUNDANCE */
    if (ldo[3]) {
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (lhe3[i__ - 1]) {
		bsburn_1.hcompa[i__ * 15 - 12] = log(hcomp[i__ * 15 + 4]);
		bsburn_1.hcompe[i__ * 15 - 12] = bsburn_1.hcompa[i__ * 15 - 
			12];
	    }
	}
    }
    if (lcncheck) {
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (lcno[i__ - 1]) {
		x12 = hcomp[i__ * 15 + 5];
		x13 = hcomp[i__ * 15 + 6];
		x14 = hcomp[i__ * 15 + 7];
		x16 = hcomp[i__ * 15 + 9];
/* VECTOR 5: C13/C12 */
		bsburn_1.hcompa[i__ * 15 - 11] = x13 / x12;
		bsburn_1.hcompe[i__ * 15 - 11] = bsburn_1.hcompa[i__ * 15 - 
			11];
/* VECTOR 6: N14/C12 */
		bsburn_1.hcompa[i__ * 15 - 10] = x14 / x12;
		bsburn_1.hcompe[i__ * 15 - 10] = bsburn_1.hcompa[i__ * 15 - 
			10];
/* VECTOR 7: O16/N14 */
		bsburn_1.hcompa[i__ * 15 - 9] = x16 / x14;
		bsburn_1.hcompe[i__ * 15 - 9] = bsburn_1.hcompa[i__ * 15 - 9];
/* VECTOR 9: C12/12 + C13/13 + N14/14 + O16/16 */
		bsburn_1.hcompa[i__ * 15 - 7] = x12 / 12. + x13 / 13. + x14 / 
			14. + x16 / 16.;
		bsburn_1.hcompe[i__ * 15 - 7] = bsburn_1.hcompa[i__ * 15 - 7];
	    }
	}
    }
/* SET CURRENT RESULTS AS THE INITIAL EXTRAPOLATION FOR THE FIRST SET OF */
/* TIME STEPS AND EXIT. */
/* Computing 2nd power */
    d__1 = *delts / (doublereal) nseq[*iest];
    x[*iest - 1] = d__1 * d__1;
    if (*iest == 1) {
	i__1 = nmax;
	for (j1 = 1; j1 <= i__1; ++j1) {
	    j = jj[j1 - 1];
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		bsburn_1.hcompi[*iest + (j + i__ * 15) * 11 - 177] = hcomp[j 
			+ i__ * 15];
	    }
	}
	if (ldo[3]) {
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		if (lhe3[i__ - 1]) {
		    bsburn_1.hcompi[*iest + (i__ * 15 + 4) * 11 - 177] = log(
			    hcomp[i__ * 15 + 4]);
		}
	    }
	}
	if (lcncheck) {
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		if (lcno[i__ - 1]) {
		    bsburn_1.hcompi[*iest + (i__ * 15 + 5) * 11 - 177] = 
			    bsburn_1.hcompa[i__ * 15 - 11];
		    bsburn_1.hcompi[*iest + (i__ * 15 + 6) * 11 - 177] = 
			    bsburn_1.hcompa[i__ * 15 - 10];
		    bsburn_1.hcompi[*iest + (i__ * 15 + 7) * 11 - 177] = 
			    bsburn_1.hcompa[i__ * 15 - 9];
		    bsburn_1.hcompi[*iest + (i__ * 15 + 9) * 11 - 177] = 
			    bsburn_1.hcompa[i__ * 15 - 7];
		}
	    }
	}
	*lconv = FALSE_;
    } else {
/* POLYNOMIAL FUNCTION EXTRAPOLATON */
/* CURRENT STEPSIZE */
	xest = x[*iest - 1];
	i__1 = nmax;
	for (j1 = 1; j1 <= i__1; ++j1) {
	    j = jj[j1 - 1];
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		d__[j + i__ * 15 - 16] = hcomp[j + i__ * 15];
	    }
	}
	if (ldo[3]) {
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		if (lhe3[i__ - 1]) {
		    d__[i__ * 15 - 12] = log(hcomp[i__ * 15 + 4]);
		}
	    }
	}
	if (lcncheck) {
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		if (lcno[i__ - 1]) {
		    x12 = hcomp[i__ * 15 + 5];
		    x13 = hcomp[i__ * 15 + 6];
		    x14 = hcomp[i__ * 15 + 7];
		    x16 = hcomp[i__ * 15 + 9];
/* VECTOR 5: C13/C12 */
		    d__[i__ * 15 - 11] = x13 / x12;
/* VECTOR 6: N14/C12 */
		    d__[i__ * 15 - 10] = x14 / x12;
/* VECTOR 7: O16/N14 */
		    d__[i__ * 15 - 9] = x16 / x14;
/* VECTOR 9: C12/12 + C13/13 + N14/14 + O16/16 */
		    d__[i__ * 15 - 7] = x12 / 12. + x13 / 13. + x14 / 14. + 
			    x16 / 16.;
		}
	    }
	}
	i__1 = *iest - 1;
	for (k1 = 1; k1 <= i__1; ++k1) {
	    delta = 1. / (x[*iest - k1 - 1] - xest);
	    f1 = xest * delta;
	    f2 = x[*iest - k1 - 1] * delta;
	    i__2 = nmax;
	    for (j1 = 1; j1 <= i__2; ++j1) {
		j = jj[j1 - 1];
		i__3 = *m;
		for (i__ = 1; i__ <= i__3; ++i__) {
		    q = bsburn_1.hcompi[k1 + (j + i__ * 15) * 11 - 177];
		    bsburn_1.hcompi[k1 + (j + i__ * 15) * 11 - 177] = 
			    bsburn_1.hcompe[j + i__ * 15 - 16];
		    delta = d__[j + i__ * 15 - 16] - q;
		    bsburn_1.hcompe[j + i__ * 15 - 16] = f1 * delta;
		    d__[j + i__ * 15 - 16] = f2 * delta;
		    bsburn_1.hcompa[j + i__ * 15 - 16] += bsburn_1.hcompe[j + 
			    i__ * 15 - 16];
		}
	    }
	}
	i__1 = nmax;
	for (j1 = 1; j1 <= i__1; ++j1) {
	    j = jj[j1 - 1];
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		bsburn_1.hcompi[*iest + (j + i__ * 15) * 11 - 177] = 
			bsburn_1.hcompe[j + i__ * 15 - 16];
	    }
	}
/* NOW CHECK IF ERROR IS WITHIN TOLERANCE */
	errmax = 1e-30;
	imax = 1;
	jmax = 1;
	i__1 = nmax;
	for (j1 = 1; j1 <= i__1; ++j1) {
	    j = jj[j1 - 1];
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		if (bsburn_1.hcompa[j + i__ * 15 - 16] > 1e-12) {
		    q = bsburn_1.hcompe[j + i__ * 15 - 16] / bsburn_1.hcompa[
			    j + i__ * 15 - 16];
		    if (abs(q) > errmax) {
			imax = i__;
			jmax = j;
			errmax = abs(q);
		    }
		}
	    }
	}
/*         WRITE(*,*)HCOMP(JMAX,IMAX),HCOMPA(JMAX,IMAX) */
	s_wsfe(&io___26);
	do_fio(&c__1, (char *)&(*iest), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&errmax, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&jmax, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&imax, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hcomp[jmax + imax * 15], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&bsburn_1.hcompa[jmax + imax * 15 - 16], (
		ftnlen)sizeof(doublereal));
	e_wsfe();
	if (errmax < .001) {
	    *lconv = TRUE_;
	}
	if (*lconv) {
/* NOW CONVERT BACK TO ABSOLUTE ABUNDANCES. */
	    if (ldo[3]) {
		i__1 = *m;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    if (lhe3[i__ - 1]) {
			bsburn_1.hcompa[i__ * 15 - 12] = exp(bsburn_1.hcompa[
				i__ * 15 - 12]);
		    }
		}
	    }
	    if (lcncheck) {
		i__1 = *m;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    if (lcno[i__ - 1]) {
/* VECTOR NINE IS C12/12+ C13/13 + N14/14 + O16/16. */
/* THEREFORE, C12 = SUMCNO/(1/12 + C13/C12*1/13 + N14/C12*1/14 + */
/* O16/N14*N14/C12*1/16) */
			sum = bsburn_1.hcompa[i__ * 15 - 11] / 13. + 
				.083333333333333329 + bsburn_1.hcompa[i__ * 
				15 - 10] / 14. + bsburn_1.hcompa[i__ * 15 - 
				10] * bsburn_1.hcompa[i__ * 15 - 9] / 16.;
			x12 = bsburn_1.hcompa[i__ * 15 - 7] / sum;
			x13 = bsburn_1.hcompa[i__ * 15 - 11] * x12;
			x14 = bsburn_1.hcompa[i__ * 15 - 10] * x12;
			x16 = bsburn_1.hcompa[i__ * 15 - 9] * x14;
/*       WRITE(*,911)X12,X13,X14,X16,HCOMPA(5,I),HCOMPA(6,I), */
/*     *             HCOMPA(7,I),HCOMPA(9,I),SUM */
/* 911   FORMAT(1P9E10.2) */
			bsburn_1.hcompa[i__ * 15 - 11] = x12;
			bsburn_1.hcompa[i__ * 15 - 10] = x13;
			bsburn_1.hcompa[i__ * 15 - 9] = x14;
			bsburn_1.hcompa[i__ * 15 - 7] = x16;
		    }
		}
	    }
	    i__1 = nmax;
	    for (j1 = 1; j1 <= i__1; ++j1) {
		j = jj[j1 - 1];
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    hcomp[j + i__ * 15] = bsburn_1.hcompa[j + i__ * 15 - 16];
		    if (hcomp[j + i__ * 15] < 1e-24) {
			hcomp[j + i__ * 15] = 0.;
		    }
		}
	    }
	}
    }
    return 0;
} /* bsrotmix_ */

