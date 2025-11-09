/* altabinit.f -- translated by f2c (version 20061008).
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
    doublereal dummy1, dummy2, dummy3, dummy4;
} alatm04_;

#define alatm04_1 alatm04_

struct {
    doublereal al_tefflmin__, al_tefflmax__;
} alatm05_;

#define alatm05_1 alatm05_

/* Table of constant values */

static integer c__1 = 1;
static doublereal c_b10 = 10.;
static integer c__9 = 9;

/*      Subroutine ALTABINIT */
/* PURPOSE */
/* To analyze the internal Allard-format tables provided by ALFILEIN, verifying them */
/* and creating needed additoinal tables and elements. */
/* Several steps are taken: */
/* 1. Find the minimum (TEFFLmin) and maximum (TEFFLmax) permissable values of TEFFL. These are */
/*    one row's width below the bottom and above the top of the table. Because the first level */
/*    of interpolation is in GL, only a single minimum and maximum value of TEFFL are needed. */
/* 2. For each row in GL, find the index of the smallest element (iGLmin) and the index of the */
/*    largest element (iGLmax). There is one pair of these for each TEFFL. */
/* 3. For each row in GL, find the the minimum (GLmin) and maximum (GLmax) permissable value of */
/*    GL. These are one column's width less than the row minimum in GL and one column's width */
/*    greater than the column maximum. There is one pair of these for each TEFFL. */
/* 4. Validate the table. (a) Ensure that there are no invalid elements inside the table, i.e., */
/*    no invalid element between the row's iGLmin and iGLmax. This check is made for every TEFFL. */
/*    (b) Ensure that every row has at least 4 valid entries and that there are at least 4 columns. */
/* Subroutine */ int altabinit_(void)
{
    /* Format strings */
    static char fmt_900[] = "(2a,f5.0,f7.2)";
    static char fmt_910[] = "(a,i3)";
    static char fmt_920[] = "(2a,2i4,2x,3f7.2)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen);
    double pow_dd(doublereal *, doublereal *);
    integer e_wsfe(void), s_wsle(cilist *), e_wsle(void), do_lio(integer *, 
	    integer *, char *, ftnlen);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j;
    static logical lbadtable;
    static integer j1, j2;
    extern /* Subroutine */ int alprint_(void);

    /* Fortran I/O blocks */
    static cilist io___6 = { 0, 0, 0, fmt_900, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_910, 0 };
    static cilist io___8 = { 0, 0, 0, fmt_920, 0 };
    static cilist io___9 = { 0, 6, 0, 0, 0 };
    static cilist io___10 = { 0, 6, 0, 0, 0 };
    static cilist io___11 = { 0, 6, 0, 0, 0 };
    static cilist io___12 = { 0, 0, 0, 0, 0 };
    static cilist io___13 = { 0, 0, 0, 0, 0 };
    static cilist io___14 = { 0, 0, 0, 0, 0 };


/* Shared: ALFILEIN, ALTABINIT and ALSURFP */
/* Shared: ALTABINIT and ALSURFP */
/* MHP 8/25 Removed character file names from common block */
/* Shared: ALFILEIN, */
/* ALSURFP and PARMIN */
/* 1. Find the minimum (TEFFLmin) and maximum (TEFFLmax) permissable values of TEFFL. These are */
/*    one row's width below the bottom and above the top of the table. Because the first level */
/*    of interpolation is in GL, only a single minimum and maximum value of TEFFL are needed. */
    alatm05_1.al_tefflmin__ = alatm01_1.teffls[0];
    alatm05_1.al_tefflmax__ = alatm01_1.teffls[alatm01_1.nteff - 1];
    alatm02_1.tefflmin = alatm01_1.teffls[0] - (alatm01_1.teffls[1] - 
	    alatm01_1.teffls[0]);
    alatm02_1.tefflmax = alatm01_1.teffls[alatm01_1.nteff - 1] + (
	    alatm01_1.teffls[alatm01_1.nteff - 1] - alatm01_1.teffls[
	    alatm01_1.nteff - 2]);
/* 2. For each row in GL, find the index of the smallest element (iGLmin) and the index of the */
/*    largest element (iGLmax). There is one pair of these for each TEFFL. */
    i__1 = alatm01_1.nteff;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = alatm01_1.ngl;
	for (j = 1; j <= i__2; ++j) {
	    if (alatm01_1.pls[i__ + j * 250 - 251] > -998.) {
		alatm02_1.iglmin[i__ - 1] = j;
		goto L100;
	    }
	}
L100:
	for (j = alatm01_1.ngl; j >= 1; --j) {
	    if (alatm01_1.pls[i__ + j * 250 - 251] > -998.) {
		alatm02_1.iglmax[i__ - 1] = j;
		goto L110;
	    }
	}
L110:
	;
    }
