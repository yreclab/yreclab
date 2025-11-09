/* rtab.f -- translated by f2c (version 20061008).
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
    logical ldebug, lcorr, lmilne, ltrack, lstpch;
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
    /* Subroutine */ void s_stop(char *, ftnlen);

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
/* KC 2025-05-30 fixed "Shared DO termination label" */
/*       DO 10 J = 1, NR */
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
/* L11: */
	}
/* L10: */
    }
    return 0;
/* 1001  FORMAT(I5,E16.8) */
/* 1002  FORMAT(5E16.8) */
/* 1011  FORMAT(I5,1PE16.8) */
/* 1012  FORMAT(1P5E16.8) */
/* 9001  FORMAT(' ERROR IN RTAB. TOO SMALL PARAMETERS: ', */
/*      1 /' NT,NR,NTM,NRM = ',4I5) */
/* 9011  FORMAT(' ERROR IN RTAB. WRONG DENSITY CONSTRUCTION: ', */
/*      1 /' N,NR,NRR = ',3I5) */
} /* rtab_ */

