/* ll95tbl.f -- translated by f2c (version 20100827).
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
    char fliv95[256];
    integer iliv95;
} lopal95_;

#define lopal95_1 lopal95_

struct llot95a_1_ {
    doublereal tgr[70], xxg[10], r0gr[19], zzg[13], cappa2[167580]	/* 
	    was [126][70][19] */;
    integer numxm[13], nz[13];
};

#define llot95a_1 (*(struct llot95a_1_ *) &llot95a_)

struct op95indx_1_ {
    integer jz, jx[16]	/* was [4][4] */, jt, jd[4];
};

#define op95indx_1 (*(struct op95indx_1_ *) &op95indx_)

struct {
    doublereal zlaol1, zlaol2, zopal1, zopal2, zopal951, zopal952, zalex1, 
	    zalex2, zkur1, zkur2;
    logical llaol89, lopal92, lopal95, lkur90, lalex95, l2z;
} newopac_;

#define newopac_1 newopac_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* Initialized data */

struct {
    doublereal fill_1[70];
    doublereal e_2[10];
    doublereal fill_3[19];
    doublereal e_4[13];
    doublereal fill_5[167580];
    integer e_6[26];
    } llot95a_ = { {0}, 0., .1, .2, .35, .5, .7, .8, .9, .95, 1., {0}, 0., 
	    1e-4, 3e-4, .001, .002, .004, .01, .02, .03, .04, .06, .08, .1, {
	    0}, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 8, 0, 10, 20, 
	    30, 40, 50, 60, 70, 80, 90, 100, 109, 118 };

struct {
    integer e_1[22];
    } op95indx_ = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	    1, 1, 1 };


/* Table of constant values */

