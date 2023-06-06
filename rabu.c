/* rabu.f -- translated by f2c (version 20100827).
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



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* RABU */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int rabu_(integer *ir, integer *nchem0, integer *nchem, 
	doublereal *atwt, doublereal *abun, doublereal *abfrcs, doublereal *
	gasmu)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_rsue(cilist *), do_uio(integer *, char *, ftnlen), e_rsue(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer ic;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 0, 0, 0, 0 };


/*     NCHEM,ATWT,ABUN,ABFRCS ARE OUTPUT */
/*     READ(IR,99) NCHEM,(ATWT(IC),ABUN(IC),ABFRCS(IC), */
/*    1       IC=1,NCHEM),GASMU */
    /* Parameter adjustments */
    --abfrcs;
    --abun;
    --atwt;

    /* Function Body */
    io___1.ciunit = *ir;
    s_rsue(&io___1);
    do_uio(&c__1, (char *)&(*nchem), (ftnlen)sizeof(integer));
    i__1 = *nchem;
    for (ic = 1; ic <= i__1; ++ic) {
	do_uio(&c__1, (char *)&atwt[ic], (ftnlen)sizeof(doublereal));
	do_uio(&c__1, (char *)&abun[ic], (ftnlen)sizeof(doublereal));
	do_uio(&c__1, (char *)&abfrcs[ic], (ftnlen)sizeof(doublereal));
    }
    do_uio(&c__1, (char *)&(*gasmu), (ftnlen)sizeof(doublereal));
    e_rsue();
    if (*nchem0 < *nchem) {
	s_stop("", (ftnlen)0);
    }
    return 0;
/* L99: */
/* L9009: */
} /* rabu_ */