/* 3. For each row in GL, find the the minimum (GLmin) and maximum (GLmax) permissable value of */
/*    GL. These are one column's width less than the row minimum in GL and one column's width */
/*    greater than the column maximum. There is one pair of these for each TEFFL. */
    alatm02_1.glxmin = 999.;
    alatm02_1.glxmax = -999.;
    i__1 = alatm01_1.nteff;
    for (i__ = 1; i__ <= i__1; ++i__) {
	j1 = alatm02_1.iglmin[i__ - 1];
	j2 = alatm02_1.iglmax[i__ - 1];
	alatm02_1.glmin[i__ - 1] = alatm01_1.gls[j1 - 1] - (alatm01_1.gls[j1] 
		- alatm01_1.gls[j1 - 1]) * 4.;
	if (alatm02_1.glmin[i__ - 1] < alatm02_1.glxmin) {
	    alatm02_1.glxmin = alatm02_1.glmin[i__ - 1];
	}
	alatm02_1.glmax[i__ - 1] = alatm01_1.gls[j2 - 1] + (alatm01_1.gls[j2 
		- 1] - alatm01_1.gls[j2 - 2]);
	if (alatm02_1.glmax[i__ - 1] > alatm02_1.glxmax) {
	    alatm02_1.glxmax = alatm02_1.glmax[i__ - 1];
	}
    }
/* 4. Validate the table. (a) Ensure that there are no invalid elements inside the table, i.e., */
/*    no invalid element between the row's iGLmin and iGLmax. This check is made for every TEFFL. */
    lbadtable = FALSE_;
    i__1 = alatm01_1.nteff;
    for (i__ = 1; i__ <= i__1; ++i__) {
	j1 = alatm02_1.iglmin[i__ - 1];
	j2 = alatm02_1.iglmax[i__ - 1];
	i__2 = j2;
	for (j = j1; j <= i__2; ++j) {
	    if (alatm01_1.pls[i__ + j * 250 - 251] < -998.) {
		lbadtable = TRUE_;
		io___6.ciunit = luout_1.ishort;
		s_wsfe(&io___6);
		do_fio(&c__1, "ALTABINIT: Bad input Allard Table: ", (ftnlen)
			35);
		do_fio(&c__1, "TEFF, GL: ", (ftnlen)10);
		d__1 = pow_dd(&c_b10, &alatm01_1.teffls[i__ - 1]);
		do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&alatm01_1.gls[j - 1], (ftnlen)sizeof(
			doublereal));
		e_wsfe();
	    }
	}
    }
/*    (b) Ensure that every row has at least 4 valid entries and that there are at least 4 columns. */
    if (alatm01_1.nteff < 4) {
	lbadtable = TRUE_;
	io___7.ciunit = luout_1.ishort;
	s_wsfe(&io___7);
	do_fio(&c__1, "ALTABINIT: Bad input Allard Table: ", (ftnlen)35);
	do_fio(&c__1, "Less than 4 rows: nTeff = ", (ftnlen)26);
	do_fio(&c__1, (char *)&alatm01_1.nteff, (ftnlen)sizeof(integer));
	e_wsfe();
    }
    i__1 = alatm01_1.nteff;
    for (i__ = 1; i__ <= i__1; ++i__) {
	j1 = alatm02_1.iglmin[i__ - 1];
	j2 = alatm02_1.iglmax[i__ - 1];
	if (j2 - j1 + 1 < 4) {
	    lbadtable = TRUE_;
	    io___8.ciunit = luout_1.ishort;
	    s_wsfe(&io___8);
	    do_fio(&c__1, "ALTABINIT: Bad input Allard Table: ", (ftnlen)35);
	    do_fio(&c__1, "Row with less that 4 elements: i,#,Teff,GLMin,GLm"
		    "ax: ", (ftnlen)53);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    i__2 = j2 - j1 + 1;
	    do_fio(&c__1, (char *)&i__2, (ftnlen)sizeof(integer));
	    d__1 = pow_dd(&c_b10, &alatm01_1.teffls[i__ - 1]);
	    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&alatm02_1.glmin[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&alatm02_1.glmax[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    e_wsfe();
	}
    }
    if (lbadtable) {
	goto L9999;
    }
/* If bad table, go to error exit */
    return 0;
/* If good table, return */
L9999:
    s_wsle(&io___9);
    e_wsle();
    s_wsle(&io___10);
    do_lio(&c__9, &c__1, "******** ALTABINIT: Program Terminated ********", (
	    ftnlen)47);
    e_wsle();
    s_wsle(&io___11);
    e_wsle();
    io___12.ciunit = luout_1.ishort;
    s_wsle(&io___12);
    e_wsle();
    io___13.ciunit = luout_1.ishort;
    s_wsle(&io___13);
    do_lio(&c__9, &c__1, "******** ALTABINIT: Program Terminated ********", (
	    ftnlen)47);
    e_wsle();
    io___14.ciunit = luout_1.ishort;
    s_wsle(&io___14);
    e_wsle();
    alprint_();
    s_stop("", (ftnlen)0);
    return 0;
} /* altabinit_ */