static integer c__1 = 1;
static integer c__9 = 9;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     LL95TBL */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int ll95tbl_(void)
{
    /* Format strings */
    static char fmt_1[] = "(a)";
    static char fmt_20[] = "(///,4x,19f7.1,/)";
    static char fmt_30[] = "(f4.2,19f7.3)";
    static char fmt_31[] = "(f4.2,18f7.3)";
    static char fmt_32[] = "(f4.2,17f7.3)";
    static char fmt_33[] = "(f4.2,16f7.3)";
    static char fmt_34[] = "(f4.2,15f7.3)";
    static char fmt_35[] = "(f4.2,14f7.3)";
    static char fmt_900[] = "(/36x,f7.4,11x,f7.4)";

    /* System generated locals */
    integer i__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_rsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rsfe(void), s_cmp(char *, char *, ftnlen, ftnlen), 
	    s_rsfi(icilist *), e_rsfi(void), s_wsle(cilist *), do_lio(integer 
	    *, integer *, char *, ftnlen), e_wsle(void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    integer f_clos(cllist *);

    /* Local variables */
    static integer i__, j, n;
    static doublereal z__;
    static integer nn, ix, iz;
    static doublereal xx, zz, xxt;
    static integer nfmt, nmax;
    static char dummy[132];
    extern /* Subroutine */ int op95ztab_(doublereal *);

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 0, 1, fmt_1, 0 };
    static icilist io___4 = { 0, dummy, 0, "(36X,F7.4,11X,F7.4)", 132, 1 };
    static cilist io___12 = { 0, 0, 0, 0, 0 };
    static cilist io___13 = { 0, 0, 1, fmt_20, 0 };
    static cilist io___15 = { 0, 0, 1, fmt_30, 0 };
    static cilist io___17 = { 0, 0, 1, fmt_31, 0 };
    static cilist io___18 = { 0, 0, 1, fmt_32, 0 };
    static cilist io___19 = { 0, 0, 1, fmt_33, 0 };
    static cilist io___20 = { 0, 0, 1, fmt_34, 0 };
    static cilist io___21 = { 0, 0, 1, fmt_35, 0 };
    static cilist io___23 = { 0, 0, 0, fmt_900, 0 };


/* MHP 7/98 MODIFIED TO READ IN ALL METAL ABUNDACES FOR OPACITY TABLES. */
/*  LOCAL VECTOR, USED TO SKIP LONG HEADER. */
/* FULL SET OF TABLES: OPACITY AS A FUNCTION OF Z AND X, T, RHO/T6**3 */
/* TABLES ARE INCREMENTED IN SETS OF NZ*NX.  SO THE TABLES FOR THE */
/* THIRD METAL ABUNDANCE (3 X 10**-4)BEGIN AT TABLE 21 AND END AT TABLE 30. */
/* FOR THE HIGH VALUES OF Z, THE NUMBER OF X TABLES IS NOT THE SAME (I.E. */
/* X<0.9 FOR Z=0.1). */
/* FOR EACH COMPOSITION A FULL GRID IN (T,RHO/T6**3) IS RETAINED. */
/* INDICES FOR INTERPOLATION IN Z,X,T, AND R */
/* NUMBER OF COMPOSITION TABLES AT LOWER Z FOR EACH ABUNDANCE */
/* NUMBER OF X TABLES AT EACH Z */
/* TABULTED SET OF X */
/* TABULATED SET OF Z */
/* INDICES FOR INTERPOLATION */
/*     READ IN OPACITY TABLES, SKIPPING HEADER.  HEY, IT WORKS. */
    o__1.oerr = 0;
    o__1.ounit = lopal95_1.iliv95;
    o__1.ofnmlen = 256;
    o__1.ofnm = lopal95_1.fliv95;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = "SEQUENTIAL";
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    nfmt = 1;
L10:
    io___2.ciunit = lopal95_1.iliv95;
    i__1 = s_rsfe(&io___2);
    if (i__1 != 0) {
	goto L9999;
    }
    i__1 = do_fio(&c__1, dummy, (ftnlen)132);
    if (i__1 != 0) {
	goto L9999;
    }
    i__1 = e_rsfe();
    if (i__1 != 0) {
	goto L9999;
    }
    if (s_cmp(dummy + (nfmt - 1), "TABLE", (ftnlen)5, (ftnlen)5) != 0) {
	goto L10;
    }
    s_rsfi(&io___4);
    do_fio(&c__1, (char *)&xx, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&zz, (ftnlen)sizeof(doublereal));
    e_rsfi();
    iz = 1;
    ix = 1;
    nn = 1;
/* ENTRY POINT FOR GETTING NEW TABLES. */
L15:
    n = llot95a_1.nz[iz - 1] + ix;
    if (ix < 10) {
	xxt = llot95a_1.xxg[ix - 1];
    } else {
	xxt = 1. - llot95a_1.zzg[iz - 1];
    }
    if (llot95a_1.zzg[iz - 1] != zz || xxt != xx) {
	io___12.ciunit = luout_1.ishort;
	s_wsle(&io___12);
	do_lio(&c__9, &c__1, " OPAL95: Z ERROR INCOMPATIBLE TABLE", (ftnlen)
		35);
	e_wsle();
	s_stop("", (ftnlen)0);
    }
/* READ IN HEADER INFO: GRID IN RHO/T6**3 */
    io___13.ciunit = lopal95_1.iliv95;
    i__1 = s_rsfe(&io___13);
    if (i__1 != 0) {
	goto L1000;
    }
    for (i__ = 1; i__ <= 19; ++i__) {
	i__1 = do_fio(&c__1, (char *)&llot95a_1.r0gr[i__ - 1], (ftnlen)sizeof(
		doublereal));
	if (i__1 != 0) {
	    goto L1000;
	}
    }
    i__1 = e_rsfe();
    if (i__1 != 0) {
	goto L1000;
    }
/* READ IN FULL TABLE: LOG CAPPA AS A FUNCTION OF LOG T AND */
/* LOG R = RHO/T6**3 */
    for (i__ = 1; i__ <= 57; ++i__) {
	io___15.ciunit = lopal95_1.iliv95;
	i__1 = s_rsfe(&io___15);
	if (i__1 != 0) {
	    goto L9999;
	}
	i__1 = do_fio(&c__1, (char *)&llot95a_1.tgr[i__ - 1], (ftnlen)sizeof(
		doublereal));
	if (i__1 != 0) {
	    goto L9999;
	}
	for (j = 1; j <= 19; ++j) {
	    i__1 = do_fio(&c__1, (char *)&llot95a_1.cappa2[n + (i__ + j * 70) 
		    * 126 - 8947], (ftnlen)sizeof(doublereal));
	    if (i__1 != 0) {
		goto L9999;
	    }
	}
	i__1 = e_rsfe();
	if (i__1 != 0) {
	    goto L9999;
	}
    }
/* MHP 12/97 NOW TREAT CORNER WITHOUT DATA. */
    io___17.ciunit = lopal95_1.iliv95;
    i__1 = s_rsfe(&io___17);
    if (i__1 != 0) {
	goto L9999;
    }
    i__1 = do_fio(&c__1, (char *)&llot95a_1.tgr[57], (ftnlen)sizeof(
	    doublereal));
    if (i__1 != 0) {
	goto L9999;
    }
    for (j = 1; j <= 18; ++j) {
	i__1 = do_fio(&c__1, (char *)&llot95a_1.cappa2[n + (j * 70 + 58) * 
		126 - 8947], (ftnlen)sizeof(doublereal));
	if (i__1 != 0) {
	    goto L9999;
	}
    }
    i__1 = e_rsfe();
    if (i__1 != 0) {
	goto L9999;
    }
    llot95a_1.cappa2[n + 165941] = 9.999;
    for (i__ = 59; i__ <= 60; ++i__) {
	io___18.ciunit = lopal95_1.iliv95;
	i__1 = s_rsfe(&io___18);
	if (i__1 != 0) {
	    goto L9999;
	}
	i__1 = do_fio(&c__1, (char *)&llot95a_1.tgr[i__ - 1], (ftnlen)sizeof(
		doublereal));
	if (i__1 != 0) {
	    goto L9999;
	}
	for (j = 1; j <= 17; ++j) {
	    i__1 = do_fio(&c__1, (char *)&llot95a_1.cappa2[n + (i__ + j * 70) 
		    * 126 - 8947], (ftnlen)sizeof(doublereal));
	    if (i__1 != 0) {
		goto L9999;
	    }
	}
	i__1 = e_rsfe();
	if (i__1 != 0) {
	    goto L9999;
	}
	for (j = 18; j <= 19; ++j) {
	    llot95a_1.cappa2[n + (i__ + j * 70) * 126 - 8947] = 9.999;
	}
    }
    for (i__ = 61; i__ <= 64; ++i__) {
	io___19.ciunit = lopal95_1.iliv95;
	i__1 = s_rsfe(&io___19);
	if (i__1 != 0) {
	    goto L9999;
	}
	i__1 = do_fio(&c__1, (char *)&llot95a_1.tgr[i__ - 1], (ftnlen)sizeof(
		doublereal));
	if (i__1 != 0) {
	    goto L9999;
	}
	for (j = 1; j <= 16; ++j) {
	    i__1 = do_fio(&c__1, (char *)&llot95a_1.cappa2[n + (i__ + j * 70) 
		    * 126 - 8947], (ftnlen)sizeof(doublereal));
	    if (i__1 != 0) {
		goto L9999;
	    }
	}
	i__1 = e_rsfe();
	if (i__1 != 0) {
	    goto L9999;
	}
	for (j = 17; j <= 19; ++j) {
	    llot95a_1.cappa2[n + (i__ + j * 70) * 126 - 8947] = 9.999;
	}
    }
    for (i__ = 65; i__ <= 69; ++i__) {
	io___20.ciunit = lopal95_1.iliv95;
	i__1 = s_rsfe(&io___20);
	if (i__1 != 0) {
	    goto L9999;
	}
	i__1 = do_fio(&c__1, (char *)&llot95a_1.tgr[i__ - 1], (ftnlen)sizeof(
		doublereal));
	if (i__1 != 0) {
	    goto L9999;
	}
	for (j = 1; j <= 15; ++j) {
	    i__1 = do_fio(&c__1, (char *)&llot95a_1.cappa2[n + (i__ + j * 70) 
		    * 126 - 8947], (ftnlen)sizeof(doublereal));
	    if (i__1 != 0) {
		goto L9999;
	    }
	}
	i__1 = e_rsfe();
	if (i__1 != 0) {
	    goto L9999;
	}
	for (j = 16; j <= 19; ++j) {
	    llot95a_1.cappa2[n + (i__ + j * 70) * 126 - 8947] = 9.999;
	}
    }
    i__ = 70;
    io___21.ciunit = lopal95_1.iliv95;
    i__1 = s_rsfe(&io___21);
    if (i__1 != 0) {
	goto L9999;
    }
    i__1 = do_fio(&c__1, (char *)&llot95a_1.tgr[i__ - 1], (ftnlen)sizeof(
	    doublereal));
    if (i__1 != 0) {
	goto L9999;
    }
    for (j = 1; j <= 14; ++j) {
	i__1 = do_fio(&c__1, (char *)&llot95a_1.cappa2[n + (i__ + j * 70) * 
		126 - 8947], (ftnlen)sizeof(doublereal));
	if (i__1 != 0) {
	    goto L9999;
	}
    }
    i__1 = e_rsfe();
    if (i__1 != 0) {
	goto L9999;
    }
    for (j = 15; j <= 19; ++j) {
	llot95a_1.cappa2[n + (i__ + j * 70) * 126 - 8947] = 9.999;
    }
/* EXIT IF CORRECT NUMBER OF TABLES READ IN. */
    if (nn >= 126) {
	goto L1000;
    }
    ++nn;
/* NEED TO ACCOUNT FOR FEWER X VALUES AT HIGHER Z. */
    if (ix <= 8) {
	nmax = 13;
    } else if (ix == 9) {
	nmax = 10;
    } else {
	nmax = 12;
    }
/* READ IN NEXT METAL ABUNDANCE (AT FIXED X) OR READ IN FIRST METAL */
/* ABUNDANCE AT NEXT X. */
    if (iz < nmax) {
	++iz;
    } else {
	iz = 1;
	++ix;
    }
/* RETURN TO READ IN NEXT TABLE. */
    io___23.ciunit = lopal95_1.iliv95;
    s_rsfe(&io___23);
    do_fio(&c__1, (char *)&xx, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&zz, (ftnlen)sizeof(doublereal));
    e_rsfe();
    goto L15;
L1000:
    cl__1.cerr = 0;
    cl__1.cunit = lopal95_1.iliv95;
    cl__1.csta = 0;
    f_clos(&cl__1);
/*  NOW GENERATE A TABLE AT A FIXED VALUE OF Z. */
/*  NOTE THAT FOR METAL DIFFUSION A 4-D INTERPOLATION (IN X,Z,T,RHO) */
/*  IS PERFORMED RATHER THAN A LINEAR INTERPOLATION BETWEEN TWO FIXED */
/*  Z TABLES. */
    z__ = newopac_1.zopal951;
    op95ztab_(&z__);
L9999:
    return 0;
} /* ll95tbl_ */

