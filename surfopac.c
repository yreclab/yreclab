/* surfopac.f -- translated by f2c (version 20100827).
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



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     SURFOPAC */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int surfopac_(doublereal *xenv)
{
    extern /* Subroutine */ int ll4th_(doublereal *), alx8th_(doublereal *), 
	    op95xtab_(doublereal *);

/* OPACITY COMMON BLOCKS - modified 3/09 */
/*     THIS SUBROUTINE SETS UP SURF OPACITY TABLES */
/*     ASSUMES TABLES HAVE ALREADY BEEN READ IN */
/*     INTERIOR TABLES */
/*     SETUP OPAL95 TABLES */
    if (newopac_1.lopal95) {
	op95xtab_(xenv);
    }
/*     SETUP IN OPAL92 TABLES AT ZOPAL1 AND ZOPAL2 */
    if (newopac_1.lopal92) {
	ll4th_(xenv);
    }
/*     LOW TEMP TABLES */
/*     INTERPOLATE ALEX95 TABLES */
    if (newopac_1.lalex95) {
	alx8th_(xenv);
    }
    return 0;
} /* surfopac_ */

