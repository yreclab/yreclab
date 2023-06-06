/* alprint.f -- translated by f2c (version 20100827).
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
    doublereal teffls[250], gls[25], fehs[25], alphas[25], pls[6250]	/* 
	    was [250][25] */, p100ls[6250]	/* was [250][25] */, t100ls[
	    6250]	/* was [250][25] */;
    logical loldnextgen;
    integer nteff, ngl, nfeh, nalpha;
} alatm01_;

#define alatm01_1 alatm01_

struct {
    doublereal glmin[250], glmax[250];
    integer iglmin[250], iglmax[250];
    doublereal tefflmin, tefflmax, glxmin, glxmax;
} alatm02_;

#define alatm02_1 alatm02_

struct {
    doublereal alatm_feh__, alatm_alpha__;
    logical laltptau100;
    integer ioatma;
} alatm03_;

#define alatm03_1 alatm03_

struct {
    doublereal dummy1, dummy2;
    char fallard[256];
    doublereal dummy3, dummy4;
} alatm04_;

#define alatm04_1 alatm04_

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static integer c__3 = 3;
static integer c__5 = 5;
static doublereal c_b59 = 10.;

/* 	Subroutine ALPRINT */
/* PURPOSE */
/* To print the internal Allard-format tables and auxilliary information provided */
/* by ALFILEIN and verified by ALTABINIT. */
/* Subroutine */ int alprint_(void)
{
    /* Format strings */
    static char fmt_900[] = "(a10,16x,a,20(5x,f6.2,5x))";
    static char fmt_910[] = "(i5,f6.0,2i4,2f6.2,1p20e16.8)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    integer s_wsle(cilist *), e_wsle(void), do_lio(integer *, integer *, char 
	    *, ftnlen), s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), 
	    e_wsfe(void);
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__, j;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 0, 0, 0, 0 };
    static cilist io___2 = { 0, 0, 0, 0, 0 };
    static cilist io___3 = { 0, 0, 0, 0, 0 };
    static cilist io___4 = { 0, 0, 0, 0, 0 };
    static cilist io___5 = { 0, 0, 0, 0, 0 };
    static cilist io___6 = { 0, 0, 0, 0, 0 };
    static cilist io___7 = { 0, 0, 0, 0, 0 };
    static cilist io___8 = { 0, 0, 0, 0, 0 };
    static cilist io___9 = { 0, 0, 0, 0, 0 };
    static cilist io___10 = { 0, 0, 0, fmt_900, 0 };
    static cilist io___12 = { 0, 0, 0, 0, 0 };
    static cilist io___13 = { 0, 0, 0, 0, 0 };
    static cilist io___14 = { 0, 0, 0, 0, 0 };
    static cilist io___16 = { 0, 0, 0, fmt_910, 0 };
    static cilist io___17 = { 0, 0, 0, 0, 0 };
    static cilist io___18 = { 0, 0, 0, 0, 0 };
    static cilist io___19 = { 0, 0, 0, 0, 0 };
    static cilist io___20 = { 0, 0, 0, fmt_910, 0 };
    static cilist io___21 = { 0, 0, 0, 0, 0 };
    static cilist io___22 = { 0, 0, 0, 0, 0 };
    static cilist io___23 = { 0, 0, 0, 0, 0 };
    static cilist io___24 = { 0, 0, 0, fmt_910, 0 };
    static cilist io___25 = { 0, 0, 0, 0, 0 };


