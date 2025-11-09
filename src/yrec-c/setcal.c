/* setcal.f -- translated by f2c (version 20061008).
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
    doublereal toll, tolr, tolz;
    logical lcals, lcalsolzx;
    doublereal calsolzx, calsolage;
} cals2_;

#define cals2_1 cals2_

struct {
    doublereal rescal[200]	/* was [4][50] */;
    integer nmodls[50], iresca[50];
    logical lfirst[50];
    integer numrun;
} ckind_;

#define ckind_1 ckind_

struct {
    doublereal endage[50], setdt[50];
    logical lendag[50], lsetdt[50];
    doublereal end_dcen__[50], end_xcen__[50], end_ycen__[50];
} sett_;

#define sett_1 sett_

struct {
    doublereal xenv0a[50], zenv0a[50], cmixla[50];
    logical lsenv0a[50];
    doublereal senv0a[50];
} newxym_;

#define newxym_1 newxym_

struct {
    doublereal dldx, drdx, dlda, drda, blp, rlp, dx, da;
    logical lsol;
} calsun_;

#define calsun_1 calsun_

struct {
    doublereal rsclzc[50], rsclzm1[50], rsclzm2[50];
    integer iolaol2, ioopal2, nk;
    logical lzramp;
} zramp_;

#define zramp_1 zramp_

/* $$$$$$ */
/* Subroutine */ int setcal_(doublereal *facage)
{
    static integer i__, j;

/*      CHARACTER*256 FLAOL2, FOPAL2 */
/* MHP 6/13 ADD OPTION TO CALIBRATE SOLAR Z/X, SOLAR Z/X, SOLAR AGE */
/* MHP 10/24 ADDED STOP CRITERIA FOR CENTRAL H,D,AND HE4 */
/*      COMMON/SETT/ENDAGE(50),SETDT(50),LENDAG(50),LSETDT(50) */
/* MHP 8/25 Removed character file names from common block */
/* SET UP RUN TO CALIBRATE A SOLAR MODEL. */
/* THIS CONSISTS OF SETTING THE NUMBER OF RUNS TO THE MAXIMUM (50), */
/* AND COPYING THE RELEVANT PARAMETERS FROM THE FIRST TWO RUNS TO */
/* THE NEXT SERIES OF 24 CALIBRATING RUNS. */
/* mhp 5/96 changed to do solar models in 3 runs rather than 2. */
    ckind_1.numrun = 48;
    for (i__ = 2; i__ <= 48; ++i__) {
	newxym_1.xenv0a[i__ - 1] = newxym_1.xenv0a[0];
	newxym_1.zenv0a[i__ - 1] = newxym_1.zenv0a[0];
	newxym_1.cmixla[i__ - 1] = newxym_1.cmixla[0];
	newxym_1.lsenv0a[i__ - 1] = newxym_1.lsenv0a[0];
	newxym_1.senv0a[i__ - 1] = newxym_1.senv0a[0];
    }
    for (i__ = 4; i__ <= 46; i__ += 3) {
	ckind_1.iresca[i__ - 1] = ckind_1.iresca[0];
	ckind_1.lfirst[i__ - 1] = TRUE_;
	ckind_1.nmodls[i__ - 1] = ckind_1.nmodls[0];
	zramp_1.rsclzc[i__ - 1] = zramp_1.rsclzc[0];
	zramp_1.rsclzm1[i__ - 1] = zramp_1.rsclzm1[0];
	zramp_1.rsclzm2[i__ - 1] = zramp_1.rsclzm2[0];
	for (j = 1; j <= 4; ++j) {
	    ckind_1.rescal[j + (i__ << 2) - 5] = ckind_1.rescal[j - 1];
	}
    }
/* MHP 06/13 HARDWIRE RUN 2 TO 1D8 YEARS AND RUN3 TO CALSOLAGE YEARS */
    sett_1.endage[1] = *facage * 1e8;
/*      ENDAGE(2) = ENDAGE(2)*FACAGE */
    sett_1.setdt[1] *= *facage;
    sett_1.endage[2] = cals2_1.calsolage * *facage;
/*      ENDAGE(3) = ENDAGE(3)*FACAGE */
    sett_1.setdt[2] *= *facage;
    for (i__ = 5; i__ <= 47; i__ += 3) {
	ckind_1.iresca[i__ - 1] = 1;
	ckind_1.lfirst[i__ - 1] = FALSE_;
	ckind_1.nmodls[i__ - 1] = ckind_1.nmodls[1];
	sett_1.endage[i__ - 1] = sett_1.endage[1];
	sett_1.lendag[i__ - 1] = sett_1.lendag[1];
	sett_1.setdt[i__ - 1] = sett_1.setdt[1];
	sett_1.lsetdt[i__ - 1] = sett_1.lsetdt[1];
    }
    for (i__ = 6; i__ <= 48; i__ += 3) {
	ckind_1.iresca[i__ - 1] = 1;
	ckind_1.lfirst[i__ - 1] = FALSE_;
	ckind_1.nmodls[i__ - 1] = ckind_1.nmodls[2];
	sett_1.endage[i__ - 1] = sett_1.endage[2];
	sett_1.lendag[i__ - 1] = sett_1.lendag[2];
	sett_1.setdt[i__ - 1] = sett_1.setdt[2];
	sett_1.lsetdt[i__ - 1] = sett_1.lsetdt[2];
    }
    calsun_1.lsol = FALSE_;
    return 0;
} /* setcal_ */

