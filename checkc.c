/* checkc.f -- translated by f2c (version 20100827).
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
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal yenv, y3env;
} comp2_;

#define comp2_1 comp2_

struct {
    doublereal dtdif, djok;
    integer itdif1, itdif2;
} difus_;

#define difus_1 difus_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal hamu[5000], cp[5000], delm[5000], delam[5000], delrm[5000], 
	    sesum[5000], om[5000], sqdt[5000], thdif[5000], svel[5000], visc[
	    5000], epsm[5000];
} mdphy_;

#define mdphy_1 mdphy_

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
} oldmod_;

#define oldmod_1 oldmod_

/* Table of constant values */

static integer c__1 = 1;

/* $$$$$$ */
/* Subroutine */ int checkc_(doublereal *hcomp, integer *it, logical *lprt, 
	integer *m, doublereal *dt, integer *iredo, logical *lok, logical *
	lredo)
{
    /* Initialized data */

    static doublereal atomwt[4] = { 1.007825,4.002603,12.,3.01603 };

    /* Format strings */
    static char fmt_1010[] = "(1x,39(\002>\002),39(\002>\002)/\002 ERROR IN "
	    "SR CHECKC\002/\002 ANOMALOUS COMP NUMBER\002,i2,\002 IN ZONE\002"
	    ",i5,\002 ABUNDANCE \002,1pe12.3/\002 3 ATTEMPTS AT TIMESTEP CUTT"
	    "ING FAILED\002/\002RUN STOPPED\002)";
    static char fmt_1015[] = "(\002 ERROR IN SR CHECKC\002/\002 TIMESTEP CUT"
	    " NUMBER \002,i2,\002 DUE TO ANOMALOUS COMP NUMBER\002,i2,\002 IN"
	    " ZONE\002,i5,\002 ABUNDANCE \002,1pe12.3)";
    static char fmt_50[] = "(\002 MAX FRAC.COMP.CHANGE\002,1pe12.3,\002 SPEC"
	    "IES\002,i2,\002 AT PT.\002,i5)";
    static char fmt_60[] = "(5x,\002NEW SURFACE LI\002,1pe14.4,\002OLD VALU"
	    "E\002,e14.4)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j;
    static doublereal dfx1, dfx2, dfx3, dfx4, amu2, emu2, delc;
    static integer jend;
    static doublereal cmin, temp;
    static integer icmax, jcmax;
    static doublereal dcomp;

    /* Fortran I/O blocks */
    static cilist io___5 = { 0, 6, 0, fmt_1010, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_1010, 0 };
    static cilist io___7 = { 0, 6, 0, fmt_1015, 0 };
    static cilist io___8 = { 0, 0, 0, fmt_1015, 0 };
    static cilist io___14 = { 0, 6, 0, fmt_50, 0 };
    static cilist io___15 = { 0, 6, 0, fmt_60, 0 };


    /* Parameter adjustments */
    hcomp -= 16;

    /* Function Body */
/*  SR CHECKC PERFORMS SEVERAL FUNCTIONS. */
/*  FIRST, IT CHECKS FOR ANOMALOUS COMPOSITIONS. */
/*  IF THEY ARE ENCOUNTERED, THE TIMESTEP IS CUT. */
/*  IT ALSO COMPUTES THE CHANGE IN MEAN MOLECULAR WEIGHT DUE TO */
/*  COMPOSITION DIFFUSION. */

/*  INPUT VARIABLES: */
/*  HCOMP :  MASS FRACTION OF ALL THE SPECIES BEING TRACKED AS A FUNCTION */
/*     OF MASS. */
/*  IT : THE PROGRAM ITERATES FOR THE DIFFUSION COEFFICIENTS; IT IS THE */
/*     ITERATION NUMBER. */
/*  ITDIF2 : USER PARAMETER - MAXIMUM NUMBER OF ITERATIONS. */
/*  IREDO : NUMBER OF TIMES DIFFUSION TIMESTEP HAS BEEN CUT. */
/*  LOK : FLAG SET T IF DIFFUSION COEFFICEINTS HAVE CONVERGED. */
/*  LPRT : FLAG SET T IF OUTPUT ABOUT CHECMICAL DIFFUSION DESIRED. */
/*  M : NUMBER OF MODEL POINTS. */

/*  OUTPUT VARIABLES: */
/*  DT : DIFFUSION TIMESTEP, WHICH CAN BE CUT IF ERRORS IN THE COMPOSITION */
/*     DIFFUSION ARE DISCOVERED. */
/*  HAMU : NEW RUN OF MEAN MOLECULAR WEIGHT. */
/*  IREDO : NUMBER OF TIMES DIFFUSION TIMESTEP HAS BEEN CUT. */
/*  LOK : SET F IF ERRORS IN COMPOSITION DIFFUSION DISCOVERED. */
/*  LREDO : SET T IF ERRORS IN COMPOSITION DIFFUSION DISCOVERED. */

/*  CHECK FOR ANOMALOUS COMPOSITIONS. */
/*  PRIOR TO THE LAST ITERATION, ONLY DIFFUSION OF H,HE,HE3 PERFORMED. */
/*  FIND NUMBER OF SPECIES BEING DIFFUSED. */
    if (*it == difus_1.itdif2) {
	jend = 11;
    } else {
	jend = 4;
    }
    *lredo = FALSE_;
    i__1 = jend;
    for (j = 1; j <= i__1; ++j) {
/*  HCOMP(3,...) IS Z, WHICH IS NOT DIFFUSED AS A UNIT. */
	if (j == 3) {
	    goto L20;
	}
	i__2 = *m - 1;
	for (i__ = 2; i__ <= i__2; ++i__) {
	    if (hcomp[j + i__ * 15] < 0. || hcomp[j + i__ * 15] > 1.) {
/*  SOME SPECIES CAN BE MIXED INTO REGIONS WHERE THEY ARE DESTROYED VERY */
/*  QUICKLY.  THE INTERPLAY BETWEEN DIFFUSION AND NUCLEAR BURNING CAN LEAD */
/*  TO SMALL NEGATIVE ABUNDANCES.  THEREFORE, ZERO OUT THESE SMALL NUMBERS */
/*  RATHER THAN STOPPING THE CODE. */
		if ((d__1 = hcomp[j + i__ * 15], abs(d__1)) < hcomp[j + *m * 
			15] * 1e-5) {
		    if (i__ == 1 || i__ == *m) {
			hcomp[j + i__ * 15] = 0.;
		    } else {
/* Computing MAX */
			d__1 = 0., d__2 = (hcomp[j + (i__ + 1) * 15] + hcomp[
				j + (i__ - 1) * 15]) * .5;
			hcomp[j + i__ * 15] = max(d__1,d__2);
		    }
		    goto L10;
		}
		++(*iredo);
		if (*iredo > 3) {
		    s_wsfe(&io___5);
		    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&hcomp[j + i__ * 15], (ftnlen)
			    sizeof(doublereal));
		    e_wsfe();
		    io___6.ciunit = luout_1.imodpt;
		    s_wsfe(&io___6);
		    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&hcomp[j + i__ * 15], (ftnlen)
			    sizeof(doublereal));
		    e_wsfe();
		    s_stop("", (ftnlen)0);
		} else {
		    *lredo = TRUE_;
		    *lok = FALSE_;
		    *dt *= .5;
		    s_wsfe(&io___7);
		    do_fio(&c__1, (char *)&(*iredo), (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&hcomp[j + i__ * 15], (ftnlen)
			    sizeof(doublereal));
		    e_wsfe();
		    io___8.ciunit = luout_1.imodpt;
		    s_wsfe(&io___8);
		    do_fio(&c__1, (char *)&(*iredo), (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&hcomp[j + i__ * 15], (ftnlen)
			    sizeof(doublereal));
		    e_wsfe();
		    goto L100;
		}
	    }
L10:
	    ;
	}
L20:
	;
    }
    if (*it == difus_1.itdif2 && *lprt) {
/*  FIND MAXIMUM FRACTIONAL CHANGE IN COMPOSITION AND PRINT IT OUT. */
	delc = 0.;
	icmax = 0;
	jcmax = 0;
	i__1 = jend;
	for (j = 1; j <= i__1; ++j) {
	    if (j == 3) {
		goto L40;
	    }
/* CMIN IS USED TO GUARD AGAINST DIVISION BY ZERO. */
/* Computing MAX */
	    d__1 = hcomp[j + *m * 15] * 1e-6;
	    cmin = max(d__1,1e-20);
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		if (oldmod_1.hcompp[j + i__ * 15 - 16] < cmin) {
		    goto L30;
		}
		dcomp = (hcomp[j + i__ * 15] - oldmod_1.hcompp[j + i__ * 15 - 
			16]) / oldmod_1.hcompp[j + i__ * 15 - 16];
		if (abs(dcomp) > abs(delc)) {
		    delc = dcomp;
		    icmax = i__;
		    jcmax = j;
		}
L30:
		;
	    }
L40:
	    ;
	}
	s_wsfe(&io___14);
	do_fio(&c__1, (char *)&delc, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&jcmax, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&icmax, (ftnlen)sizeof(integer));
	e_wsfe();
	if (flag_1.lexcom) {
	    s_wsfe(&io___15);
	    do_fio(&c__1, (char *)&hcomp[*m * 15 + 14], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&oldmod_1.hcompp[*m * 15 - 2], (ftnlen)
		    sizeof(doublereal));
	    e_wsfe();
	}
    }