/* Shared: ALFILEIN, ALTABINIT and ALSURFP */
/* Shared: ALTABINIT and ALSURFP */
/* Shared: ALFILEIN, */
/* ALSURFP and PARMIN */
    alatm02_1.tefflmin = alatm01_1.teffls[0] - (alatm01_1.teffls[1] - 
	    alatm01_1.teffls[0]);
    alatm02_1.tefflmax = alatm01_1.teffls[alatm01_1.nteff - 1] + (
	    alatm01_1.teffls[alatm01_1.nteff - 1] - alatm01_1.teffls[
	    alatm01_1.nteff - 2]);
    io___1.ciunit = luout_1.ishort;
    s_wsle(&io___1);
    e_wsle();
    io___2.ciunit = luout_1.ishort;
    s_wsle(&io___2);
    do_lio(&c__9, &c__1, " **************** Allard Table  ***************", (
	    ftnlen)47);
    e_wsle();
    io___3.ciunit = luout_1.ishort;
    s_wsle(&io___3);
    e_wsle();
    io___4.ciunit = luout_1.ishort;
    s_wsle(&io___4);
    do_lio(&c__9, &c__1, "nTeff= ", (ftnlen)7);
    do_lio(&c__3, &c__1, (char *)&alatm01_1.nteff, (ftnlen)sizeof(integer));
    do_lio(&c__9, &c__1, " ,nGL=", (ftnlen)6);
    do_lio(&c__3, &c__1, (char *)&alatm01_1.ngl, (ftnlen)sizeof(integer));
    e_wsle();
    io___5.ciunit = luout_1.ishort;
    s_wsle(&io___5);
    do_lio(&c__9, &c__1, "nFeH= ", (ftnlen)6);
    do_lio(&c__3, &c__1, (char *)&alatm01_1.nfeh, (ftnlen)sizeof(integer));
    do_lio(&c__9, &c__1, " ,nAlpha=", (ftnlen)9);
    do_lio(&c__3, &c__1, (char *)&alatm01_1.nalpha, (ftnlen)sizeof(integer));
    e_wsle();
    io___6.ciunit = luout_1.ishort;
    s_wsle(&io___6);
    e_wsle();
    io___7.ciunit = luout_1.ishort;
    s_wsle(&io___7);
    do_lio(&c__9, &c__1, "TEFFLmin= ", (ftnlen)10);
    do_lio(&c__5, &c__1, (char *)&alatm02_1.tefflmin, (ftnlen)sizeof(
	    doublereal));
    do_lio(&c__9, &c__1, " ,TEFFLmax= ", (ftnlen)12);
    do_lio(&c__5, &c__1, (char *)&alatm02_1.tefflmax, (ftnlen)sizeof(
	    doublereal));
    e_wsle();
    io___8.ciunit = luout_1.ishort;
    s_wsle(&io___8);
    do_lio(&c__9, &c__1, "GLXmin=", (ftnlen)7);
    do_lio(&c__5, &c__1, (char *)&alatm02_1.glxmin, (ftnlen)sizeof(doublereal)
	    );
    do_lio(&c__9, &c__1, " GLXmax=", (ftnlen)8);
    do_lio(&c__5, &c__1, (char *)&alatm02_1.glxmax, (ftnlen)sizeof(doublereal)
	    );
    e_wsle();
    io___9.ciunit = luout_1.ishort;
    s_wsle(&io___9);
    e_wsle();
    io___10.ciunit = luout_1.ishort;
    s_wsfe(&io___10);
    do_fio(&c__1, " PL @ Teff", (ftnlen)10);
    do_fio(&c__1, "GL ->", (ftnlen)5);
    i__1 = alatm01_1.ngl;
    for (j = 1; j <= i__1; ++j) {
	do_fio(&c__1, (char *)&alatm01_1.gls[j - 1], (ftnlen)sizeof(
		doublereal));
    }
    e_wsfe();
    io___12.ciunit = luout_1.ishort;
    s_wsle(&io___12);
    e_wsle();
    io___13.ciunit = luout_1.ishort;
    s_wsle(&io___13);
    do_lio(&c__9, &c__1, "PL at Teff,GL", (ftnlen)13);
    e_wsle();
    io___14.ciunit = luout_1.ishort;
    s_wsle(&io___14);
    e_wsle();
    i__1 = alatm01_1.nteff;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___16.ciunit = luout_1.ishort;
	s_wsfe(&io___16);
	do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	d__1 = pow_dd(&c_b59, &alatm01_1.teffls[i__ - 1]);
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&alatm02_1.iglmin[i__ - 1], (ftnlen)sizeof(
		integer));
	do_fio(&c__1, (char *)&alatm02_1.iglmax[i__ - 1], (ftnlen)sizeof(
		integer));
	do_fio(&c__1, (char *)&alatm02_1.glmin[i__ - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&alatm02_1.glmax[i__ - 1], (ftnlen)sizeof(
		doublereal));
	i__2 = alatm01_1.ngl;
	for (j = 1; j <= i__2; ++j) {
	    do_fio(&c__1, (char *)&alatm01_1.pls[i__ + j * 250 - 251], (
		    ftnlen)sizeof(doublereal));
	}
	e_wsfe();
    }
    io___17.ciunit = luout_1.ishort;
    s_wsle(&io___17);
    e_wsle();
    io___18.ciunit = luout_1.ishort;
    s_wsle(&io___18);
    do_lio(&c__9, &c__1, "PL at Tau=100", (ftnlen)13);
    e_wsle();
    io___19.ciunit = luout_1.ishort;
    s_wsle(&io___19);
    e_wsle();
    i__1 = alatm01_1.nteff;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___20.ciunit = luout_1.ishort;
	s_wsfe(&io___20);
	do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	d__1 = pow_dd(&c_b59, &alatm01_1.teffls[i__ - 1]);
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&alatm02_1.iglmin[i__ - 1], (ftnlen)sizeof(
		integer));
	do_fio(&c__1, (char *)&alatm02_1.iglmax[i__ - 1], (ftnlen)sizeof(
		integer));
	do_fio(&c__1, (char *)&alatm02_1.glmin[i__ - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&alatm02_1.glmax[i__ - 1], (ftnlen)sizeof(
		doublereal));
	i__2 = alatm01_1.ngl;
	for (j = 1; j <= i__2; ++j) {
	    do_fio(&c__1, (char *)&alatm01_1.p100ls[i__ + j * 250 - 251], (
		    ftnlen)sizeof(doublereal));
	}
	e_wsfe();
    }
    io___21.ciunit = luout_1.ishort;
    s_wsle(&io___21);
    e_wsle();
    io___22.ciunit = luout_1.ishort;
    s_wsle(&io___22);
    do_lio(&c__9, &c__1, "TL at Tau=100", (ftnlen)13);
    e_wsle();
    io___23.ciunit = luout_1.ishort;
    s_wsle(&io___23);
    e_wsle();
    i__1 = alatm01_1.nteff;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___24.ciunit = luout_1.ishort;
	s_wsfe(&io___24);
	do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	d__1 = pow_dd(&c_b59, &alatm01_1.teffls[i__ - 1]);
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&alatm02_1.iglmin[i__ - 1], (ftnlen)sizeof(
		integer));
	do_fio(&c__1, (char *)&alatm02_1.iglmax[i__ - 1], (ftnlen)sizeof(
		integer));
	do_fio(&c__1, (char *)&alatm02_1.glmin[i__ - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&alatm02_1.glmax[i__ - 1], (ftnlen)sizeof(
		doublereal));
	i__2 = alatm01_1.ngl;
	for (j = 1; j <= i__2; ++j) {
	    do_fio(&c__1, (char *)&alatm01_1.t100ls[i__ + j * 250 - 251], (
		    ftnlen)sizeof(doublereal));
	}
	e_wsfe();
    }
    io___25.ciunit = luout_1.ishort;
    s_wsle(&io___25);
    e_wsle();
    return 0;
} /* alprint_ */

