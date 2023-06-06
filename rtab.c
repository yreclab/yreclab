/* rtab.f -- translated by f2c (version 20100827).
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

/* Table of constant values */

static integer c__1 = 1;

/* ------------------------    GROUP: SR_ALL   ------------------------------- */


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* RTAB */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int rtab_(integer *ir, integer *ntm, integer *nrm, integer *
	ivar, integer *nt, integer *nr, doublereal *tl, doublereal *tdvar)
{
    /* System generated locals */
    integer tdvar_dim1, tdvar_dim2, tdvar_offset, i__1, i__2, i__3;

    /* Builtin functions */
    integer s_rsue(cilist *), do_uio(integer *, char *, ftnlen), e_rsue(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer j, n, iv, nrr;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 0, 0, 0, 0 };
    static cilist io___5 = { 0, 0, 0, 0, 0 };


/*     NT IS INPUT; NR,TL,TDVAR ARE OUTPUT */
    /* Parameter adjustments */
    --tl;
    tdvar_dim1 = *ntm;
    tdvar_dim2 = *nrm;
    tdvar_offset = 1 + tdvar_dim1 * (1 + tdvar_dim2);
    tdvar -= tdvar_offset;

    /* Function Body */
    i__1 = *nt;
    for (n = 1; n <= i__1; ++n) {
/*     READ(IR,1001) NRR,TL(N) */
	io___2.ciunit = *ir;
	s_rsue(&io___2);
	do_uio(&c__1, (char *)&nrr, (ftnlen)sizeof(integer));
	do_uio(&c__1, (char *)&tl[n], (ftnlen)sizeof(doublereal));
	e_rsue();
	if (n == 1) {
	    *nr = nrr;
	}
/*     CHECK LIMITS AND NUMBER OF DENSITIY POINTS OF TABLE */
	if (*nt > *ntm || *nr > *nrm) {
	    s_stop("", (ftnlen)0);
	}
	if (n > 1 && nrr != *nr) {
	    s_stop("", (ftnlen)0);
	}
/*     END CHECK .................................................... */
	i__2 = *nr;
	for (j = 1; j <= i__2; ++j) {
/*     READ(IR,1002) (TDVAR(N,J,IV),IV=1,IVAR) */
	    io___5.ciunit = *ir;
	    s_rsue(&io___5);
	    i__3 = *ivar;
	    for (iv = 1; iv <= i__3; ++iv) {
		do_uio(&c__1, (char *)&tdvar[n + (j + iv * tdvar_dim2) * 
			tdvar_dim1], (ftnlen)sizeof(doublereal));
	    }
	    e_rsue();
/* L10: */
	}
    }
    return 0;
/* L1001: */
/* L1002: */
/* L1011: */
/* L1012: */
/* L9001: */
/* L9011: */
} /* rtab_ */

