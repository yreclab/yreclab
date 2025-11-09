/* mhdpx.f -- translated by f2c (version 20061008).
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
    doublereal varmhd[25];
} mhdout_;

#define mhdout_1 mhdout_

struct {
    logical ldebug, lcorr, lmilne, ltrack, lstpch;
} ccout2_;

#define ccout2_1 ccout2_

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;

/* -------------------------    GROUP: SR_PX    ------------------------------- */

/*     MHD INTERPOLATION PACKAGE */
/*     PRESSURE AS ARGUMENT INTERPOLATION IN X, Z FIXED */

/*     INPUT   PGL = LOG10 (GAS PRESSURE [DYN/CM2]) */
/*             TL  = LOG10 (TEMPERATURE [K]) */
/*             XC  = HYDROGEN ABUNDANCE (BY MASS) */

/*     OUTPUT  RL  = LOG10 (DENSITY [G/CM3])        : ARGUMENT */
/*             OTHER (SEE SEPARATE INSTRUCTIONS)    : COMMON/MHDOUT/... */

/*     ERROR   IERR = 1 SIGNALS PGL,TL OUTSIDE THE DOMAIN OF TABLES */
/*             (OTHERWISE IERR = 0). */


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MHDPX */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int mhdpx_(doublereal *pl, doublereal *tl, doublereal *xc, 
	doublereal *rl)
{
    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    extern /* Subroutine */ int mhdpx1_(doublereal *, doublereal *, 
	    doublereal *);

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 0, 0, 0, 0 };
    static cilist io___2 = { 0, 0, 0, 0, 0 };


/*     S/R MHDSTX MUST BE CALLED IN MAIN. */
/*     CALLS VARIABLE-X VERSION */
    mhdpx1_(pl, tl, xc);
/*     IERR = 0 */
    *rl = mhdout_1.varmhd[0];
    return 0;
/*   999 CONTINUE */
    io___1.ciunit = luout_1.iowr;
    s_wsle(&io___1);
    do_lio(&c__9, &c__1, "ERROR (MHD): OUT OF TABLE RANGE. RETURN", (ftnlen)
	    39);
    e_wsle();
    io___2.ciunit = luout_1.ishort;
    s_wsle(&io___2);
    do_lio(&c__9, &c__1, "ERROR (MHD): OUT OF TABLE RANGE. RETURN", (ftnlen)
	    39);
    e_wsle();
    s_stop("", (ftnlen)0);
    return 0;
} /* mhdpx_ */

