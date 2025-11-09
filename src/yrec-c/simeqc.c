/* simeqc.f -- translated by f2c (version 20061008).
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



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* SIMEQC */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int simeqc_(doublereal *a, integer *m, integer *n)
{
    /* Format strings */
    static char fmt_1011[] = "(1x,\002STOPPED AT 1010\002)";

    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, k, n1, ia, ib, ic, id, ig, ih, ij, jj, it, ix, jx, 
	    jy, ny;
    static doublereal biga;
    static integer imax;
    static doublereal save;

    /* Fortran I/O blocks */
    static cilist io___9 = { 0, 5, 0, fmt_1011, 0 };


    /* Parameter adjustments */
    --a;

    /* Function Body */
    jj = -(*n);
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	jy = j + 1;
	jj = jj + *n + 1;
	biga = 0.;
	it = jj - j;
	i__2 = *n;
	for (i__ = j; i__ <= i__2; ++i__) {
	    ij = it + i__;
	    if (abs(biga) >= (d__1 = a[ij], abs(d__1))) {
		goto L30;
	    }
	    biga = a[ij];
	    imax = i__;
L30:
	    ;
	}
	if (abs(biga) == 0.) {
	    goto L1010;
	}
	goto L1012;
L1010:
	s_wsfe(&io___9);
	e_wsfe();
	s_stop("29", (ftnlen)2);
L1012:
	ia = j + *n * (j - 2);
	it = imax - j;
	i__2 = *m;
	for (k = j; k <= i__2; ++k) {
	    ia += *n;
	    ib = ia + it;
	    save = a[ia];
	    a[ia] = a[ib];
	    a[ib] = save;
	    a[ia] /= biga;
/* L50: */
	}
	if (j == *n) {
	    goto L70;
	}
	ia = *n * (j - 1);
	i__2 = *n;
	for (ix = jy; ix <= i__2; ++ix) {
	    ib = ia + ix;
	    it = j - ix;
	    i__3 = *m;
	    for (jx = jy; jx <= i__3; ++jx) {
		ic = *n * (jx - 1) + ix;
		id = ic + it;
		a[ic] -= a[ib] * a[id];
/* L60: */
	    }
/* L64: */
	}
/* L65: */
    }
L70:
    ny = *n - 1;
    it = *n * *n;
    i__1 = ny;
    for (j = 1; j <= i__1; ++j) {
	ia = it - j;
	ic = *n * *m;
	ib = ic - j;
	i__2 = j;
	for (k = 1; k <= i__2; ++k) {
	    a[ib] -= a[ia] * a[ic];
	    n1 = *m - 1;
	    ig = ib;
	    ih = ic;
L75:
	    if (n1 <= *n) {
		goto L78;
	    }
	    ig -= *n;
	    ih -= *n;
	    a[ig] -= a[ia] * a[ih];
	    --n1;
	    goto L75;
L78:
	    ia -= *n;
	    --ic;
/* L80: */
	}
/* L85: */
    }
    return 0;
} /* simeqc_ */

