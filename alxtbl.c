/* alxtbl.f -- translated by f2c (version 20100827).
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
    char opecalex[1792];
    integer ialxo;
} alexo_;

#define alexo_1 alexo_

struct {
    doublereal zlaol1, zlaol2, zopal1, zopal2, zopal951, zalex1, zkur1, zkur2,
	     tmolmin, tmolmax;
    logical lalex06, llaol89, lopal92, lopal95, lkur90, lalex95, l2z;
} newopac_;

#define newopac_1 newopac_

struct galot_1_ {
    doublereal tgr[23], xxg[7], r0gr[17], zzg[15];
};

#define galot_1 (*(struct galot_1_ *) &galot_)

struct alot_1_ {
    doublereal capalex[3128]	/* was [8][23][17] */, xe, ze;
    integer ix, it, id;
};

#define alot_1 (*(struct alot_1_ *) &alot_)

struct {
    doublereal captalex[41055]	/* was [105][23][17] */;
} alotall_;

#define alotall_1 alotall_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* Initialized data */

struct {
    doublereal e_1[62];
    } galot_ = { 3., 3.05, 3.1, 3.15, 3.2, 3.25, 3.3, 3.35, 3.4, 3.45, 3.5, 
	    3.55, 3.6, 3.65, 3.7, 3.75, 3.8, 3.85, 3.9, 3.95, 4., 4.05, 4.1, 
	    0., .1, .2, .35, .5, .7, .8, -7., -6.5, -6., -5.5, -5., -4.5, -4.,
	     -3.5, -3., -2.5, -2., -1.5, -1., -.5, 0., .5, 1., 0., 1e-5, 3e-5,
	     1e-4, 3e-4, .001, .002, .004, .01, .02, .03, .04, .06, .08, .1 };

struct {
    doublereal fill_1[3128];
    doublereal e_2[2];
    integer e_3[3];
    } alot_ = { {0}, 0., 0., 4, 12, 9 };


/* Table of constant values */

static integer c__1 = 1;

/* MHP 4/98  SUBROUTINE FOR READING IN ALEXANDER LOW T OPACITIES. */

/* ALEXANDER OPACITIES   APJ,437,879,1994 */
/* IN EACH 7 FILE FOR X = 0.0, 0.1, 0.2, 0.35, 0.5, 0.7, 0.8 */
/* DESCENDING ORDER OF Z = 0.0, 0.00001, 0.00003, 0.0001, 0.0003, */
/*     (15)               0.001, 0.002, 0.004, 0.01, 0.02, 0.03, */
/*                        0.04, 0.06, 0.08, 0.10 */
/* DESCENDING ORDER OF LOGT  4.10 4.05 4.00 3.95 3.90 3.85 3.80 3.75 */
/*     (23)                 3.70 3.65 3.60 3.55 3.50 3.45 3.40 3.35 */
/*                          3.30 3.25 3.20 3.15 3.10 3.05 3.00 */
/* ASCENDING ORDER OF  LOGR -7.0 -6.5 -6.0 -5.5 -5.0 -4.5 -4.0 -3.5 */
/*     (17)                -3.0 -2.5 -2.0 -1.5 -1.0 -0.5  0.0  0.5  1.0 */
/* WHERE R = RHO/T_6**3 */
/* READ IN ALL Z VALUES AT FIXED X AND GENERATE OPACITY ENTRIES AT */
/* EITHER ONE OR TWO FIXED VALUES OF Z.  THEN GENERATE SURFACE X TABLE */
/* IF MODEL HAS NO DIFFUSION.  INTERPOLATION BETWEEN COMPOSITIONS IS */
/* 4-POINT LAGRANGIAN. */

/* Subroutine */ int alxtbl_(void)
{
    /* Format strings */
    static char fmt_10[] = "(18x,f6.2,2x,f7.2)";
    static char fmt_20[] = "(1x,\002ERROR IN ALEXANDER OPACITY TABLES:\002/1"
	    "x,\002EXPECTED AND ACTUAL X,Z\002,4f7.2,\002 RUN STOPPED\002)";
    static char fmt_30[] = "(i2,i3,f6.3,f5.1,8f8.3/9f8.3)";
    static char fmt_40[] = "(1x,\002ERROR IN ALEXANDER OPACITY TABLES:\002/1"
	    "x,\002EXPECTED AND ACTUAL T,RHO\002,i3,4f7.2,\002 RUN STOPPED"
	    "\002)";

    /* System generated locals */
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_rsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rsfe(void), s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    integer f_clos(cllist *);

    /* Local variables */
    static integer i__, j, k;
    static doublereal t, r0;
    static integer ii, nd;
    static doublereal xx, zz;
    static integer iop;
    static doublereal captmp[17];
    extern /* Subroutine */ int alxztab_(doublereal *);

    /* Fortran I/O blocks */
    static cilist io___4 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_20, 0 };
    static cilist io___9 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___15 = { 0, 0, 0, fmt_40, 0 };


