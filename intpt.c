/* intpt.f -- translated by f2c (version 20100827).
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
    logical ldebug, lcorr, lmilne, ltrack, lstore, lstpch;
    integer npunch;
} ccout2_;

#define ccout2_1 ccout2_

/* ------------------------    GROUP: SR_P     ------------------------------- */


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* INTPT */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int intpt_(doublereal *pl, doublereal *tl, doublereal *tdvar,
	 integer *ntm, integer *nrm, integer *ivar, doublereal *tlog, integer 
	*nt, integer *nr, doublereal *var1, doublereal *var2, doublereal *y, 
	doublereal *varout)
{
    /* System generated locals */
    integer tdvar_dim1, tdvar_dim2, tdvar_offset, var1_dim1, var1_offset, 
	    var2_dim1, var2_offset, i__1;

    /* Local variables */
    static integer i__, j, l, m, n, id, ii, ir[16]	/* was [4][4] */, it[
	    4], np, iv;
    static doublereal xx[4];
    extern /* Subroutine */ int lir_(doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, integer *, integer *, integer *, 
	    integer *);
    static integer irm[4], indr, indt, ilir;
    static doublereal pmini, pmaxi;
    static integer itmax, irmax, inter;

    /* Parameter adjustments */
    --tlog;
    --varout;
    --y;
    var2_dim1 = *ivar;
    var2_offset = 1 + var2_dim1;
    var2 -= var2_offset;
    var1_dim1 = *ivar;
    var1_offset = 1 + var1_dim1;
    var1 -= var1_offset;
    tdvar_dim1 = *ntm;
    tdvar_dim2 = *nrm;
    tdvar_offset = 1 + tdvar_dim1 * (1 + tdvar_dim2);
    tdvar -= tdvar_offset;

    /* Function Body */
    i__1 = *nt;
    for (n = 1; n <= i__1; ++n) {
	if (tlog[n] >= *tl) {
	    goto L101;
	}
	it[0] = n;
/* L100: */
    }
L101:
    if (it[0] >= 2) {
	--it[0];
    }
    itmax = *nt - 3;
    if (it[0] > itmax) {
	it[0] = itmax;
    }
    for (i__ = 2; i__ <= 4; ++i__) {
/* L150: */
	it[i__ - 1] = it[0] + i__ - 1;
    }
    for (i__ = 1; i__ <= 4; ++i__) {
	irm[i__ - 1] = 1;
	indt = it[i__ - 1];
	pmini = tdvar[indt + ((tdvar_dim2 << 1) + 1) * tdvar_dim1];
	pmaxi = tdvar[indt + (*nr + (tdvar_dim2 << 1)) * tdvar_dim1];
	if (*pl > pmaxi) {
	    return 0;
	}
	i__1 = *nr;
	for (m = 1; m <= i__1; ++m) {
	    if (tdvar[indt + (m + (tdvar_dim2 << 1)) * tdvar_dim1] >= *pl) {
		goto L201;
	    }
	    irm[i__ - 1] = m;
/* L200: */
	}
L201:
	if (irm[i__ - 1] >= 2) {
	    --irm[i__ - 1];
	}
	irmax = *nr - 3;
	if (irm[i__ - 1] > irmax) {
	    irm[i__ - 1] = irmax;
	}
/* L210: */
    }
    for (i__ = 1; i__ <= 4; ++i__) {
	for (j = 1; j <= 4; ++j) {
	    ir[j + (i__ << 2) - 5] = irm[i__ - 1] + j - 1;
/* L310: */
	}
    }
    for (ilir = 1; ilir <= 4; ++ilir) {
	indt = it[ilir - 1];
	for (i__ = 1; i__ <= 4; ++i__) {
	    indr = ir[i__ + (ilir << 2) - 5];
	    xx[i__ - 1] = tdvar[indt + (indr + (tdvar_dim2 << 1)) * 
		    tdvar_dim1];
/* L400: */
	}
	for (i__ = 1; i__ <= 4; ++i__) {
	    indr = ir[i__ + (ilir << 2) - 5];
	    i__1 = *ivar;
	    for (iv = 1; iv <= i__1; ++iv) {
		var1[iv + i__ * var1_dim1] = tdvar[indt + (indr + iv * 
			tdvar_dim2) * tdvar_dim1];
/* L410: */
	    }
	}
	ii = *ivar;
	id = *ivar;
	np = 4;
	l = 1;
	inter = 1;
	lir_(pl, xx, &y[1], &var1[var1_offset], &ii, &id, &np, &l, &inter);
	i__1 = *ivar;
	for (iv = 1; iv <= i__1; ++iv) {
/* L420: */
	    var2[iv + ilir * var2_dim1] = y[iv];
	}
/* L500: */
    }
    for (i__ = 1; i__ <= 4; ++i__) {
	indt = it[i__ - 1];
/* L600: */
	xx[i__ - 1] = tlog[indt];
    }
    ii = *ivar;
    id = *ivar;
    np = 4;
    l = 1;
    inter = 1;
    lir_(tl, xx, &varout[1], &var2[var2_offset], &ii, &id, &np, &l, &inter);
    return 0;
} /* intpt_ */

