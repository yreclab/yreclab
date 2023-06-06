/* setupopac.f -- translated by f2c (version 20100827).
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
    doublereal zlaol1, zlaol2, zopal1, zopal2, zopal951, zalex1, zkur1, zkur2,
	     tmolmin, tmolmax;
    logical lalex06, llaol89, lopal92, lopal95, lkur90, lalex95, l2z;
} newopac_;

#define newopac_1 newopac_

struct {
    doublereal rsclzc[50], rsclzm1[50], rsclzm2[50];
    integer iolaol2, ioopal2, nk;
    logical lzramp;
    char flaol2[256], fopal2[256];
} zramp_;

#define zramp_1 zramp_

struct {
    doublereal fgry, fgrz;
    logical lthoul, ldifz;
} gravs3_;

#define gravs3_1 gravs3_

struct {
    doublereal olaol[64896]	/* was [12][104][52] */, oxa[12], ot[52], 
	    orho[104], tollaol;
    integer iolaol, numofxyz, numrho, numt;
    logical llaol, lpurez;
    integer iopurez;
    char flaol[256], fpurez[256];
} nwlaol_;

#define nwlaol_1 nwlaol_



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     SETUPOPAC */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int setupopac_(doublereal *xenv, doublereal *v)
{
    extern /* Subroutine */ int readalex06_(void), ll4th_(doublereal *), 
	    alx8th_(doublereal *), rdlaol_(doublereal *), alxtbl_(void), 
	    ll95tbl_(void), sulaol_(void), setllo_(void), setkrz_(void), 
	    rdzlaol_(void), op95xtab_(doublereal *), zsulaol_(void);

/* OPACITY COMMON BLOCKS - modified 3/09 */

/*     THIS SUBROUTINE READS IN SPECIFIED OPACITY TABLES AND */
/*     SET UP SPLINES FOR THE TABLES. */
/*     WHEN LZRAMP=T OR LDIFZ=T THEN READ IN SECOND SET OF */
/*     OPACITY TABLES AT DIFFERENT Z (E.G. ZOPAL952). */
    /* Parameter adjustments */
    --v;

    /* Function Body */
    newopac_1.l2z = zramp_1.lzramp || gravs3_1.ldifz;

/*     INTERIOR TABLES */

/*     READ IN OPAL95 TABLES */
    if (newopac_1.lopal95) {
	ll95tbl_();
	op95xtab_(xenv);
    }
/*     READ IN OPAL92 TABLES AT ZOPAL1 AND ZOPAL2 */
    if (newopac_1.lopal92) {
	setllo_();
	ll4th_(xenv);
    }
/*     READ IN LAOL89 TABLES AT ZLAOL1 AND ZLAOL2 */
    if (newopac_1.llaol89) {
	rdlaol_(&v[1]);
	sulaol_();
    }

/*     READ IN LAOL89 PURE Z TABLE */

    if (nwlaol_1.lpurez) {
	rdzlaol_();
	zsulaol_();
    }

/*     LOW TEMP TABLES */

/*     READ IN ALEX 2006 TABLES */
    if (newopac_1.lalex06) {
	readalex06_();
/*     READ IN ALEX 1995 TABLES */
    } else if (newopac_1.lalex95) {
	alxtbl_();
	alx8th_(xenv);
/*     READ IN KURUCZ TABLE AT ZKUR1 AND ZKUR2 */
    } else if (newopac_1.lkur90) {
	setkrz_();
    }
    return 0;
} /* setupopac_ */