/* OPACITY COMMON BLOCKS - modified 3/09 */
/*     ALEX LOW T OPACITY */
/* MHP 10/02 ISHORT UNDECLARED */
/*     LOCAL ARRAYS */
/* INITIALIZE INDEX OF PREVIOUS CLOSEST POINTS AND ENVELOPE ABUNDANCES */
    for (iop = 1; iop <= 7; ++iop) {
/* OPEN EACH OF THE TABLES AT FIXED X WITH A RANGE OF Z. */
	o__1.oerr = 0;
	o__1.ounit = alexo_1.ialxo;
	o__1.ofnmlen = 256;
	o__1.ofnm = alexo_1.opecalex + (iop - 1 << 8);
	o__1.orl = 0;
	o__1.osta = "OLD";
	o__1.oacc = 0;
	o__1.ofm = "FORMATTED";
	o__1.oblnk = 0;
	f_open(&o__1);
/* READ IN INITIAL X AND Z; ENSURE THAT THEY HAVE THE EXPECTED VALUES. */
	for (i__ = 15; i__ >= 1; --i__) {
/* INDEX FOR STORING TABLES : 15 SETS OF METAL ABUNDANCE WITH 7 SETS */
/* OF HYDROGEN FOR EACH.  THESE ARE STORED IN THE ORDER (X,Z) OF */
/* (0,0),(0.1,0),...(0.8,0),(0,0.00001),... */
	    ii = iop + (i__ - 1) * 7;
/* HEADER INFORMATION: X AND Z */
	    io___4.ciunit = alexo_1.ialxo;
	    s_rsfe(&io___4);
	    do_fio(&c__1, (char *)&xx, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&zz, (ftnlen)sizeof(doublereal));
	    e_rsfe();
	    if (xx != galot_1.xxg[iop - 1] || zz != galot_1.zzg[i__ - 1]) {
		io___7.ciunit = luout_1.ishort;
		s_wsfe(&io___7);
		do_fio(&c__1, (char *)&xx, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&galot_1.xxg[iop - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&zz, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&galot_1.zzg[i__ - 1], (ftnlen)sizeof(
			doublereal));
		e_wsfe();
		s_stop("", (ftnlen)0);
	    }
/* OPACITY INFORMATION AT EACH SHELL: CHECK FOR CONSISTENCY WITH T, */
/* STARTING R.  STORE IN A NUMZ*NUMT*NUMR ARRAY. */
	    for (j = 23; j >= 1; --j) {
		io___9.ciunit = alexo_1.ialxo;
		s_rsfe(&io___9);
		do_fio(&c__1, (char *)&alot_1.it, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&nd, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&t, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&r0, (ftnlen)sizeof(doublereal));
		for (k = 1; k <= 17; ++k) {
		    do_fio(&c__1, (char *)&captmp[k - 1], (ftnlen)sizeof(
			    doublereal));
		}
		e_rsfe();
		for (k = 1; k <= 17; ++k) {
		    alotall_1.captalex[ii + (j + k * 23) * 105 - 2521] = 
			    captmp[k - 1];
		}
		if (nd != 17 || t != galot_1.tgr[j - 1] || r0 != galot_1.r0gr[
			0]) {
		    io___15.ciunit = luout_1.ishort;
		    s_wsfe(&io___15);
		    do_fio(&c__1, (char *)&nd, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&t, (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&galot_1.tgr[j - 1], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&r0, (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&galot_1.r0gr[0], (ftnlen)sizeof(
			    doublereal));
		    e_wsfe();
		    s_stop("", (ftnlen)0);
		}
	    }
	}
	cl__1.cerr = 0;
	cl__1.cunit = alexo_1.ialxo;
	cl__1.csta = 0;
	f_clos(&cl__1);
    }
    zz = newopac_1.zalex1;
    alxztab_(&zz);
    return 0;
} /* alxtbl_ */