/*  FIND NEW RUN OF MEAN MOLECULAR WEIGHT ASSUMING FULLY IONIZED GAS. */
/*  AMUENV IS(1/MEAN MOLECULAR WEIGHT PER ION OF THE SURFACE MIXTURE.) */
/*  CORRECTION FOR PARTIAL IONIZATION NEEDED IN MASSIVE STARS. */
    if (*it > 1) {
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    dfx1 = hcomp[i__ * 15 + 1] - comp_1.xenv;
	    dfx2 = hcomp[i__ * 15 + 2] - comp2_1.yenv;
	    dfx3 = hcomp[i__ * 15 + 3] - comp_1.zenv;
	    dfx4 = hcomp[i__ * 15 + 4] - comp2_1.y3env;
	    temp = comp_1.amuenv + dfx1 / atomwt[0] + dfx2 / atomwt[1] + dfx3 
		    / atomwt[2] + dfx4 / atomwt[3];
	    amu2 = 1. / temp;
	    temp = hcomp[i__ * 15 + 1] / atomwt[0] + (hcomp[i__ * 15 + 4] / 
		    atomwt[3] + hcomp[i__ * 15 + 2] / atomwt[1]) * 2. + hcomp[
		    i__ * 15 + 3] * .5;
	    emu2 = 1. / temp;
	    mdphy_1.hamu[i__ - 1] = amu2 * emu2 / (amu2 + emu2);
/* L90: */
	}
    }
L100:
    return 0;
} /* checkc_ */

