/* op95ztab.f -- translated by f2c (version 20061008).
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
    doublereal cappa[13300]	/* was [10][70][19] */, ztab;
} llot95_;

#define llot95_1 llot95_

struct {
    doublereal tgr[70], xxg[10], r0gr[19], zzg[13], cappa2[167580]	/* 
	    was [126][70][19] */;
    integer numxm[13], nz[13];
} llot95a_;

#define llot95a_1 llot95a_

/* Table of constant values */

static integer c__1 = 1;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     OP95ZTAB */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int op95ztab_(doublereal *z__)
{
    /* Format strings */
    static char fmt_5[] = "(1x,\002DESIRED Z\002,f10.6,\002OUTSIDE OP95 TABL"
	    "E RANGE\002/\002 RUN STOPPED\002)";

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal a[4], b[4];
    static integer i__, j, k, i1, i2, i3, i4;
    static doublereal bb[4];
    static integer idz, idz2;
    extern /* Subroutine */ int intrp2_(doublereal *, doublereal *, 
	    doublereal *);

    /* Fortran I/O blocks */
    static cilist io___3 = { 0, 6, 0, fmt_5, 0 };


/* MHP 7/98 COMPUTE OPACITY TABLE AT FIXED Z FROM THE FULL OP95 SET */
/* GRID ENTRIES FOR TEMPERATURE, ABUNDANCE (X), AND RHO/T6**3 */
/* OPACITY AS A FUNCTION OF X, T, AND RHO/T6**3 */
/* FULL SET OF TABLES: OPACITY AS A FUNCTION OF Z AND X, T, RHO/T6**3 */
/* TABLES ARE INCREMENTED IN SETS OF NZ*NX.  SO THE TABLES FOR THE */
/* THIRD METAL ABUNDANCE (3 X 10**-4)BEGIN AT TABLE 21 AND END AT TABLE 30. */
/* FOR THE HIGH VALUES OF Z, THE NUMBER OF X TABLES IS NOT THE SAME (I.E. */
/* X<0.9 FOR Z=0.1). */
/* FOR EACH COMPOSITION A FULL GRID IN (T,RHO/T6**3) IS RETAINED. */
    llot95_1.ztab = *z__;
/*  FIND 4 NEAREST TABLES IN Z TO DESIRED VALUE. */
    for (i__ = 3; i__ <= 12; ++i__) {
	if (llot95a_1.zzg[i__ - 1] >= *z__) {
	    idz = i__ - 2;
	    goto L10;
	}
    }
/* DESIRED Z > 0.1D0; STOP */
    s_wsfe(&io___3);
    do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_stop("", (ftnlen)0);
L10:
/*  FIND INTERPOLATION FACTORS IN Z. */
    for (i__ = 1; i__ <= 4; ++i__) {
	a[i__ - 1] = llot95a_1.zzg[idz + i__ - 2];
    }
    intrp2_(a, b, z__);
/*  FOR X TABLES 1-8, ALL VALUES OF Z PRESENT; PERFORM INTERPOLATION. */
    for (i__ = 1; i__ <= 8; ++i__) {
/* INDICES FOR 4 DESIRED COMPOSITIONS. */
	i1 = llot95a_1.nz[idz - 1] + i__;
	i2 = llot95a_1.nz[idz] + i__;
	i3 = llot95a_1.nz[idz + 1] + i__;
	i4 = llot95a_1.nz[idz + 2] + i__;
	for (j = 1; j <= 70; ++j) {
	    for (k = 1; k <= 19; ++k) {
		llot95_1.cappa[i__ + (j + k * 70) * 10 - 711] = b[0] * 
			llot95a_1.cappa2[i1 + (j + k * 70) * 126 - 8947] + b[
			1] * llot95a_1.cappa2[i2 + (j + k * 70) * 126 - 8947] 
			+ b[2] * llot95a_1.cappa2[i3 + (j + k * 70) * 126 - 
			8947] + b[3] * llot95a_1.cappa2[i4 + (j + k * 70) * 
			126 - 8947];
	    }
	}
    }
/*  FOR X TABLES 9 AND 10, HIGH VALUES OF Z ARE NOT PRESENT */
/*  OMIT TABLE 9 (X=0.95) IF DESIRED Z > 0.04 */
    if (*z__ >= .04) {
	goto L20;
    }
/*  OTHERWISE, CHECK TO ENSURE THAT THE 4 Z TABLES USED HAVE Z < 0.04 */
/*  ADJUST INTERPOLATION FACTORS IF NEEDED */
    if (llot95a_1.zzg[idz + 2] > .04) {
	idz2 = 7;
	for (i__ = 1; i__ <= 4; ++i__) {
	    a[i__ - 1] = llot95a_1.zzg[idz2 + i__ - 2];
	}
	intrp2_(a, bb, z__);
    } else {
	idz2 = idz;
	for (i__ = 1; i__ <= 4; ++i__) {
	    bb[i__ - 1] = b[i__ - 1];
	}
    }
    i1 = llot95a_1.nz[idz2 - 1] + 9;
    i2 = llot95a_1.nz[idz2] + 9;
    i3 = llot95a_1.nz[idz2 + 1] + 9;
    i4 = llot95a_1.nz[idz2 + 2] + 9;
    for (j = 1; j <= 70; ++j) {
	for (k = 1; k <= 19; ++k) {
	    llot95_1.cappa[(j + k * 70) * 10 - 702] = bb[0] * 
		    llot95a_1.cappa2[i1 + (j + k * 70) * 126 - 8947] + bb[1] *
		     llot95a_1.cappa2[i2 + (j + k * 70) * 126 - 8947] + bb[2] 
		    * llot95a_1.cappa2[i3 + (j + k * 70) * 126 - 8947] + bb[3]
		     * llot95a_1.cappa2[i4 + (j + k * 70) * 126 - 8947];
	}
    }
L20:
/*  OMIT TABLE 10 (X = 1-Z) IF DESIRED Z >= 0.1 */
    if (*z__ >= .1) {
	goto L30;
    }
/*  CHECK TO ENSURE THAT Z=0.1 TABLE IS NOT ONE OF THE 4 TABLES; ADJUST */
/*  INTERPOLATION FACTORS IF NEEDED. */
    if (llot95a_1.zzg[idz + 2] >= .1) {
	idz2 = 9;
	for (i__ = 1; i__ <= 4; ++i__) {
	    a[i__ - 1] = llot95a_1.zzg[idz2 + i__ - 2];
	}
	intrp2_(a, bb, z__);
    } else {
	idz2 = idz;
	for (i__ = 1; i__ <= 4; ++i__) {
	    bb[i__ - 1] = b[i__ - 1];
	}
    }
L30:
    i1 = llot95a_1.nz[idz2 - 1] + 10;
    i2 = llot95a_1.nz[idz2] + 10;
    i3 = llot95a_1.nz[idz2 + 1] + 10;
    i4 = llot95a_1.nz[idz2 + 2] + 10;
    for (j = 1; j <= 70; ++j) {
	for (k = 1; k <= 19; ++k) {
	    llot95_1.cappa[(j + k * 70) * 10 - 701] = bb[0] * 
		    llot95a_1.cappa2[i1 + (j + k * 70) * 126 - 8947] + bb[1] *
		     llot95a_1.cappa2[i2 + (j + k * 70) * 126 - 8947] + bb[2] 
		    * llot95a_1.cappa2[i3 + (j + k * 70) * 126 - 8947] + bb[3]
		     * llot95a_1.cappa2[i4 + (j + k * 70) * 126 - 8947];
	}
    }
    return 0;
} /* op95ztab_ */

